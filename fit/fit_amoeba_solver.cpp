////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file implement fit_amoeba_solver
////////////////////////////////////////
 
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <fit/fit_function.h> 
#include <vnl/algo/vnl_amoeba.h>

#include <fit/fit_amoeba_solver.h>
#include <vnl/vnl_cost_function.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
class cost_function: public vnl_cost_function 
{ 
public: 
	 cost_function(vnl_least_squares_function& f): 
	  vnl_cost_function(f.get_number_of_unknowns()), f_(&f), 
		  fx_(vnl_vector<double>(f.get_number_of_residuals())){} 
	  ~cost_function(){} 
	  //: The cost function (somewhat like a functor). 
	  double f(vnl_vector<double> const& x) 
	  { 
		  f_->f(x, fx_); 
		  double c = fx_.squared_magnitude(); 
		  cout << "c " << c << endl; 
		  return c; 
	  } 
protected:
	vnl_least_squares_function* f_; 
	vnl_vector<double> fx_; 
};

bool fit_amoeba_solver::solve(fit_function  *fn,vnl_vector<double> &x){

	//data:
	cost_function gcf(* fn->lsqf_ ); 
	//vnl_vector<double> xi=fn->xi_;
	//vnl_vector<double> y=fn->y_;	//  Normalize!@Hua
	
	vnl_amoeba amoeba(gcf); 
	amoeba.set_relative_diameter(1.0); 
	amoeba.verbose = true; 
	// Set the x-tolerance. 
	amoeba.set_x_tolerance(1e-10); 
	// Set the f-tolerance. 
	amoeba.set_f_tolerance(1e-10); 
	// Set the maximum number of iterations 
	amoeba.set_max_iterations(50); 
	vnl_vector<double> params(x.size()); 
	//initial_values(xi, y, params); 
	fn->lsif_->init(params);
	// Minimize the error 
	amoeba.minimize(params); 	
	for (unsigned i=0;i<x.size();i++)
	{
		x[i]=params[i];
	}


	if (abs(fn->lsqf_->residual)> 1e-10) //if doesn't meet xtol
		return false;

	return true; 
}

string fit_amoeba_solver::outcome(vnl_vector<double> const&x){
	string r ="fit_amoeba_solver";
	cout<< "*********fit_amoeba_solver,parameter shows below:***********"<<endl;
	for (unsigned i=0;i<x.size();i++)
	{
		cout<<" "<<x[i]<<" "<<endl;		
	}
	return r;
}

bool fit_amoeba_solver::retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  ){
	cout<<"Failed first time. then will try again using n_iter= "<<n_iter
		<<"  xtol="<<xtol
		<<"  ftol="<<ftol<<endl;
	cost_function gcf(* fn->lsqf_ ); 
	vnl_vector<double> xi=fn->xi_;
	vnl_vector<double> y=fn->y_;	

	vnl_amoeba amoeba(gcf); 
	amoeba.set_relative_diameter(1.0); 
	amoeba.verbose = true; 
	// Set the x-tolerance. 
	amoeba.set_x_tolerance(xtol); 
	// Set the f-tolerance. 
	amoeba.set_f_tolerance(ftol); 
	// Set the maximum number of iterations 
	amoeba.set_max_iterations(n_iter); 
	vnl_vector<double> params(x.size()); 
	//initial_values(xi, y, params); 
	fn->lsif_->init(params);
	// Minimize the error 
	amoeba.minimize(params); 	
	for (unsigned i=0;i<x.size();i++)
	{
		x[i]=params[i];
	}
	
	return true;
}
 