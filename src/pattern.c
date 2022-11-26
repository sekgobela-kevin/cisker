#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <util.h>
#include <pattern.h>


char *commonLeadingSubString(char *first, char *second){
    size_t first_size = strlen(first);
    size_t second_size = strlen(second);
    size_t min_size = first_size<second_size? first_size:second_size;
    char *common = malloc(sizeof(char)*(min_size+1));
    for (size_t i = 0; i < first_size; i++)
    {
        if(first[i] == second[i]){
            common[i] = first[i];
        }else{
            break;
        }
    }
    common[min_size] = '\0';
    realloc(common, sizeof(char)*(strlen(common)+1));
    return common;
}

char *remainingSubString(char *str, char *leading){
    char *first_pointer = strstr(str, leading);
    int start_index;
    if(first_pointer==str){
        start_index = 0;
    }else{
        start_index = strlen(leading);
    }
    return sliceStr(str, start_index, strlen(str));
}


char *occurrenceRangePattern(int start, int end, char *dpattern){
    size_t size = intSize(end) + strlen(dpattern);
    char *pattern = malloc(sizeof(char)*(size+1));
    char *start_str = intStr(start);
    char *end_str = intStr(end);
    pattern[0] = '\0';
    if(start==end){
        if(start!=0){
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
    realloc(pattern, sizeof(char)*(strlen(pattern)+1));
    free(start_str);
    free(end_str);
    return pattern;
}

char *charRangePattern(char first, char second){
    char *pattern = malloc(sizeof(char)*(5));
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
    realloc(pattern, sizeof(char)*(strlen(pattern)+1));
    return pattern;
}

char *intRangePattern(int start, int end, char *dpattern){
    char *start_str = intStr(start);
    char *end_str = intStr(end);
    // Pattern for leading and remaining part need to be created.
    // That would require leading and remaining sub-strings.
    char *common_leading = commonLeadingSubString(start_str, end_str);
    char *start_remaining = remainingSubString(start_str, common_leading);
    char *end_remaining = remainingSubString(end_str, common_leading);
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
    // Common leading part is shared, it can be used as pattern.
    // Pattern pointer is pointed to leading part string.
    char *pattern = common_leading;
    // strlen(end_str)*strlen(dpattern)) is enough to hold pattern.
    // Some of extra memory may be unused.
    realloc(pattern, sizeof(char)*(strlen(end_str)*strlen(dpattern)));

    // pattern for remaining part is created here.
    int total_remaining_digits = max_remaining_size;
    if(start_remaining_size && end_remaining_size){
        // Range for first digit can created without problems.
        // This is possible since leading part does not change.
        char * first_digit_pattern = charRangePattern(
            start_remaining[0], end_remaining[0]
        );
        strcat(pattern, first_digit_pattern);
        // Minus by one to exclude first digit(avoid duplicate).
        // first_digit_pattern was just added and should be added again.
        total_remaining_digits -= 1;
        free(first_digit_pattern);
    }
    // Creates pattern for remaining digits.
    // total_remaining_digits-1 needs to be >= min_remaining_size as
    // required by occurrenceRangePattern().
    // First digit pattern may have alsready have been added to pattern.
    if(max_remaining_size>min_remaining_size){
        char * remaining_digits_patten = occurrenceRangePattern(
            min_remaining_size, total_remaining_digits, dpattern
        );
        strcat(pattern, remaining_digits_patten);
        free(remaining_digits_patten);
    }
    free(start_remaining);
    free(end_remaining);
    // common_leading shouldnt be freed as pattern points to it.
    // Frees memory not used by pattern string.
    realloc(pattern, sizeof(char)*(strlen(pattern)+1));
    return pattern;
}
