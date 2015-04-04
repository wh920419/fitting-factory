////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test fit_radial_basis_function
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>
#include <math.h>


#include <fit/fit_factory.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_lm_solver.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_amoeba_solver.h>

#include <fit/fit_radial_basis_function.h>

using namespace std;

double rbf1( double psize,double x)
{ 
	double delta=1.0;
	double res=0;
	for (unsigned i=0;i<psize;i++)
	{
		res+= exp(-1.5*delta*(x-delta*i)*(x-delta*i) );
	}
	//return 1*exp(-1.5*delta*(x-0)*(x-0) )+2*exp(-1.5*delta*(x-delta)*(x-delta) )+3*exp(-1.5*delta*(x-2*delta)*(x-2*delta) );
	return res;
}
static void test_rbf ()
{

  vnl_vector<double> xi(25), y(25);

  for (unsigned i=0;i<25;i++)
  {
	  xi[i]=(rand() % 8);
  }
  for (unsigned i=0;i<25;i++)
  {
	  y[i]=rbf1(xi.size(),xi[i]) ;
  }
 
 /* xi[0]=0; xi[1]=1; xi[2]=2; xi[3]=3; 
  xi[4]=4; xi[5]=5;xi[6]=6;xi[7]=7;
  
  y[0]=rbf1(xi.size(),xi[0]); y[1]=rbf1(xi.size(),xi[1]); y[2]= rbf1(xi.size(),xi[2]); y[3]=rbf1(xi.size(),xi[3]);
  y[4]=rbf1(xi.size(),xi[4]);  y[5]=rbf1(xi.size(),xi[5]);  y[6]=rbf1(xi.size(),xi[6]); y[7]=rbf1(xi.size(),xi[7]);*/
  
  //y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
  //y[5]=0.561348;
   
  vnl_vector<double> params(xi.size());  
  fit_factory f;
 // fit_svd_solver *ls=new fit_svd_solver;

//  fit_amoeba_solver *ls=new fit_amoeba_solver;
 fit_lm_solver *ls=new fit_lm_solver;
  fit_radial_basis_function *fg=new fit_radial_basis_function;
  f.register_function( fg);
  f.register_solver(ls);

//f.fit(xi,y,"fit_radial_basis_function","fit_amoeba_solver",params);
 f.fit(xi,y,"fit_radial_basis_function","fit_lm_solver",params);
//  f.fit(xi,y,"fit_radial_basis_function","fit_svd_solver",params);

  cout<< "*********solve RBF using fit_lm_solver,parameter shows below:***********"<<endl;
  for (unsigned i=0;i<params.size();i++)
  {
	  cout << "w"<<i<<" = " << params[i] << endl;
  }
  //cout << "w0 = " << params[0] << endl;
  //cout << "w1 = " << params[1]<< endl;
  //cout << "w2 = " << params[2] << endl;
   
	double eps=1;
  //TEST_NEAR("parameter w0", params[0], 1, eps); 
  //TEST_NEAR("parameter w1", params[1], 1, eps); 
  //TEST_NEAR("parameter w2", params[2], 1, eps);
	TEST_NEAR("fg->g(1) ", fg->g(1), rbf1(xi.size(),1), eps); 
	TEST_NEAR("fg->g(0) ", fg->g(0), rbf1(xi.size(),0), eps); 
	TEST_NEAR("fg->g(4) ", fg->g(4), rbf1(xi.size(),5), eps);
 

}

TESTMAIN(test_rbf );
