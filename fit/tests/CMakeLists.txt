########################################
# Hua Wang
# Nov 14, 2014
# ENGN2912B Assignment 18
#
########################################

# This is username/fit/tests/CMakeLists.txt 
ADD_EXECUTABLE( hwang_prob_1 
# Driver source and utilities 
test_driver.cxx 
# The tests 

test_all.cxx
test_gauss_lm.cxx
#test_poly.cxx
test_exp.cxx
test_rbf.cxx
test_amoeba.cxx
test_poly_svd.cxx
) 
TARGET_LINK_LIBRARIES(hwang_prob_1 fit vnl vul testlib) 
 
ADD_TEST( test_gauss_lm fit_test_all test_gauss_lm ) 
#ADD_TEST( test_poly fit_test_all test_poly ) 
ADD_TEST( test_exp fit_test_all test_exp )
ADD_TEST( test_rbf fit_test_all test_rbf )
ADD_TEST( test_amoeba fit_test_all test_amoeba )
ADD_TEST( test_all fit_test_all test_all )
ADD_TEST( test_poly_svd fit_test_all test_poly_svd )