#pragma once
#include <time.h>

struct tm *presentTime();

size_t intSize(int num);

char* intStr(int num);

int strInt(char* str);

int isTwentiethCentury(unsigned int year);

int getCentury(unsigned int year);

void slice(const void *src, void *dest, int start, int end);
