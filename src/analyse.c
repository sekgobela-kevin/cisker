#include <analyse.h>
#include <util.h>

#include <time.h>
#include <stdlib.h>


StudentsInfo getDefaultStudentsInfo(){
    StudentsInfo students_info;
    struct tm *current_time = presentTime();
    year_t current_year = current_time->tm_year;
    students_info.start_year = START_YEAR;
    students_info.end_year = current_year + 1;
    students_info.min_year = MIN_YEAR;
    students_info.min_pos = START_POS;
    students_info.max_pos = END_POS;
    students_info.start_pos = START_POS;
    students_info.end_pos = END_POS;
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
    if(strict && getCentury(year)==20){
        return 2;
    }else{
        return intSize(year);
    }
}

