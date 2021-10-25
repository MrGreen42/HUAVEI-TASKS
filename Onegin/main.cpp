#include <stdio.h>
#include <stdlib.h>
#include "Onegin_lib.h"
#include <cstring>

#define CHECK(a) \
    if (Check(a)) { \
        return 0; \
    } \

//function to check errors by returning value of functions
int Check(int error_num);

int main() {

	printf("By Evgenii\n Enter name of source file:\n");
	int error_num = 0;
	
	char filename[256] = {}; // in linux max length of path is 255 bytes(symbols)
	scanf("%s", filename);
	FILE *f = fopen(filename, "rb");
	if (!f) {
		printf("cannot open file\n");
		return 0;;
	}
	int size = FileSize(f); //FileSize() returns number of symbols in text file
    CHECK(size);

	char* buffer = (char*)calloc((size_t)(size + 2), sizeof(char));
	buffer[0] = '\0';
	buffer++;

	error_num = ReadFile(f, buffer, size); //Read text from file to buffer
	CHECK(error_num);


	for (int i = 0; i < size + 1; ++i) {
        if(buffer[i] == '\n') {
            buffer[i] = '\0';
        }
    }

	int num_str = StrCount(buffer, size); //Count number of strings in buffer	
	CHECK(num_str);

    char** str_begin = (char**)calloc((size_t)(num_str + 1), sizeof(char**));
	char** str_end = (char**)calloc((size_t)(num_str + 1), sizeof(char**));
    error_num = FindStr(str_begin, str_end, buffer, size, num_str); 
	CHECK(error_num);
    
	error_num = FindStr(str_begin, str_end, buffer, size, num_str); 
	CHECK(error_num);

	error_num = Sort(str_begin, (size_t)num_str, sizeof(char*), Comparator); // sort
	CHECK(error_num);

	error_num = Sort(str_end, (size_t)num_str, sizeof(char*), RevComparator);
	CHECK(error_num);

	fclose(f);

	f = fopen("result.txt", "w+");
	
	fprintf(f, "Sort by beginnings of strings: \n");
	error_num = Print_Sort(f, str_begin, num_str);
    CHECK(error_num);


	fprintf(f, "\n\nSort by endings of strings:\n");
	error_num = Print_Rev(f, str_end, num_str);
	CHECK(error_num);

	fprintf(f, "\n\nOriginal text:\n");
	error_num = Print_Orig(f, buffer, size);
	CHECK(error_num);

	free(buffer - 1);
	free(str_begin);
	free(str_end);
	fclose(f);
	return 0;
}



int Check(int error_num) {
	switch (error_num) {
		case BAD_FILE: printf("invalid file descriptor\n");
			return 1;
		case BAD_BUFFER: printf("invalid buffer\n");
			return 1;
		case BAD_READ: printf("unsuccesful reading from file\n");
			return 1;
		case BAD_SIZE: printf("invalid size\n");
			return 1;
		case BAD_NUM_STR: printf("invalid number of strings\n");
			return 1;
		case BAD_ARRAY: printf("invalid array of strings\n");
			return 1;
		case BAD_COMPARATOR: printf("invalid pointer to func \"comparator\"\n");
			return 1;
		default: return 0;
	}
}


