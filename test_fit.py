import py_fit
import matplotlib.pyplot as plt
import numpy as np
#  generate random samples

x = 5 * np.random.randn(1000)

x.sort()
gauss = 2 * np.exp(- x ** 2 / 5) - 3;
poly=5*x**3+4*x**2+x*3+2

xe =2.5* np.random.randn(100)
xe.sort()
exponetial = np.exp(xe)+1.0;

# call fitting library. note that you need tolist() called on the numpy array to coverted to a regular Python List.
gauss_lm = py_fit.fit_gauss(x.tolist(),gauss.tolist(),"fit_lm_solver")
gauss_amoe  = py_fit.fit_gauss(x.tolist(),gauss.tolist(),"fit_amoeba_solver")
gauss_svd = py_fit.fit_gauss(x.tolist(),gauss.tolist(),"fit_svd_solver")

exponetial_lm = py_fit.fit_exponential(xe.tolist(),exponetial.tolist(),"fit_lm_solver")
exponetial_amoe  = py_fit.fit_exponential(xe.tolist(),exponetial.tolist(),"fit_amoeba_solver")
exponetial_svd = py_fit.fit_exponential(xe.tolist(),exponetial.tolist(),"fit_svd_solver")

poly_lm = py_fit.fit_polynomial(x.tolist(),poly.tolist(),"fit_lm_solver")
poly_amoe  = py_fit.fit_polynomial(x.tolist(),poly.tolist(),"fit_amoeba_solver")
poly_svd = py_fit.fit_polynomial(x.tolist(),poly.tolist(),"fit_svd_solver")

xr =2.5* np.random.randn(15)
xr.sort()
rbf=np.exp(-1.5*(xr-0)*(xr-0) )+2*np.exp(-1.5*(xr-1)*(xr-1) )+3*np.exp(-1.5*(xr-2)*(xr-2) )
rbf_lm = py_fit.fit_rbf(xr.tolist(),rbf.tolist(),"fit_lm_solver")
rbf_amoe  = py_fit.fit_rbf(xr.tolist(),rbf.tolist(),"fit_amoeba_solver")
rbf_svd = py_fit.fit_rbf(xr.tolist(),rbf.tolist(),"fit_svd_solver")


#plotting functions
plt.plot(x,gauss,"-",ms=10)
plt.plot(x,gauss_lm ,".",ms=10)
plt.plot(x,gauss_amoe,"-",ms=10)
plt.figure()
plt.plot(xe,exponetial,"o",ms=10)
plt.plot(xe,exponetial_amoe,"*",ms=10)
plt.plot(xe,exponetial_lm ,".",ms=10)
#plt.plot(xe,exponetial_svd,"-",ms=10)
plt.figure()
plt.plot(x,poly,".",ms=10)
plt.plot(x,poly_lm ,"o",ms=10)
plt.plot(x,poly_amoe,"*",ms=10)
plt.plot(x,poly_svd,".",ms=10)
plt.figure()
plt.plot(xr,rbf,".",ms=10)
plt.plot(xr,rbf_lm,"o",ms=10)
plt.plot(xr,rbf_amoe,"*",ms=10)
#plt.plot(xr,rbf_svd,"-",ms=10)

plt.show()
