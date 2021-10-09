#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "funcs.cpp"
#include <cstring>

int main() {
	FILE *f = fopen("norm1.txt", "rb");

	int size = FileSize(f); //FileSize() returns number of symbols in text file

	char* buffer = (char*)calloc(size + 3, sizeof(char));
	buffer[0] = '\0';
	buffer++;

	ReadFile(f, buffer, size); //Read text from file to buffer

	for (int i = 0; i < size+2; ++i) {
       		if(buffer[i] == '\n') {
            		buffer[i] = '\0';
      		}
    	}

	int num_str = StrCount(buffer, size); //Count number of strings in buffer	
	printf("size %d,  num_str %d \n", size, num_str);

	char* str_begin[num_str];
	char* str_end[num_str+1];
	
	FindStr(str_begin, str_end, buffer, size, num_str); // add to str_begin[] begins of strings from buffer and add to str_end ends of strings from buffer 
	
	for (int i = 0; i < num_str; i++) {
		printf("%p %p\n", str_begin[i], str_end[i]);
	}
	
	Sort(str_begin, num_str, Comparator); // sort
	
	Sort(str_end, num_str, RevComparator);
	
	fclose(f);

	f = fopen("result.txt", "w+");
	fprintf(f, "Sort by beginnings of strings: \n");
	Print_Sort(f, str_begin, num_str);


	fprintf(f, "\n\nSort by endings of strings:\n");
	Print_Rev(f, str_end, num_str);
	fprintf(f, "\n\nOriginal text:\n");
	Print_Orig(f, buffer, size);

	free(buffer - 1);

	fclose(f);

}
