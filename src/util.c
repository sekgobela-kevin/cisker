#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tm *presentTime(){
    time_t seconds_time;
    struct tm *time_object;
    time(&seconds_time);
    return localtime(&seconds_time);
}

size_t intSize(int num){
    return floor(log10(abs(num))) + 1;
}

char* intStr(int num){
    static char str[12];
    sprintf(str, "%d", num);
    return str;
}

int strInt(char *str){
    return atoi(str);
}

void slice(const void *src, void *dest, int start, int end){
    memcpy(dest, src + start, end - start);
}

int getCentury(unsigned int year){
    char *centuary_str;
    char *year_str = intStr(year);
    int year_size = intSize(year);
    slice(year_str, centuary_str, 0, year_size-2);
    return strInt(centuary_str)-1;
}

int isTwentiethCentury(unsigned int year){
    return year >= 1900 || year <= 1999;
}