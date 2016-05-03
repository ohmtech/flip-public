/*****************************************************************************

      TestDocument.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDocument.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/Optional.h"
#include "flip/Variant.h"
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

void  TestDocument::run ()
{
   Model::version ("test.document");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float")
      .member <ObjectRef <A>, &A::_ref_a> ("ref_a");

   Model::declare <B> ()
      .name ("B")
      .inherit <A> ()
      .member <Int, &B::_int2> ("int2")
      .member <Float, &B::_float2> ("float2")
      .member <Collection <A>, &B::_coll> ("coll");

   Model::declare <Root::C> ()
      .name ("C")
      .enumerator <Root::C::x0> ("x0")
      .enumerator <Root::C::x1> ("x1");

   Model::declare <Root> ()
      .name ("Root")
      .member <Bool, &Root::_bool> ("bool")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <Array <A>, &Root::_array_a> ("array_a")
      .member <Enum <Root::C>, &Root::_enum> ("enum");



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
   run_020 ();
   run_021 ();
   run_022 ();
   run_023 ();
   run_024 ();
   run_025 ();
   run_026 ();
   run_027 ();
   run_028 ();
   run_029 ();
   run_030 ();
   run_031 ();
   run_032 ();
   run_033 ();
   run_034 ();
   run_035 ();
   run_036 ();
   run_037 ();
   run_038 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
Note :
   Support for MSVC 2013u4.
==============================================================================
*/

TestDocument::A::A (A && rhs)
:  Object (std::move (rhs))
,  _int (std::move (rhs._int))
,  _float (std::move (rhs._float))
,  _ref_a (std::move (rhs._ref_a))
{
}



/*
==============================================================================
Name : ctor
Note :
   Support for MSVC 2013u4.
==============================================================================
*/

TestDocument::B::B (B && rhs)
:  A (std::move (rhs))
,  _int2 (std::move (rhs._int2))
,  _float2 (std::move (rhs._float2))
,  _coll (std::move (rhs._coll))
{
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestDocument::run_000 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._bool.flip ();
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._blob = std::vector <uint8_t> ({0x01, 0x23});
   root._string = "this is a test";
   root._enum = Root::C::x1;

   flip_TEST (root._bool == true);
   flip_TEST (root._bool.value () == true);
   flip_TEST (root._int == 3LL);
   flip_TEST (root._int.value () == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._float.value () == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._ref_a.value () == &root._b);
   flip_TEST (root._ref_a.get () == root._b.ref ());
   flip_TEST (root._blob == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._blob.value () == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string == "this is a test");
   flip_TEST (root._string.value () == "this is a test");
   flip_TEST (std::string (root._string) == "this is a test");
   flip_TEST (root._enum == Root::C::x1);
   flip_TEST (root._enum.value () == Root::C::x1);
   flip_TEST (static_cast <Root::C> (root._enum) == Root::C::x1)

   flip_TEST (root._bool.before () == false);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root._ref_a.before () == nullptr);
   flip_TEST (root._ref_a.get_before () == Ref::null);
   flip_TEST (root._blob.before () == std::vector <uint8_t> ());
   flip_TEST (root._blob.before ().empty ());
   flip_TEST (root._blob.before ().size () == 0);
   flip_TEST (root._string.before () == "");
   flip_TEST (root._string.before ().empty ());
   flip_TEST (root._string.before ().size () == 0);
   flip_TEST (root._enum.before () == Root::C::x0);

   flip_TEST (root.changed ());
   flip_TEST (root._bool.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
   flip_TEST (root._ref_a.changed ());
   flip_TEST (root._blob.changed ());
   flip_TEST (root._blob.changed ());     // x2
   flip_TEST (root._string.changed ());
   flip_TEST (root._string.changed ());   // x2
   flip_TEST (root._enum.changed ());

   document.commit ();

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._ref_a.get () == root._b.ref ());
   flip_TEST (root._blob == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string == "this is a test");
   flip_TEST (root._enum == Root::C::x1);

   flip_TEST (root._bool == true);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root._ref_a.before () == &root._b);
   flip_TEST (root._ref_a.get_before () == root._b.ref ());
   flip_TEST (root._blob.before () == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string.before () == "this is a test");
   flip_TEST (root._enum.before () == Root::C::x1);

   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());
   flip_TEST (!root._ref_a.changed ());
   flip_TEST (!root._blob.changed ());
   flip_TEST (!root._blob.changed ());    // x2
   flip_TEST (!root._string.changed ());
   flip_TEST (!root._string.changed ());  // x2
   flip_TEST (!root._enum.changed ());
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDocument::run_001 ()
{
   bool ok_flag = false;

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._bool = true;
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._blob = std::vector <uint8_t> ({0x01, 0x23});
   root._string = "this is a test";
   root._enum = Root::C::x1;

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._ref_a.get () == root._b.ref ());
   flip_TEST (root._blob == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string == "this is a test");
   flip_TEST (root._enum == Root::C::x1);

   flip_TEST (root._bool.before () == false);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root._ref_a.before () == nullptr);
   flip_TEST (root._ref_a.get_before () == Ref::null);
   flip_TEST (root._blob.before () == std::vector <uint8_t> ());
   flip_TEST (root._blob.before ().empty ());
   flip_TEST (root._blob.before ().size () == 0);
   flip_TEST (root._string.before () == "");
   flip_TEST (root._string.before ().empty ());
   flip_TEST (root._string.before ().size () == 0);
   flip_TEST (root._enum.before () == Root::C::x0);

   flip_TEST (root.changed ());
   flip_TEST (root._bool.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
   flip_TEST (root._ref_a.changed ());
   flip_TEST (root._blob.changed ());
   flip_TEST (root._blob.changed ());     // x2
   flip_TEST (root._string.changed ());
   flip_TEST (root._string.changed ());   // x2
   flip_TEST (root._enum.changed ());

   Transaction tx = document.commit ();

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._ref_a.get () == root._b.ref ());
   flip_TEST (root._blob == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string == "this is a test");

   flip_TEST (root._bool == true);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root._ref_a.before () == &root._b);
   flip_TEST (root._ref_a.get_before () == root._b.ref ());
   flip_TEST (root._blob.before () == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string.before () == "this is a test");

   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());
   flip_TEST (!root._ref_a.changed ());
   flip_TEST (!root._blob.changed ());
   flip_TEST (!root._blob.changed ());    // x2
   flip_TEST (!root._string.changed ());
   flip_TEST (!root._string.changed ());  // x2

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._ref_a.get () == Ref::null);
   flip_TEST (root._blob == std::vector <uint8_t> ());
   flip_TEST (root._blob.empty ());
   flip_TEST (root._blob.size () == 0);
   flip_TEST (root._string == "");
   flip_TEST (root._string.empty ());
   flip_TEST (root._string.size () == 0);
   flip_TEST (root._enum == Root::C::x0);

   flip_TEST (root._bool.before () == true);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root._ref_a.before () == &root._b);
   flip_TEST (root._ref_a.get_before () == root._b.ref ());
   flip_TEST (root._blob.before () == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (root._string.before () == "this is a test");
   flip_TEST (root._enum.before () == Root::C::x1);

   flip_TEST (root.changed ());
   flip_TEST (root._bool.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
   flip_TEST (root._ref_a.changed ());
   flip_TEST (root._blob.changed ());
   flip_TEST (root._blob.changed ());     // x2
   flip_TEST (root._string.changed ());
   flip_TEST (root._string.changed ());   // x2
   flip_TEST (root._enum.changed ());

   document.commit ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._ref_a.get () == Ref::null);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._blob.size () == 0);
   flip_TEST (root._string == "");
   flip_TEST (root._string.empty ());
   flip_TEST (root._string.size () == 0);
   flip_TEST (root._enum == Root::C::x0);

   flip_TEST (root._bool.before () == false);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root._ref_a.before () == nullptr);
   flip_TEST (root._ref_a.get_before () == Ref::null);
   flip_TEST (root._blob.before () == std::vector <uint8_t> ());
   flip_TEST (root._blob.before ().empty ());
   flip_TEST (root._blob.before ().size () == 0);
   flip_TEST (root._string.before () == "");
   flip_TEST (root._string.before ().empty ());
   flip_TEST (root._string.before ().size () == 0);
   flip_TEST (root._enum.before () == Root::C::x0);

   flip_TEST (!root.changed ());
   flip_TEST (!root._bool.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());
   flip_TEST (!root._ref_a.changed ());
   flip_TEST (!root._blob.changed ());
   flip_TEST (!root._blob.changed ());    // x2
   flip_TEST (!root._string.changed ());
   flip_TEST (!root._string.changed ());  // x2
   flip_TEST (!root._enum.changed ());
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDocument::run_002 ()
{
   bool ok_flag = false;

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._a._int = 3LL;
   root._a._float = 4.3;
   root._a._ref_a = &root._b;

   flip_TEST (root._a._int == 3LL);
   flip_TEST (root._a._float == 4.3);
   flip_TEST (root._a._ref_a == &root._b);
   flip_TEST (root._a._ref_a.get () == root._b.ref ());
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float.before () == 0.0);
   flip_TEST (root._a._ref_a.before () == nullptr);
   flip_TEST (root._a._ref_a.get_before () == Ref::null);
   flip_TEST (root.changed ());
   flip_TEST (root._a.changed ());
   flip_TEST (root._a._int.changed ());
   flip_TEST (root._a._float.changed ());
   flip_TEST (root._a._ref_a.changed ());

   Transaction tx = document.commit ();

   flip_TEST (root._a._int == 3LL);
   flip_TEST (root._a._float == 4.3);
   flip_TEST (root._a._ref_a == &root._b);
   flip_TEST (root._a._ref_a.get () == root._b.ref ());
   flip_TEST (root._a._int.before () == 3LL);
   flip_TEST (root._a._float.before () == 4.3);
   flip_TEST (root._a._ref_a.before () == &root._b);
   flip_TEST (root._a._ref_a.get_before () == root._b.ref ());
   flip_TEST (!root.changed ());
   flip_TEST (!root._a.changed ());
   flip_TEST (!root._a._int.changed ());
   flip_TEST (!root._a._float.changed ());
   flip_TEST (!root._a._ref_a.changed ());

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._ref_a == nullptr);
   flip_TEST (root._a._ref_a.get () == Ref::null);
   flip_TEST (root._a._int.before () == 3LL);
   flip_TEST (root._a._float.before () == 4.3);
   flip_TEST (root._a._ref_a.before () == &root._b);
   flip_TEST (root._a._ref_a.get_before () == root._b.ref ());
   flip_TEST (root.changed ());
   flip_TEST (root._a.changed ());
   flip_TEST (root._a._int.changed ());
   flip_TEST (root._a._float.changed ());
   flip_TEST (root._a._ref_a.changed ());

   document.commit ();

   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._ref_a == nullptr);
   flip_TEST (root._a._ref_a.get () == Ref::null);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float.before () == 0.0);
   flip_TEST (root._a._ref_a.before () == nullptr);
   flip_TEST (root._a._ref_a.get_before () == Ref::null);
   flip_TEST (!root.changed ());
   flip_TEST (!root._a.changed ());
   flip_TEST (!root._a._int.changed ());
   flip_TEST (!root._a._float.changed ());
   flip_TEST (!root._a._ref_a.changed ());
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestDocument::run_003 ()
{
   bool ok_flag = false;

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll_a.emplace ();
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &root._b;

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &root._b);

   document.set_label ("change");
   Transaction tx = document.commit ();

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &root._b);
   flip_TEST (tx.use_metadata_map ().size () == 1);
   flip_TEST (tx.use_metadata_map () ["label"] == "change");

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST_NOTHING (root._coll_a.begin ()->_int == 0LL);
   flip_TEST_NOTHING (root._coll_a.begin ()->_float == 0.0);
   flip_TEST_NOTHING (root._coll_a.begin ()->_ref_a == nullptr);

   document.set_label ("revert");
   Transaction tx2 = document.commit ();
   flip_TEST (tx.use_metadata_map ().size () == 1);
   flip_TEST (tx2.use_metadata_map () ["label"] == "revert");

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestDocument::run_004 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll_a.emplace ();
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &a;

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &a);

   document.revert ();

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestDocument::run_005 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();
   root._bool = true;
   root._int = 5LL;
   root._float = 45.2;
   root._ref_a = &root._b;
   root._blob = std::vector <uint8_t> ({0x01, 0x23});
   root._string = "this is a test";

   A & a = *root._coll_a.emplace ();
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &root._a;

   flip_TEST (document.object_ptr <Root> (Ref::root) != nullptr);
   flip_TEST (document.object_ptr <Bool> (Ref::root + 1) != nullptr);
   flip_TEST (*document.object_ptr <Bool> (Ref::root + 1) == true);
   flip_TEST (document.object_ptr <Int> (Ref::root + 2) != nullptr);
   flip_TEST (*document.object_ptr <Int> (Ref::root + 2) == 5LL);
   flip_TEST (document.object_ptr <Float> (Ref::root + 3) != nullptr);
   flip_TEST (*document.object_ptr <Float> (Ref::root + 3) == 45.2);
   flip_TEST (document.object_ptr <ObjectRef <A>> (Ref::root + 4) != nullptr);
   flip_TEST (*document.object_ptr <ObjectRef <A>> (Ref::root + 4) == &root._b);
   flip_TEST (document.object_ptr <Blob> (Ref::root + 5) != nullptr);
   flip_TEST (*document.object_ptr <Blob> (Ref::root + 5) == std::vector <uint8_t> ({0x01, 0x23}));
   flip_TEST (document.object_ptr <String> (Ref::root + 6) != nullptr);
   flip_TEST (*document.object_ptr <String> (Ref::root + 6) == "this is a test");

   Ref ref = Ref::get_first (document.user (), document.actor ());

   flip_TEST (document.object_ptr <A> (ref) != nullptr);
   flip_TEST (document.object_ptr <Int> (ref + 1) != nullptr);
   flip_TEST (*document.object_ptr <Int> (ref + 1) == 3LL);
   flip_TEST (document.object_ptr <Float> (ref + 2) != nullptr);
   flip_TEST (*document.object_ptr <Float> (ref + 2) == 4.3);
   flip_TEST (document.object_ptr <ObjectRef <A>> (ref + 3) != nullptr);
   flip_TEST (*document.object_ptr <ObjectRef <A>> (ref + 3) == &root._a);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestDocument::run_006 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &root._b;

   root._coll_a.insert (a);

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &root._b);

   document.commit ();
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestDocument::run_007 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &root._b;

   auto it = root._coll_a.insert (a);
   root._coll_a.erase (it);

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   document.commit ();
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestDocument::run_008 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B b;
   b._int = 3LL;
   b._float = 4.3;
   b._ref_a = &root._b;
   b._int2 = 4LL;
   b._float2 = 5.3;

   auto it = root._coll_a.insert (b);
   root._coll_a.erase (it);

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   document.commit ();
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestDocument::run_009 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B b;
   b._int = 3LL;
   b._float = 4.3;
   b._ref_a = &root._b;
   b._int2 = 4LL;
   b._float2 = 5.3;
   A & a = *b._coll.emplace ();
   a._int = 2LL;
   a._float = 4.0;
   a._ref_a = &root._a;

   auto it = root._coll_a.insert (b);

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   B & b2 = dynamic_cast <B &> (*root._coll_a.begin ());
   flip_TEST (b2.changed ());
   flip_TEST (b2._int == 3LL);
   flip_TEST (b2._float == 4.3);
   flip_TEST (b2._ref_a == &root._b);
   flip_TEST (b2._int2 == 4LL);
   flip_TEST (b2._float2 == 5.3);
   flip_TEST (b2._coll.count_if ([](A &){return true;}) == 1);
   A & a2 = *b2._coll.begin ();
   flip_TEST (a2.changed ());
   flip_TEST (a2._int == 2LL);
   flip_TEST (a2._float == 4.0);
   flip_TEST (a2._ref_a == &root._a);

   root._coll_a.erase (it);

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   document.commit ();
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestDocument::run_010 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B b;
   b._int = 3LL;
   b._float = 4.3;
   b._ref_a = &root._b;
   b._int2 = 4LL;
   b._float2 = 5.3;
   B & bb = dynamic_cast <B &> (*b._coll.emplace <B> ());
   bb._int = 2LL;
   bb._float = 4.0;
   bb._ref_a = &root._a;
   bb._int2 = 6LL;
   bb._float2 = 12.0;

   auto it = root._coll_a.insert (b);

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   B & b2 = dynamic_cast <B &> (*root._coll_a.begin ());
   flip_TEST (b2.changed ());
   flip_TEST (b2._int == 3LL);
   flip_TEST (b2._float == 4.3);
   flip_TEST (b2._ref_a == &root._b);
   flip_TEST (b2._int2 == 4LL);
   flip_TEST (b2._float2 == 5.3);
   flip_TEST (b2._coll.count_if ([](A &){return true;}) == 1);
   B & bb2 = dynamic_cast <B &> (*b2._coll.begin ());
   flip_TEST (bb2.changed ());
   flip_TEST (bb2._int == 2LL);
   flip_TEST (bb2._float == 4.0);
   flip_TEST (bb2._ref_a == &root._a);
   flip_TEST (bb2._int2 == 6LL);
   flip_TEST (bb2._float2 == 12.0);

   root._coll_a.erase (it);

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   document.commit ();
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestDocument::run_011 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());

   document.commit ();

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());

   root._int += 4LL;
   root._float += 2.0;

   flip_TEST (root._int == 7LL);
   flip_TEST (root._float == 6.3);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestDocument::run_012 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());

   document.commit ();

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());

   root._int -= 4LL;
   root._float -= 2.0;

   flip_TEST (root._int == -1LL);
   flip_TEST (root._float == 2.3);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestDocument::run_013 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());

   document.commit ();

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());

   root._int *= 2LL;
   root._float *= 2.0;

   flip_TEST (root._int == 6LL);
   flip_TEST (root._float == 8.6);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestDocument::run_014 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 4LL;
   root._float = 6.0;

   flip_TEST (root._int == 4LL);
   flip_TEST (root._float == 6.0);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());

   document.commit ();

   flip_TEST (root._int == 4LL);
   flip_TEST (root._float == 6.0);
   flip_TEST (root._int.before () == 4LL);
   flip_TEST (root._float.before () == 6.0);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());

   root._int /= 2LL;
   root._float /= 2.0;

   flip_TEST (root._int == 2LL);
   flip_TEST (root._float == 3.0);
   flip_TEST (root._int.before () == 4LL);
   flip_TEST (root._float.before () == 6.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestDocument::run_015 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 6.0;

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 6.0);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());

   document.commit ();

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 6.0);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 6.0);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());

   root._int /= 2LL;
   root._float /= 2.0;

   flip_TEST (root._int == 1LL);
   flip_TEST (root._float == 3.0);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 6.0);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestDocument::run_016 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._float == 0.0);
   flip_TEST (root._float.before () == 0.0);

   flip_CHECK_THROW (root._float /= 0.0);
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestDocument::run_017 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._a._int = root._int;
   root._a._float = root._float;
   root._a._ref_a = root._ref_a;

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._int.before () == 0LL);
   flip_TEST (root._float.before () == 0.0);
   flip_TEST (root._ref_a.before () == nullptr);
   flip_TEST (root._a._int == 3LL);
   flip_TEST (root._a._float == 4.3);
   flip_TEST (root._a._ref_a == &root._b);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float.before () == 0.0);
   flip_TEST (root._a._ref_a.before () == nullptr);
   flip_TEST (root.changed ());
   flip_TEST (root._int.changed ());
   flip_TEST (root._float.changed ());
   flip_TEST (root._ref_a.changed ());
   flip_TEST (root._a.changed ());
   flip_TEST (root._a._int.changed ());
   flip_TEST (root._a._float.changed ());
   flip_TEST (root._a._ref_a.changed ());

   document.commit ();

   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._int.before () == 3LL);
   flip_TEST (root._float.before () == 4.3);
   flip_TEST (root._ref_a.before () == &root._b);
   flip_TEST (root._a._int == 3LL);
   flip_TEST (root._a._float == 4.3);
   flip_TEST (root._a._ref_a == &root._b);
   flip_TEST (root._a._int.before () == 3LL);
   flip_TEST (root._a._float.before () == 4.3);
   flip_TEST (root._a._ref_a.before () == &root._b);
   flip_TEST (!root.changed ());
   flip_TEST (!root._int.changed ());
   flip_TEST (!root._float.changed ());
   flip_TEST (!root._ref_a.changed ());
   flip_TEST (!root._a.changed ());
   flip_TEST (!root._a._int.changed ());
   flip_TEST (!root._a._float.changed ());
   flip_TEST (!root._a._ref_a.changed ());
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestDocument::run_018 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll_a.emplace ();
   a._int = 3LL;
   a._float = 4.3;
   a._ref_a = &root._b;

   document.commit ();

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A & elem){
      return (!elem.removed ()) && (!elem.added ());
   }) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &root._b);

   root._coll_a.clear ();

   flip_TEST (root.changed ());
   flip_TEST (root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A & elem){
      return !elem.removed ();
   }) == 0);

   document.revert ();

   flip_TEST (!root.changed ());
   flip_TEST (!root._coll_a.changed ());
   flip_TEST (root._coll_a.count_if ([](A & elem){
      return (!elem.removed ()) && (!elem.added ());
   }) == 1);
   flip_TEST (root._coll_a.begin ()->_int == 3LL);
   flip_TEST (root._coll_a.begin ()->_float == 4.3);
   flip_TEST (root._coll_a.begin ()->_ref_a == &root._b);
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestDocument::run_019 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   BackEndIR backend1 = document.write ();

   Root & root = document.root <Root> ();
   root._bool = true;
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._blob = std::vector <uint8_t> ({0x01, 0x23});
   root._string = "this is a test";
   root._a._int = 4LL;
   root._a._float = 5.7;
   root._a._ref_a = &root._a;
   root._b._int = 5LL;
   root._b._float = 7.9;
   root._b._ref_a = &root._a;
   root._b._int2 = 6LL;
   root._b._float2 = -9.1;
   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());
   b._int = 7LL;
   b._float = 123.0;
   b._ref_a = &b;
   b._int2 = 8LL;
   b._float2 = 0.0;
   root._coll_a.emplace ();
   B & b2 = *root._coll_b.emplace ();
   b2._int = 9LL;
   root._enum = Root::C::x1;

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (!root.changed ());
   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (!root._blob.changed ());
   flip_TEST (!root._blob.changed ()); // x2
   flip_TEST (root._blob == std::vector <uint8_t> ());
   flip_TEST (!root._string.changed ());
   flip_TEST (!root._string.changed ());  // x2
   flip_TEST (root._string == "");
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._ref_a == nullptr);
   flip_TEST (root._b._int == 0LL);
   flip_TEST (root._b._float == 0.0);
   flip_TEST (root._b._ref_a == nullptr);
   flip_TEST (root._b._int2 == 0LL);
   flip_TEST (root._b._float2 == 0.0);
   flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);
   flip_TEST (root._enum == Root::C::x0);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestDocument::run_020 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._a._int = 4LL;
   root._a._float = 5.7;
   root._a._ref_a = &root._a;
   root._b._int = 5LL;
   root._b._float = 7.9;
   root._b._ref_a = &root._a;
   root._b._int2 = 6LL;
   root._b._float2 = -9.1;
   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());
   b._int = 7LL;
   b._float = 123.0;
   b._ref_a = &b;
   b._int2 = 8LL;
   b._float2 = 0.0;
   root._coll_a.emplace ();
   B & b2 = *root._coll_b.emplace ();
   b2._int = 9LL;

   document.commit ();

   BackEndIR backend1 = document.write ();

   root.impl_reset ();

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (!root.changed ());
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._a._int == 4LL);
   flip_TEST (root._a._float == 5.7);
   flip_TEST (root._a._ref_a == &root._a);
   flip_TEST (root._b._int == 5LL);
   flip_TEST (root._b._float == 7.9);
   flip_TEST (root._b._ref_a == &root._a);
   flip_TEST (root._b._int2 == 6LL);
   flip_TEST (root._b._float2 == -9.1);
   flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._b._coll.begin ()->_int == 7LL);
   flip_TEST (root._b._coll.begin ()->_float == 123.0);
   flip_TEST (root._b._coll.begin ()->_ref_a == &*root._b._coll.begin ());
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._int2 == 8LL);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._float2 == 0.0);
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._coll_b.begin ()->_int == 9LL);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestDocument::run_021 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._a._int = 4LL;
   root._a._float = 5.7;
   root._a._ref_a = &root._a;
   root._b._int = 5LL;
   root._b._float = 7.9;
   root._b._ref_a = &root._a;
   root._b._int2 = 6LL;
   root._b._float2 = -9.1;
   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());
   b._int = 7LL;
   b._float = 123.0;
   b._ref_a = &b;
   b._int2 = 8LL;
   b._float2 = 0.0;
   root._coll_a.emplace ();
   B & b2 = *root._coll_b.emplace ();
   b2._int = 9LL;

   document.commit ();

   BackEndIR backend1 = document.write ();

   root.impl_reset ();

   B & b3 = *root._coll_b.emplace ();
   b3._int = 10LL;

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (!root.changed ());
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._a._int == 4LL);
   flip_TEST (root._a._float == 5.7);
   flip_TEST (root._a._ref_a == &root._a);
   flip_TEST (root._b._int == 5LL);
   flip_TEST (root._b._float == 7.9);
   flip_TEST (root._b._ref_a == &root._a);
   flip_TEST (root._b._int2 == 6LL);
   flip_TEST (root._b._float2 == -9.1);
   flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._b._coll.begin ()->_int == 7LL);
   flip_TEST (root._b._coll.begin ()->_float == 123.0);
   flip_TEST (root._b._coll.begin ()->_ref_a == &*root._b._coll.begin ());
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._int2 == 8LL);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._float2 == 0.0);
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._coll_b.begin ()->_int == 9LL);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_022
==============================================================================
*/

void  TestDocument::run_022 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._a._int = 4LL;
   root._a._float = 5.7;
   root._a._ref_a = &root._a;
   root._b._int = 5LL;
   root._b._float = 7.9;
   root._b._ref_a = &root._a;
   root._b._int2 = 6LL;
   root._b._float2 = -9.1;
   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());
   b._int = 7LL;
   b._float = 123.0;
   b._ref_a = &b;
   b._int2 = 8LL;
   b._float2 = 0.0;
   A & a = *b._coll.emplace ();
   a._int = 10LL;
   root._coll_a.emplace ();
   B & b2 = *root._coll_b.emplace ();
   b2._int = 9LL;

   document.commit ();

   BackEndIR backend1 = document.write ();

   root.impl_reset ();

   B & b3 = *root._coll_b.emplace ();
   b3._int = 10LL;

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (!root.changed ());
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._a._int == 4LL);
   flip_TEST (root._a._float == 5.7);
   flip_TEST (root._a._ref_a == &root._a);
   flip_TEST (root._b._int == 5LL);
   flip_TEST (root._b._float == 7.9);
   flip_TEST (root._b._ref_a == &root._a);
   flip_TEST (root._b._int2 == 6LL);
   flip_TEST (root._b._float2 == -9.1);
   flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._b._coll.begin ()->_int == 7LL);
   flip_TEST (root._b._coll.begin ()->_float == 123.0);
   flip_TEST (root._b._coll.begin ()->_ref_a == &*root._b._coll.begin ());
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._int2 == 8LL);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._float2 == 0.0);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._coll.begin ()->_int == 10LL);
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._coll_b.begin ()->_int == 9LL);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_023
==============================================================================
*/

void  TestDocument::run_023 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();
   root._int = 3LL;
   root._float = 4.3;
   root._ref_a = &root._b;
   root._a._int = 4LL;
   root._a._float = 5.7;
   root._a._ref_a = &root._a;
   root._b._int = 5LL;
   root._b._float = 7.9;
   root._b._ref_a = &root._a;
   root._b._int2 = 6LL;
   root._b._float2 = -9.1;
   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());
   b._int = 7LL;
   b._float = 123.0;
   b._ref_a = &b;
   b._int2 = 8LL;
   b._float2 = 0.0;
   A & a = *b._coll.emplace ();
   a._int = 10LL;
   root._coll_a.emplace ();
   B & b2 = *root._coll_b.emplace ();
   b2._int = 9LL;

   document.commit ();

   BackEndIR backend1 = document.write ();

   root.impl_reset ();

   B & b3 = *root._coll_b.emplace ();
   b3._int = 10LL;
   b3._coll.emplace ();
   b3._coll.emplace ();

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (!root.changed ());
   flip_TEST (root._int == 3LL);
   flip_TEST (root._float == 4.3);
   flip_TEST (root._ref_a == &root._b);
   flip_TEST (root._a._int == 4LL);
   flip_TEST (root._a._float == 5.7);
   flip_TEST (root._a._ref_a == &root._a);
   flip_TEST (root._b._int == 5LL);
   flip_TEST (root._b._float == 7.9);
   flip_TEST (root._b._ref_a == &root._a);
   flip_TEST (root._b._int2 == 6LL);
   flip_TEST (root._b._float2 == -9.1);
   flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._b._coll.begin ()->_int == 7LL);
   flip_TEST (root._b._coll.begin ()->_float == 123.0);
   flip_TEST (root._b._coll.begin ()->_ref_a == &*root._b._coll.begin ());
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._int2 == 8LL);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._float2 == 0.0);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (dynamic_cast <B &> (*root._b._coll.begin ())._coll.begin ()->_int == 10LL);
   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._coll_b.begin ()->_int == 9LL);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_024
==============================================================================
*/

void  TestDocument::run_024 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (&root.ancestor <Root> () == &root);
   flip_TEST (&root._a.ancestor <Root> () == &root);
   flip_TEST (&root._a.ancestor <A> () == &root._a);
   flip_TEST (&root._b.ancestor <Root> () == &root);
   flip_TEST (&root._b.ancestor <A> () == &root._b);
   flip_TEST (&root._b.ancestor <B> () == &root._b);

   flip_CHECK_THROW (root.ancestor <A> ());
   flip_CHECK_THROW (root.ancestor <B> ());
   flip_CHECK_THROW (root._a.ancestor <B> ());

   B & b = dynamic_cast <B &> (*root._b._coll.emplace <B> ());

   flip_TEST (&b.ancestor <Root> () == &root);
}



/*
==============================================================================
Name : run_025
==============================================================================
*/

void  TestDocument::run_025 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._ref_a.impl_internal_set (Ref::root + 123456);

   flip_TEST (root._ref_a == nullptr);
   flip_TEST (!(root._ref_a != nullptr));

   A a;

   flip_CHECK_THROW (test (root._ref_a == &a));
   flip_CHECK_THROW (test (root._ref_a != &a));
}



/*
==============================================================================
Name : run_026
==============================================================================
*/

void  TestDocument::run_026 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (&root._a.parent <Root> () == &root);
   flip_CHECK_THROW (root._a.parent <A> ());
   flip_TEST (root._a.parent ().ptr <Root> () == &root);
   flip_TEST (root._a.parent ().ptr <A> () == nullptr);
   flip_TEST (&root._a.parent ().before <Root> () == &root);
   flip_CHECK_THROW (root._a.parent ().before <A> ());
   flip_TEST (root._a.parent ().before_ptr <Root> () == &root);
   flip_TEST (root._a.parent ().before_ptr <A> () == nullptr);

   auto it = root._array_a.emplace (root._array_a.end ());
   A & a = *it;

   flip_TEST (a.parent ().changed ());
   flip_TEST (&a.parent <Array <A>> () == &root._array_a);
   flip_CHECK_THROW (a.parent ().before <Array <A>> ());

   document.commit ();

   root._array_a.erase (it);

   flip_TEST (a.parent ().changed ());
   flip_CHECK_THROW (a.parent <Array <A>> ());
   flip_TEST (&a.parent ().before <Array <A>> () == &root._array_a);
}



/*
==============================================================================
Name : run_027
==============================================================================
*/

void  TestDocument::run_027 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._float = 2.5;

   document.commit ();
   document.squash ();

   root._float = 3.5;
   document.commit ();
   auto tx = document.squash ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   flip_TEST (root._float == 0.0);
}



/*
==============================================================================
Name : run_028
==============================================================================
*/

void  TestDocument::run_028 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._float = 2.5;

   document.commit ();

   root._float = 0.0;

   document.commit ();

   document.squash ();

   auto tx = document.squash ();

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_029
==============================================================================
*/

void  TestDocument::run_029 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();

   document.commit ();

   root._coll_a.erase (it);

   document.commit ();

   document.squash ();

   auto tx = document.squash ();

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_030
==============================================================================
*/

void  TestDocument::run_030 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   auto tx = document.squash ();

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_031
==============================================================================
*/

void  TestDocument::run_031 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._float = 2.5;
   document.commit ();

   root._float = 3.5;
   document.commit ();

   root._float = 4.7;
   document.commit ();

   root._int = 2;
   // don't commit

   auto tx = document.squash ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._int == 2LL);
}



/*
==============================================================================
Name : run_032
==============================================================================
*/

void  TestDocument::run_032 ()
{
   {
      Bool val;
      flip_TEST (false == val);
      flip_TEST (true != val);
   }

   {
      Int val;
      flip_TEST (0LL == val);
      flip_TEST (4LL != val);
   }

   {
      Float val;
      flip_TEST (0.0 == val);
      flip_TEST (2.5 != val);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      root._a._ref_a = &root._b;
      A & a = *root._a._ref_a;
      flip_UNUSED (a);
      flip_TEST (nullptr == root._ref_a);
      flip_TEST (&a != root._ref_a);
   }

   {
      Blob val;
      std::vector <uint8_t> v1;
      flip_TEST (v1 == val);

      std::vector <uint8_t> v2 {0xff, 0x03};
      flip_TEST (v2 != val);
   }

   {
      String val;
      flip_TEST (std::string ("") == val);
      flip_TEST ("" == val);
      flip_TEST (std::string ("test") != val);
      flip_TEST ("test" != val);
   }
}



/*
==============================================================================
Name : run_033
==============================================================================
*/

void  TestDocument::run_033 ()
{
   {
      auto x = Bool {true};
      flip_TEST (true == x);

      auto x2 = std::move (x);
      flip_TEST (true == x2);
   }

   {
      auto x = Int {3};
      flip_TEST (3LL == x);

      auto x2 = std::move (x);
      flip_TEST (3LL == x2);
   }

   {
      auto x = Float {4.5};
      flip_TEST (4.5 == x);

      auto x2 = std::move (x);
      flip_TEST (4.5 == x2);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      auto x = ObjectRef <A> {&root._a};
      flip_TEST (&root._a == x);

      auto x2 = std::move (x);
      flip_TEST (&root._a == x2);
   }

   {
      std::vector <uint8_t> v {0x12, 0x34};

      auto x = Blob {v};
      flip_TEST (v == x);

      auto x2 = std::move (x);
      flip_TEST (v == x2);
   }

   {
      std::string s {"this is a test"};

      auto x = String {s};
      flip_TEST (s == x);

      auto x2 = std::move (x);
      flip_TEST (s == x2);
   }

   {
      A a;
      a._int = 2;
      a._float = 3.25;

      auto x = A {a};
      flip_TEST (int64_t (a._int) == x._int);
      flip_TEST (double (a._float) == x._float);

      auto x2 = std::move (x);
      flip_TEST (int64_t (a._int) == x2._int);
      flip_TEST (double (a._float) == x2._float);

      A x3;
      x3 = x2;
      flip_TEST (int64_t (a._int) == x3._int);
      flip_TEST (double (a._float) == x3._float);
   }

   {
      B b;
      b._int = 2;
      b._float = 3.25;
      b._int2 = 3;
      b._float2 = 4.75;

      auto x = B {b};
      flip_TEST (int64_t (b._int) == x._int);
      flip_TEST (double (b._float) == x._float);
      flip_TEST (int64_t (b._int2) == x._int2);
      flip_TEST (double (b._float2) == x._float2);

      auto x2 = std::move (x);
      flip_TEST (int64_t (b._int) == x2._int);
      flip_TEST (double (b._float) == x2._float);
      flip_TEST (int64_t (b._int2) == x2._int2);
      flip_TEST (double (b._float2) == x2._float2);

      B x3;
      x3 = x2;
      flip_TEST (int64_t (b._int) == x3._int);
      flip_TEST (double (b._float) == x3._float);
      flip_TEST (int64_t (b._int2) == x3._int2);
      flip_TEST (double (b._float2) == x3._float2);
   }

   {
      A a;
      a._int = 2;
      a._float = 3.25;

      Array <A> array;
      array.insert (array.end (), a);

      auto x = Array <A> {array};
      flip_TEST (std::distance (x.begin (), x.end ()) == 1);
      flip_TEST (std::count_if (x.begin (), x.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      auto x2 = std::move (x);
      flip_TEST (std::distance (x2.begin (), x2.end ()) == 1);
      flip_TEST (std::count_if (x2.begin (), x2.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Array <A> x3;
      x3 = std::move (x2);
      flip_TEST (std::distance (x3.begin (), x3.end ()) == 1);
      flip_TEST (std::count_if (x3.begin (), x3.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Array <A> x4;
      x4 = x3;
      flip_TEST (std::distance (x4.begin (), x4.end ()) == 1);
      flip_TEST (std::count_if (x4.begin (), x4.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);
   }

   {
      A a;
      a._int = 2;
      a._float = 3.25;

      Collection <A> coll;
      coll.insert (a);

      auto x = Collection <A> {coll};
      flip_TEST (std::distance (x.begin (), x.end ()) == 1);
      flip_TEST (std::count_if (x.begin (), x.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      auto x2 = std::move (x);
      flip_TEST (std::distance (x2.begin (), x2.end ()) == 1);
      flip_TEST (std::count_if (x2.begin (), x2.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Collection <A> x3;
      x3 = std::move (x2);
      flip_TEST (std::distance (x3.begin (), x3.end ()) == 1);
      flip_TEST (std::count_if (x3.begin (), x3.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Collection <A> x4;
      x4 = x3;
      flip_TEST (std::distance (x4.begin (), x4.end ()) == 1);
      flip_TEST (std::count_if (x4.begin (), x4.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);
   }

   {
      A a;
      a._int = 2;
      a._float = 3.25;

      Variant <A> variant;
      variant = a;

      auto x = Variant <A> {variant};
      flip_TEST (std::distance (x.begin (), x.end ()) == 1);
      flip_TEST (std::count_if (x.begin (), x.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      auto x2 = std::move (x);
      flip_TEST (std::distance (x2.begin (), x2.end ()) == 1);
      flip_TEST (std::count_if (x2.begin (), x2.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Variant <A> x3;
      x3 = std::move (x2);
      flip_TEST (std::distance (x3.begin (), x3.end ()) == 1);
      flip_TEST (std::count_if (x3.begin (), x3.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Variant <A> x4;
      x4 = x3;
      flip_TEST (std::distance (x4.begin (), x4.end ()) == 1);
      flip_TEST (std::count_if (x4.begin (), x4.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);
   }

   {
      A a;
      a._int = 2;
      a._float = 3.25;

      Optional <A> optional;
      optional = a;

      auto x = Optional <A> {optional};
      flip_TEST (std::distance (x.begin (), x.end ()) == 1);
      flip_TEST (std::count_if (x.begin (), x.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      auto x2 = std::move (x);
      flip_TEST (std::distance (x2.begin (), x2.end ()) == 1);
      flip_TEST (std::count_if (x2.begin (), x2.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Optional <A> x3;
      x3 = std::move (x2);
      flip_TEST (std::distance (x3.begin (), x3.end ()) == 1);
      flip_TEST (std::count_if (x3.begin (), x3.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);

      Optional <A> x4;
      x4 = x3;
      flip_TEST (std::distance (x4.begin (), x4.end ()) == 1);
      flip_TEST (std::count_if (x4.begin (), x4.end (), [](const A & val) {
         return (val._int == 2LL) && (val._float == 3.25);
      }) == 1);
   }

   {
      auto x = Message <> {};
      auto x2 = std::move (x);
   }
}



/*
==============================================================================
Name : run_034
==============================================================================
*/

void  TestDocument::run_034 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   flip_CHECK_THROW (auto x = std::move (root._bool));
   flip_CHECK_THROW (auto x = std::move (root._int));
   flip_CHECK_THROW (auto x = std::move (root._float));
   flip_CHECK_THROW (auto x = std::move (root._ref_a));
   flip_CHECK_THROW (auto x = std::move (root._blob));
   flip_CHECK_THROW (auto x = std::move (root._string));
   flip_CHECK_THROW (auto x = std::move (root._a));
   flip_CHECK_THROW (auto x = std::move (root._b));
   flip_CHECK_THROW (auto x = std::move (root._coll_a));
   flip_CHECK_THROW (auto x = std::move (root._coll_b));
   flip_CHECK_THROW (auto x = std::move (root._array_a));

   Collection <A> coll;
   flip_CHECK_THROW (coll = std::move (root._coll_a));

   Array <A> array;
   flip_CHECK_THROW (array = std::move (root._array_a));
}



/*
==============================================================================
Name : run_035
==============================================================================
*/

void  TestDocument::run_035 ()
{
#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE) \
   && (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   Document mutable_document (Model::use (), 123456789UL, 'appl', 'gui ');
   const Document & document = mutable_document;
   const Root & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   const Entity & entity = root.entity ();

   flip_TEST (entity.has <A> () == false);
   flip_TEST (entity.get <A> () == nullptr);
   flip_CHECK_THROW (entity.use <A> ());

   mutable_document.root <Root> ().entity ().emplace <int> (2);

   flip_TEST (entity.has <int> () == true);
   flip_TEST (entity.get <int> () != nullptr);
   flip_TEST (entity.use <int> () == 2);

   mutable_document.root <Root> ().entity ().erase <int> ();
#endif
}



/*
==============================================================================
Name : run_036
==============================================================================
*/

void  TestDocument::run_036 ()
{
   Document mutable_document (Model::use (), 123456789UL, 'appl', 'gui ');
   const Document & document = mutable_document;
   const Root & root = document.object <Root> (Ref::root);

   flip_TEST (root._int == 0LL);
}



/*
==============================================================================
Name : run_037
==============================================================================
*/

void  TestDocument::run_037 ()
{
   Document mutable_document (Model::use (), 123456789UL, 'appl', 'gui ');
   const Document & document = mutable_document;
   const Root * root_ptr = document.object_ptr <Root> (Ref::root);
   flip_TEST (root_ptr != nullptr);

   const Root & root = *root_ptr;
   flip_TEST (root._int == 0LL);
}



/*
==============================================================================
Name : run_038
==============================================================================
*/

void  TestDocument::run_038 ()
{
   {
      String s;
      s = std::string {};
   }

   {
      String s;
      String s2;
      s = s2;
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

