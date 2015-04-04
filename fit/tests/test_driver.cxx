#include <testlib/testlib_register.h> 

DECLARE( test_gauss_lm ); 
DECLARE( test_poly_svd ); 
DECLARE( test_exp ); 
 DECLARE( test_rbf ); 
DECLARE( test_amoeba ); 
DECLARE( test_all ); 
void 
register_tests() 
{ 

//REGISTER( test_gauss_lm );
//REGISTER( test_poly_svd );
 //REGISTER( test_exp );
//REGISTER( test_rbf );
//REGISTER( test_amoeba );
REGISTER( test_all );
} 
DEFINE_MAIN; 