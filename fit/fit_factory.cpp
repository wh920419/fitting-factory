////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 18
//
//  This file implement  fit_factory 
////////////////////////////////////////

#include <fit/fit_function.h> 
#include <fit/fit_solver.h>
#include <fit/fit_factory.h>

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_svd.h> 
#include <iostream>
#include <vector>
#include <map>
using namespace std;

bool fit_factory::register_solver(fit_solver * s){
	string name= s->name();//the name of solver	
	pair<string, fit_solver*> p(name, s); 
	solver_.insert(p); 
	return true;
}
bool fit_factory::register_function(fit_function *fn){
	string name= fn->name();//the name of solver	
	pair<string, fit_function *> p(name, fn); 
	fit_fun_.insert(p); 
	//fit_fun_=fn;
	return true;
}
bool fit_factory::fit(vnl_vector<double>xi,vnl_vector<double>y,string f,string sov,vnl_vector<double>&x){
	//vnl_vector<double> nx(fit_fun_->xi_.size()),ny(fn->y_.size());
	vnl_vector<double> t(xi.size()) ;
	out_y_=t;

	fit_function * fn=fit_fun_[f];
	fn->xi_=xi;
	fn->y_=y;
 
	fn->myNormalize();
	fn->setData(fn->xi_norm_,fn->y_norm_); 
	fn->setDataInit(fn->xi_norm_,fn->y_norm_);
	//fn->setData(xi,y);//normalize later! todo@Hua
	//fn->setDataInit(xi,y);
	 fit_solver* s=solver_[sov];
	 bool r=s->solve(fn,x);
	 fn->x_=x;

	 if (!r) {
		 s->retry(fn,x,10000,1e-10,1e-10);
		 fn->x_=x;
	 }
	 s->outcome(x);
	 
	 for (unsigned i=0;i<fn->xi_norm_.size();i++)
	 {
		 out_y_[i]=fn->g(fn->xi_[i]);
	 }
	 return r;
}

vnl_vector<double> fit_factory::outy(){
	return out_y_;
}