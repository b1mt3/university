#include <math.h>

double radius_calc (double p, double n, double t, double b)
{
	double radius;
	radius = 0;
	radius = p/(n*t);
	radius = pow(radius, 1/b);
	return radius;
}

double cell_perf_calc (double lambda, double r)
{
	double prob, pw, radius;
	radius = 0;
	prob = -1;
	pw = 1;
	radius = pow(r,2);
	pw = lambda*radius*M_PI;
	prob = 1 - (1/exp(pw));
	return prob;
}

double cell_fad_calc (double lambda, double mean, double theta, double noise, double prop, double pw, double r) {
	double cfct, xpn1, xpn2, step_sum, prob_a, prob_b, prob_i, prob;
	double h = 0.001;
	int i, m;

	prob = 0;
	step_sum = 0;
	cfct = 2*lambda*M_PI;
	m = r/h;
	for (i=1; i<=m; i++) {
	  xpn1 = 1/(exp((mean*theta*noise*pow(i*h, prop))/(pw)));
	  xpn2 = 1/exp(lambda*M_PI*pow(i*h, 2));
	  prob_i = cfct*xpn1*xpn2*(i*h);
	  step_sum += prob_i;
	}

	xpn1 = 1/(exp((mean*theta*noise)/(pw)));
	xpn2 = 1/exp(lambda*M_PI);
	prob_a = cfct*xpn1*xpn2;

	xpn1 = 1/(exp((mean*theta*noise*pow(r, prop))/(pw)));
	xpn2 = 1/exp(lambda*M_PI*pow(r, 2));
	prob_b = cfct*xpn1*xpn2*r;

	prob = h*(2*step_sum + prob_a + prob_b)/2;
    return prob;
}
