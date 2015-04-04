////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file declare fit_least_squares_function_h_, the basic function of all fit_least_squares_function
////////////////////////////////////////


#ifndef fit_least_squares_function_h_
#define fit_least_squares_function_h_


#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_least_squares_init_function.h>
using namespace std;

class fit_least_squares_function:public vnl_least_squares_function{
protected:
	
public:
	double residual;

	fit_least_squares_function(vnl_vector<double> const& xi,
		vnl_vector<double> const& y,unsigned numberOfUnknown): 
	//    vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::no_gradient), xi_(xi), y_(y){}  
	vnl_least_squares_function(numberOfUnknown, xi.size(),vnl_least_squares_function::use_gradient){}  
	virtual void f(vnl_vector<double> const& x, vnl_vector<double>& fx) = 0;
	virtual void gradf(vnl_vector<double> const& x, vnl_matrix<double>& jacobian)=0;
};



#endif // fit_least_squares_function_h_
