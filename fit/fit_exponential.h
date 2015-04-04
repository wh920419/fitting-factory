////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file declare fit_exponential 
////////////////////////////////////////

#ifndef fit_exponential_h_
#define fit_exponential_h_
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_function.h>
#include <fit/fit_exponential_init.h>
using namespace std;
class exponential_least_squares_fn : public fit_least_squares_function
{
public:
	//: Constructor
	exponential_least_squares_fn(vnl_vector<double> const& xi,
		vnl_vector<double> const& y): 

	fit_least_squares_function(xi,y,3 ), xi_(xi), y_(y){}  
	//: Destructor
	~exponential_least_squares_fn() {}
	virtual void f(vnl_vector<double> const& params,
		vnl_vector<double>& residuals);

	virtual void gradf(vnl_vector<double> const& params,
		vnl_matrix<double>& jacobian);
protected:
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
};


class fit_exponential:public fit_function
{

public:
	fit_exponential(){}
	virtual void setDataInit(vnl_vector<double> const& xi,vnl_vector<double> const& y){
		this->lsif_=new fit_exponential_init(xi,y);
	}
	virtual void setData(vnl_vector<double> const& xi,	vnl_vector<double> const& y){
		this->lsqf_=new exponential_least_squares_fn(xi,y);
	}
	virtual double g( double d){
		vnl_vector<double> params(this->x_.size());
		params=this->x_;
		double a0=  params[0];
		double a =  params[1];
		double b =  params[2];
		double dn=(d-this->avex_)/ (this->stdx_);

		double arg = exp(b*dn);
		double res= a*arg+a0;

		return res*(this->stdy_)+this->avey_;
	}
	virtual string name(){return "fit_exponential";}
};




#endif // fit_exponential_h_

