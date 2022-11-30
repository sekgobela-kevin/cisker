#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <util.h>
#include <pattern.h>


char *commonLeadingSubString(char *first, char *second){
    size_t first_size = strlen(first);
    size_t second_size = strlen(second);
    size_t min_size = first_size<second_size? first_size:second_size;
    char *common = malloc(sizeof(char)*(min_size+1));
    size_t i;
    for (i=0; i < first_size; i++)
    {
        if(first[i] == second[i]){
            common[i] = first[i];
        }else{
            break;
        }
    }
    // Remeber that 'i' is incremented by for loop.
    // It points to index of null character.
    common[i] = '\0';
    char *mm = shrinkMem(common, sizeof(char)*(i+1));
    return mm;
}

char *remainingSubString(char *str, char *leading){
    char *first_pointer = strstr(str, leading);
    size_t str_size = strlen(str);
    size_t leading_size = strlen(leading);
    int start_index;
    if(first_pointer==str){
        start_index = leading_size;
    }else{
        start_index = str_size;
    }
    return sliceStr(str, start_index, str_size);
}


char *occurrenceRangePattern(int start, int end, char *dpattern){
    size_t size = intSize(end) + strlen(dpattern);
    char *pattern = malloc(sizeof(char)*(size+1));
    char *start_str = intStr(start);
    char *end_str = intStr(end);
    pattern[0] = '\0';
    if(start==end){
        if(start==1){
            strcat(pattern, dpattern);
        }else if(start!=0){
            strcat(pattern, dpattern);
            strcat(pattern, "{");
            strcat(pattern, start_str);
            strcat(pattern, "}");
        }
    }else{
        strcat(pattern, dpattern);
        strcat(pattern, "{");
        strcat(pattern, start_str);
        strcat(pattern, ",");
        strcat(pattern, end_str);
        strcat(pattern, "}");
    }
    free(start_str);
    free(end_str);
    return pattern;
}

char *charRangePattern(char first, char second){
    char *pattern = malloc(sizeof(char)*6);
    char first_str[2] = {first, '\0'};
    char second_str[2] = {second, '\0'};
    pattern[0] = '\0';
    if(first == second){
        strcat(pattern, first_str);
    }else{
        strcat(pattern, "[");
        strcat(pattern, first_str);
        strcat(pattern, "-");
        strcat(pattern, second_str);
        strcat(pattern, "]");
    }
    return pattern;
}

char *strIntRangePattern(char* start, char *end, char *dpattern){
    // Pattern for leading and remaining part need to be created.
    // That would require leading and remaining sub-strings.
    char *common_leading = commonLeadingSubString(start, end);
    char *start_remaining = remainingSubString(start, common_leading);
    char *end_remaining = remainingSubString(end, common_leading);
    // size for remaining parts is required to create pattern.
    size_t start_remaining_size = strlen(start_remaining);
    size_t end_remaining_size = strlen(end_remaining);
    size_t min_remaining_size;
    size_t max_remaining_size;
    // Maximum size for remaining parts is also important.
    if(start_remaining_size > end_remaining_size){
        min_remaining_size = end_remaining_size;
        max_remaining_size = start_remaining_size;
    }else{
        min_remaining_size = start_remaining_size;
        max_remaining_size = end_remaining_size;
    }
    // This is enough to hold characters for pattern.
    // dpattern is expected to be used once within pattern.
    // +10 for other characters that may be used in pattern.
    size_t pattern_size = max_remaining_size+strlen(dpattern)+10;
    // Common leading part is shared, it can be used as pattern.
    char *pattern = calloc(sizeof(char), pattern_size);
    strcpy(pattern, common_leading);

    // pattern for remaining part is created here.
    if(start_remaining_size && end_remaining_size){
        if(start_remaining_size==end_remaining_size){
            // Range for first digit can created without problems.
            // This is possible since leading part does not change.
            char * first_digit_pattern = charRangePattern(
                start_remaining[0], end_remaining[0]
            );
            strcat(pattern, first_digit_pattern);
            // Minus by one to exclude first digit(avoid duplicate).
            // first_digit_pattern was just added and should be added again.
            min_remaining_size -= 1;
            max_remaining_size -= 1;
            free(first_digit_pattern);
        }
    }
    // Creates pattern for remaining digits.
    // occurrenceRangePattern() does not require negative numbers.
    // First digit pattern may have already been added to pattern.
    if(min_remaining_size>=0){
        char * remaining_digits_patten = occurrenceRangePattern(
            min_remaining_size, max_remaining_size, dpattern
        );
        strcat(pattern, remaining_digits_patten);
        free(remaining_digits_patten);
    }
    free(start_remaining);
    free(end_remaining);
    free(common_leading);
    // Frees memory not used by pattern string.
    return shrinkStr(pattern);
}

char *intRangePattern(int start, int end, char *dpattern){
    char *start_str = intStr(start);
    char *end_str = intStr(end);
    char *pattern = strIntRangePattern(start_str, end_str, dpattern);
    free(start_str);
    free(end_str);
    return pattern;
}

char *yearPartPattern(SNumsInfo students_info){
    year_t start_year = students_info.start_year;
    year_t end_year = students_info.end_year;
    if(students_info.strict){
        part_t start_year_part = toYearPart(start_year, students_info);
        part_t end_year_part = toYearPart(end_year, students_info);
        int start_year_part_int = strInt(start_year_part);
        int end_year_part_int = strInt(end_year_part);
        size_t start_year_part_size = strlen(start_year_part);
        size_t end_year_part_size = strlen(end_year_part);
        char *start_year_pattern = NULL;
        char *end_year_pattern = NULL;
        char *pattern = NULL;
        if(start_year_part_size==2 && end_year_part_size!=2){
            // 99 -> year 1999 & 2000 -> year 2000
            start_year_pattern = strIntRangePattern(
                start_year_part, "99", "\\d");
            end_year_pattern = intRangePattern(
                2000, end_year_part_int, "\\d");
        }else if(start_year_part_size!=2 && end_year_part_size==2){
            // 1899 -> year 1899 & 00 -> year 1900
            start_year_pattern = intRangePattern(
                start_year_part_int, 1899, "\\d");
            end_year_pattern = strIntRangePattern(
                "00", end_year_part, "\\d");
        }else{
            pattern = intRangePattern(start_year_part_int,
                                      end_year_part_int, "\\d");
        }
        if(start_year_pattern!=NULL && end_year_pattern!=NULL){
            pattern = malloc(strlen(start_year_pattern) +
                             strlen(end_year_pattern) + 5 + 1);
            sprintf(pattern, "(%s)|(%s)", start_year_pattern,
                    end_year_pattern);
            free(start_year_pattern);
            free(end_year_pattern);
        }
        return pattern;
    }
    return intRangePattern(start_year, end_year, "\\d");
}

char *posPartPattern(SNumsInfo students_info){
    int year_capacity = students_info.year_capacity;
    int start_pos = students_info.start_pos;
    int end_pos = students_info.end_pos;
    if(start_pos<0){
        start_pos = students_info.min_pos;
    }
    if(end_pos<0){
        end_pos = calMaxPos(students_info.min_pos, year_capacity);
    }
    size_t pos_part_size = posPartSize(students_info.min_pos,
                                       year_capacity);
    char *start_pos_str = intStr(start_pos);
    char *end_pos_str = intStr(end_pos);
    //Start and end pos are zero filled.
    char *start_pos_str_fill = fillStr(start_pos_str, '0', pos_part_size);
    char *end_pos_str_fill = fillStr(end_pos_str, '0', pos_part_size);
    // Pattern is created from those zero filled positions.
    char *pattern = strIntRangePattern(
        start_pos_str_fill, end_pos_str_fill, "\\d");
    free(start_pos_str);
    free(end_pos_str);
    free(start_pos_str_fill);
    free(end_pos_str_fill);
    return pattern;
}

char *studentNumbersPattern(SNumsInfo students_info){
    char *year_part_pattern = yearPartPattern(students_info);
    char *pos_part_pattern = posPartPattern(students_info);
    char *pattern = malloc(strlen(year_part_pattern) +
                        strlen(pos_part_pattern) + 5 + 1);
    sprintf(pattern, "(%s)(%s)", year_part_pattern, pos_part_pattern);
    free(year_part_pattern);
    free(pos_part_pattern);
    return pattern;
}
