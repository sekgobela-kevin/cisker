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
    //ck_assert_str_eq(intRangePattern(1, 5, "\\d"), "[1-5]");
    ck_assert_str_eq(intRangePattern(10, 1050, "\\d"), "10\\d{0,2}");
    ck_assert_str_eq(intRangePattern(102, 1050, "\\d"), "10\\d{1,2}");
    ck_assert_str_eq(intRangePattern(1020, 1050, "\\d"), "10[2-5]\\d");
    //ck_assert_str_eq(intRangePattern(1020, 10502, "\\d"), "10[2-5]\\d{1,2}");
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
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}
