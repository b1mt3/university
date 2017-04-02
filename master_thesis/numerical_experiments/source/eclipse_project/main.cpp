#include <stdio.h>
#include <math.h>
#include "performance.h"

int main (int argc, char **argv) {
  // ---------------------------------- DECLARATIONS ----------------------------------

	// mode for type of experiments
  int mode;
    // exit codes for every function to be called
  int ex_code;
    // input and output files
  FILE *ifp, *ofp;
    // initial parameters for BSs and UEs
  double bs_dens, bs_pw, bs_thr, bs_thn, bs_pex, u_dens, u_pw, u_thr, u_thn, u_pex;
  double mu;
    // search disk radiuses for BSs and UEs
  double r1, r2;
    // probability of a loop step
  double step_prob, last_step_prob;
    // area of integration
  double step_area;
    // loop variables
  int i, k;
  double j, m, l;

  // ----------------------------------- EXECUTIONS ------------------------------------

  ifp = open_input ("ipf_sh0.txt", ifp);
  if (ifp == 0) { return -1; }
  else {
	  ofp = open_output ("ofp_sh0.txt", ofp);
	  if (ofp == 0) { return -2; }
  }

  mode = select_mode (ifp);
  last_step_prob = 0.000;

  if (mode == 0) {
    ex_code = cell_parms_fill (ifp, &bs_dens, &bs_pw, &bs_pex, &bs_thn, &bs_thr);
    if (ex_code == -4) { fclose (ifp); fclose (ofp); return -5; }
    else {
    	for (j=0.00000001; j<=1; j*=2){
          r1 = radius_calc (bs_pw, bs_thn, bs_thr, bs_pex);
          step_prob = cell_perf_calc (j, r1);
          if (fabs(step_prob-last_step_prob)<0.001) continue;
          else { last_step_prob = step_prob; }
          if (step_prob >= 0.999) { step_prob = 1.000; break;}
	      ex_code = write_output (ofp, j, step_prob);
    	}
      return 1;
    }
  }

  if (mode == 1) {
    ex_code = d2d_parms_fill (ifp, &bs_dens, &bs_pw, &bs_pex, &bs_thn, &bs_thr, &u_dens, &u_pw, &u_pex, &u_thn, &u_thr);
    if (ex_code == -4) { fclose (ifp); fclose (ofp); return -5; }
    else {
      r1 = radius_calc (bs_pw, bs_thn, bs_thr, bs_pex);
      r2 = radius_calc (u_pw, u_thn, u_thr, u_pex);
      for (m=0.00000001,l=0.000001;m<=1,l<=1000;m*=2,l*=2){
		  for (j=r1+0.001; j<=r1+r2; j++) {
			step_area = area_over (r1, r2, j);
	        step_prob = cell_perf_calc (m, r1);
			step_prob += calc_dev (l, m, r1, j, step_area);
			if (fabs(last_step_prob - step_prob)<0.001) { continue; }
			if (step_prob >= 0.999) { step_prob = 1.000; break; }
			//m = j;
			//k = m*10;
			//if (k%10==0){ last_step_prob = step_prob; ex_code = write_output (ofp, j, step_prob); }
			last_step_prob = step_prob;
		  }
		if (step_prob==1.000) { ex_code = write_output_d2d (ofp, m, l, step_prob); break; }
		ex_code = write_output_d2d (ofp, m, l, step_prob);
      }
      return 2;
    }
  }

  if (mode == 2) {
	ex_code = cell_fad_fill (ifp, &bs_dens, &bs_pw, &bs_pex, &bs_thn, &bs_thr, &mu);
	if (ex_code == -4) { fclose (ifp); fclose (ofp); return -5;}
	else {
		for (l=0.0000000001; l<=1; l*=10){
			for (j=0.001; j<=1 ; j+=0.001) {
			  step_prob = cell_fad_calc (bs_dens, l, bs_thr, bs_thn, bs_pex, bs_pw, j);
			  if (fabs(last_step_prob - step_prob)<0.001) { continue; }
			  if (step_prob >= 0.999) { step_prob = 1.000; break; }
			  // if (step_prob <= 0.001) { break; }
			  last_step_prob = step_prob;
			  // ex_code = write_output (ofp, j, step_prob);
			}
		if (step_prob==1.000) { ex_code = write_output (ofp, l, step_prob); break; }
		ex_code = write_output (ofp, l, step_prob);
		}
	  return 3;
	}
  }

  // TODO: multiple hop with fading (mode 4)
  else {
	fclose (ifp);
	fclose (ofp);
	return -3;
  }
  return 0;
}
