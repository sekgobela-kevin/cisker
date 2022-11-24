#include <util.h>
#include <analyse.h>
#include <generate.h>

#include <tests.h>


START_TEST(testGuessPos)
{
    SNumsInfo students_info = createSNumsInfo();
    pos_t pos = guessPos(students_info);
    ck_assert_int_ge(pos, 0);
    ck_assert_int_le(pos, END_POS);

    students_info.start_pos = END_POS-5;
    pos = guessPos(students_info);
    ck_assert_int_ge(pos, END_POS-5);
    ck_assert_int_le(pos, END_POS);
}
END_TEST

START_TEST(testGuessYear)
{
    SNumsInfo students_info = createSNumsInfo();
    pos_t year = guessYear(students_info);
    ck_assert_int_ge(year, students_info.start_year);
    ck_assert_int_le(year, students_info.end_year);

    students_info.start_year = 1990;
    students_info.end_year = 1995;
    year = guessYear(students_info);
    ck_assert_int_ge(year, students_info.start_year);
    ck_assert_int_le(year, students_info.end_year);
}
END_TEST

START_TEST(testGuessYearPart)
{
    SNumsInfo students_info = createSNumsInfo();
    part_t year_part = guessYearPart(students_info);
    pos_t year = toYear(year_part, students_info);
    ck_assert_int_ge(year, students_info.start_year);
    ck_assert_int_le(year, students_info.end_year);
}
END_TEST

START_TEST(testGuessPosPart)
{
    SNumsInfo students_info = createSNumsInfo();
    part_t pos_part = guessPosPart(students_info);
    pos_t pos = toPos(pos_part, students_info);
    ck_assert_int_ge(pos, students_info.min_pos);
    ck_assert_int_le(pos, calMaxPos(MIN_POS, YEAR_CAPACITY));
}
END_TEST

START_TEST(testGuessStudentNumber)
{
    SNumsInfo students_info = createSNumsInfo();
    int pos_part = guessStudentNumber(students_info);
    ck_assert(studentNumberValid(pos_part, students_info));
}
END_TEST

START_TEST(testCreateStudentNumber)
{
    SNumsInfo students_info = createSNumsInfo();
    int student_num = createStudentNumber(2015, 461, students_info);
    ck_assert_int_eq(student_num, 201500461);
    students_info.year_capacity = 1000000;
    student_num = createStudentNumber(2015, 461, students_info);
    ck_assert_int_eq(student_num, 2015000461);
}
END_TEST

START_TEST(testPreviousStudentNumber)
{
    SNumsInfo students_info = createSNumsInfo();
    int student_num = previousStudentNumber(201500461, students_info);
    ck_assert_int_eq(student_num, 201500460);
    student_num = previousStudentNumber(201500000, students_info);
    ck_assert_int_eq(student_num, 201499999);
}
END_TEST

START_TEST(testNextStudentNumber)
{
    SNumsInfo students_info = createSNumsInfo();
    int student_num = nextStudentNumber(201500461, students_info);
    ck_assert_int_eq(student_num, 201500462);
    student_num = nextStudentNumber(201599999, students_info);
    ck_assert_int_eq(student_num, 201600000);
}
END_TEST



Suite * create_generate_suite(void)
{
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("generate");
    test_case = tcase_create("generate");

    tcase_add_test(test_case, testGuessPos);
    tcase_add_test(test_case, testGuessYear);
    tcase_add_test(test_case, testGuessPosPart);
    tcase_add_test(test_case, testGuessYearPart);
    tcase_add_test(test_case, testCreateStudentNumber);
    tcase_add_test(test_case, testGuessStudentNumber);
    tcase_add_test(test_case, testPreviousStudentNumber);
    tcase_add_test(test_case, testNextStudentNumber);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}

