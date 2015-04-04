////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_polynomial 
////////////////////////////////////////

#ifndef fit_polynomial_h_
#define fit_polynomial_h_
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_function.h>
#include <fit/fit_polynomial_init.h>
using namespace std;
class polynomial_least_squares_fn : public fit_least_squares_function
{
public:
	//: Constructor
	polynomial_least_squares_fn(vnl_vector<double> const& xi,
		vnl_vector<double> const& y): 
	//    vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::no_gradient), xi_(xi), y_(y){}  
	//fit_least_squares_function(3, xi.size(),vnl_least_squares_function::use_gradient), xi_(xi), y_(y){}  
	fit_least_squares_function(xi,y,4 ), xi_(xi), y_(y){}  
	//: Destructor
	~polynomial_least_squares_fn() {}
	virtual void f(vnl_vector<double> const& params,
		vnl_vector<double>& residuals);

	virtual void gradf(vnl_vector<double> const& params,
		vnl_matrix<double>& jacobian);
protected:
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
};


class fit_polynomial:public fit_function
{

public:
	fit_polynomial(){}
	virtual void setDataInit(vnl_vector<double> const& xi,vnl_vector<double> const& y){
		this->lsif_=new fit_polynomial_init(xi,y);
	}
	virtual void setData(vnl_vector<double> const& xi,	vnl_vector<double> const& y){
		this->lsqf_=new polynomial_least_squares_fn(xi,y);
	}
	virtual double g( double d){
		vnl_vector<double> params(this->x_.size());
		params=this->x_;
		double a0=  params[0];
		double a1 =  params[1];
		double a2 =  params[2];
		double a3 =  params[3];
		double dn=(d-this->avex_)/ (this->stdx_);

		double res= pow(dn,3.0)*a3+pow(dn,2.0)*a2+dn*a1+a0;

		return res*(this->stdy_)+this->avey_;
	}
	virtual string name(){return "fit_polynomial";}
};

#endif // fit_polynomial_h_

