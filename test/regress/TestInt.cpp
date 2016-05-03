/*****************************************************************************

      TestInt.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestInt.h"

#include "flip/BackEndBinary.h"
#include "flip/BackEndMl.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Mold.h"
#include "flip/contrib/Utml.h"
#include "flip/detail/ExecFlags.h"

#include "TestDef.h"

#include <algorithm>

#include <cinttypes>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestInt::run ()
{
   Model::version ("test.document");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int");

   run_pre ();
   run_000 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre
==============================================================================
*/

void  TestInt::run_pre ()
{
   static_assert (int64_t (34) == 34, "");
   static_assert (int64_t (12) == 12L, "");
   static_assert (int64_t (67) == 67LL, "");
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestInt::run_000 ()
{
   {
      Int int_;
      int_ = 3;

      flip_TEST (int_ == 3);
      flip_TEST (int_ != 2);
   }

   {
      Int int_;
      int_ = 5L;

      flip_TEST (int_ == 5L);
      flip_TEST (int_ != 4L);
   }

   {
      Int int_;
      int_ = 9LL;

      flip_TEST (int_ == 9LL);
      flip_TEST (int_ != 10LL);
   }

   {
      Int int_;
      int_ = int64_t (11);

      flip_TEST (int_ == int64_t (11));
      flip_TEST (int_ != int64_t (12));
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

