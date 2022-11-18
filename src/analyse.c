#include <analyse.h>
#include <util.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


SNumsInfo createSNumsInfo(){
    SNumsInfo students_info;
    struct tm *current_time = presentTime();
    year_t current_year = current_time->tm_year;
    students_info.min_year = MIN_YEAR;
    students_info.start_year = START_YEAR;
    students_info.end_year = current_year + 1;
    students_info.min_pos = MIN_POS;
    students_info.max_pos = MAX_POS;
    students_info.start_pos = -1;
    students_info.end_pos = -1;
    free(current_time);
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
    if(max_pos==0){
        return 1;
    }
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


bool yearValid(year_t year, SNumsInfo students_info){
    // Checks if year is valid for student numbers
    return year>=students_info.end_year && year<=students_info.end_year;
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
        year_t year = strInt(year_part);
        if(students_info.strict && isTwentiethCentury(year)){
            if(!(year>=10 && year<100)){
                return false;
            }
        }
        return yearValid(year, students_info);
    }
    return false;
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
    size_t pos_part_size = posPartSize(students_info.min_pos,
                                  students_info.year_capacity);
    if(strlen(pos_part)==pos_part_size){
        pos_t pos = strInt(pos_part);
        return posValid(pos, students_info);
    }
    return false;
}

bool studentNumberValid(part_t stnum, SNumsInfo students_info){

}
