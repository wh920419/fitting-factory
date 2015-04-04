////////////////////////////////////////
// Hua Wang
// October 25, 2014
// ENGN2912B Assignment 17
//
//  This file contain functions to implement fit_gauss
////////////////////////////////////////

#include <cmath>
#include <iostream>

#include <vcl_cassert.h>
#include <vcl_iostream.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_fastops.h>
#include <vnl/vnl_vector_ref.h>
#include <vnl/vnl_matrix_ref.h>

#include "fit_gauss.h"
#include "fit_gradient_descent.h"

double sumR(vnl_vector<double> v){
	double s=0;
	for (unsigned i=0;i<v.size();i++)
	{
		s+=v[i]*v[i];
	}
	return s;
}
void fit_gradient_descent::setLamda(double d){
	this->lamda_=d;

}
bool fit_gradient_descent::minimize(vnl_vector<double>& x)
{
	if ( f_->has_gradient() )
		return minimize_using_gradient(x);
	else
	return false;
}

bool fit_gradient_descent::minimize_using_gradient(vnl_vector<double>& x)
{
	num_iterations_ = 0;
	//vnl_vector<double> x;
	//double lamda=0.001;
	//fsm
	if (! f_->has_gradient()) {
		vcl_cerr << __FILE__ ": called method minimize_using_gradient(), but f_ has no gradient.\n";
		return false;
	}
	long m = f_->get_number_of_residuals(); // I  Number of residuals, must be > #unknowns
	long n = f_->get_number_of_unknowns();  // I  Number of unknowns

	if (m < n) {
		vcl_cerr << __FILE__ ": Number of unknowns("<<n<<") greater than number of data ("<<m<<")\n";
		failure_code_ = ERROR_DODGY_INPUT;
		return false;
	}

	vnl_vector<double> residuals(m);
	vnl_vector<double> params=x;
	vnl_matrix<double> jacobian(m,n);
	vnl_matrix<double> jacobianT=jacobian.transpose();

	f_->gradf(params,jacobian);//Calculate jacobian
	f_->f(params,residuals);//calculate residual

	jacobianT=jacobian.transpose();
	
	while (sumR(residuals)> (this->ftol))
	{
		f_->gradf(params,jacobian);//Calculate jacobian
		f_->f(params,residuals);//calculate residual
		jacobianT=jacobian.transpose();
		params=params-lamda_*jacobianT*residuals;
		num_iterations_ ++;
	}
	x=params;
	return true;
}
//--------------------------------------------------------------------------------

void fit_gradient_descent::diagnose_outcome() const
{
	diagnose_outcome(vcl_cerr);
}

// fsm: should this function be a method on vnl_nonlinear_minimizer?
// if not, the return codes should be moved into LM.
void fit_gradient_descent::diagnose_outcome(vcl_ostream& s) const
{
#define whoami "fit_gradient_descent"
	//if (!verbose_) return;
	switch (failure_code_) {
		//  case -1:
		// have already warned.
		//    return;
	case ERROR_FAILURE:
		s << (whoami ": OIOIOI -- failure in leastsquares function\n");
		break;
	case ERROR_DODGY_INPUT:
		s << (whoami ": OIOIOI -- lmdif dodgy input\n");
		break;
	case CONVERGED_FTOL: // ftol
		s << (whoami ": converged to ftol\n");
		break;
	case CONVERGED_XTOL: // xtol
		s << (whoami ": converged to xtol\n");
		break;
	case CONVERGED_XFTOL: // both
		s << (whoami ": converged nicely\n");
		break;
	case CONVERGED_GTOL:
		s << (whoami ": converged via gtol\n");
		break;
	case FAILED_TOO_MANY_ITERATIONS:
		s << (whoami ": too many iterations\n");
		break;
	case FAILED_FTOL_TOO_SMALL:
		s << (whoami ": ftol is too small. no further reduction in the sum of squares is possible.\n");
		break;
	case FAILED_XTOL_TOO_SMALL:
		s << (whoami ": xtol is too small. no further improvement in the approximate solution x is possible.\n");
		break;
	case FAILED_GTOL_TOO_SMALL:
		s << (whoami ": gtol is too small. Fx is orthogonal to the columns of the jacobian to machine precision.\n");
		break;
	default:
		s << (whoami ": OIOIOI: unkown info code from lmder.\n");
		break;
	}
	unsigned int m = f_->get_number_of_residuals();
	s << whoami ": " << num_iterations_ << " iterations, "
		<< vcl_endl;
#undef whoami
}



















