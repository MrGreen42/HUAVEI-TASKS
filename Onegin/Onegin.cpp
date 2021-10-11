#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "funcs.cpp"
#include <cstring>

int Check(int error_num);

int main() {
	int error_num = 0;

	FILE *f = fopen("norm1.txt", "rb");
	if (!(f)) {
		printf("cannot open file\n");
		return 0;;
	}
	int size = FileSize(f); //FileSize() returns number of symbols in text file
	if (Check(size)) {
		return 0;;
	}

	char* buffer = (char*)calloc(size + 2, sizeof(char));
	buffer[0] = '\0';
	buffer++;

	error_num = ReadFile(f, buffer, size); //Read text from file to buffer
	if (Check(error_num)) {
                return 0;;
        }


	for (int i = 0; i < size+1; ++i) {
       		if(buffer[i] == '\n') {
            		buffer[i] = '\0';
      		}
    	}

	int num_str = StrCount(buffer, size); //Count number of strings in buffer	
	if (Check(num_str)) {
                return 0;;
        }

	char* str_begin[num_str];
	char* str_end[num_str+1];
	
	error_num = FindStr(str_begin, str_end, buffer, size, num_str); // add to str_begin[] begins of strings from buffer and add to str_end ends of strings from buffer 
	if (Check(error_num)) {
                return 0;;
        }

	error_num = Sort(str_begin, num_str, Comparator); // sort
	if (Check(error_num)) {
                return 0;;
        }

	error_num = Sort(str_end, num_str, RevComparator);
	if (Check(error_num)) {
                return 0;;
        }

	fclose(f);

	f = fopen("result.txt", "w+");
	
	fprintf(f, "Sort by beginnings of strings: \n");
	error_num = Print_Sort(f, str_begin, num_str);
	if (Check(error_num)) {
                return 0;
        }



	fprintf(f, "\n\nSort by endings of strings:\n");
	error_num = Print_Rev(f, str_end, num_str);
	if (Check(error_num)) {
                return 0;;
        }

	fprintf(f, "\n\nOriginal text:\n");
	error_num = Print_Orig(f, buffer, size);
	if (Check(error_num)) {
                return 0;
        }

	free(buffer - 1);

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


