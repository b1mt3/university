// fucntion for calculation of radii for cellular and d2d
// input: power of a transmitter(p), thermal noise(n), success threshold(n),
// environment coefficient(b)

double radii(double p, double n, double t, double b)
{
	double radius;
	radius = 0;
	radius = p/(n*t);
	radius = pow(radius, 1/b);
	return radius;
}