////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file declare fit_function, the base of all fit function
////////////////////////////////////////


#ifndef fit_function_h_
#define fit_function_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
//#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_least_squares_init_function.h>
#include <fit/fit_least_squares_function.h>   
#include <iostream>

using namespace std;

class fit_function{
//protected:
public:
	fit_least_squares_function * lsqf_;
	fit_least_squares_init_function *lsif_;
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
	vnl_vector<double> xi_norm_; 
	vnl_vector<double> y_norm_; 
	
	double avex_;//used to normalize
	double avey_;
	double stdx_;
	double stdy_;

	vnl_vector<double> x_; //parameter
public:
	virtual void myNormalize();
	virtual double g(double)=0;
	virtual void setData(vnl_vector<double> const& xi,	vnl_vector<double> const& y)=0;
	virtual void setDataInit(vnl_vector<double> const& xi,	vnl_vector<double> const& y)=0;
	virtual string name()=0;
};


#endif // fit_function_h_
