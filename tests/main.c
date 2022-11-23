#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include <tests.h>

int main(void)
 {
   Suite *suite_utils = create_utils_suite();
   Suite *suite_analyse = create_analyse_suite();
   Suite *suite_generate = create_generate_suite();
   SRunner *suite_runner = srunner_create(suite_utils);

   srunner_add_suite(suite_runner, suite_analyse);
   srunner_add_suite(suite_runner, suite_generate);

   srunner_run_all(suite_runner, CK_NORMAL);

   int total_failed = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);
   return total_failed > 0 ? EXIT_FAILURE: EXIT_SUCCESS;
 }