////////////////////////////////////////
// Hua Wang
// October 31, 2014
// ENGN2912B Assignment 17
//
//  This file contain functions to implement fit_gauss
////////////////////////////////////////
#ifndef fit_gradient_descent_h_
#define fit_gradient_descent_h_

#include <vcl_iosfwd.h>

#include <vnl/vnl_vector_fixed.h>
#include <vnl/vnl_matrix.h>
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <vnl/vnl_nonlinear_minimizer.h>
//#include <vnl/algo/vnl_netlib.h> // lmdif_()
using namespace std;

class fit_gradient_descent : public vnl_nonlinear_minimizer
{
public:

	//: Initialize with the function object that is to be minimized.
	fit_gradient_descent(vnl_least_squares_function& f) { 
		f_=&f;	
		lamda_=0.1;
	}
	bool minimize(vnl_vector<double>& x);
//	bool minimize_without_gradient(vnl_vector<double>& x);
	bool minimize_using_gradient  (vnl_vector<double>& x);
	void diagnose_outcome() const;
    void diagnose_outcome(vcl_ostream&) const;
	void setLamda(double);
protected:
	vnl_least_squares_function* f_;	
private:
	double lamda_;
};

#endif // fit_gradient_descent_h_
