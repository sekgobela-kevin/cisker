#include <analyse.h>
#include <util.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


SNumsInfo createSNumsInfo(){
    SNumsInfo students_info;
    //students_info.min_year = MIN_YEAR;
    students_info.start_year = START_YEAR;
    students_info.end_year = presentYear() + 1;
    students_info.min_pos = MIN_POS;
    //students_info.max_pos = MAX_POS;
    students_info.year_capacity = YEAR_CAPACITY;
    students_info.start_pos = -1;
    students_info.end_pos = -1;
    students_info.strict = STRICT;
    return students_info;
}

capacity_t calYearCapacity(pos_t min_pos, pos_t max_pos){
    // Calculates year capacity from year start and last position
    // max_pos = (year_capacity + min_pos) - 1
    // year_capacity = max_pos - min_pos + 1
    if(min_pos == max_pos){
        return 0;
    }
    return (max_pos - min_pos) + 1;
}

pos_t calMaxPos(pos_t min_pos, capacity_t year_capacity){
    // Calculates end position for student numbers
    if(year_capacity == 0){
        return min_pos;
    }
    return (year_capacity + min_pos) - 1;
}

pos_t calStartPos(pos_t max_pos, capacity_t year_capacity){
    // Calculates start position for student numbers
    // max_pos = (year_capacity + min_pos) - 1
    if(year_capacity==0){
        return max_pos;
    }
    return (max_pos - year_capacity) + 1;
}

size_t posPartSize(pos_t min_pos, capacity_t year_capacity){
    // Calculates size(digits) position part of student number.
    pos_t max_pos = calMaxPos(min_pos, year_capacity);
    return intSize(max_pos);
}

size_t yearPartSize(year_t year, unsigned int strict){
    // Calculates size(digits) of year part of student number.
    if(strict && isTwentiethCentury(year)){
        return 2;
    }else{
        return intSize(year);
    }
}


pos_t toPos(part_t pos_part, SNumsInfo students_info){
    return strInt(pos_part);
}

year_t toYear(part_t year_part, SNumsInfo students_info){
    year_t year = strInt(year_part);
    if(students_info.strict && strlen(year_part)==2){
        //year_t start_year = students_info.start_year;
        //year_t end_year = students_info.start_year;
        //if(isTwentiethCentury(start_year)||isTwentiethCentury(end_year)){
        year += 1900;
    }
    return year;
}

part_t toPosPart(pos_t pos, SNumsInfo students_info){
    char *pos_str = intStr(pos);
    size_t pos_part_size = posPartSize(students_info.min_pos,
                                    students_info.year_capacity);
    part_t pos_part = fillStr(pos_str, '0', pos_part_size);
    free(pos_str);
    return pos_part;
}

part_t toYearPart(year_t year, SNumsInfo students_info){
    part_t year_part;
    char * year_str = intStr(year);
    size_t year_size = strlen(year_str);
    if(students_info.strict && isTwentiethCentury(year)){
        year_part = sliceStr(year_str, year_size - 2, year_size);
        free(year_str);
    }else{
        year_part = year_str;
    }
    return year_part;
}


bool yearValid(year_t year, SNumsInfo students_info){
    // Checks if year is valid for student numbers
    return year>=students_info.start_year && year<=students_info.end_year;
}

bool partValid(part_t part){
    // Checks if part contains only decimal digits.
    // char *buf;
    // size_t size = strlen(part);
    // buf = malloc(size+1);
    // // itea() is non-standard function.
    // itoa(atoi(part), buf, 10);
    // bool valid = size == strlen(buf);
    // free(buf);
    // return valid;
    return strspn(part, "0123456789") == strlen(part);
}

bool yearPartValid(part_t year_part, SNumsInfo students_info){
    // Checks if year part is valid for student numbers
    if(partValid(year_part)){
        year_t year = toYear(year_part, students_info);
        if(students_info.strict&&isTwentiethCentury(year)){
            if(strlen(year_part)!=2){
                return false;
            }
        }
        return yearValid(year, students_info);
    }else{
        return false;
    }
}

bool posValid(pos_t pos, SNumsInfo students_info){
    // Checks if position is valid for student numbers
    pos_t start_pos, end_pos;
    if(students_info.start_pos<0){
        start_pos = students_info.min_pos;
    }else{
        start_pos = students_info.start_pos;
    }
    if(students_info.end_pos<0){
        end_pos = calMaxPos(students_info.min_pos,
                            students_info.year_capacity);
    }else{
        end_pos = students_info.end_pos;
    }
    return pos>=start_pos && pos<=end_pos;
}

bool posPartValid(part_t pos_part, SNumsInfo students_info){
    // Checks if position part is valid for student numbers
    size_t pos_size = posPartSize(students_info.min_pos,
                                  students_info.year_capacity);
    if(strlen(pos_part)==pos_size){
        pos_t pos = toPos(pos_part, students_info);
        return posValid(pos, students_info);
    }else{
        return false;
    }
}

part_t extractYearPart(snum_t student_number, SNumsInfo students_info){
    part_t snum_part = intStr(student_number);
    size_t pos_size = posPartSize(students_info.min_pos,
                                  students_info.year_capacity);
    size_t snum_size = strlen(snum_part);
    int end_index = 0;
    if(snum_size>pos_size){
        end_index = snum_size-pos_size;
    }
    // else student number is not valid a sits missing year part
    part_t year_part = sliceStr(snum_part, 0, end_index);
    free(snum_part);
    return year_part;
}

part_t extractPosPart(snum_t student_number, SNumsInfo students_info){
    part_t snum_part = intStr(student_number);
    size_t pos_size = posPartSize(students_info.min_pos,
                                students_info.year_capacity);
    size_t snum_size = strlen(snum_part);
    int start_index = snum_size;
    int end_index = start_index;
    if(snum_size>pos_size){
        start_index = snum_size - pos_size;
    }
    // else student number is not valid a sits missing year part
    part_t pos_part = sliceStr(snum_part, start_index, end_index);
    free(snum_part);
    return pos_part;
}

year_t extractYear(snum_t student_number, SNumsInfo students_info){
    part_t year_part = extractYearPart(student_number, students_info);
    year_t year = toYear(year_part, students_info);
    free(year_part);
    return year;
}

pos_t extractPos(snum_t student_number, SNumsInfo students_info){
    part_t pos_part = extractPosPart(student_number, students_info);
    year_t pos = toPos(pos_part, students_info);
    free(pos_part);
    return pos;
}

SNum splitStudentNumber(snum_t student_number, SNumsInfo students_info){
    SNum split_snum;
    split_snum.student_number = student_number;
    split_snum.year_part = extractYearPart(student_number, students_info);
    split_snum.pos_part = extractPosPart(student_number, students_info);
    return split_snum;
}


bool studentNumberValid(snum_t student_number, SNumsInfo students_info){
    part_t pos_part = extractPosPart(student_number, students_info);
    part_t year_part = extractYearPart(student_number, students_info);
    bool is_valid;
    if(pos_part && year_part){
        is_valid = yearPartValid(year_part, students_info) &&
                   posPartValid(pos_part, students_info);
    }else{
        is_valid = false;
    }
    free(year_part);
    free(pos_part);
    return is_valid;
}
