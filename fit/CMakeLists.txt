########################################
# Hua Wang
# Nov 14, 2014
# ENGN2912B Assignment 19
#
########################################

# This is hwang/fit/CMakeLists.txt 

    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
    endif(COMMAND cmake_policy)


SET(fit_sources
      
fit_gauss.cxx fit_gauss.h fit_gauss_init.h 
fit_polynomial.cxx fit_polynomial.h  fit_polynomial_init.h
fit_exponential.cxx fit_exponential.h fit_exponential_init.h
fit_radial_basis_function.cxx fit_radial_basis_function.h fit_radial_basis_function_init.h

fit_least_squares_init_function.h
fit_levenberg_marquardt.h
fit_function.h fit_function.cpp
fit_exponential.h
fit_polynomial.h
fit_least_squares_function.h
 

fit_factory.h fit_factory.cpp
fit_solver.h
fit_non_linear_solver.h
fit_linear_solver.h
fit_svd_solver.h fit_svd_solver.cpp
fit_amoeba_solver.h fit_amoeba_solver.cpp
fit_lm_solver.h fit_lm_solver.cpp
 )


ADD_LIBRARY(fit ${fit_sources})

TARGET_LINK_LIBRARIES(fit vnl_algo vnl)

FIND_PACKAGE(PYTHONLIBS)


IF( PYTHONLIBS_FOUND )

    
INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
     
SET(py_fit_sources
        
# python_functions.h   
python_functions.cxx
        )

    
PYTHON_ADD_MODULE(py_fit ${py_fit_sources})
    
TARGET_LINK_LIBRARIES(py_fit fit ${PYTHON_LIBRARY})


ENDIF(PYTHONLIBS_FOUND)



IF( BUILD_TESTING )
  
SUBDIRS(tests)

ENDIF( BUILD_TESTING )

