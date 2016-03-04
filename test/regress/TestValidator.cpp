/*****************************************************************************

      TestValidator.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestValidator.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "TestDef.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestValidator::run ()
{
   Model::version ("test.validator");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_number> ("number")
      .member <Float, &Root::_distance> ("distance");

   run_000 ();
}



/*
==============================================================================
Name : validate
==============================================================================
*/

void  TestValidator::Validator::validate (Root & root)
{
   if (root.removed ()) return;  // abort

   if (root._number > 10000)
   {
      flip_VALIDATION_FAILED ("number too big");
   }

   if (root._distance < 0.0)
   {
      flip_VALIDATION_FAILED ("negative distance");
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestValidator::run_000 ()
{
   Validator validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._number = 1LL;
   root._distance = 2.5;

   document.commit ();

   root._number = 20000LL;
   root._distance = 4.5;

   flip_CHECK_THROW (document.commit ());

   flip_TEST (root._number == 1LL);
   flip_TEST (root._distance == 2.5);

   root._number = 5LL;
   root._distance = -4.5;

   flip_CHECK_THROW (document.commit ());

   flip_TEST (root._number == 1LL);
   flip_TEST (root._distance == 2.5);

   root._number = 10000LL;
   root._distance = 4.5;

   document.commit ();

   flip_TEST (root._number == 10000LL);
   flip_TEST (root._distance == 4.5);

   {
      Transaction tx;
      tx.push_int64_set (root.ref () + 1, 0, 10000LL, 20000LL);

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);
   }

   {
      Transaction tx;
      tx.push_int64_set (root.ref () + 1, 0, 20000LL, 10000LL);

      bool ok_flag = document.execute_backward (tx);
      flip_TEST (!ok_flag);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

