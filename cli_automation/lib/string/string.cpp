#pragma once  
#include <./string.h>  
#include <corecrt_malloc.h>

char* concat(const char* s1, const char* s2)  
{  
	const size_t s1_len = strlen(s1);
	const size_t s2_len = strlen(s2);
	char* result = (char*)malloc(s1_len + s2_len + 1);
	if (!result) return NULL;
	memcpy(result, s1, s1_len);
	memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return result;
}