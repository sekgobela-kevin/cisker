#pragma once
#include <time.h>
#include <stdbool.h>

struct tm *presentTime();

unsigned int presentYear();

size_t intSize(int num);

char *intStr(int num);

int strInt(char *str);

int *sliceIntArr(const int *arr, int start, int end);

char *sliceStr(const char *str, int start, int end);

bool equalIntArrays(const int *arr, int *sarr, size_t size);

unsigned int getCentury(unsigned int year);

bool isTwentiethCentury(unsigned int year);

int randomInt(int start, int end);

char *concatStr(const char *first, const char *second);

char *fillStr(const char *str, char fill, size_t size);

bool equalStr(const char*first, const char *second);

void *shrinkMem(void *ptr, size_t size);

char *shrinkStr(char *str);
