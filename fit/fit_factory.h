////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file declare fit_factory_h_
////////////////////////////////////////


#ifndef fit_factory_h_
#define fit_factory_h_

#include <fit/fit_function.h> 
#include <fit/fit_solver.h>

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class fit_factory{
private:
	map<string, fit_solver* > solver_;//name is index
	map<string, fit_function* > fit_fun_;//name is index
	//fit_function * fit_fun_;
public:
	bool register_solver(fit_solver *);
	bool register_function(fit_function *);
	bool fit(vnl_vector<double>xi,vnl_vector<double>y,string fn,string sov,vnl_vector<double> &x );
	vnl_vector<double> out_y_;
	vnl_vector<double> outy();
};


#endif // fit_factory_
