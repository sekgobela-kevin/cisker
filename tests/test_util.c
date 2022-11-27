#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <util.h>
#include <check.h>


START_TEST(test_time_functions)
{
    time_t seconds_time = time(NULL);
    struct tm * local_time = localtime(&seconds_time);
    int local_year = local_time->tm_year;
    struct tm * cisker_time = presentTime();
    int cisker_year = cisker_time->tm_year;
    
    ck_assert_int_eq(cisker_year, local_year );
    ck_assert_int_eq(presentYear(), local_year+1900);
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

START_TEST(test_slice_int_array)
{
    int *dest_arr;
    int src_arr[6] = {1,2,3,4,5,6};
    int result_arr[2] = {4,5};
    dest_arr = sliceIntArr(src_arr, 3, 5);
    // Failing as elements not copied to result_arr.
    // result_arr contains random numbers(unused space)
    ck_assert(equalIntArrays(dest_arr, result_arr, 2));
    free(result_arr);
}
END_TEST

START_TEST(test_slice_str)
{
    char* dest_str;
    dest_str = sliceStr("name", 1, 3);
    ck_assert_str_eq(dest_str, "am");
    free(dest_str);
}
END_TEST

START_TEST(test_equal_int_arrays)
{
    int arr1[4] = {1,2,3,4};
    int arr2[4] = {1,2,3,4};
    int* arr3 = calloc(2, sizeof(int));
    *arr3 = 1;
    *(arr3+1) = 8;
    ck_assert(equalIntArrays(arr1, arr2, 4));
    ck_assert(equalIntArrays(arr1, arr3, 1));
    ck_assert(!equalIntArrays(arr1, arr3, 2));
    free(arr3);
}
END_TEST

START_TEST(test_get_century)
{
    ck_assert_int_eq(getCentury(2015), 21);
    ck_assert_int_eq(getCentury(1540), 16);
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

START_TEST(test_random_int)
{
    int random_num = randomInt(100, 200);
    ck_assert_int_ge(random_num, 100);
    ck_assert_int_lt(random_num, 200);
    int another_random_num = randomInt(300, 600000);
    ck_assert_int_ge(another_random_num, 300);
    ck_assert_int_lt(another_random_num, 600000);
}
END_TEST

START_TEST(test_concat_str)
{
    ck_assert_str_eq(concatStr("name", "space"), "namespace");
    ck_assert_str_eq(concatStr("", ""), "");
    ck_assert_str_eq(concatStr("aaa", "b"), "aaab");
}
END_TEST

START_TEST(test_fill_str)
{
    ck_assert_str_eq(fillStr("name", '-', 0), "name");
    ck_assert_str_eq(fillStr("name", '-', 4), "name");
    ck_assert_str_eq(fillStr("name", '-', 6), "--name");
    ck_assert_str_eq(fillStr("name", '-', 10), "------name");
}
END_TEST

START_TEST(test_equal_str)
{
    ck_assert(equalStr("name", "name"));
    ck_assert(!equalStr("name", "aaaa"));
}
END_TEST

START_TEST(test_shrink_mem)
{
    char *str = malloc(10);
    strcpy(str, "name");
    ck_assert_str_eq((char*)shrinkMem(str, strlen(str)+1), "name");
}
END_TEST

START_TEST(test_shrink_str)
{
    char *str = malloc(10);
    strcpy(str, "name");
    ck_assert_str_eq(shrinkStr(str), "name");
}
END_TEST


Suite * create_utils_suite(void)
{
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("utilities");
    test_case = tcase_create("utilities");

    tcase_add_test(test_case, test_time_functions);
    tcase_add_test(test_case, test_int_size);
    tcase_add_test(test_case, test_int_str);
    tcase_add_test(test_case, test_str_int);
    tcase_add_test(test_case, test_slice_int_array);
    tcase_add_test(test_case, test_slice_str);
    tcase_add_test(test_case, test_equal_int_arrays);
    tcase_add_test(test_case, test_get_century);
    tcase_add_test(test_case, test_is_twentieth_century);
    tcase_add_test(test_case, test_random_int);
    tcase_add_test(test_case, test_concat_str);
    tcase_add_test(test_case, test_fill_str);
    tcase_add_test(test_case, test_equal_str);
    tcase_add_test(test_case, test_shrink_mem);
    tcase_add_test(test_case, test_shrink_str);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}
