/*****************************************************************************

      TestNonDefaultCtor.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestNonDefaultCtor.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/History.h"
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

void  TestNonDefaultCtor::run ()
{
   Model::version ("test.non-default-ctor");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <Root> ()
      .name ("Root")
      .member <A, &Root::_a> ("a");

   //

   Model2::version ("test.non-default-ctor");

   Model2::declare <A2> ()
      .name ("A2")
      .member <Int, &A2::_int> ("int")
      .member <Float, &A2::_float> ("float");

   Model2::declare <Root2> ()
      .name ("Root")
      .member <Collection <A2>, &Root2::_coll> ("coll")
      .member <Array <A2>, &Root2::_array> ("array");

   //

   Model3::version ("test.non-default-ctor");

   Model3::declare <A3> ()
      .name ("A3")
      .member <Int, &A3::_int> ("int")
      .member <Float, &A3::_float> ("float");

   Model3::declare <Root3> ()
      .name ("Root")
      .member <Collection <A3>, &Root3::_coll> ("coll")
      .member <Array <A3>, &Root3::_array> ("array");


   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestNonDefaultCtor::run_000 ()
{
#if ! defined (NDEBUG)
   flip_CHECK_THROW (Document document (Model::use (), 123456789UL, 'appl', 'gui '));
#endif
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestNonDefaultCtor::run_001 ()
{
   Document document (Model2::use (), 123456789UL, 'appl', 'gui ');

   Root2 & root = document.root <Root2> ();

   // this is OK and shall not throw
   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_CHECK_THROW (document.execute_forward (tx));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestNonDefaultCtor::run_002 ()
{
   Document document (Model2::use (), 123456789UL, 'appl', 'gui ');

   Root2 & root = document.root <Root2> ();

   // this is OK and shall not throw
   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_CHECK_THROW (document.execute_forward (tx));
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestNonDefaultCtor::run_003 ()
{
   Document document (Model3::use (), 123456789UL, 'appl', 'gui ');

   Root3 & root = document.root <Root3> ();

   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestNonDefaultCtor::run_004 ()
{
   Document document (Model3::use (), 123456789UL, 'appl', 'gui ');

   Root3 & root = document.root <Root3> ();

   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

