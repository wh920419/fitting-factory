////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test fit_amoeba
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>
#include <math.h>


#include <fit/fit_factory.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_lm_solver.h>
#include <fit/fit_amoeba_solver.h>
#include <fit/fit_gauss.h>

using namespace std;

static void test_amoeba()
{
	vnl_vector<double> xi(6), y(6);
	xi[0]=0; xi[1]=-5; xi[2]=10; xi[3]=5; xi[4]=20; xi[5]=-10;
	y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
	y[5]=0.561348;
	double alpha=0, mu=0, sigma=0;
	vnl_vector<double> x(4);
	//bool good = fit_gauss::fit_gradient(xi, y, alpha, mu, sigma);
	fit_factory f;
	//fit_lm_solver *ls=new fit_lm_solver;
	fit_amoeba_solver *ls=new fit_amoeba_solver;
	fit_gauss *fg=new fit_gauss;
	f.register_function( fg);
	f.register_solver(ls);
	f.fit(xi,y,"fit_gauss","fit_amoeba_solver",x);


	cout<< "*********fit_amoeba_solver,parameter shows below:***********"<<endl;
	cout << "alpha = " << x[0] << endl;
	cout << "mu = " << x[1]<< endl;
	cout << "sigma = " << x[2] << endl;
	cout << "a0= " << x[3] << endl;
	cout <<"......."<<fg->g(-5)<<"......."<<endl;

}

TESTMAIN(test_amoeba);

