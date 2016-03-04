/*****************************************************************************

      TestOptional.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestOptional.h"

#include "flip/detail/ExecFlags.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Mold.h"
#include "TestDef.h"

#include <algorithm>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestOptional::run ()
{
   Model::version ("test.optional");

   Model::declare <Content> ()
      .name ("Content")
      .member <Int, &Content::_int> ("int");

   Model::declare <ContentA> ()
      .name ("ContentA")
      .inherit <Content> ()
      .member <Int, &ContentA::_int_a> ("int_a");

   Model::declare <ContentB> ()
      .name ("ContentB")
      .inherit <Content> ()
      .member <Int, &ContentB::_int_b> ("int_b");

   Model::declare <ContentC> ()
      .name ("ContentC")
      .inherit <Content> ()
      .member <Int, &ContentC::_int_c> ("int_c");

   Model::declare <ContentOptional> ()
      .name ("ContentOptional")
      .member <Optional <Content>, &ContentOptional::_optional> ("_optional");

   Model::declare <Root> ()
      .name ("Root")
      .member <ContentOptionalColl, &Root::_coll> ("coll");



   run_pre ();
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
   run_013 ();
   run_014 ();
   run_015 ();
   run_016 ();
   run_017 ();
   run_018 ();
   run_019 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre
==============================================================================
*/

void  TestOptional::run_pre ()
{
   /*
   Optional <Content> optional;

   error : 'emplace' is a protected member of 'flip::Collection <flip::TextOptional::Content>'
   optional.emplace <Content> ();
   */
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestOptional::run_000 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   Content & content = elem._optional.reset <Content> ();
   content._int = 2;

   document.commit ();
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestOptional::run_001 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   document.commit ();
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestOptional::run_002 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   Content & content = elem._optional.reset <Content> ();
   content._int = 2;

   Content & content2 = elem._optional.reset <Content> ();
   content2._int = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestOptional::run_003 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   Content & content = elem._optional.reset ();
   content._int = 2;

   document.commit ();

   Content & content2 = elem._optional.reset ();
   content2._int = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestOptional::run_004 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentA & content = elem._optional.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentA & content2 = elem._optional.reset <ContentA> ();
   content2._int_a = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestOptional::run_005 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentA & content = elem._optional.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentB & content2 = elem._optional.reset <ContentB> ();
   content2._int_b = 3;

   document.commit ();

   Content & content3 = elem._optional;
   flip_TEST (dynamic_cast <ContentB &> (content3)._int_b == 3LL);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestOptional::run_006 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Content content;
   content._int = 2LL;

   ContentOptional & elem = *root._coll.emplace ();

   elem._optional = content;

   document.commit ();

   Content & content2 = elem._optional;

   flip_TEST (content2._int == 2LL);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestOptional::run_007 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Optional <Content> optional;
   optional.reset ()._int = 2LL;

   ContentOptional & elem = *root._coll.emplace ();

   elem._optional = optional;

   document.commit ();

   Content & content2 = elem._optional;

   flip_TEST (content2._int == 2LL);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestOptional::run_008 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentA & content = elem._optional.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentA & content2 = elem._optional.reset <ContentA> ();
   content2._int_a = 3;

   Content & content3 = elem._optional;

   flip_TEST (dynamic_cast <ContentA &> (content3)._int_a == 3LL);
   flip_TEST (dynamic_cast <ContentA &> (elem._optional.before ())._int_a.before () == 2LL);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestOptional::run_009 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentB & content = elem._optional.reset <ContentB> ();
   content._int_b = 2;

   document.commit ();

   ContentA & content2 = elem._optional.reset <ContentA> ();
   content2._int_a = 3;

   auto & content3 = elem._optional.value ();

   flip_TEST (dynamic_cast <ContentA &> (content3)._int_a == 3LL);
   flip_TEST (dynamic_cast <ContentA &> (content3)._int_a == 3LL);
   flip_TEST (dynamic_cast <ContentB &> (elem._optional.before ())._int_b.before () == 2LL);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestOptional::run_010 ()
{
   Optional <Content> optional;
   optional.reset ()._int = 2LL;

   Optional <Content> optional2 = optional;
   Content & content = optional2;
   flip_TEST (content._int == 2LL);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestOptional::run_011 ()
{
   Optional <Content> optional;
   optional.reset <ContentA> ()._int_a = 2LL;

   Optional <Content> optional2 = optional;
   flip_TEST (optional2.use <ContentA> ()._int_a == 2LL);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestOptional::run_012 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   elem._optional.reset <ContentB> ()._int_b = 2LL;

   document.commit ();

   elem._optional.reset <ContentA> ()._int_a = 3LL;

   flip_TEST (elem._optional.use <ContentA> ()._int_a == 3LL);
   flip_TEST (elem._optional.before <ContentB> ()._int_b.before () == 2LL);
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestOptional::run_013 ()
{
   Content a;
   a._int = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   Optional <Content> optional;

   optional.reset (mold);

   flip_TEST (optional.use <Content> ()._int == 2LL);
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestOptional::run_014 ()
{
   ContentA a;
   a._int_a = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   Optional <Content> optional;

   optional.reset <ContentA> (mold);

   flip_TEST (optional.use <ContentA> ()._int_a == 2LL);
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestOptional::run_015 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   Content & content = elem._optional.reset ();
   content._int = 2;

   document.commit ();

   elem._optional.reset (none);

   flip_TEST (elem._optional.empty ());
   flip_TEST (bool (elem._optional.empty ()));

   if (elem._optional)
   {
      flip_TEST_FAILED;   // COV_NF_LINE
   }

   if (!elem._optional)
   {
      // nothing
   }
   else
   {
      flip_TEST_FAILED;   // COV_NF_LINE
   }
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestOptional::run_016 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentC & content = elem._optional.reset <ContentC> (3);

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestOptional::run_017 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentC c (3LL);

   Mold mold (Model::use ());
   mold.make (c);

   ContentC & content = elem._optional.reset <ContentC> (mold);

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestOptional::run_018 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   Content c;
   c._int = 3LL;

   Content & content = elem._optional.reset (std::move (c));

   flip_TEST (content._int == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestOptional::run_019 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentOptional & elem = *root._coll.emplace ();

   ContentC c (3LL);

   ContentC & content = elem._optional.reset <ContentC, ContentC> (std::move (c));

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

