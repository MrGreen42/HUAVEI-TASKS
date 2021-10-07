#include "header.h"

int FileSize(FILE* f) {
	fseek(f, 0, SEEK_END); //place position in the end of file
	int size = ftell(f); // ftell returns number of position
	fseek(f, 0, SEEK_SET); // place position back to the begin
	return size;
}

int ReadFile(FILE* f, char* buffer, int size) {
	size_t n = fread(buffer, sizeof(char), size, f);
	return n;
}	

int StrCount(char* buffer, int size) {
	int num_str = 0;
	for (int k = 0; k < size + 1; k++) {
		if (buffer[k] == '\n') {
			num_str++;
		}
	}
	return num_str;
}

int FindStr(char** begin, char** end, char* buffer, int size, int num_str) {
	int curr_str = 0;
	begin[curr_str] = buffer;
	for (int k = 0; k < size + 1; k++) {
		if (buffer[k] == '\n') {
			end[curr_str] = &buffer[k];
			curr_str++;
			if (curr_str < num_str) {
				begin[curr_str] = &buffer[k + 1];
			}
		}
	}
	return 0;
}

int Sort(char** arr, int num_str, int (*cmp)(const void* str1, const void* str2));

int Print_Sort(FILE* f, char** str_begin, int num_str);

int Print_Rev(FILE* f, char** str_end, int num_str);

int Print_Orig(FILE*, char* buffer, int size);

int Comparator(const void* str1, const void* str2);

int RevComparator(const void* str1, const void* str2);

