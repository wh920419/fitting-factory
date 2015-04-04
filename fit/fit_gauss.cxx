////////////////////////////////////////
// Hua Wang
// October 31, 2014
// ENGN2912B Assignment 17
//
//  This file contain functions to implement fit_gauss
////////////////////////////////////////


//#include <fit/fit_function.h>
//#include <fit/fit_factory.h>
//#include <fit/fit_solver.h>


#include <cmath>
#include <iostream>
#include "fit_gauss.h"
//#include "fit_gradient_descent.h"
#include <vnl/algo/vnl_levenberg_marquardt.h>

static double gauss(double alpha, double mu, double sigma, double a0, double x)
{
  double arg = (x-mu)/sigma;
  return alpha*exp(-arg*arg/2)+a0;
}


void gauss_least_squares_fn::f(vnl_vector<double> const& gauss_params,
                               vnl_vector<double>& residuals)
{
  double alpha = gauss_params[0];
  double mu = gauss_params[1];
  double sigma = gauss_params[2];
  double a0=gauss_params[3];
  double r=0;
  for(unsigned i = 0; i<residuals.size(); ++i){
      residuals[i] = y_[i]-gauss(alpha, mu, sigma,a0, xi_[i]);
	 r+=residuals[i]*residuals[i];
  }
  //cout << "gauss params " << gauss_params << endl;
  //cout << "residuals "  << residuals << endl << endl;
  this->residual=sqrt(r);
}

void gauss_least_squares_fn::gradf(vnl_vector<double> const& gauss_params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned n = gauss_params.size();
  unsigned m = jacobian.rows();
  double alpha = gauss_params[0];
  double mu = gauss_params[1];
  double sigma = gauss_params[2];
  double a0=gauss_params[3];
  double sigma_2 = 1/(sigma*sigma);
  double sigma_3 = sigma_2/sigma;
  for(unsigned r = 0; r<m; ++r)
    {
      double d = xi_[r]-mu;
      jacobian[r][0]=-gauss(1.0,mu,sigma,0.0,xi_[r]);
      jacobian[r][1]=-gauss(alpha,mu,sigma,0.0,xi_[r])*d*sigma_2;
      jacobian[r][2]=-gauss(alpha,mu,sigma,0.0,xi_[r])*d*d*sigma_3;
	  jacobian[r][3]= -1;

    }
  //cout << "J \n " << jacobian << endl << endl;
}
