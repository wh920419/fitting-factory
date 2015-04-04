////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test fit_svd_solver
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>
#include <math.h>

#include <fit/fit_factory.h>
#include <fit/fit_amoeba_solver.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_lm_solver.h>

#include <fit/fit_polynomial.h>

using namespace std;

double gn(double x){
	return   pow(x,3.0)*5+pow(x,2.0)*4+x*3+2;
}

static void test_poly_svd()
{
  vnl_vector<double> xi(8), y(8);
  xi[0]=0; xi[1]=1; xi[2]=2; xi[3]=3; xi[4]=4; xi[5]=5;xi[6]=6;xi[7]=7;
  
  y[0]=gn(xi[0]); y[1]=gn(xi[1]); y[2]= gn(xi[2]); y[3]=gn(xi[3]); y[4]=gn(xi[4]);
  y[5]=gn(xi[5]);y[6]=gn(xi[6]);y[7]=gn(xi[7]); 
  
  vnl_vector<double> params(4);
  
  fit_factory f;
fit_svd_solver *ls=new fit_svd_solver;
//  fit_lm_solver *ls=new fit_lm_solver;
 // fit_amoeba_solver *ls=new fit_amoeba_solver;

  fit_polynomial *fg=new fit_polynomial;
  f.register_function( fg);
  f.register_solver(ls);
  f.fit(xi,y,"fit_polynomial","fit_svd_solver",params);
 // f.fit(xi,y,"fit_polynomial","fit_amoeba_solver",params);
 

  cout<< "*********fit_svd_solver,parameter shows below:***********"<<endl;
  cout << "a0 = " << params[0] << endl;
  cout << "a1 = " << params[1]<< endl;
  cout << "a2 = " << params[2] << endl;
  cout << "a3 = " << params[3] << endl;
  //cout<<	pow(1.0,3.0)*params[3]+pow(1.0,2.0)*params[2]+1*params[1]+params[0] <<endl;
  //cout<<	pow(2.0,3.0)*params[3]+pow(2.0,2.0)*params[2]+2*params[1]+params[0] <<endl;
  double eps=1e-5;
  //TEST_NEAR("parameter a0", params[0], 2, eps); 
  //TEST_NEAR("parameter a1", params[1], 3, eps); 
  //TEST_NEAR("parameter a2", params[2], 4, eps); 
  //TEST_NEAR("parameter a3", params[3], 5, eps); 
  //TEST_NEAR("x^3 *5+x^2 *4+x *3+2, when x=1", pow(1.0,3.0)*params[3]+pow(1.0,2.0)*params[2]+1*params[1]+params[0] , 14, eps); 

  TEST_NEAR("fg->g(1) ", fg->g(1), gn(1), eps); 
  TEST_NEAR("fg->g(2) ", fg->g(2), gn(2), eps); 
  TEST_NEAR("fg->g(3) ", fg->g(3), gn(3), eps);

}

TESTMAIN(test_poly_svd);
