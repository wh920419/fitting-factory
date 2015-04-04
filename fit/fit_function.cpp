////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file implement fit_function, the base of all fit function
////////////////////////////////////////

#include <iostream>
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
//#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_least_squares_init_function.h>
#include <fit/fit_least_squares_function.h>   
#include <fit/fit_function.h>

using namespace std;

void fit_function::myNormalize(){
	vnl_vector<double> nx(this->xi_.size()),ny(this->y_.size());
	xi_norm_=nx;
	y_norm_=ny;
	double avex=0,avey=0;
	double stx=0,sty=0;

	vnl_matrix<double> C(2,2,0);
	vector<vnl_matrix<double> > data; 

	for(unsigned i = 0; i<xi_.size(); i++) 
	{ 
		avex+=xi_[i];
	} 
	avex/=xi_.size();

	for(unsigned i = 0; i<y_.size(); i++) 
	{ 
		avey+=y_[i];
	} 
	avey/=y_.size();

	for(unsigned i = 0; i<xi_.size(); i++) 
	{ 
		stx+=(xi_[i]-avex)*(xi_[i]-avex);
	} 
	//stx/=xi_.size();
	stx=sqrt(stx);
	for(unsigned i = 0; i<y_.size(); i++) 
	{ 
		sty+=(y_[i]-avey)*(y_[i]-avey);
	} 
	//sty/=y_.size();
	sty=sqrt(sty);
	
	for(unsigned i = 0; i<xi_.size(); i++) 
	{ 
		xi_norm_[i]=(xi_[i]-avex)/stx;		
	} 
	for(unsigned i = 0; i<y_.size(); i++) 
	{ 
		y_norm_[i]=(y_[i]-avey)/sty;		 
	} 	
	avex_=avex;avey_=avey;
	stdx_=stx;stdy_=sty;
}


