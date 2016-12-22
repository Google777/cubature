// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
// Copyright (C) 2016 Balasubramanian Narasimhan
//
// We need both R and C/C++ interfaces!

#include <Rcpp.h>      // need to include the main Rcpp header file only

#include <cuba.h>

SEXP r_fun;                   /* The function itself */

// REMINDER ndim is 3, ncomp = 1
int fWrapper(const int *ndim, const double x[],
	     const int *ncomp, double fval[], void *fdata, const int nvec) {

    // Rprintf("In Wrapper: nvec = %i\n", nvec);

    Rcpp::NumericVector xVal(*ndim);   /* The x argument for the R function f */
    double* xp = xVal.begin();        /* The ptr to x (real) vector */
    for (int i = 0; i < (*ndim); ++i) {
        xp[i] = x[i];
        // Rcpp::Rcout<< x[j][i] <<std::endl;
    }

        // Rcpp::Rcout<<"before call" <<std::endl;

    Rcpp::NumericVector fx = Rcpp::Function(r_fun)(xVal);

    //    Rcpp::Rcout<<"after call" <<std::endl;

    double* fxp = fx.begin();         /* The ptr to f(x) (real) vector */
    for (int i = 0; i < (*ncomp); ++i) {
        fval[i] = fxp[i];
        // Rcpp::Rcout<< fval[i] <<std::endl;
    }
    return 0;
}

// [[Rcpp::export]]
Rcpp::List doCuhre(int ndim, int ncomp, SEXP f,
		   int maxEval, double absErr, double tol, int key) {

  r_fun = f;

  Rcpp::NumericVector integral(ncomp);
  Rcpp::NumericVector errVals(ncomp);
  Rcpp::NumericVector prob(ncomp);

  int nregions, neval, fail;

  //   Rcpp::Rcout<<"Call Integrator" <<std::endl;
  Cuhre(ndim, ncomp, (integrand_t) fWrapper, NULL, 1,
	tol, absErr, 0,
	0, maxEval, key,
	NULL, NULL,
	&nregions, &neval, &fail,
	integral.begin(), errVals.begin(), prob.begin());

  //   Rcpp::Rcout<<"After Call Integrator" <<std::endl;

  return Rcpp::List::create(
			    Rcpp::_["integral"] = integral,
			    Rcpp::_["error"] = errVals,
			    Rcpp::_["nregions"] = nregions,
			    Rcpp::_["neval"] = neval,
			    Rcpp::_["returnCode"] = fail);
}

