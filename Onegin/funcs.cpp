
int FileSize(FILE* f) {
	if (!f) {
		return BAD_FILE;
	}
	fseek(f, 0, SEEK_END); //place position in the end of file
	int size = ftell(f); // ftell returns number of position
	if (size < 0) {
                return BAD_SIZE;
        }
	fseek(f, 0, SEEK_SET); // place position back to the begin
	return size;
}

int ReadFile(FILE* f, char* buffer, int size) {
	if (!f) {
                return BAD_FILE;
        }
	if (!buffer) {
                return BAD_BUFFER;
        }

	size_t n = fread(buffer, sizeof(char), size, f);
	if (n != size) {
                return BAD_READ;
        }
	return 0;
}	

int StrCount(char* buffer, int size) {
	if (!buffer) {
                return BAD_BUFFER;
        }
	if (size < 0) {
                return BAD_SIZE;
        }
	int num_str = 0;
	for (int k = 0; k < size; k++) {
		if (buffer[k] == '\0') {
			num_str++;
		}
	}
	return num_str;
}

int FindStr(char** begin, char** end, char* buffer, int size, int num_str) {
	if (!buffer) {
                return BAD_BUFFER;
        }
	if ((!begin) || (!end)) {
                return BAD_ARRAY;
        }
	if (size < 0) {
                return BAD_SIZE;
        }
	if (num_str < 0) {
                return BAD_NUM_STR;
        }
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
	if (!arr) {
                return BAD_ARRAY;
        }
	if (num_str < 0) {
                return BAD_NUM_STR;
        }
	if (!cmp) {
                return BAD_COMPARATOR;
        }
	qsort(arr, num_str, sizeof(char*), cmp);
	return 0;
}
	

int Print_Sort(FILE* f, char** str_begin, int num_str) {
	if (!f) {
                return BAD_FILE;
        }
	if (!str_begin) {
                return BAD_ARRAY;
        }
        if (num_str < 0) {
                return BAD_NUM_STR;
        }
	for (int k = 0; k < num_str; k++) {
		fprintf(f, "%s", str_begin[k]);
		fprintf(f,"\n");
	}
	return 0;
}

int Print_Rev(FILE* f, char** str_end, int num_str) {
	if (!f) {
                return BAD_FILE;
        }
        if (!str_end) {
                return BAD_ARRAY;
        }
        if (num_str < 0) {
                return BAD_NUM_STR;
        }
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
	if (!f) {
                return BAD_FILE;
        }
        if (!buffer) {
                return BAD_BUFFER;
        }
        if (size < 0) {
                return BAD_SIZE;
        }
	for (int k = 0; k < size + 1; k++) {
		fprintf(f, "%c", buffer[k]);
		if (buffer[k] == '\0') {
			fprintf(f, "\n");
		}
	}
	return 0;
}

int Comparator(const void* str1, const void* str2) {
	int k = 0;
	while (*(*(char**)str1 + k) == *(*(char**)str2 + k)) {
		k++;
	}
	return *(*(char**)str1 + k) - *(*(char**)str2 + k);
}

int RevComparator(const void* str1, const void* str2) {
	int k1 = 0, k2 = 0;
	while (!(( ('A' <= *(*(char**)str1 - k1)) && ( *(*(char**)str1 - k1) <= 'Z')) || ( ('a' <= *(*(char**)str1 - k1)) && ( *(*(char**)str1 - k1) <= 'z')) )) {
		k1++;
	}
	while (!(( ('A' <= *(*(char**)str2 - k2)) && ( *(*(char**)str2 - k2) <= 'Z')) || ( ('a' <= *(*(char**)str2 - k2)) && ( *(*(char**)str2 - k2) <= 'z')) )) {

                k2++;
        }
	while (*(*(char**)str1 - k1) == *(*(char**)str2 - k2)) {
                k1++;
		k2++;
        }
	return *(*(char**)str1 - k1) - *(*(char**)str2 - k2);
}


