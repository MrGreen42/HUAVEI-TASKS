// File header.h
#ifndef HEADER
#define HEADER

/*!-----------------------------------------------------------
Solution of square equation ax^2 + bx + c = 0

\param[in] a coefficient of equation
\param[in] b coefficient of equation
\param[in] c coefficient of equation

\param[out] x1 pointer to the 1st root
\param[out] x2 pointer to the 2st root


\return number of roots

if the number of roots is infinite returns INF_ROOTS
*/

int Solution(double a, double b, double c, double* x1, double* x2);


/*!---------------------------------------------------------
Function for test for one set of numbers

\param[in] test_num number of test
\param[in] a coefficient of equation
\param[in] b coefficient of equation
\param[in] c coefficient of equation
\param[in] ans_nRoots correct number of roots
\param[in] ans_x1 correct answer
\param[in] ans_x2 correct answer

\return 0 if success and 1 if failed, because of enum TESTS_RESULTS
*/

int part_test(int test_num, double a, double b, double c, int ans_nRoots, double ans_x1, double ans_x2);


/*!-----------------------------------------------------------
Function for tests, using function part_test for every particular test

\return sum of returns of part_test 's
\note because every part_test returns 0 if success and 1 if failed, so Test() returns 0 if all tests success and int > 0 if one of them failed
*/

int Test(void);


/*!--------------------------------------------------------
Comparing two double numbers with EPSILON precision

\param [in] first_val 
\param [in] second_val

\return 1 or 0
*/

int Comp_Double(double first_val, double second_val);

/*!-----------------------------------------------------------
Solution of linear  equation bx + c = 0

\param[in] c  coefficient of equation
\param[in] b coefficient of equation

\param[out] x1  pointer to the root

\return number of roots

if the number of roots is infinite returns INF_ROOTS
*/

int Lin_Sol(double b, double c, double* x1);

#endif
