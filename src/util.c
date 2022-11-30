#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <util.h>


struct tm *presentTime(){
    time_t seconds_time = time(NULL);
    return localtime(&seconds_time);
}

unsigned int presentYear(){
    struct tm *current_time = presentTime();
    unsigned int year = current_time->tm_year + 1900;
    // Never free struct tm pointer(static variable).
    //free(current_time);
    return year;
}

size_t intSize(int num){
    if(num==0){
        return 1;
    }
    return floor(log10(abs(num))) + 1;
}

char *intStr(int num){
    size_t size = intSize(num);
    char *str = malloc(size+1);
    sprintf(str, "%d", num);
    return str;
}

int strInt(char *str){
    return atoi(str);
}

int *sliceIntArr(const int *arr, int start, int end){
    int size = end-start;
    int *sub_arr = malloc(sizeof(int)*size);
    for (size_t i = start; i < end; i++)
    {
        sub_arr[i-start] = arr[i];
    }
    return sub_arr;
}

char *sliceStr(const char *str, int start, int end){
    int size = end-start;
    char *sub_str = malloc((sizeof(char)*size)+1);
    strncpy(sub_str, str+start, size);
    // Without null termination, it wont be seen string.
    // Dont know if strncpy() does add null to destination.
    *(sub_str+size) = 0;
    return sub_str;
}

bool equalIntArrays(const int *arr, int *sarr, size_t size){
    for (size_t i = 0; i < size; i++){
        if (*(arr+i) != *(sarr+i)){
            return false;
        }
    }
    return true;
}

bool equalStr(const char*first, const char *second){
    // Getting length of string is bad practice.
    // strlen() is likely to be have time complexity of linear(O(n)).
    // Length of string is not stored in any place.
    size_t first_size = strlen(first);
    size_t second_size = strlen(second);
    size_t min_size;
    if(first_size==second_size){
        min_size = first_size<second_size? first_size: second_size;
        // Not need to compare null terminating character.
        return memcmp(first, second, min_size)==0;
    }else{
        return false;
    }
    
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

int randomInt(int start, int end){
    float ratio = (float)rand()/RAND_MAX;
    return (int)(start + ((end-start)*ratio));
}

char *concatStr(const char *first, const char *second){
    int size = strlen(first)+strlen(second);
    char *res_str = malloc(sizeof(char)*(size+10));
    strcpy(res_str, first);
    strcat(res_str, second);
    res_str[size] = '\0'; 
    return res_str;
}

char *fillStr(const char *str, char fill, size_t size){
    size_t fill_size;
    char *fill_str;
    char *filled_str;
    if(size>strlen(str)){
        fill_size = size - strlen(str);
    }else{
        fill_size = 0;
    }
    fill_str = malloc(sizeof(char)*(fill_size+1));
    for (size_t i = 0; i < fill_size; i++)
    {
        fill_str[i] = fill;
    }
    fill_str[fill_size] = '\0'; 
    filled_str = concatStr(fill_str, str);
    free(fill_str);
    return filled_str;
}

void *shrinkMem(void *ptr, size_t size){
    char *new_mem = realloc(ptr, size);
    if(new_mem!=NULL){
        return new_mem;
    }
    return ptr;
}

char *shrinkStr(char *str){
    return shrinkMem(str, strlen(str)+1);
}