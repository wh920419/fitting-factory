////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file implement fit_polynomial
////////////////////////////////////////

#include <cmath>
#include <iostream>
#include <fit/fit_polynomial.h>
//#include "fit_gradient_descent.h"
#include <vnl/algo/vnl_levenberg_marquardt.h>

//static double gauss(double alpha, double mu, double sigma, double x)
//{
//  double arg = (x-mu)/sigma;
//  return alpha*exp(-arg*arg/2);
//}
static double gn(double a0, double a1, double a2, double a3,double x){
	return pow(x,3.0)*a3+pow(x,2.0)*a2+x*a1+a0;
}

void polynomial_least_squares_fn ::f(vnl_vector<double> const& params,
                               vnl_vector<double>& residuals)
{
  double a0 = params[0];
  double a1 = params[1];
  double a2 = params[2];
  double a3 = params[3];
  double r=0;
  for(unsigned i = 0; i<residuals.size(); ++i){
      residuals[i] = y_[i]-gn(a0, a1, a2,a3, xi_[i]);
	r+=residuals[i];
  }
  //cout << "polynomial params " << params << endl;
  //cout << "residuals "  << residuals << endl << endl;
  this->residual=r;
}

void polynomial_least_squares_fn::gradf(vnl_vector<double> const& params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned n = params.size();
  unsigned m = jacobian.rows();
  double a0 = params[0];
  double a1 = params[1];
  double a2 = params[2];
  double a3 = params[3];

  for(unsigned r = 0; r<m; ++r)
    {
		jacobian[r][0]=-1;
		jacobian[r][1]=-xi_[r];
		jacobian[r][2]=-xi_[r]*xi_[r];
		jacobian[r][3]=-xi_[r]*xi_[r]*xi_[r];
    }
 // cout << "J \n " << jacobian << endl << endl;
}
