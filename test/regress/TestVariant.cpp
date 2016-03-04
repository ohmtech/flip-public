/*****************************************************************************

      TestVariant.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestVariant.h"

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

void  TestVariant::run ()
{
   Model::version ("test.variant");

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

   Model::declare <ContentVariant> ()
      .name ("ContentVariant")
      .member <Variant <Content>, &ContentVariant::_variant> ("_variant");

   Model::declare <Root> ()
      .name ("Root")
      .member <ContentVariantColl, &Root::_coll> ("coll");



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

void  TestVariant::run_pre ()
{
   /*
   Variant <Content> variant;

   error : 'emplace' is a protected member of 'flip::Collection <flip::TextVariant::Content>'
   variant.emplace <Content> ();
   */
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestVariant::run_000 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   Content & content = elem._variant.reset <Content> ();
   content._int = 2;

   document.commit ();
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestVariant::run_001 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   flip_CHECK_THROW (document.commit ());
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestVariant::run_002 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   Content & content = elem._variant.reset <Content> ();
   content._int = 2;

   Content & content2 = elem._variant.reset <Content> ();
   content2._int = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestVariant::run_003 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   Content & content = elem._variant.reset ();
   content._int = 2;

   document.commit ();

   Content & content2 = elem._variant.reset ();
   content2._int = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestVariant::run_004 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentA & content = elem._variant.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentA & content2 = elem._variant.reset <ContentA> ();
   content2._int_a = 3;

   document.commit ();
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestVariant::run_005 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentA & content = elem._variant.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentB & content2 = elem._variant.reset <ContentB> ();
   content2._int_b = 3;

   document.commit ();

   Content & content3 = elem._variant;
   flip_TEST (dynamic_cast <ContentB &> (content3)._int_b == 3LL);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestVariant::run_006 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Content content;
   content._int = 2LL;

   ContentVariant & elem = *root._coll.emplace ();

   elem._variant = content;

   document.commit ();

   Content & content2 = elem._variant;

   flip_TEST (content2._int == 2LL);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestVariant::run_007 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Variant <Content> variant;
   variant.reset ()._int = 2LL;

   ContentVariant & elem = *root._coll.emplace ();

   elem._variant = variant;

   document.commit ();

   Content & content2 = elem._variant;

   flip_TEST (content2._int == 2LL);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestVariant::run_008 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentA & content = elem._variant.reset <ContentA> ();
   content._int_a = 2;

   document.commit ();

   ContentA & content2 = elem._variant.reset <ContentA> ();
   content2._int_a = 3;

   Content & content3 = elem._variant;

   flip_TEST (dynamic_cast <ContentA &> (content3)._int_a == 3LL);
   flip_TEST (dynamic_cast <ContentA &> (elem._variant.before ())._int_a.before () == 2LL);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestVariant::run_009 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentB & content = elem._variant.reset <ContentB> ();
   content._int_b = 2;

   document.commit ();

   ContentA & content2 = elem._variant.reset <ContentA> ();
   content2._int_a = 3;

   auto & content3 = elem._variant.value ();

   flip_TEST (dynamic_cast <ContentA &> (content3)._int_a == 3LL);
   flip_TEST (dynamic_cast <ContentB &> (elem._variant.before ())._int_b.before () == 2LL);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestVariant::run_010 ()
{
   Variant <Content> variant;
   variant.reset ()._int = 2LL;

   Variant <Content> variant2 = variant;
   Content & content = variant2;
   flip_TEST (content._int == 2LL);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestVariant::run_011 ()
{
   Variant <Content> variant;
   variant.reset <ContentA> ()._int_a = 2LL;

   Variant <Content> variant2 = variant;
   flip_TEST (variant2.use <ContentA> ()._int_a == 2LL);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestVariant::run_012 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   elem._variant.reset <ContentB> ()._int_b = 2LL;

   document.commit ();

   elem._variant.reset <ContentA> ()._int_a = 3LL;

   flip_TEST (elem._variant.use <ContentA> ()._int_a == 3LL);
   flip_TEST (elem._variant.before <ContentB> ()._int_b.before () == 2LL);
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestVariant::run_013 ()
{
   Content a;
   a._int = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   Variant <Content> variant;

   variant.reset (mold);

   flip_TEST (variant.use <Content> ()._int == 2LL);
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestVariant::run_014 ()
{
   ContentA a;
   a._int_a = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   Variant <Content> variant;

   variant.reset <ContentA> (mold);

   flip_TEST (variant.use <ContentA> ()._int_a == 2LL);
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestVariant::run_016 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentC & content = elem._variant.reset <ContentC> (3);

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestVariant::run_017 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentC c (3LL);

   Mold mold (Model::use ());
   mold.make (c);

   ContentC & content = elem._variant.reset <ContentC> (mold);

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestVariant::run_018 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   Content c;
   c._int = 3LL;

   Content & content = elem._variant.reset (std::move (c));

   flip_TEST (content._int == 3LL);

   document.commit ();
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestVariant::run_019 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   ContentVariant & elem = *root._coll.emplace ();

   ContentC c (3LL);

   ContentC & content = elem._variant.reset <ContentC, ContentC> (std::move (c));

   flip_TEST (content._int_c == 3LL);

   document.commit ();
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

