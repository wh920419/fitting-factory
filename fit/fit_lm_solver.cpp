////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file implement fit_lm_solver
////////////////////////////////////////
 
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <fit/fit_function.h> 
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <fit/fit_solver.h>
#include <fit/fit_non_linear_solver.h>
#include <fit/fit_lm_solver.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool fit_lm_solver::solve(fit_function  *fn,vnl_vector<double> &x){
	//fn->lsqf_;
	//data:
	vnl_levenberg_marquardt  levmarq( * fn->lsqf_ ); 
	//vnl_vector<double> xi=fn->xi_;
	//vnl_vector<double> y=fn->y_;
 
//	levmarq.set_verbose(true);
	levmarq.set_x_tolerance(1e-10);
	levmarq.set_epsilon_function(1);
	levmarq.set_f_tolerance(1e-10);
	levmarq.set_max_function_evals(50);
	vnl_vector<double> params(x.size());
	//initial_values(xi, y, params);
	fn->lsif_->init(params);
	// Minimize the error and get the best intersection point
	levmarq.minimize(params);
	levmarq.diagnose_outcome();
	//double t;
	for (unsigned i=0;i<x.size();i++)
	{
		x[i]=params[i];
		// t=x[i];
	}

	if (abs(fn->lsqf_->residual)> 1e-10) 
		return false;

	return true;

}
string fit_lm_solver::outcome(vnl_vector<double> const&x){
	string r ="fit_lm_solver";
	cout<< "*********fit_lm_solver,parameter shows below:***********"<<endl;
	for (unsigned i=0;i<x.size();i++)
	{
		cout<<" "<<x[i]<<" "<<endl;		
	}
	return r;
}

bool fit_lm_solver::retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  ){
	cout<<"Failed first time. then will try again using n_iter= "<<n_iter
		<<"  xtol="<<xtol
		<<"  ftol="<<ftol<<endl;

	vnl_levenberg_marquardt  levmarq( * fn->lsqf_ ); 
	vnl_vector<double> xi=fn->xi_;
	vnl_vector<double> y=fn->y_;
	
	levmarq.set_verbose(true);
	levmarq.set_x_tolerance(xtol);
	levmarq.set_epsilon_function(1);
	levmarq.set_f_tolerance(ftol);
	levmarq.set_max_function_evals(n_iter);
	vnl_vector<double> params(x.size());
	//initial_values(xi, y, params);
	fn->lsif_->init(params);
	// Minimize the error and get the best intersection point
	levmarq.minimize(params);
	levmarq.diagnose_outcome();

	for (unsigned i=0;i<x.size();i++)
	{
		x[i]=params[i];
	}

	return true;
}
 