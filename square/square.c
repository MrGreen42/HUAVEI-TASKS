#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "header.h"

enum NUMBER_OF_ROOTS {
	NO_ROOTS,
	ONE_ROOT,
	TWO_ROOTS,
	INF_ROOTS,
	FAILED_CHECK
};

enum TESTS_RESULTS {
	TEST_SUCCESS,
	TEST_FAILED
};

const double EPSILON = 2.22045e-016;

int main(void) {
	printf("Solver of square equation\n #(c) Evgenii\n");
	
	if (!Test()) {
		printf("Tests completed \n");
	}
	else {
		return 0;
	}

	printf("Enter coefficients a, b, c:");
	double a = NAN, b = NAN, c = NAN;
	if ((scanf("%lg %lg %lg", &a, &b, &c)) != 3) {
		printf("You have to enter three numbers - coefficients of square equation \n");
		return 0;
	}

	double x1 = 0, x2 = 0;
	int nRoots = Solution(a, b, c, &x1, &x2);
	
	switch (nRoots) {
		case NO_ROOTS: printf("No roots\n");
			break;
		case ONE_ROOT: printf("The only one root x = %lg \n", x1);
			break;
		case TWO_ROOTS: printf("Two roots: x1 = %lg, x2 = %lg \n", x1, x2);
			break;
		case INF_ROOTS: printf("Any number is a root \n");
			break;
		case FAILED_CHECK: printf("Something went wrong, plese try again \n");
			break;
		default: printf("ERROR: nRoots = %d \n", nRoots);
			 return 1;
	}
	return 0;
}

int Solution(double a, double b, double c, double* x1, double* x2) {

        if (!((isfinite(a)) && (isfinite(b)) && (isfinite(c)))) {
		return FAILED_CHECK;
	}
	if (!(x1 && x2 && (x1 != x2))) {
		return FAILED_CHECK;
        }

        if (Comp_Double(a, 0)) {
                return Lin_Sol(b, c, x1);
        }
        else { //if a != 0
                double d = b * b - 4 * a *c; // d - discriminant of equation
                if (Comp_Double(d, 0)) {
			*x1 = -b / (2*a);
                        return ONE_ROOT;
                }
                else if  (d < 0) {
                        return NO_ROOTS;
                }
                else { // id d > 0
                        double sq_d = sqrt(d); //shortening countings for x1 and x2
                        double a2 = 2*a; //shortening countings for x1 and x2
                        *x1 = (-b - sq_d) / a2;
                        *x2 = (-b + sq_d) / a2;
                        return TWO_ROOTS;
                }
        }
}


int Lin_Sol(double b, double c, double* x1) {
	if (!((isfinite(b)) && (isfinite(c)))) {
                printf("Please, try again and enter tree numbers\n");
                return FAILED_CHECK;
        }
        if (!(x1)) {
                printf("Something went wrong, plese try again \n");
                return FAILED_CHECK;
        }

        if (Comp_Double(b, 0)) {
                if (Comp_Double(c, 0)) {
                        return INF_ROOTS;
                }
                else {
                        return 0;
                }
        }
        else { //if b != 0
                *x1 = -c / b;
                return ONE_ROOT;
        }
}

int Comp_Double(double first_val, double second_val) {
        if (abs(first_val - second_val) < EPSILON) {
                return 1;// numbers are equal
        }
        else {
                return 0;// numbers are not equal
        }
}

int Test(void) {
	int sum_of_returns = 0;
        sum_of_returns += part_test(1, 0, 0, 0, INF_ROOTS, 0, 0);
        sum_of_returns += part_test(2, 1, 2, 1, 1, -1, -1);
        sum_of_returns += part_test(3, 0, 1, 1, 1, -1, 0);
        sum_of_returns += part_test(4, 1, 2, 2, 0, 0, 0);
        sum_of_returns += part_test(5, 1, -5, 6, 2, 2, 3);
	return sum_of_returns;
}


int part_test(int test_num, double a, double b, double c, int ans_nRoots, double ans_x1, double ans_x2) {
        double x1 = 0, x2 = 0;
        int nRoots = Solution(a, b, c, &x1, &x2);
        if (nRoots != ans_nRoots) {
                printf("Test %d failed. nRoots = %d, should be %d \n", test_num, nRoots, ans_nRoots);
                return TEST_FAILED;
        }
        if (nRoots == INF_ROOTS) { //  in this case it is useless to check roots
                return TEST_SUCCESS;
        }
        if (Comp_Double(x1, ans_x1) - 1) {      // (Comp_Double() - 1) is the same to the negative Comp_Double()
                printf("Test %d failed. First root x1 = %lg, should be %lg \n", test_num, x1, ans_x1);
                return TEST_FAILED;
        }
        if (nRoots == 1) { // if there is one root it is useless to check x2
               return TEST_SUCCESS;
        }
        if (Comp_Double(x2, ans_x2) - 1) {
                printf("Test %d failed. Second root x2 = %lg, should be %lg \n", test_num, x2, ans_x2);
                return TEST_FAILED;
        }
	return TEST_SUCCESS;
}

