// i/o functions
FILE * open_input (const char *lbl, FILE *infile);
FILE * open_output (const char *lbl, FILE *outfile);
int select_mode (FILE *infile);
int cell_parms_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr);
int d2d_parms_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr, double *ue_dens, double *ue_pw, double *ue_prop, double *ue_noise, double *ue_thr);
int cell_fad_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr, double *f_mu);
int write_output (FILE *outfile, double distance, double service_prob);
int write_output_d2d (FILE *outfile, double distance, double br, double service_prob);

// CELLULAR PERFORMANCE FUNCTIONS
double radius_calc (double p, double n, double t, double b);
double cell_perf_calc (double lambda, double r);
double cell_fad_calc (double lambda, double mean, double theta, double noise, double prop, double pw, double r);

// DEVICE-TO-DEVICE PERFORMANCE FUNCTIONS
double area_over (double r1, double r2, double r);
double int_func (double lu, double lb, double r, double area);
double calc_dev (double lu, double lb, double a, double b, double area);
