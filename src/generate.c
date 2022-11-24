
#include <util.h>
#include <generate.h>

pos_t guessPos(SNumsInfo students_info){
    int start_pos = students_info.start_pos;
    pos_t end_pos = calMaxPos(students_info.min_pos,
                            students_info.year_capacity);
    if(start_pos<0){
        start_pos = students_info.min_pos;
    }
    return randomInt(start_pos, end_pos+1);
}

pos_t guessYear(SNumsInfo students_info){
    return randomInt(students_info.start_year, students_info.end_year+1);
}

part_t guessYearPart(SNumsInfo students_info){
    return toYearPart(guessYear(students_info), students_info);
}

part_t guessPosPart(SNumsInfo students_info){
    return toPosPart(guessPos(students_info), students_info);
}

int createStudentNumber(year_t year, pos_t pos, SNumsInfo students_info){
    part_t year_part = toYearPart(year, students_info);
    part_t pos_part = toPosPart(pos, students_info);
    char *student_number_str = concatStr(year_part, pos_part);
    int student_number = strInt(student_number_str);
    free(year_part);
    free(pos_part);
    free(student_number_str);
    return student_number;
}

int guessStudentNumber(SNumsInfo students_info){
    year_t year = guessYear(students_info);
    pos_t pos = guessPos(students_info);
    return createStudentNumber(year, pos, students_info);
}

int previousStudentNumber(int student_number, SNumsInfo students_info){
    int start_pos = students_info.start_pos;
    if(start_pos<0){
        start_pos = students_info.min_pos;
    }
    year_t year = extractYear(student_number, students_info);
    pos_t pos = extractPos(student_number, students_info);
    if(pos>start_pos){
        pos -= 1;
    }else{
        pos = calMaxPos(students_info.min_pos,
                        students_info.year_capacity);
        year -= 1;
    }
    return createStudentNumber(year, pos, students_info);
}

int nextStudentNumber(int student_number, SNumsInfo students_info){
    int end_pos = students_info.end_pos;
    int start_pos = students_info.start_pos;
    if(start_pos<0){
        start_pos = students_info.min_pos;
    }
    if(end_pos<0){
        end_pos = calMaxPos(students_info.min_pos,
                                students_info.year_capacity);
    }
    year_t year = extractYear(student_number, students_info);
    pos_t pos = extractPos(student_number, students_info);
    if(pos<end_pos){
        pos += 1;
    }else{
        pos = start_pos;
        year += 1;
    }
    return createStudentNumber(year, pos, students_info);
}
