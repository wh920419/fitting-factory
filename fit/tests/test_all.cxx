////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file contain functions to test all
////////////////////////////////////////
#include <testlib/testlib_test.h>
#include <vnl/vnl_vector.h>
#include <iostream>
#include <math.h>


#include <fit/fit_factory.h>

#include <fit/fit_lm_solver.h>
#include <fit/fit_svd_solver.h> 
#include <fit/fit_amoeba_solver.h>

#include <fit/fit_factory.h>
#include <fit/fit_gauss.h>
#include <fit/fit_radial_basis_function.h>
#include <fit/fit_polynomial.h>
#include <fit/fit_exponential.h>
using namespace std;

double rbf( double x)//RBF function, which parameters are: w0=w1=w2=1
{
	double delta=1.0;
	return 1*exp(-1.5*delta*(x-0)*(x-0) )+2*exp(-1.5*delta*(x-delta)*(x-delta) )+3*exp(-1.5*delta*(x-2*delta)*(x-2*delta) );
}
double gau(double x)//Gaussian function, whose parameters are alpha=10.0,  mu=2.0,   sigma=5.0,a0=1.0;
{
	double alpha=-2.0,  mu=-2.0,   sigma=25.0,a0=1.0;
	double arg = (x-mu)/sigma;
	return alpha*exp(-arg*arg/2)+a0;
}
double ex(double x)//Exponential function, whose parameters are a=b=a0=1
{
	double r=exp(x)+1.0;
	return r;
}
double pol(double x){
	return pow(x,3.0)*5+pow(x,2.0)*4+x*3+2;//Polynomial function ,whose parameters are a0=2,a1=3,a2=4,a3=5
}
static void test_all()
{
	//vnl_vector<double> xi(8), yg(8),ye(8),yp(8),yr(8);
	vnl_vector<double> xi(1000), yg(1000),ye(100),yp(1000),yr(25),xii(100),xir(25);
	vnl_vector<double>		 xg(4),xe(3),xp(4);
	//xi[0]=0; xi[1]=1; xi[2]=2; xi[3]=3; xi[4]=4; xi[5]=-1;xi[6]=-3;xi[7]=-2;
	for (unsigned i=0;i<1000;i++)
	{
		xi[i]=rand()%10 ;
	}
	//y for Gaussian
	//yg[0]=gau(xi[0]); yg[1]=gau(xi[1]); yg[2]= gau(xi[2]); yg[3]=gau(xi[3]); yg[4]=gau(xi[4]);
	//yg[5]=gau(xi[5]);yg[6]=gau(xi[6]);yg[7]=gau(xi[7]);
	for (unsigned i=0;i<1000;i++)
	{
		yg[i]=gau(xi[i]) ;
	}
	//y for exponential function
	//ye[0]=ex(xi[0]); ye[1]=ex(xi[1]); ye[2]= ex(xi[2]); ye[3]=ex(xi[3]); ye[4]=ex(xi[4]);
	//ye[5]=ex(xi[5]);ye[6]=ex(xi[6]);ye[7]=ex(xi[7]);
	for (unsigned i=0;i<100;i++)
	{
		xii[i]=(rand() % 200)/ 50.0;
	}
	for (unsigned i=0;i<100;i++)
	{
		ye[i]=ex(xii[i]) ;
	}
	//y for polynomial function
	//yp[0]=pol(xi[0]); yp[1]=pol(xi[1]); yp[2]= pol(xi[2]); yp[3]=pol(xi[3]); yp[4]=pol(xi[4]);
	//yp[5]=pol(xi[5]);yp[6]=pol(xi[6]);yp[7]=pol(xi[7]);
	for (unsigned i=0;i<1000;i++)
	{
		yp[i]=pol(xi[i]) ;
	}
	//y for RBF
	//yr[0]=rbf(xi[0]); yr[1]=rbf(xi[1]); yr[2]= rbf(xi[2]); yr[3]=rbf(xi[3]); yr[4]=rbf(xi[4]);
	//yr[5]=rbf(xi[5]);yr[6]=rbf(xi[6]);yr[7]=rbf(xi[7]);
	for (unsigned i=0;i<25;i++)
	{
		xir[i]=(rand() % 8);
	}
	for (unsigned i=0;i<25;i++)
	{
		yr[i]=rbf(xir[i]) ;
	}
	vnl_vector<double> xr(xir.size());//the number of parameters for RBF is depend on size of data
	//y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
	//y[5]=0.561348;

	fit_factory f;

	fit_gauss *fg=new fit_gauss;
	fit_exponential *fe=new fit_exponential;
	fit_polynomial *fp=new fit_polynomial;
	fit_radial_basis_function *fr=new fit_radial_basis_function;

	fit_lm_solver *ls=new fit_lm_solver;
	fit_amoeba_solver *as=new fit_amoeba_solver;
	fit_svd_solver *ss=new fit_svd_solver;

	f.register_function( fg);
	f.register_function( fe);
	f.register_function( fp);
	f.register_function( fr);
	
	f.register_solver(ls);
	f.register_solver(as);
	f.register_solver(ss);

	//*************************Gaussian**************************
	//Test fit Gaussian using fit_lm_solver
	f.fit(xi,yg,"fit_gauss","fit_lm_solver",xg);
	cout<< "*********fit Gaussian using fit_lm_solver,parameter shows below:***********"<<endl;
	cout << "alpha = " << xg[0] << endl;
	cout << "mu = " << xg[1]<< endl;
	cout << "sigma = " << xg[2] << endl;
	cout << "a0 = " << xg[3] << endl;
	double eps=1;
	
	//vnl_vector<double> o=f.outy();
	//for (unsigned i=0;i<8;i++)
	//{
	//	cout<<o[i]<<endl;
	//}
	//for (unsigned i=0;i<1000;i++)
	//{
	//	//TEST_NEAR("fg->g(1) ", fg->g( xi[i] ), gau(xi[i]), eps);
	//	TEST_NEAR("fg->g(1) ", o[i], gau(xi[i]), eps);
	//	//yp[i]=pol(xi[i]) ;
	//}
	TEST_NEAR("fg->g(1) ", fg->g(1), gau(1), eps); 
	TEST_NEAR("fg->g(-1) ", fg->g(-1), gau(-1), eps); 
	TEST_NEAR("fg->g(2) ", fg->g(2), gau(2), eps);
	
	//fit Gaussian using fit_amoeba_solver
	f.fit(xi,yg,"fit_gauss","fit_amoeba_solver",xg);
	cout<< "*********fit Gaussian using fit_amoeba_solver,parameter shows below:***********"<<endl;
	cout << "alpha = " << xg[0] << endl;
	cout << "mu = " << xg[1]<< endl;
	cout << "sigma = " << xg[2] << endl;
	cout << "a0 = " << xg[3] << endl;
	 
	TEST_NEAR("fg->g(1) ", fg->g(1), gau(1), eps); 
	TEST_NEAR("fg->g(-1) ", fg->g(-1), gau(-1), eps); 
	TEST_NEAR("fg->g(2) ", fg->g(2), gau(2), eps);
	
	//fit Gaussian using fit_svd_solver
	f.fit(xi,yg,"fit_gauss","fit_svd_solver",xg);
	cout<< "*********fit Gaussian using fit_svd_solver,parameter shows below:***********"<<endl;
	cout << "alpha = " << xg[0] << endl;
	cout << "mu = " << xg[1]<< endl;
	cout << "sigma = " << xg[2] << endl;
	cout << "a0 = " << xg[3] << endl;
	
	TEST_NEAR("fg->g(1) ", fg->g(1), gau(1), eps); 
	TEST_NEAR("fg->g(5) ", fg->g(5), gau(5), eps); 
	TEST_NEAR("fg->g(2) ", fg->g(2), gau(2), eps);

	//*************************Exponential**************************
	//Test fit exponential using fit_lm_solver
	f.fit(xii,ye,"fit_exponential","fit_lm_solver",xe);
	cout<< "*********fit exponentialusing fit_lm_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xe[0] << endl;
	cout << "a = " << xe[1]<< endl;
	cout << "b = " << xe[2] << endl;	
	 eps=1e-1;
	TEST_NEAR("fg->g(1) ", fe->g(1), ex(1), eps); 
	TEST_NEAR("fg->g(2) ", fe->g(2), ex(2), eps); 
	TEST_NEAR("fg->g(3) ", fe->g(3), ex(3), eps);

	//fit exponential using fit_amoeba_solver
	f.fit(xii,ye,"fit_exponential","fit_amoeba_solver",xe);
	cout<< "*********fit exponential using fit_amoeba_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xe[0] << endl;
	cout << "a = " << xe[1]<< endl;
	cout << "b = " << xe[2] << endl;	
	 
	TEST_NEAR("fg->g(1) ", fe->g(1), ex(1), eps); 
	TEST_NEAR("fg->g(2) ", fe->g(2), ex(2), eps); 
	TEST_NEAR("fg->g(3) ", fe->g(3), ex(3), eps);

	//fit exponential using fit_svd_solver
	f.fit(xii,ye,"fit_exponential","fit_svd_solver",xe);
	cout<< "*********fit exponentialusing fit_svd_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xe[0] << endl;
	cout << "a = " << xe[1]<< endl;
	cout << "b = " << xe[2] << endl;	
	 
	TEST_NEAR("fg->g(1) ", fe->g(1), ex(1), eps); 
	TEST_NEAR("fg->g(2) ", fe->g(2), ex(2), eps); 
	TEST_NEAR("fg->g(3) ", fe->g(3), ex(3), eps);


	//*************************Polynomial**************************
	//Test fit polynomial using fit_lm_solver
	f.fit(xi,yp,"fit_polynomial","fit_lm_solver",xp);
	cout<< "*********fit polynomial using fit_lm_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xp[0] << endl;
	cout << "a1 = " << xp[1]<< endl;
	cout << "a2 = " << xp[2] << endl;
	cout << "a3 = " << xp[3] << endl;	
	 
	TEST_NEAR("fg->g(1) ", fp->g(1), pol(1), eps); 
	TEST_NEAR("fg->g(2) ", fp->g(2),pol(2), eps); 
	TEST_NEAR("fg->g(3) ", fp->g(3),pol(3), eps);

	//fit polynomial using fit_amoeba_solver
	f.fit(xi,yp,"fit_polynomial","fit_amoeba_solver",xp);
	cout<< "*********fit polynomial using fit_amoeba_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xp[0] << endl;
	cout << "a1 = " << xp[1]<< endl;
	cout << "a2 = " << xp[2] << endl;
	cout << "a3 = " << xp[3] << endl;	
	 
	TEST_NEAR("fg->g(1) ", fp->g(1), pol(1), eps); 
	TEST_NEAR("fg->g(2) ", fp->g(2),pol(2), eps); 
	TEST_NEAR("fg->g(3) ", fp->g(3),pol(3), eps);

	//fit polynomial using fit_svd_solver
	f.fit(xi,yp,"fit_polynomial","fit_svd_solver",xp);
	cout<< "*********fit polynomial using fit_svd_solver,parameter shows below:***********"<<endl;
	cout << "a0 = " << xp[0] << endl;
	cout << "a1 = " << xp[1]<< endl;
	cout << "a2 = " << xp[2] << endl;
	cout << "a3 = " << xp[3] << endl;	
	 
	TEST_NEAR("fg->g(1) ", fp->g(1), pol(1), eps); 
	TEST_NEAR("fg->g(2) ", fp->g(2),pol(2), eps); 
	TEST_NEAR("fg->g(3) ", fp->g(3),pol(3), eps);

	//*************************Radial_Basis_Function**************************
	//Test fit radial_basis_function using fit_lm_solver
	f.fit(xir,yr,"fit_radial_basis_function","fit_lm_solver",xr);
	cout<< "*********fit radial_basis_function using fit_lm_solver,parameter shows below:***********"<<endl;
	//cout << "w0 = " << xr[0] << endl;
	//cout << "w1 = " << xr[1]<< endl;
	//cout << "w2 = " << xr[2] << endl;
	 for (unsigned i=0;i<xr.size();i++)
	{
		cout << "w"<<i<<" = " << xr[i] << endl;
	}
	
	TEST_NEAR("fg->g(1) ", fr->g(1), rbf(1), eps); 
	TEST_NEAR("fg->g(4) ", fr->g(4), rbf(4), eps); 
	TEST_NEAR("fg->g(0) ", fr->g(0), rbf(0), eps);

	//fit radial_basis_function using fit_amoeba_solver
	f.fit(xir,yr,"fit_radial_basis_function","fit_amoeba_solver",xr);
	cout<< "*********fit radial_basis_function using fit_amoeba_solver,parameter shows below:***********"<<endl;
	for (unsigned i=0;i<xr.size();i++)
	{
		cout << "w"<<i<<" = " << xr[i] << endl;
	}
	 
	TEST_NEAR("fg->g(1) ", fr->g(1), rbf(1), eps); 
	TEST_NEAR("fg->g(4) ", fr->g(4), rbf(4), eps); 
	TEST_NEAR("fg->g(0) ", fr->g(0), rbf(0), eps);

	//fit radial_basis_function using fit_svd_solver
	f.fit(xir,yr,"fit_radial_basis_function","fit_svd_solver",xr);
	cout<< "*********fit radial_basis_function using fit_svd_solver,parameter shows below:***********"<<endl;
	for (unsigned i=0;i<xr.size();i++)
	{
		cout << "w"<<i<<" = " << xr[i] << endl;
	}
	 
	TEST_NEAR("fg->g(1) ", fr->g(1), rbf(1), eps); 
	TEST_NEAR("fg->g(4) ", fr->g(4), rbf(4), eps); 
	TEST_NEAR("fg->g(0) ", fr->g(0), rbf(0), eps);


}

TESTMAIN(test_all);
