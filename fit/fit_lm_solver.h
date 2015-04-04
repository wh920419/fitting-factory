////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_lm_solver_h_
////////////////////////////////////////


#ifndef fit_lm_solver_h_
#define fit_lm_solver_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <fit/fit_function.h> 
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <fit/fit_solver.h>
#include <fit/fit_non_linear_solver.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class fit_lm_solver: public fit_non_linear_solver{
public:	
	//fit_lm_solver();
	virtual string name(){return "fit_lm_solver";}
	virtual bool solve(fit_function  *fn,vnl_vector<double> &x);
	virtual bool retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  );
	virtual string outcome(vnl_vector<double> const&x);
};


#endif // fit_lm_solver_
