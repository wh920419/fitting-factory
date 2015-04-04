////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_svd_solver_h_
////////////////////////////////////////


#ifndef fit_svd_solver_h_
#define fit_svd_solver_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
#include <fit/fit_function.h> 
#include <fit/fit_linear_solver.h>
//#include <fit/fit_solver.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <vnl/vnl_matrix.h> 
#include <string>
using namespace std;

class fit_svd_solver:public fit_linear_solver{
public:

	virtual string name(){return "fit_svd_solver";}
	virtual bool solve(fit_function  *fn,vnl_vector<double> &x);
	virtual bool retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  );
	virtual string outcome(vnl_vector<double> const&x);
};

#endif // fit_svd_solver_
