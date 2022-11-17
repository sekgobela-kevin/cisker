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
    students_info.start_pos = START_POS;
    students_info.end_pos = END_POS;
    free(current_time);
}

capacity_t calYearCapacity(pos_t start_pos, pos_t end_pos){
    // Calculates year capacity from year start and last position
    // end_pos = (year_capacity + start_pos) - 1
    // year_capacity = end_pos - start_pos + 1
    if(start_pos == end_pos){
        return 0;
    }
    return (end_pos - start_pos) + 1;
}

pos_t calEndpos(pos_t start_pos, capacity_t year_capacity){
    // Calculates last position for student numbers
    if(year_capacity == 0){
        return start_pos;
    }
    return (year_capacity + start_pos) - 1;
}

size_t posPartSize(pos_t start_pos, capacity_t year_capacity){
    // Calculates size(digits) position part of student number.
    pos_t end_pos = calEndpos(start_pos, year_capacity);
    return intSize(end_pos);
}

size_t yearPartSize(year_t year, unsigned int strict){
    // Calculates size(digits) of year part of student number.
    if(strict && getCentury(year)==20){
        return 2;
    }else{
        return intSize(year);
    }
}

