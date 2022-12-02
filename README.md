# Cisker
Analyses University of Limpopo(UL) student numbers with C programming.
Its more than just analysing student numbers but it can generate student
numbers and regular expression pattern for matching them. 

Student numbers of 20th century are supported in which year is 
represented by 2 digits as caused by [Year 2000 problem](https://en.wikipedia.org/wiki/Year_2000_problem). 

See this [article](https://www.linkedin.com/pulse/analysing-university-limpopo-student-numbers-python-kevin-sekgobela/)
for more about ULIM student numbers.
See python implementation [ulsid](https://github.com/sekgobela-kevin/ulsid/)

## Linking
Cisker does not currently have any released library or provide a way 
to install one into your system. The easiest way to link cisker to your code is to 
add as it subdirectory or build it with [Cmake](https://cmake.org/).

### Including Cisker
Using git submodule seems to be the easiest and reliable solution.  
See including CMake projects with [git submodules](https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html).

Clone or create submodule into extern/ directory, add cisker
as subdirectory and then link to it.
```cmake
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/cisker"))
target_link_libraries(your_project PRIVATE cisker)
```

There are other ways for [including CMake projects](https://cliutils.gitlab.io/modern-cmake/chapters/projects.html).

### Existing built library
Not release yet

## Building
```bash
git clone https://github.com/sekgobela-kevin/cisker.git
cd cisker
mkdir build
cmake -S . -B build
cmake --build build --target cisker
```
See more on [building and running](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html) CMake project.


## Testing
Tests were written using [Check](https://github.com/libcheck/check)
unit tests framework. Tests can be built into their own executable 
which can be executable to see results of tests.
```
cmake --build build --target tests
build/tests.exe
```

## Usage
Information about student numbers is needed to successfully analyse 
them. This can include their years, capacity for each year and other 
useful data that may influence student numbers structure.

This creates default information which is compliant to current ULIM
student numbers. Default values for the structure attributes are the 
same as those assigned.
```C
#include <cisker.h> 
#include <stdbool.h>

SNumsInfo students_info = createStudentsInfo();
students_info.start_year = 1959;
students_info.end_year = 2023; // current_year + 1
students_info.year_capacity = 100000;
students_info.min_pos = 0;
students_info.start_pos = 0; // relative to min_pos
students_info.end_pos = 99999; // relative to year_capacity
students_info.strict = false;
```

>`strict` controls if student numbers should be ULIM compliant by causing
>year part for 20th century student numbers to be represented by 2 digits.

Determining validity for student number is the main objection of Cisker.
Student number is only valid if it satisfies conditions of student
numbers information.

```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
studentNumberValid(2022090451, students_info);// true
studentNumberValid(12345, students_info);// false
students_info.end_year = 2010;
studentNumberValid(2022090451, students_info);// false
```

Extracts year and application position for student number as integers.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
extractYear(2022090451, students_info);// 2022
extractPos(2022090451, students_info);// 90451

extractYear(8405384, students_info);// 1984
extractPos(8405384, students_info);// 5384
```

Year and position can be extracted without being transformed in form 
of null terminated string. The returned strings are dynamically 
allocated and will need to be manually freed after use.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
extractYearPart(2022090451, students_info);// "2022"
extractPos(2022090451, students_info);// "090451"

extractYear(8405384, students_info);// "84"
extractPos(8405384, students_info);// "05384"
```
> Year and position part strings need to be manually freed after use.


Previous and next student number can be created from existing student 
student number. Zero is expected if current student number or resulting 
student number is not valid.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
nextStudentNumber(202200000, students_info);// 202200001
nextStudentNumber(202299999, students_info);// 20230000

previousStudentNumber(202200001, students_info);// 202200000
previousStudentNumber(20230000, students_info);// 202299999
```

Total  student numbers left can be detected which may be useful when 
getting next or previous student numbers.

```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
students_info.start_year = 2022;
startDistance(202200000, students_info);// 0
startDistance(202299999, students_info);// 99999

endDistance(202200000, students_info);// 99999
endDistance(202299999, students_info);// 0
```

Maximum and minimum digits for student numbers can be detected also
total student numbers in range.

```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
studentNumbersMinSize(students_info);// 7;
studentNumbersMaxSize(students_info);// 9;

students_info.start_year = 2020;
students_info.start_year = 2022;
totalStudentNumbers(students_info);// 300000;
```

Student number can be created from random or existing year and position.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
guessStudentNumber(students_info);// 88174528;
guessStudentNumber(students_info);// 200504620;

createStudentNumber(2021, 34004, students_info)// 202134004
createStudentNumber(1964, 34004, students_info)// 6434004
createStudentNumber(2021, 483, students_info)// 202100483
```

Regular expressions for matching certain student numbers can 
be created. Its not guaranteed to match only valid student numbers 
but guaranteed to match all valid student numbers.

Pattern can be improved by being restrictive on student numbers
to be matched. Smaller position and years range can improve created
regex and ensure it matches only expected digits.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
students_info.end_year = 2022;
createPattern(students_info);// "(([5-9]\\d)|(20[0-2]\\d))|([0-9]\\d{4})"
students_info.status = false;
createPattern(students_info);// "([1-2]\\d{3})|([0-9]\\d{4})"
```

The regex is too large but it was split into 2 groups being pattern
for year part and position part. It takes tricks to generate the 
regex and efforts to simplify it.

> Regex string is dynamically allocated(needs to be manually freed).

Year can be converted into year part for student numbers also for 
position part and vice-verse.
```C
#include <cisker.h> 

SNumsInfo students_info = createStudentsInfo();
toYearPart(1966, students_info); // "66"
toYearPart(2010, students_info); // "2010"
toYear("66", students_info); // 1966
toYear("2010", students_info); // 2010

toPosPart(9357, students_info); // "09357"
toPosPart(40, students_info); // "00040"
toPos("09357", students_info); // 9357
toPos("00040", students_info); // 40
```
> Year and position part strings need to be freed manually.

## Note
Cisker is still under development(use at your own risk).

## Other Implementations
- python [ulsid](https://github.com/sekgobela-kevin/ulsid/)

## License
Cisker is released as open-source under conditions of 
[LGPL-3.0](https://github.com/sekgobela-kevin/cisker/blob/main/LICENSE) license.
