////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test fit_exponential
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>
#include <math.h>


#include <fit/fit_factory.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_amoeba_solver.h>

#include <fit/fit_lm_solver.h>
#include <fit/fit_exponential.h>

using namespace std;

double gn2(double x)
{
	return exp(x)+1;
}
static void test_exp ()
{
  vnl_vector<double> xi(100), y(100);
  //xi[0]=0; xi[1]=1; xi[2]=2; xi[3]=3; xi[4]=4; xi[5]=5;xi[6]=6;xi[7]=7;
  //
  //y[0]=gn2(xi[0]); y[1]=gn2(xi[1]); y[2]= gn2(xi[2]); y[3]=gn2(xi[3]); y[4]=gn2(xi[4]);
  //y[5]=gn2(xi[5]);y[6]=gn2(xi[6]);y[7]=gn2(xi[7]);
  
	for (unsigned i=0;i<100;i++)
	{
		
		xi[i]=(rand() % 200)/ 50.0;

	}
	for (unsigned i=0;i<100;i++)
	{
		y[i]=gn2(xi[i]) ;
	}
  
  vnl_vector<double> params(3);  
  fit_factory f;
 // fit_svd_solver *ls=new fit_svd_solver;
  fit_lm_solver *ls=new fit_lm_solver;
 //fit_amoeba_solver *ls=new fit_amoeba_solver;
  fit_exponential *fg=new fit_exponential;
  f.register_function( fg);
  f.register_solver(ls);
//  f.fit(xi,y,"fit_svd_solver",params);
  f.fit(xi,y,"fit_exponential","fit_lm_solver",params);
 //f.fit(xi,y,"fit_exponential","fit_amoeba_solver",params);
  cout<< "*********fit_lm_solver,parameter shows below:***********"<<endl;
  cout << "a0 = " << params[0] << endl;
  cout << "a = " << params[1]<< endl;
  cout << "b = " << params[2] << endl;	  
  //cout<<	params[1]*exp(params[2]*1)+params[0]<<endl;
  //cout<<	params[1]*exp(params[2]*2)+params[0]<<endl;
  double eps=1e-1;
  //TEST_NEAR("parameter a0", params[0], 1, eps); 
  //TEST_NEAR("parameter a", params[1], 1, eps); 
  //TEST_NEAR("parameter b", params[2], 1, eps); 
  //TEST_NEAR("e", params[1]*exp(params[2]*1)+params[0], 2.71828, eps); 
  TEST_NEAR("fg->g(1) ", fg->g(1), gn2(1), eps); 
  TEST_NEAR("fg->g(2) ", fg->g(2), gn2(2), eps); 
  TEST_NEAR("fg->g(3) ", fg->g(3), gn2(3), eps);
 
}

TESTMAIN(test_exp );
