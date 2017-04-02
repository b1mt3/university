#include <math.h>

double area_over (double r1, double r2, double r) {
	double area, arccosine1, arccosine2, exp1, exp2, exp3;

	arccosine1 = (pow(r,2) + pow(r2,2) - pow(r1,2)) / (2*r*r2);
	arccosine1 = acos(arccosine1);
	exp1 = pow(r2,2)*arccosine1;

	arccosine2 = (pow(r,2) + pow(r1,2) - pow(r2,2)) / (2*r*r1);
	arccosine2 = acos(arccosine2);
	exp2 = pow(r1,2)*arccosine2;

	exp3 = (r2+r1-r)*(r+r2-r1)*(r-r2+r1)*(r+r1+r2);
	exp3 = sqrt(exp3);
	exp3 = exp3/2;

	area = exp1 + exp2 - exp3;
	return area;
}

double int_func (double lu, double lb, double r, double area) {
	double fval, circle, exp1, exp2;

	circle = M_PI*pow(r,2);
	exp1 = 2*lb*M_PI*r;
	exp1 = exp1/exp(lb*circle);

	exp2 = exp(lu*area);
	exp2 = 1/exp2;
	exp2 = 1 - exp2;

	fval = exp1*exp2;
	return fval;
}

double calc_dev (double lu, double lb, double a, double b, double area) {
	double h = 0.001;
	double sum = 0;
	double prob = -1;
	int i, m;

	m = (b-a)/h;
	for (i=1; i<=m; i++) {
		sum += int_func (lu, lb, a+i*h, area);
	}
	prob = h*(int_func(lu, lb, a, area) + 2.0*sum + int_func(lu, lb, b, area))/2.0;
	return prob;
}
