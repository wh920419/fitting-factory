////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_gaussian, which derive from fit_function 
////////////////////////////////////////
#ifndef fit_gauss_h_
#define fit_gauss_h_
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_function.h>
#include <fit/fit_gauss_init.h>
using namespace std;
class gauss_least_squares_fn : public fit_least_squares_function
{
public:
	//: Constructor
	gauss_least_squares_fn(vnl_vector<double> const& xi,
		vnl_vector<double> const& y): 
	//    vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::no_gradient), xi_(xi), y_(y){}  
	//fit_least_squares_function(3, xi.size(),vnl_least_squares_function::use_gradient), xi_(xi), y_(y){}  
	fit_least_squares_function(xi,y,4 ), xi_(xi), y_(y){}  
	//: Destructor
	~gauss_least_squares_fn() {}

	//: The main function.
	//  Given the parameter vector x, compute the vector of residuals fx.
	//  fx has been sized appropriately before the call.
	virtual void f(vnl_vector<double> const& gauss_params,
		vnl_vector<double>& residuals);

	virtual void gradf(vnl_vector<double> const& gauss_params,
		vnl_matrix<double>& jacobian);
protected:
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
};


class fit_gauss:public fit_function
{

public:
	fit_gauss(){}
	virtual void setDataInit(vnl_vector<double> const& xi,vnl_vector<double> const& y){
			this->lsif_=new gauss_least_squares_fn_init(xi,y);
	}
	virtual void setData(vnl_vector<double> const& xi,	vnl_vector<double> const& y){
		this->lsqf_=new gauss_least_squares_fn(xi,y);
	}
	virtual double g( double d){
		vnl_vector<double> params(this->x_.size());
		params=this->x_;
		double alpha =  params[0];
		double mu =  params[1];
		double sigma =  params[2];
		double a0=params[3];

		double dn=(d-this->avex_)/ (this->stdx_);


		double arg = (dn-mu)/sigma;
		double res=alpha*exp(-arg*arg/2)+a0;
		double r=res*(this->stdy_)+this->avey_;
		return r;
			
	}
	virtual string name(){return "fit_gauss";}
};




#endif // fit_gauss_h_
