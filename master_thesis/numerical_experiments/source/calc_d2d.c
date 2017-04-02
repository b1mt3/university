double (*int_func)(double lu, double lb, double r, double r1, double r2)
{
	double fval;
	double area, dens, prob;
	area = -1;
	dens = -1;
	prob = -1;
	area = pow(r2,2)*(1/(cos((pow(r,2)+pow(r2,2)-pow(r1,2))/2*r*r2));
	area += pow(r1,2)*(1/(cos((pow(r,2)+pow(r1,2)-pow(r2,2))/2*r*r1));
	area -= (1/2)*sqrt((r2+r1-r)*(r+r2-r1)*(r-r2+r1)*(r+r1+r2));
	dens = 2*lb*M_PI*r;
	dens *= exp((-1)*lb*M_PI*r*r);
	prob = 1 - exp((-1)*lu*area);
	fval = prob*dens;
	return fval;
}

typedef double (*int_func)(double lu, double lb, double r, double r1, double r2);

double calc_dev(double lu, double lb, double r1, double r2, double n, int_func f)
{
	double h = ((r1+r2)-r1) / n;
	double sum1 = 0;
	double sum2 = 0;
	int i;
	for(i = 0;i < n;i++)
      sum1 += f(lu, lb, r1 + h * i + h / 2.0, r1, r2);
 
    for(i = 1;i < n;i++)
      sum2 += f(lu, lb, r1 + h * i, r1, r2);
 
    prob = h / 6.0 * (f(lu,lb,r1,r1,r2) + f(lu,lb,r1+r2,r1,r2) + 4.0 * sum1 + 2.0 * sum2);
	
	return prob;
}