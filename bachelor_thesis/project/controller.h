#include <iostream>
#include <fstream>
#include "solution.h"

using namespace std;

class controller
{
private:
	double *r_mu, **r_covar;
	elps_model *ellips;
public:
	controller(char *resrc)
	{
		ifstream fp_in;
		fp_in.open(resrc, ios::in);
		r_mu = new double [2];
		r_covar = new double * [2];
		for (int i = 0; i <= 1; i++)
		{
			r_covar[i] = new double [2];
		}
		for (int i = 0; i <= 1; i++)
		{
			fp_in >> r_mu[i];
		}
		for (int i = 0; i <= 1; i++)
		{
			for (int j = 0; j <= 1; j++)
			{
				fp_in >> r_covar[i][j];
			}
		}
		ellips = new elps_model (r_mu, r_covar);
	}
	double *init_ellips(double ofset_ang, double constant)
	{
		double *coords;
		coords = ellips->elps_transf(constant,ofset_ang);
		return coords;
	}
	~controller()
	{
		int i;
		delete ellips;
		delete[] r_mu;
		for (i = 0; i < 2; i++)
			delete[] r_covar[i];
		delete[] r_covar;
	}
};