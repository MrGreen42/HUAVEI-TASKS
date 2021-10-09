#include "header.h"
#include <cassert>

enum ERRORS {
	ERR_OPEN = -1,

};

int FileSize(FILE* f) {
	if (!f) {
		return ERR_OPEN;
	}
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
	for (int k = 0; k < size; k++) {
		if (buffer[k] == '\0') {
			num_str++;
		}
	}
	return num_str;
}

int FindStr(char** begin, char** end, char* buffer, int size, int num_str) {
	int curr_str = 0;
	begin[curr_str] = buffer;
	for (int k = 0; k < size; k++) {
		if (buffer[k] == '\0') {
			end[curr_str] = &buffer[k - 1];
			curr_str++;
			if (curr_str < num_str) {
				begin[curr_str] = &buffer[k + 1];
			}
		}
	}
	return 0;
}

int Sort(char** arr, int num_str, int (*cmp)(const void* str1, const void* str2)) {
	assert(arr);
	assert(cmp);
	qsort(arr, num_str, sizeof(char*), cmp);
	return 0;
}
	

int Print_Sort(FILE* f, char** str_begin, int num_str) {
	
	for (int k = 0; k < num_str; k++) {
		fprintf(f, "%s", str_begin[k]);
		fprintf(f,"\n");
	}
	return 0;
}

int Print_Rev(FILE* f, char** str_end, int num_str) {
	char curr = '\n';
	int n = 0;
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
	for (int k = 0; k < size + 1; k++) {
		fprintf(f, "%c", buffer[k]);
		if (buffer[k] == '\0') {
			fprintf(f, "\n");
		}
	}
	return 0;
}

int Comparator(const void* str1, const void* str2) {
	//assert(0);
	int k = 0;
	while (*(*(char**)str1 + k) == *(*(char**)str2 + k)) {
		k++;
	}
	return *(*(char**)str1 + k) - *(*(char**)str2 + k);
}

int RevComparator(const void* str1, const void* str2) {
	assert(str1);
	assert(str2);
	int k1 = 0, k2 = 0;
	//printf("%d <= %d <= %d\n", (int)'a' , (int)**(char**)str1 , (int)'z');
	if (!(( ('A' <= **(char**)str1) && ( **(char**)str1 <= 'Z')) || ( ('a' <= **(char**)str1) && ( **(char**)str1 <= 'z')) )) {
		k1++;
	}
	if (!(( ('A' <= **(char**)str2) && ( **(char**)str2 <= 'Z')) || ( ('a' <= **(char**)str2) && ( **(char**)str2 <= 'z')) )) {

                k2++;
        }

	printf("str1 p: %p	c0:%c	c1:%c	k1: %d\n", *(char**)str1, **(char**)str1, *(*(char**)str1 - k1), k1);
	printf("str2 p: %p      c0:%c   c1:%c   k2: %d\n\n", *(char**)str2, **(char**)str2, *(*(char**)str2 - k2), k2);


	while (*(*(char**)str1 - k1) == *(*(char**)str2 - k2)) {
                k1++;
		k2++;
        }
	return *(*(char**)str1 - k1) - *(*(char**)str2 - k2);
	
	
}


