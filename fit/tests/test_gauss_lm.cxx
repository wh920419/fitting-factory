////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test fit_gauss
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>

#include <fit/fit_svd_solver.h> 
#include <fit/fit_factory.h>
#include <fit/fit_lm_solver.h>
#include <fit/fit_gauss.h>
using namespace std;

double gau1(double x)
{
	double alpha=10.0,  mu=2.0,   sigma=5.0,a0=1.0;
	double arg = (x-mu)/sigma;
	return alpha*exp(-arg*arg/2)+a0;
}

static void test_gauss_lm()
{
  vnl_vector<double> xi(8), y(8);
     xi[0]=0; xi[1]=1; xi[2]=2; xi[3]=3; xi[4]=4; xi[5]=-3;xi[6]=-2;xi[7]=-1;
 // xi[0]=0; xi[1]=-5; xi[2]=10; xi[3]=5; xi[4]=20; xi[5]=-10;

  y[0]=gau1(xi[0]); y[1]=gau1(xi[1]); y[2]= gau1(xi[2]); y[3]=gau1(xi[3]); y[4]=gau1(xi[4]);  y[5]=gau1(xi[5]); 
  y[6]=gau1(xi[6]); y[7]=gau1(xi[7]); 


  //y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
  //y[5]=0.561348;
  /*double alpha=0, mu=0, sigma=0;*/
  vnl_vector<double> x(4);
  //bool good = fit_gauss::fit_gradient(xi, y, alpha, mu, sigma);
  fit_factory f;
  fit_lm_solver *ls=new fit_lm_solver;
//  fit_svd_solver *ls=new fit_svd_solver;


  fit_gauss *fg=new fit_gauss;
  f.register_function( fg);
  f.register_solver(ls);
  f.fit(xi,y,"fit_gauss","fit_lm_solver",x);


  cout<< "*********fit Gaussian using fit_lm_solver,parameter shows below:***********"<<endl;
  cout << "alpha = " << x[0] << endl;
  cout << "mu = " << x[1]<< endl;
  cout << "sigma = " << x[2] << endl;
  cout << "a0 = " << x[3] << endl;
  double eps=1;
  TEST_NEAR("fg->g(1) ", fg->g(1), gau1(1), eps); 
  TEST_NEAR("fg->g(5) ", fg->g(5), gau1(5), eps); 
  TEST_NEAR("fg->g(3) ", fg->g(3), gau1(3), eps);
	//cout <<"......."<<fg->g(-5)<<"......."<<endl;
	//cout <<"......."<<fg->g(5)<<"......."<<endl;

}

TESTMAIN(test_gauss_lm);
