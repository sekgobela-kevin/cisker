#include <time.h>
#include <stdlib.h>

#include <util.h>
#include <check.h>


START_TEST(test_present_time)
{
    time_t seconds_time;
    struct tm *time_object;
    time(&seconds_time);
    struct tm * local_time = localtime(&seconds_time);
    struct tm * cisker_time = presentTime();

    ck_assert_int_eq(cisker_time->tm_mon, local_time->tm_mon);
    ck_assert_int_eq(cisker_time->tm_year, local_time->tm_year);
    free(local_time);
    free(cisker_time);
}
END_TEST


START_TEST(test_int_size)
{
    ck_assert_int_eq(intSize(10), 2);
    ck_assert_int_eq(intSize(3456), 4);
    ck_assert_int_eq(intSize(2632694), 7);
}
END_TEST


START_TEST(test_int_str)
{
    ck_assert_str_eq(intStr(10), "10");
    ck_assert_str_eq(intStr(3456), "3456");
    ck_assert_str_eq(intStr(2632694), "2632694");
}
END_TEST

START_TEST(test_str_int)
{
    ck_assert_int_eq(strInt("10"), 10);
    ck_assert_int_eq(strInt("3456"), 3456);
    ck_assert_int_eq(strInt("2632694"), 2632694);
}
END_TEST

START_TEST(test_slice)
{
    char dest_str[4];
    int dest_arr[2];
    int src_arr[6] = {1,2,3,4,5,6};
    int result_arr[2] = {4,5};
    slice("name", dest_str, 0, 3);
    slice(src_arr, dest_arr, 3, 5);
    ck_assert_str_eq(dest_str, "na");
    ck_assert(dest_arr == result_arr);
    free(dest_str);
}
END_TEST

START_TEST(test_get_century)
{
    ck_assert_int_eq(getCentury(2015), 21);
    ck_assert_int_eq(intSize(1540), 16);
    ck_assert_int_eq(getCentury(20050), 201);
}
END_TEST

START_TEST(test_is_twentieth_century)
{
    ck_assert_int_eq(isTwentiethCentury(2015), 0);
    ck_assert_int_eq(isTwentiethCentury(1940), 1);
    ck_assert_int_eq(isTwentiethCentury(20050), 0);
}
END_TEST