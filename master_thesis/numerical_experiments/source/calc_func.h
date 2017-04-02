double cel(double lambda, double r);
double radii(double p, double n, double t, double b);
double (*int_func)(double lu, double lb, double r, double r1, double r2);
double calc_dev(double lu, double lb, double r1, double r2, double n, int_func f);