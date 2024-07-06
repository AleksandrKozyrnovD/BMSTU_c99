#include "check_test.h"
#include <check.h>
#include <stdio.h>

#define SIZE 256

///Тесты на llo (unsigned long long octahedral)
START_TEST(test_llo_1)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, sizeof(s1), "%llo + %llo = %llo", 07LL, 06LL, 07LL + 06LL);
    n2 = my_snprintf(s2, sizeof(s2), "%llo + %llo = %llo", 07LL, 06LL, 07LL + 06LL);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

// START_TEST(test_llo_2)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//
//     n1 = snprintf(s1, 5, "%llo + %llo = %llo", 07LL, 06LL, 07LL + 06LL);
//     n2 = my_snprintf(s2, 5, "%llo + %llo = %llo", 07LL, 06LL, 07LL + 06LL);
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST


START_TEST(test_llo_3)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, sizeof(s1), "%llo", -1LL);
    n2 = my_snprintf(s2, sizeof(s2), "%llo", -1LL);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

// START_TEST(test_llo_4)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//
//     n1 = snprintf(s1, 3, "%llo", -1LL);
//     n2 = my_snprintf(s2, 3, "%llo", -1LL);
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST


///Проверка на строчки
START_TEST(test_s_1)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, sizeof(s1), "Hello, %s! Hello again, %s", "Aleksandr", "Sasha");
    n2 = my_snprintf(s2, sizeof(s1), "Hello, %s! Hello again, %s", "Aleksandr", "Sasha");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

// START_TEST(test_s_2)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//
//     n1 = snprintf(s1, 5, "Hello, %s! Hello again, %s", "Aleksandr", "Sasha");
//     n2 = my_snprintf(s2, 5, "Hello, %s! Hello again, %s", "Aleksandr", "Sasha");
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST

// START_TEST(test_s_3)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//
//     n1 = snprintf(s1, SIZE, "Hello, %s! Hello again, %s", NULL, "Sasha");
//     n2 = my_snprintf(s2, SIZE, "Hello, %s! Hello again, %s", NULL, "Sasha");
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST

// START_TEST(test_s_4)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//
//     n1 = snprintf(s1, 3, "Hello, %s! Hello again, %s", NULL, "Sasha");
//     n2 = my_snprintf(s2, 3, "Hello, %s! Hello again, %s", NULL, "Sasha");
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST

START_TEST(test_s_5)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, SIZE, "%s", "");
    n2 = my_snprintf(s2, SIZE, "%s", "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_s_6)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, SIZE, "%s", "\0");
    n2 = my_snprintf(s2, SIZE, "%s", "\0");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_s_7)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];

    n1 = snprintf(s1, SIZE, "%s", "abc\0");
    n2 = my_snprintf(s2, SIZE, "%s", "abc\0");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST


///Общие тесты
START_TEST(test_1)
{
    int n1, n2;
    char s1[SIZE];
    char s2[SIZE];
    
    n1 = snprintf(s1, SIZE, "%%%%");
    n2 = my_snprintf(s2, SIZE, "%%%%");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_2)
{
    // int n1, n2;
    int n2;
    // char s1[SIZE];
    char s2[SIZE];
    
    // n1 = snprintf(s1, 0, "1234");
    n2 = my_snprintf(s2, 0, "1234");

    ck_assert_int_eq(4, n2);
    // ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_3)
{
    // int n1, n2;
    int n2;
    // char s1[SIZE];
    // char s2[SIZE];
    
    // n1 = snprintf(NULL, SIZE, "1234");
    n2 = my_snprintf(NULL, SIZE, "1234");

    ck_assert_int_eq(4, n2);
    // ck_assert_str_eq(s1, s2);
}
END_TEST
// START_TEST(test_2)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//     
//     n1 = snprintf(s1, SIZE, "%");
//     n2 = my_snprintf(s2, SIZE, "%");
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST

// START_TEST(test_3)
// {
//     int n1, n2;
//     char s1[SIZE];
//     char s2[SIZE];
//     
//     n1 = snprintf(s1, SIZE, "%1%%%2");
//     n2 = my_snprintf(s2, SIZE, "%1%%%2");
//
//     ck_assert_int_eq(n1, n2);
//     ck_assert_str_eq(s1, s2);
// }
// END_TEST

Suite *get_test_suite(void)
{
    Suite *suite = suite_create("Test");

    TCase *test_llo = tcase_create("llo");

    tcase_add_test(test_llo, test_llo_1);
    // tcase_add_test(test_llo, test_llo_2);
    tcase_add_test(test_llo, test_llo_3);
    // tcase_add_test(test_llo, test_llo_4);

    TCase *test_s = tcase_create("s");

    tcase_add_test(test_s, test_s_1);
    // tcase_add_test(test_s, test_s_2);
    // tcase_add_test(test_s, test_s_3);
    // tcase_add_test(test_s, test_s_4);
    tcase_add_test(test_s, test_s_5);
    tcase_add_test(test_s, test_s_6);
    tcase_add_test(test_s, test_s_7);

    TCase *test = tcase_create("all");

    tcase_add_test(test, test_1);
    tcase_add_test(test, test_2);
    tcase_add_test(test, test_3);

    suite_add_tcase(suite, test_llo);
    suite_add_tcase(suite, test_s);
    suite_add_tcase(suite, test);

    return suite;
}

