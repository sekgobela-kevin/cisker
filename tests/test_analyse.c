#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <analyse.h>
#include <util.h>
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
    ck_assert_int_eq(calMaxPos(0,0), 0);
    ck_assert_int_eq(calMaxPos(5,0), 5);
    ck_assert_int_eq(calMaxPos(0,10), 9);
    ck_assert_int_eq(calMaxPos(1,9), 9);
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



START_TEST(testPartValid)
{
    ck_assert(partValid("2034"));
    ck_assert(!partValid("20B34"));
    ck_assert(partValid("0000000"));
    ck_assert(partValid("99999999"));
}
END_TEST

START_TEST(testCreateSNumsInfo)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(students_info.start_year, START_YEAR);
    ck_assert_int_eq(students_info.end_year, presentYear()+1);
    ck_assert_int_eq(students_info.min_pos, MIN_POS);
    ck_assert_int_eq(students_info.start_pos, -1);
    ck_assert_int_eq(students_info.end_pos, -1);
    ck_assert_int_eq(students_info.year_capacity, YEAR_CAPACITY);
    ck_assert(students_info.strict==STRICT);
}
END_TEST

START_TEST(testToPos)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(toPos("00400", students_info), 400);
}
END_TEST

START_TEST(testToYear)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(toYear("2015", students_info), 2015);
    ck_assert_int_eq(toYear("84", students_info), 1984);
    students_info.strict = false;
    ck_assert_int_eq(toYear("84", students_info), 84);
    ck_assert_int_eq(toYear("1984", students_info), 1984);
}
END_TEST

START_TEST(testToPosPart)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_str_eq(toPosPart(400, students_info), "00400");
    students_info.year_capacity = 1000;
    ck_assert_str_eq(toPosPart(400, students_info), "400");
}
END_TEST

START_TEST(testToYearPart)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_str_eq(toYearPart(2015, students_info), "2015");
    ck_assert_str_eq(toYearPart(1984, students_info), "84");
    students_info.strict = false;
    ck_assert_str_eq(toYearPart(84, students_info), "84");
}
END_TEST

START_TEST(testYearValid)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert(!yearValid(400, students_info));
    //ck_assert(yearValid(1960, students_info));
    ck_assert(yearValid(presentYear()+1, students_info));
    ck_assert(!yearValid(presentYear()+2, students_info));

    students_info.start_year = 0;
    ck_assert(yearValid(400, students_info));
    students_info.start_year = 1000;
    ck_assert(!yearValid(400, students_info));
    ck_assert(yearValid(1000, students_info));
    students_info.end_year = 30090;
    ck_assert(yearValid(30090, students_info));
    ck_assert(!yearValid(30091, students_info));
}
END_TEST

START_TEST(testPosValid)
{
    SNumsInfo students_info = createSNumsInfo();
    //ck_assert(posValid(0, students_info));
    ck_assert(posValid(99999, students_info));
    ck_assert(!posValid(100000, students_info));

    students_info.min_pos = 10;
    ck_assert(!posValid(4, students_info));
    ck_assert(posValid(99999+10, students_info));
    ck_assert(!posValid(99999+11, students_info));

    students_info.start_pos = 500;
    ck_assert(!posValid(200, students_info));
    ck_assert(posValid(99999+10, students_info));
    
    students_info = createSNumsInfo();
    students_info.year_capacity = 500;
    ck_assert(posValid(200, students_info));
    ck_assert(!posValid(500, students_info));
}
END_TEST

START_TEST(testYearPartValid)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert(!yearPartValid("400", students_info));
    ck_assert(yearPartValid("84", students_info));
    ck_assert(!yearPartValid("1984", students_info));
    ck_assert(yearPartValid("2015", students_info));
    ck_assert(!yearPartValid("num1", students_info));

    students_info.strict = false;
    ck_assert(!yearPartValid("84", students_info));
    ck_assert(yearPartValid("2015", students_info));
}
END_TEST

START_TEST(testPosPartValid)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert(!posPartValid("0", students_info));
    ck_assert(posPartValid("00000", students_info));
    ck_assert(posPartValid("99999", students_info));
    ck_assert(!posPartValid("9999", students_info));
    ck_assert(!posPartValid("100000", students_info));

    students_info.year_capacity = 5000;
    students_info.start_pos = 500;
    ck_assert(!posPartValid("0400", students_info));
    ck_assert(posPartValid("0600", students_info));
    ck_assert(!posPartValid("5000", students_info));
}
END_TEST


START_TEST(testExtractYearPart)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_str_eq(extractYearPart(201500371, students_info), "2015");
    ck_assert_str_eq(extractYearPart(8400371, students_info), "84");
    ck_assert_str_eq(extractYearPart(00371, students_info), "");
    ck_assert_str_eq(extractYearPart(23, students_info), "");

    students_info.year_capacity = 1000000;
    ck_assert_str_eq(extractYearPart(201500371, students_info), "201"); 
}
END_TEST

START_TEST(testExtractPosPart)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_str_eq(extractPosPart(201500371, students_info), "00371");
    ck_assert_str_eq(extractPosPart(8400371, students_info), "00371");
    ck_assert_str_eq(extractPosPart(53371, students_info), "");
    ck_assert_str_eq(extractPosPart(23, students_info), "");
    
    students_info.year_capacity = 1000000;
    ck_assert_str_eq(extractPosPart(201500371, students_info), "500371");
}
END_TEST

START_TEST(testExtractYear)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(extractYear(201500371, students_info), 2015);
    ck_assert_int_eq(extractYear(8400371, students_info), 1984);
    //ck_assert_int_eq(extractYear(53371, students_info), "");
    //ck_assert_int_eq(extractYear(23, students_info), "");

    students_info.year_capacity = 1000000;
    ck_assert_int_eq(extractYear(201500371, students_info), 201);
}
END_TEST

START_TEST(testExtractPos)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(extractPos(201500371, students_info),371);
    ck_assert_int_eq(extractPos(8400371, students_info), 371);
    //ck_assert_int_eq(extractPos(00371, students_info), "");
    //ck_assert_int_eq(extractPos(23, students_info), "");
    
    students_info.year_capacity = 1000000;
    ck_assert_int_eq(extractPos(201500371, students_info), 500371);
}
END_TEST


START_TEST(testSplitStudentNumber)
{
    SNumsInfo students_info = createSNumsInfo();
    SNum split_snum = splitStudentNumber(201500371, students_info);
    ck_assert_str_eq(split_snum.year_part, "2015");
    ck_assert_str_eq(split_snum.pos_part, "00371");
}
END_TEST

START_TEST(testStudentNumberValid)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert(studentNumberValid(201500371, students_info));
    ck_assert(!studentNumberValid(198400371, students_info));;
    ck_assert(studentNumberValid(8400371, students_info));
    ck_assert(!studentNumberValid(4400371, students_info));

    students_info.end_year = 2014;
    ck_assert(!studentNumberValid(201500371, students_info));
    students_info.start_year = 1900;
    ck_assert(studentNumberValid(4400371, students_info));


    students_info.year_capacity = 10000;
    ck_assert(!studentNumberValid(4400371, students_info));
    ck_assert(studentNumberValid(440371, students_info));

    students_info.strict = false;
    ck_assert(!studentNumberValid(440371, students_info));
    ck_assert(studentNumberValid(19440371, students_info));
}
END_TEST




START_TEST(testStudentNumbersMaxSize)
{
    SNumsInfo students_info = createSNumsInfo();
    ck_assert_int_eq(studentNumbersMaxSize(students_info), 9);
    students_info.start_year = 1982;
    students_info.end_year = 1990;
    ck_assert_int_eq(studentNumbersMaxSize(students_info), 7);

    students_info.strict = false;
    ck_assert_int_eq(studentNumbersMaxSize(students_info), 9);
    students_info.year_capacity = 90;
    ck_assert_int_eq(studentNumbersMaxSize(students_info), 6);
}
END_TEST

START_TEST(testTotalStudentNumbers)
{
    SNumsInfo students_info = createSNumsInfo();
    students_info.start_year = 2010;
    students_info.end_year = 2010;
    ck_assert_int_eq(totalStudentNumbers(students_info), 100000);
    students_info.end_year = 2011;
    ck_assert_int_eq(totalStudentNumbers(students_info), 100000*2);
    students_info.year_capacity = 10;
    ck_assert_int_eq(totalStudentNumbers(students_info), 10*2);

    students_info.start_pos = 5;
    ck_assert_int_eq(totalStudentNumbers(students_info), 10);
    students_info.end_pos = 14;
    ck_assert_int_eq(totalStudentNumbers(students_info), 10*2);
}
END_TEST

START_TEST(testStartDistance)
{
    SNumsInfo students_info = createSNumsInfo();
    students_info.start_year = 2010;
    students_info.end_year = 2010;
    ck_assert_int_eq(startDistance(201099999, students_info), 100000-1);
    students_info.end_year = 2011;
    ck_assert_int_eq(startDistance(201199999, students_info), (100000*2)-1);
    students_info.year_capacity = 10;
    ck_assert_int_eq(startDistance(20109, students_info), 10-1);
    ck_assert_int_eq(startDistance(20119, students_info), (10*2)-1);
}
END_TEST

START_TEST(testEndDistance)
{
    SNumsInfo students_info = createSNumsInfo();
    students_info.start_year = 2010;
    students_info.end_year = 2010;
    ck_assert_int_eq(endDistance(201000000, students_info), 100000-1);
    students_info.end_year = 2011;
    ck_assert_int_eq(endDistance(201000000, students_info), (100000*2)-1);
    students_info.year_capacity = 10;
    ck_assert_int_eq(endDistance(20100, students_info), (10*2)-1);
    ck_assert_int_eq(endDistance(20110, students_info), 10-1);
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


    tcase_add_test(test_case, testCreateSNumsInfo);
    tcase_add_test(test_case, testToPos);
    tcase_add_test(test_case, testToYear);
    tcase_add_test(test_case, testToPosPart);
    tcase_add_test(test_case, testToYearPart);

    tcase_add_test(test_case, testPartValid);
    tcase_add_test(test_case, testYearValid);
    tcase_add_test(test_case, testPosValid);
    tcase_add_test(test_case, testYearPartValid);
    tcase_add_test(test_case, testPosPartValid);

    tcase_add_test(test_case, testExtractPosPart);
    tcase_add_test(test_case, testExtractYearPart);
    tcase_add_test(test_case, testExtractPos);
    tcase_add_test(test_case, testExtractYear);

    tcase_add_test(test_case, testSplitStudentNumber);
    tcase_add_test(test_case, testStudentNumberValid);

    tcase_add_test(test_case, testStudentNumbersMaxSize);
    tcase_add_test(test_case, testTotalStudentNumbers);
    tcase_add_test(test_case, testStartDistance);
    tcase_add_test(test_case, testEndDistance);
    
    suite_add_tcase(test_suite, test_case);
    return test_suite;
}
