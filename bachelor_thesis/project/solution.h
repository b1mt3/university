class elps_model
{
private:
	double *mu, *lambda, *matr_turn, *new_coords, *S, prob;
	double **covar, **covar_reverse;
	int counter_S;
public:
	int lagrange_method(double a, double b, double c, double d, double e, double f)
	{
		printf("%lfx^2 + %lfxy + %lfy^2 + %lfx + %lfy + %lf = 0\n", a,2*b,c,2*d,2*e,f);
		printf("starting lagrange process...\n");
		printf("Step#1:\t%lf(x + %lf)^2 + %lfy^2 + %lfx + %lfy + %lf = 0\n",a,b/a,(c-(pow(b,2)/a)),2*d,2*e,f);
		printf("Step#2:\t(%lf(x + %lfy))^2 + %lfy^2 + %lfx + %lfy + %lf = 0\n",sqrt(a),b/a,sqrt(c-(pow(b,2)/a)),2*d,2*e,f);
		printf("Step#3:\tSubstitution - (1)<x'=%lf(x + %lfy)>\t(2)<y'=%lfy>\n",sqrt(a),b/a,sqrt(c-(pow(b,2)/a)));
		printf("Step#4:\t(x' + %lf)^2 + (y' + %lf)^2 = %lf\n",d/sqrt(a),(a*e-b*d)/(a*sqrt(c-(pow(b,2)/a))),(pow(d,2)/a)+(pow(a*e-b*d,2))/(pow(a,2)*(c-pow(b,2)/a))-f);
		printf("Step#5:\tSubstituition - (3)<x\"=x' + %lf>\t(4)<y\"=y'+%lf>\n",d/sqrt(a),(a*e-b*d)/(a*sqrt(c-(pow(b,2)/a))));
		printf("Step#6(equation of a circle):\tx\"^2 + y\"^2 = %lf\n",(pow(d,2)/a)+(pow(a*e-b*d,2))/(pow(a,2)*(c-pow(b,2)/a))-f);
		printf("Step#7:\tReverse substitution: - (5)<x\" = %lfx + %lfy + %lf>\t(6)<y\" = %lfy + %lf>\n", sqrt(a), b/sqrt(a), d/sqrt(a), sqrt(c-(pow(b,2)/a)), (a*e-b*d)/(a*sqrt(c-(pow(b,2)/a))));
		printf("Step#8:\t(%lfx + %lfy + %lf)^2 + (%lfy + %lf)^2 = %lf\n",sqrt(a), b/sqrt(a), d/sqrt(a), sqrt(c-(pow(b,2)/a)), (a*e-b*d)/(a*sqrt(c-(pow(b,2)/a))),(pow(d,2)/a)+(pow(a*e-b*d,2))/(pow(a,2)*(c-pow(b,2)/a))-f);
		return 0;
	}

	void set_covar(double **covar_in)
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
			{
				covar[i][j] = covar_in[i][j];
			}
	}

	void set_mu(double *val)
	{
		for (int i = 0; i < 2; i++)
		{
			mu[i] = val[i];
		}
	}

	int calc_rvs_cov(double **mass, double **M_obr, int cnt_str)
	{
		int i, j, k;
		for(i = 0;i < cnt_str; i++)
		{
			for(j = 0; j < cnt_str; j++) M_obr[i][j] = 0;
			M_obr[i][i]=1;
		}
		//прямой ход методом Гаусса
		double a, b;
		for(i = 0; i < cnt_str; i++)
		{
			a = mass[i][i];
			for(j = i + 1; j < cnt_str; j++)
			{
				b = mass[j][i];
				for(k = 0;k < cnt_str; k++)
				{
					mass[j][k] = mass[i][k]*b - mass[j][k]*a;
					M_obr[j][k] = M_obr[i][k]*b - M_obr[j][k]*a;
				}
			}
		}
		//обратный ход вычисления элементов обратной матрицы
		double sum;
		for(i = 0; i < cnt_str; i++)
		{
			for(j = cnt_str - 1; j >= 0; j--)
			{
				sum = 0;
				for(k = cnt_str - 1; k > j; k--)
					sum += mass[j][k]*M_obr[k][i];
				if(mass[j][j] == 0)
				{
					for(i = 0;i < cnt_str; i++)
						delete []M_obr[i];
					delete []M_obr;
					return 0;
				}
				M_obr[j][i] = (M_obr[j][i] - sum)/mass[j][j];
			}
		}
		return 1;
	}

	double *get_lambda()
	{
		lambda[0] = ((covar_reverse[0][0] + covar_reverse[1][1]) + (sqrt(pow((covar_reverse[0][0] + covar_reverse[1][1]), 2) - 4 * (covar_reverse[0][0] * covar_reverse[1][1] - pow((covar_reverse[0][1]), 2))))) / 2;
		lambda[1] = ((covar_reverse[0][0] + covar_reverse[1][1]) - (sqrt(pow((covar_reverse[0][0] + covar_reverse[1][1]), 2) - 4 * (covar_reverse[0][0] * covar_reverse[1][1] - pow((covar_reverse[0][1]), 2))))) / 2;
		return lambda;
	}

	void set_rot_angle()
	{
		double angle, a_1_1, a_1_2, a_2_2, d;
		a_2_2 = covar_reverse[1][1];
		a_1_1 = covar_reverse[0][0];
		a_1_2 = covar_reverse[0][1];
		d = pow((a_2_2 - a_1_1),2) + 4*pow(a_1_2, 2);
		angle = atan((a_2_2 - a_1_1 + sqrt(d))/(2*a_1_2));
		matr_turn[0] = cos(angle);
		matr_turn[1] = sin(angle);
	}

	double *elps_transf(double constant, double angle)
	{
		int lagr;
		double  a, b, c, d, e, f, new_coords[2];
	// execute lagrange method
	// obtain the circle equation
		a = covar_reverse[0][0];
		b = covar_reverse[0][1];
		c = covar_reverse[1][1];
		d = covar_reverse[0][1]*mu[1] - covar_reverse[0][0]*mu[0];
		e = 0 - (covar_reverse[0][1]*mu[0] - covar_reverse[0][0]*mu[1]);
		f = covar_reverse[0][0]*pow(mu[0], 2) + 2*covar_reverse[0][1]*mu[0]*mu[1] + covar_reverse[1][1]*pow(mu[1], 2);
		lagr = lagrange_method(a, b/2, c, d/2, e/2, f - constant);
		b /= 2;
		d /= 2;
		e /= 2;
		new_coords[1] = (constant*cos(angle) - (a*e - b*d)/(a*sqrt(c - pow(b, 2)/a)))/(sqrt(c - pow(b, 2)/a));
		new_coords[0] = (constant*sin(angle) - (b/sqrt(a))*((new_coords[1] - (a*e - b*d)/(a*sqrt(c - pow(b, 2)/a)))/(sqrt(c - pow(b, 2)/a))) + d/sqrt(a))/(sqrt(a));
		return new_coords;
	}

	elps_model(double *val_mu, double **covar_in)
	{
		int rvs_cov;
		mu = new double [2];
		matr_turn = new double [2];
		new_coords = new double [3];
		lambda = new double [2];
		covar = new double* [2];
		covar_reverse = new double* [2];
		for (int i = 0; i < 2; i++)
		{
			covar[i] = new double [2];
			covar_reverse[i] = new double [2];
 		}
	// initializing mean-vector, covariation matrix
	// calculate reverse covariation matrix, calculate rotation angle 
		set_mu(val_mu);
		set_covar(covar_in);
		rvs_cov = calc_rvs_cov(covar, covar_reverse, 2);
		if (rvs_cov == 0) exit(-1);
		set_rot_angle();
	}

	void get_area(double constant, double *A, double *B, int start = 0)
	{
		if (start == 1)// высчитывание площади первого слоя
		{
			counter_S = 0;
			S[0] = 0.25 * M_PI * pow(constant, 2);
		}
		else// высчитывание площадей всех остальных слоев
		{
			S[counter_S] = 0.25 * M_PI * pow(constant, 2);
			S[counter_S] -= S[counter_S - 1];
			counter_S++;
		}
	}

	~elps_model()
	{
		int i;
		delete[] mu;
		for (i = 0; i < 2; i++)
		{
			delete[] covar[i];
			delete[] covar_reverse[i];
		}
		delete[] covar;
		delete[] covar_reverse;
		delete[] new_coords;
		delete[] lambda;
		delete[] matr_turn;
	}
};