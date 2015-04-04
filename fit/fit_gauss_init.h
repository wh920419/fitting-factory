////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file declare fit_gauss_init_h_
////////////////////////////////////////
#ifndef fit_gauss_init_h_
#define fit_gauss_init_h_

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>

#include <fit/fit_least_squares_init_function.h>

using namespace std;
class gauss_least_squares_fn_init : public fit_least_squares_init_function
	//public vnl_least_squares_function, 
{
 public:
  //: Constructor
  gauss_least_squares_fn_init(vnl_vector<double> const& xi, vnl_vector<double> const& y) : 
  fit_least_squares_init_function(xi.size()), xi_(xi), y_(y){} 
  //: Destructor
  ~gauss_least_squares_fn_init() {}
  virtual void init(vnl_vector<double>& gauss_params) {
	  double mean = 0, xsq = 0, ymax = -vnl_numeric_traits<double>::maxval;
	  unsigned m = xi_.size();
	  for(unsigned i = 0; i<m ; ++i)
	  {
		  double x = xi_[i];
		  mean += x;
		  xsq += x*x;
		  if(y_[i]>ymax) ymax = y_[i];
	  }
	  mean/=m;
	  double var = xsq - m*mean*mean;
	  gauss_params[0] = ymax;
	  gauss_params[1] = mean;
	  gauss_params[2] = sqrt(var/m);
	  gauss_params[3] =this->y_.min_value();
  }
 protected:
  vnl_vector<double> xi_;
  vnl_vector<double> y_;
};

#endif // fit_gauss_h_
