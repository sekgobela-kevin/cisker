#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <util.h>


struct tm *presentTime(){
    time_t seconds_time;
    time(&seconds_time);
    return localtime(&seconds_time);
}

unsigned int presentYear(){
    struct tm *current_time = presentTime();
    unsigned int year = current_time->tm_year + 1900;
    free(current_time);
    return year;
}

size_t intSize(int num){
    return floor(log10(abs(num))) + 1;
}

char* intStr(int num){
    char *str = malloc(intSize(num)+1);
    sprintf(str, "%d", num);
    return str;
}

int strInt(char *str){
    return atoi(str);
}

void slice(const void *src, void *dest, int start, int end){
    memcpy(dest, src + start, end - start);
}

char* sliceStr(const char *str, int start, int end){
    int size = end-start+1;
    char *dest = malloc(size);
    strcpy(dest, "");
    slice(str, dest, start, end);
    // Without null termination, it wont be seen string.
    // Dont know if memcpy() does add null to destination.
    //*(dest+size) = '\0';
    return dest;
}

bool equalIntArrays(const int *arr, int *sarr, size_t size){
    for (size_t i = 0; i < size; i++){
        if (*(arr+i) != *(sarr+i)) return 0;
    }
    return 1;
}

unsigned int getCentury(unsigned int year){
    int year_size = intSize(year);
    char *centuary_str;
    char *year_str = intStr(year);
    centuary_str = sliceStr(year_str, 0, year_size-2);
    int century = strInt(centuary_str) + 1;
    free(centuary_str);
    return century;
}

bool isTwentiethCentury(unsigned int year){
    return year>=1900 && year<=1999;
}
