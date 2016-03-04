/*****************************************************************************

      TestDef.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"



#define flip_CHECK_THROW(expr) \
   {bool flip_check_throw_flag = false; \
   try {expr;} catch (...) {flip_check_throw_flag = true;} \
   if (!flip_check_throw_flag) std::terminate ();}

#if (flip_COMPILER == flip_COMPILER_CLANG) || (flip_COMPILER == flip_COMPILER_GNU)
   #define flip_TEST(expr) \
      if (!(expr)) {printf ("      Test failed: %s\n", __PRETTY_FUNCTION__); std::terminate ();}
   #define flip_TEST_FAILED \
      {printf ("      Test failed: %s\n", __PRETTY_FUNCTION__); std::terminate ();}

#elif (flip_COMPILER == flip_COMPILER_MSVC)
   #define flip_TEST(expr) \
      if (!(expr)) {printf ("      Test failed: %s\n", __FUNCDNAME__); std::terminate ();}
   #define flip_TEST_FAILED \
      {printf ("      Test failed: %s\n", __FUNCDNAME__); std::terminate ();}

#else
   #error Unsupported Compiler.

#endif

#if (flip_NOTHING == flip_NOTHING_ZERO)
   #define flip_TEST_NOTHING(expr) \
      flip_TEST (expr)

#elif (flip_NOTHING == flip_NOTHING_FATAL)
   #define flip_TEST_NOTHING(expr) \
      flip_CHECK_THROW (flip_TEST (expr))

#else
   #error flip_NOTHING not defined

#endif



namespace flip
{



}  // namespace flip



//#include  "flip/TestDef.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

