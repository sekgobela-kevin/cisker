#include <stdlib.h>

#include <filter.h>
#include <analyse.h>
#include <util.h>


int *filterStudentNumbers(int *student_numbers, SNumsInfo students_info,
                          size_t size)
{
    int *valid_student_numbers = malloc(sizeof(int)*size);
    int index = 0;
    for (size_t i = 0; i < size; i++){
        if (studentNumberValid(student_numbers[i], students_info)){
            valid_student_numbers[index] = student_numbers[i];
            index++;
        }   
    }
    return shrinkMem(valid_student_numbers, sizeof(int)*index);
}

// int readStudentNumbers(char *filename, SNumsInfo students_info){
//     char buffer[BUFSIZ];
//     FILE *fp = fopen(filename, "r");
//     if(ferror(fp)){
//         perror("FileError");
//         return 0;
//     }
//     fseek(fp, SEEK_END, 0);
//     size_t fp_size = ftell(fp);
//     fseek(fp, SEEK_SET, 0);
//     size_t student_nums_size = studentNumbersSize(students_info);
//     size_t *valid_student_numbers = malloc(student_nums_size);
//     int index = 0;
//     for(;;){
//         char *line = fgets(buffer, 100, fp);
//         if(line!=NULL){
//             //valid_student_numbers[index] = 
//         }
//     }
//     return 0;
// }
