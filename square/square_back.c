#include <math.h>
#include "header.h"

enum NUMBER_OF_ROOTS {
        NO_ROOTS,
        ONE_ROOT,
        TWO_ROOTS,
        INF_ROOTS,
        FAILED_CHECK
};

const double EPSILON = 2.22045e-016;

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
                double d = b*b - 4*a*c; // d - discriminant of equation
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
                return FAILED_CHECK;
        }
        if (!(x1)) {
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
        return abs(first_val - second_val) < EPSILON; //1 if comparison is TRUE and 0 if FALSE
}

