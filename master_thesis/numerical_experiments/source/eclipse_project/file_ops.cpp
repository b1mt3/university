#include <stdio.h>

FILE *open_input (const char *lbl, FILE *infile) {
	infile = fopen (lbl, "r");
    if (infile == NULL) { fprintf (stderr, "Can't open input file %s.\n", lbl); return 0; }
	return infile;
}

FILE *open_output (const char *lbl, FILE *outfile) {
	outfile = fopen (lbl, "w");
	if (outfile == NULL) {fprintf (stderr, "Can't open output file %s.\n", lbl); return 0; }
	return outfile;
}

int select_mode (FILE *infile) {
	int result;

	fscanf (infile, "%d", &result);
	return result;
}

int cell_parms_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr) {
	int result;
	result = fscanf (infile, "%lf", bs_dens);
	fscanf (infile, "%lf", bs_pw);
	fscanf (infile, "%lf", bs_prop);
	fscanf (infile, "%lf", bs_noise);
	fscanf (infile, "%lf", bs_thr);
	return 0;
}

int d2d_parms_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr, double *ue_dens, double *ue_pw, double *ue_prop, double *ue_noise, double *ue_thr) {
	fscanf (infile, "%lf", bs_dens);
	fscanf (infile, "%lf", ue_dens);
	fscanf (infile, "%lf", bs_pw);
	fscanf (infile, "%lf", ue_pw);
	fscanf (infile, "%lf", bs_prop);
	fscanf (infile, "%lf", ue_prop);
	fscanf (infile, "%lf", bs_noise);
	fscanf (infile, "%lf", ue_noise);
	fscanf (infile, "%lf", bs_thr);
	fscanf (infile, "%lf", ue_thr);
	return 0;
}

int cell_fad_fill (FILE *infile, double *bs_dens, double *bs_pw, double *bs_prop, double *bs_noise, double *bs_thr, double *f_mu) {
	fscanf (infile, "%lf", bs_dens);
	fscanf (infile, "%lf", bs_pw);
	fscanf (infile, "%lf", bs_prop);
	fscanf (infile, "%lf", bs_noise);
	fscanf (infile, "%lf", bs_thr);
	fscanf (infile, "%lf", f_mu);
	return 0;
}

int write_output (FILE *outfile, double distance, double service_prob) {
	fprintf (outfile, "%.8lf %.3lf\n", distance, service_prob);
	return 0;
}

int write_output_d2d (FILE *outfile, double distance, double br, double service_prob) {
	fprintf (outfile, "%.8lf %.6lf %.3lf\n", distance, br, service_prob);
	return 0;
}
