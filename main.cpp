#include <iostream>
#include <tuple>
#include "code.h"

/*
This file unit tests the function(s) in code.cpp
Dr. Ritchey had to write this because Replit doesn't support unit testing for C++ (smh)
By the end of 121, you could be able to write this (and better), too.
*/

std::tuple<int,int> test(const int* leap_years, int n, int offset);

template <typename E>
std::tuple<int,int> test_exception(const int* leap_year, int n);

int main() {
    int pass_cnt = 0, fail_cnt = 0;

    {
        // leap years
        const int leap_years[] = {1600, 2000, 1696, 1704, 2147483644};

        // next year is leap year
        const int leap_years_1[] = {2003, 2399, 1703, 376781987, 2147483643};

        // 2 years until next leap year
        const int leap_years_2[] = {2006, 2022, 3454, 1582, 2147483642};

        // 3 years until next leap year
        const int leap_years_3[] = {8675309, 1991, 2001, 3005, 2397, 2147483641};

        // 7 years until next leap year
        const int leap_years_7[] = {1697, 1797, 1897, 2597};

        const int* tests[] = {leap_years, leap_years_1, leap_years_2, leap_years_3, leap_years_7};
        const int n[] = {sizeof(leap_years) / sizeof(int), sizeof(leap_years_1) / sizeof(int), sizeof(leap_years_2) / sizeof(int), sizeof(leap_years_3) / sizeof(int), sizeof(leap_years_7) / sizeof(int)};
        const int offsets[] = {0, -1, -2, -3, -7};
        const int num_tests = sizeof(tests) / sizeof(int*);
        for (int index = 0; index < num_tests; index++) {
            const int* testcase = tests[index];
            int p, f;
            std::tie(p,f) = test(testcase, n[index], offsets[index]);
            pass_cnt += p;
            fail_cnt += f;
        }
    }

    // out of bounds
    const int out_of_bounds[] = {1581, 0 , -1, INT32_MIN};

    // range error
    const int range_error[] = {2147483645, 2147483646, 2147483647};
    
    int n = sizeof(out_of_bounds) / sizeof(int);
    int p, f;
    std::tie(p,f) = test_exception<std::invalid_argument>(out_of_bounds, n);
    pass_cnt += p;
    fail_cnt += f;

    n = sizeof(range_error) / sizeof(int);
    std::tie(p,f) = test_exception<std::out_of_range>(out_of_bounds, n);
    pass_cnt += p;
    fail_cnt += f;

    std::cout << "passing " << pass_cnt << std::endl;
    std::cout << "failing " << fail_cnt << std::endl;
}

std::tuple<int,int> test(const int* leap_years, int n, int offset) {
    std::cout << "testing leap years "<< offset << std::endl;

    int pass_cnt = 0, fail_cnt = 0;

    for (int index = 0; index < n; index++) {
        int year = leap_years[index];
        int actual = next_leap_year(year);
        int expected = year - offset;
        if (actual != expected) {
            std::cout << "[FAIL] expected next_leap_year("<<year<<") to be " << expected << ", got " << actual << std::endl;
            fail_cnt++;
        } else {
            pass_cnt++;
        }
    }

    return std::make_tuple(pass_cnt, fail_cnt);
}

template <typename E>
std::tuple<int,int> test_exception(const int* leap_year, int n) {
    std::cout << "testing years that should throw "<<typeid(E).name() << std::endl;
    int pass_cnt = 0, fail_cnt = 0;
    for (int index = 0; index < n; index++) {
        int year = leap_year[index];
        try {
            next_leap_year(year);
            std::cout << "[FAIL] expected next_leap_year("<<year<<") to throw "<<typeid(E).name()<<", got nothing." << std::endl;
            fail_cnt++;
        } catch (const std::invalid_argument& err) {
            pass_cnt++;
        } catch (const std::exception& err) {
            std::cout << "[FAIL] expected next_leap_year("<<year<<") to throw "<<typeid(E).name()<<", got " << typeid(err).name() << std::endl;
            fail_cnt++;
        } catch (...) {
            std::cout << "[FAIL] expected next_leap_year("<<year<<") to throw "<<typeid(E).name()<<", got non-standard exception." << std::endl;
            fail_cnt++;
        }
    }

    return std::make_tuple(pass_cnt, fail_cnt);
}