/*****************************************************************************

      TestDocumentIO.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDocumentIO.h"

#include "flip/BackEndBinary.h"
#include "flip/BackEndMl.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "TestDef.h"

#include <iostream>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestDocumentIO::run ()
{
   Model::version ("rev.1");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("_int")
      .member <Float, &A::_float> ("_float");

   Model::declare <B> ()
      .name ("B")
      .member <Int, &B::_int> ("_int2");

   Model::declare <C> ()
      .name ("C")
      .inherit <A> ()
      .member <Float, &C::_float> ("_float2")
      .member <B, &C::_b> ("_b")
      .member <ObjectRef <B>, &C::_b_ref> ("_b_ref")
      .member <Collection <B>, &C::_b_coll> ("_b_coll");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("_int")
      .member <Float, &Root::_float> ("_float")
      .member <A, &Root::_a> ("_a")
      .member <ObjectRef <A>, &Root::_a_ref> ("_a_ref")
      .member <Collection <A>, &Root::_a_coll> ("_a_coll")
      .member <B, &Root::_b> ("_b")
      .member <ObjectRef <B>, &Root::_b_ref> ("_b_ref")
      .member <Collection <B>, &Root::_b_coll> ("_b_coll")
      .member <C, &Root::_c> ("_c")
      .member <ObjectRef <C>, &Root::_c_ref> ("_c_ref")
      .member <Collection <C>, &Root::_c_coll> ("_c_coll");

   run_000 ();
   run_001 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestDocumentIO::run_000 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      // Root & root = document.root <Root> ();

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      // Root & root = document.root <Root> ();

      document.read (backend);
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDocumentIO::run_001 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      Root & root = document.root <Root> ();
      root._int = 1LL;
      root._float = 2.5;
      root._a._int = 3LL;
      root._a._float = 4.5;
      root._a_ref = &root._a;
      A & a = *root._a_coll.emplace ();
      a._int = 5LL;
      a._float = 6.3;

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      flip_TEST (root._int == 0LL);
      flip_TEST (root._float == 0.0);
      flip_TEST (root._a._int == 0LL);
      flip_TEST (root._a._float == 0.0);
      flip_TEST (root._a_ref.get () == Ref::null);
      flip_TEST (root._a_coll.count_if ([](A &) {return true;}) == 0);

      document.read (backend);

      flip_TEST (root._int == 1LL);
      flip_TEST (root._float == 2.5);
      flip_TEST (root._a._int == 3LL);
      flip_TEST (root._a._float == 4.5);
      flip_TEST (root._a_ref == &root._a);
      flip_TEST (root._a_coll.count_if ([](A &) {return true;}) == 1);
      flip_TEST (root._a_coll.count_if ([](A & a) {
         return (a._int == 5LL) && (a._float == 6.3);
      }) == 1);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

