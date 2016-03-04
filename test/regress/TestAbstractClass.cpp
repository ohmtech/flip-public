/*****************************************************************************

      TestAbstractClass.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestAbstractClass.h"

#include "flip/detail/ExecFlags.h"
#include "flip/detail/TypeTraits.h"
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

void  TestAbstractClass::run ()
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

#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility
#else
   Model::declare <ContentC> ()
      .name ("ContentC")
      .inherit <Content> ()
      .member <Int, &ContentC::_int_c> ("int_c");
#endif

   Model::declare <Root> ()
      .name ("Root")
      .member <ContentColl, &Root::_coll> ("coll")
      .member <ContentArray, &Root::_array> ("array");



   run_pre ();
   run_000 ();
   run_001 ();
   run_001b ();
   run_001c ();
   run_002 ();
   run_002b ();
   run_002c ();
   run_003 ();
   run_003b ();
   run_004 ();
   run_004b ();
}



/*
==============================================================================
Name : ContentA::foo
==============================================================================
*/

void  TestAbstractClass::ContentA::foo ()
{
   _int_a = 45;
}



/*
==============================================================================
Name : ContentB::foo
==============================================================================
*/

void  TestAbstractClass::ContentB::foo ()
{
   _int_b = 59;
}



/*
==============================================================================
Name : ContentC::foo
==============================================================================
*/

#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility
#else
void  TestAbstractClass::ContentC::foo ()
{
   _int_c = 67;
}
#endif



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre
==============================================================================
*/

void  TestAbstractClass::run_pre ()
{
   /*Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   // U must support default constructor
   root._coll.emplace <Content> ();*/

   static_assert (is_copy_constructible <A>::value == true, "");
#if (flip_COMPILER != flip_COMPILER_MSVC) || (_MSC_VER != 1800)
   static_assert (is_copy_constructible <B>::value == false, "");
   static_assert (is_copy_constructible <C>::value == false, "");
#endif
   static_assert (is_copy_constructible <D>::value == false, "");
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestAbstractClass::run_000 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   root._coll.emplace <ContentA> ();
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestAbstractClass::run_001 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Transaction tx;
   KeyRandom key;
   tx.push_collection_insert (
      root._coll.ref (), 0,
      key, Class <Content>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 12345678)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_001b
==============================================================================
*/

void  TestAbstractClass::run_001b ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace <ContentA> ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll.ref (), 0,
      it.key (), Class <Content>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_001c
==============================================================================
*/

void  TestAbstractClass::run_001c ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace <ContentA> ();
   it->foo ();

   auto & content = dynamic_cast <ContentA &> (*it);

   flip_TEST (content._int_a == 45LL);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestAbstractClass::run_002 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   Transaction tx;
   KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   tx.push_array_insert (
      root._array.ref (), 0,
      key, Class <Content>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 12345678)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_002b
==============================================================================
*/

void  TestAbstractClass::run_002b ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace <ContentA> (root._array.end ());

   Transaction tx;
   tx.push_array_erase (
      root._array.ref (), 0,
      it.key (), Class <Content>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_002c
==============================================================================
*/

void  TestAbstractClass::run_002c ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace <ContentB> (root._array.end ());
   it->foo ();

   auto & content = dynamic_cast <ContentB &> (*it);

   flip_TEST (content._int_b == 59LL);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestAbstractClass::run_003 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto ptr = new ContentA;
   auto uptr = std::unique_ptr <Content> (ptr);

   auto it = root._coll.insert (std::move (uptr));
   it->foo ();

   auto & content = dynamic_cast <ContentA &> (*it);

   flip_TEST (content._int_a == 45LL);
}



/*
==============================================================================
Name : run_003b
==============================================================================
*/

void  TestAbstractClass::run_003b ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto ptr = new ContentA;
   auto uptr = std::unique_ptr <Content> (ptr);

   auto it = root._array.insert (root._array.end (), std::move (uptr));
   it->foo ();

   auto & content = dynamic_cast <ContentA &> (*it);

   flip_TEST (content._int_a == 45LL);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestAbstractClass::run_004 ()
{
#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility

#else
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto ptr = new ContentC;
   auto uptr = std::unique_ptr <Content> (ptr);

   auto it = root._coll.insert (std::move (uptr));
   it->foo ();

   auto & content = dynamic_cast <ContentC &> (*it);

   flip_TEST (content._int_c == 67LL);
#endif
}



/*
==============================================================================
Name : run_004b
==============================================================================
*/

void  TestAbstractClass::run_004b ()
{
#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility

#else
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   auto ptr = new ContentC;
   auto uptr = std::unique_ptr <Content> (ptr);

   auto it = root._array.insert (root._array.end (), std::move (uptr));
   it->foo ();

   auto & content = dynamic_cast <ContentC &> (*it);

   flip_TEST (content._int_c == 67LL);
#endif
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

