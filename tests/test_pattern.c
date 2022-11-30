#include <stdio.h>
#include <tests.h>
#include <pattern.h>


START_TEST(testCommonLeadingSubString)
{
    char *common_leading;
    common_leading = commonLeadingSubString("namespace", "named");
    ck_assert_str_eq(common_leading, "name");
    common_leading = commonLeadingSubString("name", "namespace");
    ck_assert_str_eq(common_leading, "name");
    common_leading = commonLeadingSubString("human", "surname");
    ck_assert_str_eq(common_leading, "");
    common_leading = commonLeadingSubString("human", "");
    ck_assert_str_eq(common_leading, "");
}
END_TEST

START_TEST(testRemainingSubString)
{
    ck_assert_str_eq(remainingSubString("namespace", "name"), "space");
    ck_assert_str_eq(remainingSubString("human", "surname"), "");
    ck_assert_str_eq(remainingSubString("human", ""), "human");
}
END_TEST

START_TEST(testOccurrenceRangePattern)
{
    ck_assert_str_eq(occurrenceRangePattern(0, 2, "\\d"), "\\d{0,2}");
    ck_assert_str_eq(occurrenceRangePattern(0, 0, "\\d"), "");
    ck_assert_str_eq(occurrenceRangePattern(1, 1, "\\d"), "\\d");
    ck_assert_str_eq(occurrenceRangePattern(2, 2, "\\d"), "\\d{2}");
}
END_TEST


START_TEST(testCharRangePattern)
{
    ck_assert_str_eq(charRangePattern('a', 'b'), "[a-b]");
    ck_assert_str_eq(charRangePattern('a', 'a'), "a");
}
END_TEST

START_TEST(testIntRangePattern)
{
    ck_assert_str_eq(intRangePattern(1, 5, "\\d"), "[1-5]");
    ck_assert_str_eq(intRangePattern(10, 1050, "\\d"), "10\\d{0,2}");
    ck_assert_str_eq(intRangePattern(102, 1050, "\\d"), "10\\d{1,2}");
    ck_assert_str_eq(intRangePattern(1020, 1050, "\\d"), "10[2-5]\\d");
    ck_assert_str_eq(intRangePattern(10201, 10501, "\\d"), "10[2-5]\\d{2}");
    ck_assert_str_eq(intRangePattern(1020, 10502, "\\d"), "10\\d{2,3}");
}
END_TEST


START_TEST(testYearPartPattern)
{
    SNumsInfo students_info = createSNumsInfo();
    students_info.end_year = 2022;
    char *mpattern = "([5-9]\\d)|(20[0-2]\\d)";
    ck_assert_str_eq(yearPartPattern(students_info), mpattern);
    students_info.end_year = 1990;
    ck_assert_str_eq(yearPartPattern(students_info), "[5-9]\\d");
    students_info.start_year = 1820;
    mpattern = "(18[2-9]\\d)|([0-9]\\d)";
    ck_assert_str_eq(yearPartPattern(students_info), mpattern);
    students_info.start_year = 2000;
    students_info.end_year = 2022;
    ck_assert_str_eq(yearPartPattern(students_info), "20[0-2]\\d");
    students_info.end_year = 2009;
    ck_assert_str_eq(yearPartPattern(students_info), "200[0-9]");
}
END_TEST

START_TEST(testPosPartPattern)
{
    // Regex patterns were created by the function tested.
    // Cannot guarantee if they are correct(but they seem correct).
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_str_eq(posPartPattern(students_info), "[0-9]\\d{4}");
    students_info.year_capacity = 1000;
    ck_assert_str_eq(posPartPattern(students_info), "[0-9]\\d{2}");
    students_info.year_capacity = 100000;
    students_info.end_pos = 5000;
    ck_assert_str_eq(posPartPattern(students_info), "0[0-5]\\d{3}");
    students_info.start_pos = 5000;
    students_info.end_pos = 5080;
    ck_assert_str_eq(posPartPattern(students_info), "050[0-8]\\d");
}
END_TEST

START_TEST(testStudentNumbersPattern)
{
    SNumsInfo students_info = createSNumsInfo();
    students_info.end_year = 2022;
    char *year_part_pattern = "([5-9]\\d)|(20[0-2]\\d)";
    char *pos_part_pattern = "[0-9]\\d{4}";
    char mpattern[50];
    sprintf(mpattern, "(%s)(%s)", year_part_pattern, pos_part_pattern);
    ck_assert_str_eq(studentNumbersPattern(students_info), mpattern);
}
END_TEST



Suite * create_pattern_suite(void)
{
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("pattern");
    test_case = tcase_create("pattern");

    tcase_add_test(test_case, testCommonLeadingSubString);
    tcase_add_test(test_case, testRemainingSubString);
    tcase_add_test(test_case, testOccurrenceRangePattern);
    tcase_add_test(test_case, testCharRangePattern);
    tcase_add_test(test_case, testIntRangePattern);

    tcase_add_test(test_case, testYearPartPattern);
    tcase_add_test(test_case, testPosPartPattern);
    tcase_add_test(test_case, testStudentNumbersPattern);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}
