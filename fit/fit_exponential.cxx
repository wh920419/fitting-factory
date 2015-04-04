////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file implement fit_exponential
////////////////////////////////////////

#include <cmath>
#include <iostream>
#include <vnl/algo/vnl_levenberg_marquardt.h>

#include <fit/fit_exponential.h>

static double ex(double a0, double a, double b, double x)
{
	double arg = exp(b*x);
	return a*arg+a0;
}

void exponential_least_squares_fn::f(vnl_vector<double> const& params,
                               vnl_vector<double>& residuals)
{
  double a0 = params[0];
  double a = params[1];
  double b= params[2];
  double r=0;
  for(unsigned i = 0; i<residuals.size(); ++i){
      residuals[i] = y_[i]-ex(a0, a, b, xi_[i]);
	  r+=residuals[i];
  }
  //cout << "exponential params " << params << endl;
  //cout << "residuals "  << residuals << endl << endl;
  this->residual=r;
}

void exponential_least_squares_fn::gradf(vnl_vector<double> const& params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned n = params.size();
  unsigned m = jacobian.rows();
  double a0 = params[0];
  double a = params[1];
  double b= params[2];

  for(unsigned r = 0; r<m; ++r)
    {
      double x= xi_[r];
      jacobian[r][0]=-1;
      jacobian[r][1]=-exp(b*x);
      jacobian[r][2]=-a*x*exp(b*x);
    }
  //cout << "J \n " << jacobian << endl << endl;
}
