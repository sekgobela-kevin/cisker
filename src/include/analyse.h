#pragma once
#include<stdbool.h>


// Minimum supported year
#define MIN_YEAR 1000

// Year UL started to operate
#define START_YEAR 1959;
// End year is based on current year plus 1
//#define END_YEAR = presentTime()->year + 1;


// 'Year 2000 bug' or 'Year 2000 problem'
// The year caused year parts of student numbers to change.
#define Y2K_YEAR 2000
#define BEFORE_Y2K_YEAR Y2K_YEAR - 1;

// First position likely 0
#define MIN_POS 0
// Max capacity for a each year
#define YEAR_CAPACITY 100000
// Last/max end position for year
#define MAX_POS YEAR_CAPACITY + MIN_POS - 1

#define START_POS MIN_POS
#define END_POS MAX_POS


typedef unsigned int year_t;
typedef unsigned int pos_t;
typedef unsigned int capacity_t;
typedef unsigned int size_t;
typedef char* part_t;
typedef unsigned int snum_t;

struct StudentNumsInfo{
    year_t start_year;
    year_t end_year;
    year_t min_year;
    year_t year_capacity;
    pos_t min_pos;
    pos_t max_pos;
    int start_pos;
    int end_pos;
    bool strict;
};

struct StudentNumber{
    part_t year_part;
    part_t pos_part;
};

typedef struct StudentNumsInfo SNumsInfo;
typedef struct StudentNumber SNum;

SNumsInfo createSNumsInfo();

capacity_t calYearCapacity(pos_t min_pos, pos_t max_pos);

pos_t calMaxPos(pos_t min_pos, capacity_t year_capacity);

pos_t calStartPos(pos_t max_pos, capacity_t year_capacity);

size_t posPartSize(pos_t min_pos, capacity_t year_capacity);

size_t yearPartSize(year_t year, unsigned int strict);


bool yearValid(year_t year, SNumsInfo students_info);

bool yearPartValid(part_t year_part, SNumsInfo students_info);

bool posValid(year_t pos, SNumsInfo students_info);

bool posPartValid(part_t pos_part, SNumsInfo students_info);

bool studentNumberValid(part_t stnum, SNumsInfo students_info);


pos_t toPos(part_t pos_part, SNumsInfo students_info);

pos_t toYear(part_t year_part, SNumsInfo students_info);

part_t toPosPart(pos_t pos, SNumsInfo students_info);

part_t toYearPart(year_t year, SNumsInfo students_info);


part_t extractYearPart(snum_t student_number, SNumsInfo students_info);

part_t extractPosPart(snum_t student_number, SNumsInfo students_info);

year_t extractYear(snum_t student_number, SNumsInfo students_info);

pos_t extractPos(snum_t student_number, SNumsInfo students_info);


SNum splitStudentNumber(snum_t student_number, SNumsInfo students_info);
