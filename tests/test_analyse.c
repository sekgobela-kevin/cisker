#include <stdio.h>

#include <analyse.h>
#include <check.h>


START_TEST(testCalYearCapacity)
{
    ck_assert_int_eq(calYearCapacity(0,0), 0);
    ck_assert_int_eq(calYearCapacity(5,5), 0);
    ck_assert_int_eq(calYearCapacity(0,9), 10);
    ck_assert_int_eq(calYearCapacity(1,9), 9);
}
END_TEST


START_TEST(testCalEndpos)
{
    ck_assert_int_eq(calEndpos(0,0), 0);
    ck_assert_int_eq(calEndpos(5,0), 5);
    ck_assert_int_eq(calEndpos(0,10), 9);
    ck_assert_int_eq(calEndpos(1,9), 9);
}
END_TEST

START_TEST(testCalStartPos)
{
    ck_assert_int_eq(calStartPos(0,0), 0);
    ck_assert_int_eq(calStartPos(5,0), 5);
    ck_assert_int_eq(calStartPos(9,10), 0);
    ck_assert_int_eq(calStartPos(9,9), 1);
}
END_TEST

START_TEST(testPosPartSize)
{
    ck_assert_int_eq(posPartSize(0,0), 1);
    ck_assert_int_eq(posPartSize(0,10), 1);
    ck_assert_int_eq(posPartSize(1,10), 2);
    ck_assert_int_eq(posPartSize(200,1000), 4);
}
END_TEST

START_TEST(testYearPartSize)
{
    ck_assert_int_eq(yearPartSize(2015, 0), 4);
    ck_assert_int_eq(yearPartSize(2015, 1), 4);
    ck_assert_int_eq(yearPartSize(1966, 1), 2);
    ck_assert_int_eq(yearPartSize(18208, 1), 5);
}
END_TEST


Suite * create_analyse_suite(void){
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("analyse");
    test_case = tcase_create("analyse");

    tcase_add_test(test_case, testCalYearCapacity);
    tcase_add_test(test_case, testCalEndpos);
    tcase_add_test(test_case, testPosPartSize);
    tcase_add_test(test_case, testYearPartSize);
    tcase_add_test(test_case, testCalStartPos);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}


