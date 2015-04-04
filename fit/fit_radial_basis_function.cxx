////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to implement fit_radial_basis_function
////////////////////////////////////////

#include <cmath>
#include <iostream>
#include <vnl/algo/vnl_levenberg_marquardt.h>

#include <fit/fit_radial_basis_function.h>

static double rbf(vnl_vector<double> const& params, double x)
{
	double delta=1.0; 
	double res=0;
	for (unsigned i=0;i<params.size();i++)
	{
		res+=params[i]*exp(-1.5*delta*(x-delta*i)*(x-delta*i) );
	}
	//return  w0*exp(-1.5*delta*(x-0)*(x-0) )+w1*exp(-1.5*delta*(x-delta)*(x-delta) )+w2*exp(-1.5*delta*(x-2*delta)*(x-2*delta) );
	return res;
}

void radial_basis_function_least_squares_fn::f(vnl_vector<double> const& params,
                               vnl_vector<double>& residuals)
{
  //double w0 = params[0];
  //double w1 = params[1];
  //double w2 = params[2];
 //@redo
  double r=0;
  for(unsigned i = 0; i<residuals.size(); ++i){
      residuals[i] = y_[i]-rbf( params,  xi_[i]); 
	r+=residuals[i];
  }
  //cout << "radial_basis_function params " << params << endl;
  //cout << "residuals "  << residuals << endl << endl;
  this->residual=r;
}

void radial_basis_function_least_squares_fn::gradf(vnl_vector<double> const& params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned n = params.size();
  unsigned m = jacobian.rows();

  for(unsigned r = 0; r<m; ++r)
    {
		double x= xi_[r]; double delta=1.0;
		for (unsigned j=0;j<params.size();j++)
		{//@redo
			jacobian[r][j]=-exp(-1.5*delta*(x-delta*j)*(x-delta*j) );
			//jacobian[r][1]=-exp(-1.5*delta*(x-delta)*(x-delta) );
			//jacobian[r][2]=-exp(-1.5*delta*(x-2*delta)*(x-2*delta) );			 
		}	   
    }
 // cout << "J \n " << jacobian << endl << endl;
}
