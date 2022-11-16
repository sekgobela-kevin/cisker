#pragma once
#include <time.h>

struct tm *presentTime();

size_t intSize(int num);

char* intStr(int num);

int strInt(char* str);

void slice(const void *src, void *dest, int start, int end);

char* sliceStr(const char *str, int start, int end);

int equalIntArrays(const int *arr, int *sarr, size_t size);

int isTwentiethCentury(unsigned int year);

int getCentury(unsigned int year);
