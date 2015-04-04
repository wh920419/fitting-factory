////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file declare fit_least_squares_init_function_h_, the basic function of all fit_least_squares_function_init
////////////////////////////////////////

#ifndef fit_least_squares_init_function_h_
#define fit_least_squares_init_function_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
//#include <vnl/vnl_least_squares_function.h>
using namespace std;
class fit_least_squares_init_function 
{ 
public: 
	fit_least_squares_init_function(unsigned int number_of_unknowns) 
		: n_(number_of_unknowns) {};
	virtual ~fit_least_squares_init_function() {}; 
	virtual void init(vnl_vector<double>& x) = 0; 
protected: 
	unsigned n_; 
}; 

#endif // vnl_least_squares_init_function_h_
