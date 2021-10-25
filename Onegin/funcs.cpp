#include <cstdio>
#include "header.h"
#include <stdlib.h>
#include <ctype.h>
#include <cstring>

#define CHECK_FILE \
	if (!f) { \
		return BAD_FILE; \
	} \

#define CHECK_BUFFER \
	if (!buffer) { \
		return BAD_BUFFER; \
	} \

#define CHECK_SIZE \
	if (size < 0) { \
		return BAD_SIZE; \
	} \

#define CHECK_NUM_STR \
	if (num_str < 0) { \
		return BAD_NUM_STR; \
	} \

#define CHECK_ARR(a) \
	if (!a) { \
		return BAD_ARRAY; \
	} \





int FileSize(FILE* f) {
	CHECK_FILE;
	fseek(f, 0, SEEK_END); //place position in the end of file
	int size = (int)ftell(f); // ftell returns number of position
	CHECK_SIZE;
	fseek(f, 0, SEEK_SET); // place position back to the begin
	return size;
}

int ReadFile(FILE* f, char* buffer, int size) {
	CHECK_FILE;
	CHECK_BUFFER;
	CHECK_SIZE;
	int n = (int)fread(buffer, sizeof(char), (size_t)size, f);
	if (n != size) {
		return BAD_READ;
	}
	return 0;
}	

int StrCount(char* buffer, int size) {
	CHECK_BUFFER;
	CHECK_SIZE;
	int num_str = 0;
	for (int k = 0; k < size; k++) {
		if ((buffer[k] == '\0') && (buffer[k+1] != '\0')) {
			num_str++;
		}
	}
	return num_str;
}

int FindStr(char** begin, char** end, char* buffer, int size, int num_str) {
	CHECK_BUFFER;
	CHECK_ARR(begin);
	CHECK_ARR(end);
	CHECK_SIZE;
	CHECK_NUM_STR;
	int curr_str = 0;
	begin[curr_str] = buffer;
	for (int k = 0; k < size; k++) {
		if (buffer[k] == '\0') {
			if ((curr_str <= num_str) && (buffer[k-1] != '\0')) {
				end[curr_str] = &buffer[k - 1];
				curr_str++;
			}
			if ((curr_str <= num_str) && (buffer[k+1] != '\0')) {
				begin[curr_str] = &buffer[k + 1];
			}
		}
	}
	return 0;
}

int Sort(void* arr, size_t num, size_t size,  int (*cmp)(const void* str1, const void* str2)) {
	CHECK_ARR(arr);
	if (!cmp) {
		return BAD_COMPARATOR;
	}
	RecurSort(arr, 0, num, size, cmp);
	return 0;
}

int RecurSort(void* arr, size_t start, size_t end, size_t size,  int (*cmp) (const void* str1, const void* str2)) {
	size_t base = 0;
	if (start < end) {
		base = Partition(arr, start, end, size, cmp); 
		if (base != 0) { 
			RecurSort(arr, start, base - 1, size, cmp);
		}
		RecurSort(arr, base + 1, end, size, cmp);
	}
	return 0;
}

size_t Partition(void* arr, size_t start, size_t end, size_t size, int (*cmp) (const void* str1, const void* str2)) {
	void* base = (char*)arr +  end * size ;
	size_t i = start;
	for (size_t j = start; j < end; j++ ) {
		if (cmp((char*)arr + j * size, base) <= 0) {
			Swap((char*)arr + j * size, (char*)arr + i * size, size);
			i ++;
		}
	}
	Swap((char*)arr + end * size, (char*)arr + i * size, size);
	return i;
}

int Swap(void* val1, void* val2, size_t size) {
	char tmp[size] = {};
	memcpy(tmp, val1, size);
	memcpy(val1, val2, size);
	memcpy(val2, tmp, size);
	
	return 0;
}

int Print_Sort(FILE* f, char** str_begin, int num_str) {
	CHECK_FILE;
	CHECK_ARR(str_begin);
	CHECK_NUM_STR;
	for (int k = 0; k < num_str; k++) {
		fprintf(f, "%s", str_begin[k]);
		fprintf(f,"\n");
	}
	return 0;
}


int Print_Rev(FILE* f, char** str_end, int num_str) {
	CHECK_FILE;
	CHECK_ARR(str_end);
	CHECK_NUM_STR;
	for (int k = 0; k < num_str; k++) {
		while (*(str_end[k]) != '\0') {
			str_end[k]--;
		} 
		fprintf(f, "%s", str_end[k] + 1);
		fprintf(f,"\n");
	}
	return 0;
}


int Print_Orig(FILE* f, char* buffer, int size) {
	CHECK_FILE;
	CHECK_BUFFER;
	CHECK_SIZE;
	for (int k = 0; k < size; k++) {
		fprintf(f, "%c", buffer[k]);
		if (buffer[k] == '\0') {
			fprintf(f, "\n");
		}
	}
	return 0;
}

int Comparator(const void* str1, const void* str2) {
	char* val1 = *(char* const*)str1;
	char* val2 = *(char* const*)str2;
	if (val1 == val2) {
		return 0;
	}
	while (*val1 == *val2) {
		val1++;
		val2++;
	}
	return *val1 - *val2;
}

int RevComparator(const void* str1, const void* str2) {
	char* val1 = *(char* const*)str1;
 	char* val2 = *(char* const*)str2;
	if (val1 == val2) {
		return 0;
	}

	while (!isalpha(*val1)) {
		val1--;
	}
	while (!isalpha(*val2)) {
		val2--;
	}

	while (*val1 == *val2) {
		val1--;
		val2--;
	}
	return *val1 - *val2;
}


