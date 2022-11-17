#pragma once

// Year UL started to operate
#define START_YEAR 1959;
// End year is based on current year plus 1
//#define END_YEAR = presentTime()->year + 1;

// Minimum supported year
#define MIN_YEAR 1000

// 'Year 2000 bug' or 'Year 2000 problem'
// The year caused year parts of student numbers to change.
#define Y2K_YEAR 2000
#define BEFORE_Y2K_YEAR Y2K_YEAR - 1;

// First position likely 0
#define START_POS 0
// Max capacity for a each year
#define YEAR_CAPACITY 100000
// Last/max end position for year
#define END_POS YEAR_CAPACITY + START_POS - 1


typedef unsigned int year_t;
typedef unsigned int pos_t;
typedef unsigned int capacity_t;
typedef unsigned int size_t;

struct StudentsInfo{
    year_t start_year;
    year_t end_year;
    year_t min_year;
    year_t year_capacity;
    pos_t start_pos;
    pos_t end_pos;
    unsigned int strict;
};

typedef struct StudentsInfo StudentsInfo;

StudentsInfo getDefaultStudentsInfo();


/**
 * @brief Gets end year from local time year as (current year + 1)
 * 
 * @return year_t 
 */
year_t getEndYear(void);

capacity_t calYearCapacity(pos_t start_pos, pos_t end_pos);

pos_t calEndpos(pos_t start_pos, capacity_t year_capacity);

size_t posPartSize(pos_t start_pos, capacity_t year_capacity);

size_t yearPartSize(year_t year, unsigned int strict);
