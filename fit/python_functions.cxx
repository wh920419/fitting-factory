////////////////////////////////////////
// Hua Wang
// November 9, 2014
// ENGN2912B Assignment 19
//
//  This file is to be interfaced to Python to support easy scripting and plotting
////////////////////////////////////////
#include <string>
#include <vnl/vnl_vector.h>
#include <Python.h>

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
//static PyMethodDef py_fit_methods[6];//change this number to the number you need
static fit_factory* FF;
static fit_gauss * GAUSS;
static fit_exponential* EXPO;
static fit_polynomial *POLY;
static fit_radial_basis_function *RBF;
static fit_lm_solver *SOLVER_LM;
static fit_svd_solver *SOLVER_SVD;
static fit_amoeba_solver *SOLVER_AMO;

void register_fit_factory(){
	//fit_factory *FF=new fit_factory;
	//fit_gauss *GAUSS=new fit_gauss;
	//fit_exponential *fe=new fit_exponential;
	//fit_polynomial *fp=new fit_polynomial;
	//fit_radial_basis_function *fr=new fit_radial_basis_function;
	//PyObject* res;
	//fit_lm_solver *ls=new fit_lm_solver;
	//fit_amoeba_solver *as=new fit_amoeba_solver;
	//fit_svd_solver *ss=new fit_svd_solver;
	FF=new fit_factory;
	GAUSS=new fit_gauss;
	EXPO=new fit_exponential;
	POLY=new fit_polynomial;
	RBF=new fit_radial_basis_function;
	PyObject* res;
	SOLVER_LM=new fit_lm_solver;
	SOLVER_AMO=new fit_amoeba_solver;
	SOLVER_SVD=new fit_svd_solver;

	FF->register_function( GAUSS);
	FF->register_function( EXPO);
	FF->register_function( POLY);
	FF->register_function( RBF);

	FF->register_solver(SOLVER_LM);
	FF->register_solver(SOLVER_AMO);
	FF->register_solver(SOLVER_SVD);

	//return Py_BuildValue("i", 1);
}

//static PyObject* remove_fit_factory(PyObject * /*self*/, PyObject *args){
void remove_fit_factory( ){
	fit_factory *d=FF;
	delete SOLVER_LM;SOLVER_LM=NULL;	
	delete SOLVER_SVD;SOLVER_AMO=NULL;	
	delete SOLVER_SVD;SOLVER_SVD=NULL;	

	delete GAUSS;GAUSS=NULL;
	delete RBF;RBF=NULL;
	delete POLY;POLY=NULL;
	delete EXPO;EXPO=NULL;
	//d->fit_fun_
	delete d;   
	FF=NULL;   
	//return NULL;
}

static PyObject* py_fit_gauss(PyObject * /*self*/, PyObject *args) 
{ 
	PyObject* xList_obj,*yList_obj;
	
	char * fit_solver_type;
	if(! PyArg_ParseTuple(args, "O!O!s", &PyList_Type, &xList_obj, 
		&PyList_Type, &yList_obj,&fit_solver_type) ) return NULL; //&fit_func_type
	// query to get the data 
	int num_elem = PyList_Size(xList_obj); 
	/* should raise an error here. */ 
	if(num_elem< 0) return NULL; /* Not a list */ 
	vnl_vector<double> xi(num_elem), y(num_elem); 
	/* iterate over items of the list, grabbing PyObjects, and 
	converting to doubles */ 
	for (unsigned i=0; i<num_elem; i++){ 
		/* grab the string object from the next element of the list */ 
		PyObject* listItemX_obj,*listItemY_obj; 
		listItemX_obj = PyList_GetItem(xList_obj, i); 
		xi[i]= (PyFloat_AsDouble(listItemX_obj ));/* and convert to double*/ 
		listItemY_obj = PyList_GetItem(yList_obj, i); 
		y[i] = (PyFloat_AsDouble( listItemY_obj )); 
	}
	//**************C+ code for gaussian****************
	register_fit_factory();
	string solver_name=fit_solver_type;
	vnl_vector<double> output_y(num_elem);
	vnl_vector<double> params(4),y_out(num_elem);
	FF->fit(xi,y,"fit_gauss",solver_name,params);
	
	//**************************************
	//create new List 
	PyObject* output_vals_obj = PyList_New(num_elem); 
	y_out=FF->outy();
	for(unsigned i=0; i<num_elem; i++) 
		//set each list item using Py_BuildValue 
	{
		PyList_SetItem(output_vals_obj, i, Py_BuildValue("d", y_out[i] ) );		
	}
	
	//return output_vals_obj;
	remove_fit_factory();
	return Py_BuildValue("O",output_vals_obj ); 
} 


static PyObject *py_fit_rbf(PyObject * /*self*/, PyObject *args)
{
		PyObject* xList_obj,*yList_obj;	
	char * fit_solver_type;
	if(! PyArg_ParseTuple(args, "O!O!s", &PyList_Type, &xList_obj, 
		&PyList_Type, &yList_obj,&fit_solver_type) ) return NULL; //&fit_func_type
	// query to get the data 
	int num_elem = PyList_Size(xList_obj); 
	/* should raise an error here. */ 
	if(num_elem< 0) return NULL; /* Not a list */ 
	vnl_vector<double> xi(num_elem), y(num_elem); 
	/* iterate over items of the list, grabbing PyObjects, and 
	converting to doubles */ 
	for (unsigned i=0; i<num_elem; i++){ 
		/* grab the string object from the next element of the list */ 
		PyObject* listItemX_obj,*listItemY_obj; 
		listItemX_obj = PyList_GetItem(xList_obj, i); 
		xi[i]= (PyFloat_AsDouble(listItemX_obj ));/* and convert to double*/ 
		listItemY_obj = PyList_GetItem(yList_obj, i); 
		y[i] = (PyFloat_AsDouble( listItemY_obj )); 
	}
	//**************C+ code for gaussian****************
	register_fit_factory();
	string solver_name=fit_solver_type;
	//vnl_vector<double> output_y(num_elem);
	vnl_vector<double> params(num_elem),y_out(num_elem);
	FF->fit(xi,y,"fit_radial_basis_function",solver_name,params);	
	//**************************************
	//create new List 
	PyObject* output_vals_obj = PyList_New(num_elem); 
	y_out=FF->outy();
	for(unsigned i=0; i<num_elem; i++) 
		//set each list item using Py_BuildValue 
	{
		PyList_SetItem(output_vals_obj, i, Py_BuildValue("d", y_out[i] ) );		
	}	
	//return output_vals_obj;
	remove_fit_factory();
	return Py_BuildValue("O",output_vals_obj );  
    
}

static PyObject *py_fit_exponential(PyObject * /*self*/, PyObject *args)
{
	PyObject* xList_obj,*yList_obj;	
	char * fit_solver_type;
	if(! PyArg_ParseTuple(args, "O!O!s", &PyList_Type, &xList_obj, 
		&PyList_Type, &yList_obj,&fit_solver_type) ) return NULL; //&fit_func_type
	// query to get the data 
	int num_elem = PyList_Size(xList_obj); 
	/* should raise an error here. */ 
	if(num_elem< 0) return NULL; /* Not a list */ 
	vnl_vector<double> xi(num_elem), y(num_elem); 
	/* iterate over items of the list, grabbing PyObjects, and 
	converting to doubles */ 
	for (unsigned i=0; i<num_elem; i++){ 
		/* grab the string object from the next element of the list */ 
		PyObject* listItemX_obj,*listItemY_obj; 
		listItemX_obj = PyList_GetItem(xList_obj, i); 
		xi[i]= (PyFloat_AsDouble(listItemX_obj ));/* and convert to double*/ 
		listItemY_obj = PyList_GetItem(yList_obj, i); 
		y[i] = (PyFloat_AsDouble( listItemY_obj )); 
	}
	//**************C+ code for gaussian****************
	register_fit_factory();
	string solver_name=fit_solver_type;
	//vnl_vector<double> output_y(num_elem);
	vnl_vector<double> params(3),y_out(num_elem);
	FF->fit(xi,y,"fit_exponential",solver_name,params);	
	//**************************************
	//create new List 
	PyObject* output_vals_obj = PyList_New(num_elem); 
	y_out=FF->outy();
	for(unsigned i=0; i<num_elem; i++) 
		//set each list item using Py_BuildValue 
	{
		PyList_SetItem(output_vals_obj, i, Py_BuildValue("d", y_out[i] ) );		
	}	
	//return output_vals_obj;
	remove_fit_factory();
	return Py_BuildValue("O",output_vals_obj );     
}

static PyObject *py_fit_polynomial(PyObject * /*self*/, PyObject *args)
{
	PyObject* xList_obj,*yList_obj;	
	char * fit_solver_type;
	if(! PyArg_ParseTuple(args, "O!O!s", &PyList_Type, &xList_obj, 
		&PyList_Type, &yList_obj,&fit_solver_type) ) return NULL; //&fit_func_type
	// query to get the data 
	int num_elem = PyList_Size(xList_obj); 
	/* should raise an error here. */ 
	if(num_elem< 0) return NULL; /* Not a list */ 
	vnl_vector<double> xi(num_elem), y(num_elem); 
	/* iterate over items of the list, grabbing PyObjects, and 
	converting to doubles */ 
	for (unsigned i=0; i<num_elem; i++){ 
		/* grab the string object from the next element of the list */ 
		PyObject* listItemX_obj,*listItemY_obj; 
		listItemX_obj = PyList_GetItem(xList_obj, i); 
		xi[i]= (PyFloat_AsDouble(listItemX_obj ));/* and convert to double*/ 
		listItemY_obj = PyList_GetItem(yList_obj, i); 
		y[i] = (PyFloat_AsDouble( listItemY_obj )); 
	}
	//**************C+ code for gaussian****************
	register_fit_factory();
	string solver_name=fit_solver_type;
	//vnl_vector<double> output_y(num_elem);
	vnl_vector<double> params(4),y_out(num_elem);
	FF->fit(xi,y,"fit_polynomial",solver_name,params);	
	//**************************************
	//create new List 
	PyObject* output_vals_obj = PyList_New(num_elem); 
	y_out=FF->outy();
	for(unsigned i=0; i<num_elem; i++) 
		//set each list item using Py_BuildValue 
	{
		PyList_SetItem(output_vals_obj, i, Py_BuildValue("d", y_out[i] ) );		
	}	
	//return output_vals_obj;
	remove_fit_factory();
	return Py_BuildValue("O",output_vals_obj );  
    
}


static PyMethodDef py_fit_methods[] = { 
	{"fit_gauss",py_fit_gauss, METH_VARARGS,"fit points to a Gaussian using the python API" },
	{"fit_exponential",py_fit_exponential, METH_VARARGS,"fit points to a Exponential using the python API" },
	{"fit_polynomial",py_fit_polynomial, METH_VARARGS,"fit points to a Polynomial using the python API" },
	{"fit_rbf",py_fit_rbf, METH_VARARGS,"fit points to a Radial Basis Function using the python API" },

	{NULL, NULL, 0, NULL} /* Sentinel */ 
}; 

PyMODINIT_FUNC
initpy_fit(void)
{        
    PyObject* pyfit=Py_InitModule("py_fit", py_fit_methods);    
}
