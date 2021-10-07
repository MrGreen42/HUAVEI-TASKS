#include <stdio.h>
#include <stdlib.h>

int FileSize(FILE* f);

int ReadFile(FILE* f, char* buffer);

int StrCount(char* buffer, int size);

int FindStr(char** begin, char** end, char* buffer, int size, int num_str);

int Sort(char** arr, int num_str, int (*cmp)(const void* str1, const void* str2));

int Print_Sort(FILE* f, char** str_begin, int num_str);

int Print_Rev(FILE* f, char** str_end, int num_str);

int Print_Orig(FILE*, char* buffer, int size);

int Comparator(const void* str1, const void* str2);

int RevComparator(const void* str1, const void* str2);


int main() {
	const char* text_r = "norm1.txt";
	const char* text_w = "result1.txt";

	FILE *f = fopen("norm1.txt", "rb");

	int size = FileSize(f); //FileSize() returns number of symbols in text file

	char* buffer = (char*)calloc(size + 1, sizeof(char));

	ReadFile(f, buffer); //Read text from file to buffer

	int num_str = StrCount(buffer, size); //Count number of strings in buffer

	char* str_begin[num_str];
	char* str_end[num_str];

	FindStr(str_begin, str_end, buffer, size, num_str); // add to str_begin[] begins of strings from buffer and add to str_end ends of strings from buffer 

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

	free(buffer);

	fclose(f);

}
