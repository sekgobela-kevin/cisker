#include <tests.h>
#include <cisker.h>


START_TEST(testToPos)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(toPos("00400", students_info), 400);
}
END_TEST


START_TEST(testGuessPos)
{
    SNumsInfo students_info = createSNumsInfo();
    pos_t pos = guessPos(students_info);
    ck_assert_int_ge(pos, 0);
    ck_assert_int_le(pos, END_POS);
}
END_TEST


START_TEST(testRemainingSubString)
{
    ck_assert_str_eq(remainingSubString("namespace", "name"), "space");
    ck_assert_str_eq(remainingSubString("human", "surname"), "");
    ck_assert_str_eq(remainingSubString("human", ""), "human");
}
END_TEST

Suite * create_cisker_suite(void)
{
    Suite *test_suite;
    TCase *test_case;

    test_suite = suite_create("cisker");
    test_case = tcase_create("cisker");

    tcase_add_test(test_case, testToPos);
    tcase_add_test(test_case, testGuessPos);
    tcase_add_test(test_case, testRemainingSubString);
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}