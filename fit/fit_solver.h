////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_solver_h_, the base of all fit_solver
////////////////////////////////////////


#ifndef fit_solver_h_
#define fit_solver_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
#include <fit/fit_function.h>
#include <iostream>

using namespace std;

class fit_solver{

public:
	virtual string type()=0;
	virtual string name()=0;
	virtual bool solve(fit_function  *fn,vnl_vector<double>&x)=0;
	virtual bool retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  )=0;
	virtual string outcome(vnl_vector<double> const&x)=0;
};


#endif // fit_solver_
