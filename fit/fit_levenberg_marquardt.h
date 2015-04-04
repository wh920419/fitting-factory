////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file fit_levenberg_marquardt_h_,
////////////////////////////////////////


#ifndef fit_levenberg_marquardt_h_
#define fit_levenberg_marquardt_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <fit/fit_least_squares_init_function.h>
using namespace std;
class fit_levenberg_marquardt : public vnl_levenberg_marquardt
{
public:
	//: Constructor
	fit_levenberg_marquardt( vnl_least_squares_function & f):vnl_levenberg_marquardt(f){}; 
	bool minimize(vnl_vector<double>& x, fit_least_squares_init_function& x0) 
	{ 
		x0.init(x); 
		return this->vnl_levenberg_marquardt::minimize(x); 
	} 

};


#endif // fit_levenberg_marquardt_h_
