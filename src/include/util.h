#pragma once
#include <time.h>
#include <stdbool.h>

struct tm *presentTime();

unsigned int presentYear();

size_t intSize(int num);

char* intStr(int num);

int strInt(char* str);

void slice(const void *src, void *dest, int start, int end);

char* sliceStr(const char *str, int start, int end);

bool equalIntArrays(const int *arr, int *sarr, size_t size);

unsigned int getCentury(unsigned int year);

bool isTwentiethCentury(unsigned int year);
