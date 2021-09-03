#ifndef CODE_H
#define CODE_H

/*
parameters
    year: a year in the range [1582, 2147483647]
returns the next leap year (including the input year)
throws
    std::invalid_argument if the input is out of bounds
    std::out_of_range if the next leap year would overflow int
*/
int next_leap_year(int year);

#endif  // CODE_H