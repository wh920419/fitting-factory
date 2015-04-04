########################################
# Hua Wang
# Nov 14, 2014
# ENGN2912B Assignment 19
#
########################################

# This is hwang_prob_1/CMakeLists.txt 
PROJECT(hwang_prob_1) 
FIND_PACKAGE(VXL) 
IF(VXL_FOUND) 
# include the standard VXL stuff 
SET(VXL_PROVIDE_STANDARD_OPTIONS 1) 
INCLUDE(${VXL_CMAKE_DIR}/UseVXL.cmake) 
INCLUDE_DIRECTORIES(${hwang_prob_1_SOURCE_DIR})  
SUBDIRS(fit) 
ENDIF(VXL_FOUND) 





