#include <tests.h>
#include <filter.h>

START_TEST(testFilterStudnetNumbers)
{}
END_TEST


Suite * create_filter_suite(void)
{
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("filter");
    test_case = tcase_create("filter");

    tcase_add_test(test_case, testFilterStudnetNumbers);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}