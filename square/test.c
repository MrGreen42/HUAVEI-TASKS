#include <stdio.h>
#include <math.h>
#include "header.h"
#include "square_back.c"

enum TESTS_RESULTS {
        TEST_SUCCESS,
        TEST_FAILED
};

int main(void) {
	if (!Test()) {
                printf("Tests completed \n");
        }
        return 0;
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
		printf("Test %d OK\n", test_num);
                return TEST_SUCCESS;
        }
        if (!(Comp_Double(x1, ans_x1))) {      // (Comp_Double() - 1) is the same to the negative Comp_Double()
                printf("Test %d failed. First root x1 = %lg, should be %lg \n", test_num, x1, ans_x1);
                return TEST_FAILED;
        }
        if (nRoots == 1) { // if there is one root it is useless to check x2
		printf("Test %d OK\n", test_num);
               return TEST_SUCCESS;
        }
        if (Comp_Double(x2, ans_x2) - 1) {
                printf("Test %d failed. Second root x2 = %lg, should be %lg \n", test_num, x2, ans_x2);
                return TEST_FAILED;
        }
	printf("Test %d OK\n", test_num);
        return TEST_SUCCESS;
}

