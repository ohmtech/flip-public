/*****************************************************************************

      TestDocumentHub.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDocumentHub.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentHub.h"
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

void  TestDocumentHub::run ()
{
   Model::version ("test.tx");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <B> ()
      .name ("B")
      .inherit <A> ()
      .member <Int, &B::_int2> ("int2")
      .member <Float, &B::_float2> ("float2")
      .member <Collection <A>, &B::_coll> ("coll");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b");



   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestDocumentHub::run_000 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   document_hub.add (document);

   Root & root = document.root <Root> ();

   root._int = 3LL;

   document.commit ();
   document.push ();

   document_hub.pull ();
   document_hub.commit ();

   Root & root_hub = document_hub.root <Root> ();

   flip_TEST (root_hub._int == 3LL);

   document_hub.remove (document);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDocumentHub::run_001 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   Root & root_hub = document_hub.root <Root> ();
   root_hub._int = 3LL;
   document_hub.commit ();

   flip_TEST (root_hub._int == 3LL);
   flip_TEST (root_hub._int.before () == 3LL);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   document_hub.add (document);
   Root & root = document.root <Root> ();

   document.pull ();

   flip_TEST (root._int == 3LL);

   document_hub.remove (document);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDocumentHub::run_002 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   {
      Root & root_hub = document_hub.root <Root> ();
      root_hub._int = 3LL;
      root_hub._float = 27.5;
      A & a = *root_hub._coll_a.emplace ();
      a._int = 4LL;
      a._float = 1.0 / 7.0;

      document_hub.commit ();

      flip_TEST (root_hub._int == 3LL);
      flip_TEST (root_hub._float == 27.5);
      flip_TEST (root_hub._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root_hub._coll_a.begin ()->_int == 4LL);
      flip_TEST (root_hub._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   document_hub.add (document);

   document.pull ();

   {
      Root & root = document.root <Root> ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   document_hub.remove (document);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestDocumentHub::run_003 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   {
      Root & root_hub = document_hub.root <Root> ();
      root_hub._int = 3LL;
      root_hub._float = 27.5;
      A & a = *root_hub._coll_a.emplace ();
      a._int = 4LL;
      a._float = 1.0 / 7.0;

      document_hub.commit ();

      flip_TEST (root_hub._int == 3LL);
      flip_TEST (root_hub._float == 27.5);
      flip_TEST (root_hub._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root_hub._coll_a.begin ()->_int == 4LL);
      flip_TEST (root_hub._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Document document2 (Model::use (), 123456789UL, 'appl', 'auen');

   document_hub.add (document);
   document_hub.add (document2);

   {
      Root & root = document.root <Root> ();

      flip_TEST (root._int == 0LL);
      flip_TEST (root._float == 0.0);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 0);

      document.pull ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   {
      Root & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);
      flip_TEST (root._float == 0.0);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 0);

      document2.pull ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   document_hub.remove (document);
   document_hub.remove (document2);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestDocumentHub::run_004 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Document document2 (Model::use (), 123456789UL, 'appl', 'auen');

   document_hub.add (document);
   document_hub.add (document2);

   {
      document.pull ();

      Root & root = document.root <Root> ();

      root._int = 3LL;
      root._float = 27.5;
      A & a = *root._coll_a.emplace ();
      a._int = 4LL;
      a._float = 1.0 / 7.0;

      document.commit ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);

      document.push ();
   }

   {
      Root & root = document_hub.root <Root> ();

      flip_TEST (root._int == 0LL);
      flip_TEST (root._float == 0.0);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 0);
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   {
      document_hub.pull ();
      document_hub.commit ();

      Root & root = document_hub.root <Root> ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 27.5);
      flip_TEST (root._coll_a.count_if ([](const A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 4LL);
      flip_TEST (root._coll_a.begin ()->_float == 1.0 / 7.0);
   }

   document_hub.remove (document);
   document_hub.remove (document2);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestDocumentHub::run_005 ()
{
   DocumentHub document_hub (Model::use (), 123456789UL, 'appl', 'hub ');

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   document_hub.add (document);

   Root & root = document.root <Root> ();

   {
      root._int = 3LL;
      document.commit ();
      document.push ();
   }

   {
      root._int = 5LL;
      document.commit ();
      document.push ();
   }

   {
      root._int = 19LL;
      document.commit ();
      document.push ();
   }

   document_hub.pull ();
   document_hub.commit ();

   Root & root_hub = document_hub.root <Root> ();

   flip_TEST (root_hub._int == 19LL);

   document_hub.remove (document);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

