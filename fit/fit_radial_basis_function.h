////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_radial_basis_function_h_
////////////////////////////////////////

#ifndef fit_radial_basis_function_h_
#define fit_radial_basis_function_h_
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
#include <fit/fit_function.h>
#include <fit/fit_radial_basis_function_init.h>
using namespace std;
class radial_basis_function_least_squares_fn : public fit_least_squares_function
{
public:
	//: Constructor
	radial_basis_function_least_squares_fn(vnl_vector<double> const& xi,
		vnl_vector<double> const& y): 
	//    vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::no_gradient), xi_(xi), y_(y){}  
	//fit_least_squares_function(3, xi.size(),vnl_least_squares_function::use_gradient), xi_(xi), y_(y){}
	// @rbf_redo
	fit_least_squares_function(xi,y,xi.size()), xi_(xi), y_(y){}  
	//: Destructor
	~radial_basis_function_least_squares_fn() {}
	virtual void f(vnl_vector<double> const& params,
		vnl_vector<double>& residuals);

	virtual void gradf(vnl_vector<double> const& params,
		vnl_matrix<double>& jacobian);
protected:
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
};


class fit_radial_basis_function:public fit_function
{

public:
	fit_radial_basis_function(){}
	virtual void setDataInit(vnl_vector<double> const& xi,vnl_vector<double> const& y){
		this->lsif_=new fit_radial_basis_function_init(xi,y);
	}
	virtual void setData(vnl_vector<double> const& xi,	vnl_vector<double> const& y){
		this->lsqf_=new radial_basis_function_least_squares_fn(xi,y);
	}
	virtual double g( double d){
		vnl_vector<double> params(this->x_.size());
		params=this->x_;
		//double w0=  params[0];
		//double w1 =  params[1];
		//double w2 =  params[2];
		 
		double dn=(d-this->avex_)/ (this->stdx_);

		double delta=1.0;
		 double res=0;
		for (unsigned i=0;i<params.size();i++)
		{
			res+=params[i]*exp(-1.5*delta*(dn-delta*i)*(dn-delta*i) );
		}

		//double res=  w0*exp(-1.5*delta*(dn-0)*(dn-0) )+w1*exp(-1.5*delta*(dn-delta)*(dn-delta) )+w2*exp(-1.5*delta*(dn-2*delta)*(dn-2*delta) );

		return res*(this->stdy_)+this->avey_;
	}
	virtual string name(){return "fit_radial_basis_function";}
};




#endif // fit_radial_basis_function_h_

