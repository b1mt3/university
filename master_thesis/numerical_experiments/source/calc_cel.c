double cel(double lambda, double r)
{
	double prob, pw, radius;
	radius = 0;
	prob = -1;
	pw = 1;
	radius = pow(r,2);
	pw = (-1)*l*radius*M_PI;
	prob = 1 - exp(pw);
	return prob;
}