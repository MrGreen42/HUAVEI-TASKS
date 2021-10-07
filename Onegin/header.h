// File header


/*!-----------------------------------------------------------
Find number of symbols in text from file 

\param[in] f file descriptor of file

\param[out] size number of symbols in text

\return code of error

\note if return value < 0 it is error and the value is its code
*/
int FileSize(FILE* f);

/*!-----------------------------------------------------------
Fills the buffer with symbols from file

\param[in] f file descriptor of file
\param[in] buffer array of char 

\return code of error

\note if return value < 0 it is error and the value is its code
*/
int ReadFile(FILE* f, char* buffer, int size);

/*!-----------------------------------------------------------
Counts number of strings in buffer 

\param[in] buffer array of symbols
\param[in] size number of symbols in buffer

\param[out] size number of symbols in text

\return code of error

\note if return value < 0 it is error and the value is its code
*/
int StrCount(char* buffer, int size);

int FindStr(char** begin, char** end, char* buffer, int size, int num_str);

int Sort(char** arr, int num_str, int (*cmp)(const void* str1, const void* str2));

int Print_Sort(FILE* f, char** str_begin, int num_str);

int Print_Rev(FILE* f, char** str_end, int num_str);

int Print_Orig(FILE*, char* buffer, int size);

int Comparator(const void* str1, const void* str2);

int RevComparator(const void* str1, const void* str2);

