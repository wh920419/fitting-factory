////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file implement svd solver.
////////////////////////////////////////


#include <fit/fit_function.h> 
#include <fit/fit_linear_solver.h>
#include <fit/fit_svd_solver.h>

#include <iostream>
#include <vector>
#include <math.h>
#include <vnl/vnl_matrix.h> 
#include <string>
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
using namespace std;

bool fit_svd_solver::solve(fit_function  *fn,vnl_vector<double> &x){

	vnl_vector<double> xi=fn->xi_norm_;
	vnl_vector<double> y=fn->y_norm_;
	vnl_matrix<double> M(5,5,0.0);
	double d,d2;

	d=0;d2=0;double k1=0,k2=0;
	for (unsigned i=0;i<xi.size();i++)
	{
		M[0][0]+=pow(xi[i],6.0); M[0][1]+=pow(xi[i],5.0); M[0][2]+=pow(xi[i],4.0); M[0][3]+=(pow(xi[i],3.0)*y[i]);M[0][4]+=pow(xi[i],3.0);
		M[1][0]+=pow(xi[i],5.0); M[1][1]+=pow(xi[i],4.0); M[1][2]+=pow(xi[i],3.0); M[1][3]+=(pow(xi[i],2.0)*y[i]);M[1][4]+= xi[i]*xi[i] ;
		M[2][0]+=pow(xi[i],4.0); M[2][1]+=pow(xi[i],3.0); M[2][2]+=pow(xi[i],2.0); M[2][3]+=(xi[i]*y[i]);M[2][4]+= xi[i] ;
		M[3][0]+=(pow(xi[i],3.0)*y[i]); M[3][1]+=(pow(xi[i],2.0)*y[i]); M[3][2]+=(xi[i]*y[i]);  M[3][3]+= y[i]*y[i] ;M[3][4]+=y[i];
		M[4][0]+=pow(xi[i],3.0); M[4][1]+=pow(xi[i],2.0); M[4][2]+= xi[i];  M[4][3]+=y[i];M[4][4]+=1;

	}

	for (unsigned i=0;i<5;i++){
		for (unsigned j=0;j<5;j++)
		{
			M[i][j]/=xi.size();
		}
	}
	vnl_svd<double> svd(M);
	svd.zero_out_absolute(); 
	unsigned rk = svd.rank();
	vnl_matrix<double> V = svd.V(); 	
	vnl_vector<double> v2 = V.get_column(4);
	cout << "parameter = " << v2 <<endl; 
	cout <<V<<endl; 
	x[0]=v2[4]/abs(v2[3]); x[1]=v2[2]/abs(v2[3]); x[2]=v2[1]/abs(v2[3]); 
	for(unsigned i=3;i<x.size();i++){
	//x.size()>3){
		x[i]=v2[0]/abs(v2[3]);
	}	
	return true;
}
string fit_svd_solver::outcome(vnl_vector<double> const&x){
	string r ="fit_svd_solver";
	cout<< "*********fit_svd_solver,parameter shows below:***********"<<endl;
	for (unsigned i=0;i<x.size();i++)
	{
		cout<<" "<<x[i]<<" "<<endl;		
	}
	return r;
}

bool fit_svd_solver::retry(fit_function  *fn,vnl_vector<double>&x,unsigned n_iter,double xtol,double ftol  ){
	return true;
}


