#include <stdlib.h>

#include <analyse.h>


pos_t guessPos(SNumsInfo students_info);

pos_t guessYear(SNumsInfo students_info);

part_t guessYearPart(SNumsInfo students_info);

part_t guessPosPart(SNumsInfo students_info);

int guessStudentNumber(SNumsInfo students_info);

int createStudentNumber(year_t year, pos_t pos, SNumsInfo students_info);

int previousStudentNumber(int student_number, SNumsInfo students_info);

int nextStudentNumber(int student_number, SNumsInfo students_info);
