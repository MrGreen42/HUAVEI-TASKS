#include <stdio.h>
#include <math.h>
#include "header.h"
#include "square_back.c"

int main(void) {
	printf("Solver of square equation\n #(c) Evgenii\n");
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
