/*****************************************************************************

      TestClass.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestClass.h"

#include "flip/Document.h"
#include "flip/Ref.h"
#include "flip/detail/TypeId.h"
#include "TestDef.h"

#include <utility>
#include <vector>

#include <climits>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestClass::run ()
{
   Model::version ("the.version");

#if ! defined (NDEBUG)
   flip_CHECK_THROW (Class <A>::get ());
#endif

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <B> ()
      .name ("B")
      .inherit <A> ()
      .member <Int, &B::_int> ("int2")
      .member <Float, &B::_float> ("float2")
      .member <Collection <A>, &B::_coll> ("coll");

   Model::declare <C> ()
      .name ("C")
      .enumerator <C::x0> ("x0")
      .enumerator <C::x1> ("x1")
      .enumerator <C::x2> ("x2");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Bool, &Root::_bool> ("bool")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <Enum <C>, &Root::_enum> ("enum");

   // force post processing for unit test
   Model::use ();


   Model2::version ("another.version");

   Model2::add <A> ();

   Model2::use ();


   flip_TEST (Model::use ().has_class ("A"));
   flip_TEST (Class <A>::use ().members ().size () == 2);
   flip_TEST (Class <A>::use ().name () == std::string ("A"));
   flip_TEST (Class <A>::use ().type_id (Model::use ()) == TypeId::OBJECT);
   flip_TEST (Class <A>::use ().size_of () == 3);
   flip_TEST (!Class <A>::use ().inherit_from (Class <B>::use ()));
   flip_TEST (!Class <A>::use ().inherit_from (Class <Root>::use ()));
   flip_TEST (Model::use ().has_class (TypeId::OBJECT));
   flip_TEST (&Model::use ().get_class (TypeId::OBJECT) == &Class <A>::use ());
   flip_TEST (&Model::use ().get_class ("A") == &Class <A>::use ());

   flip_TEST (Model::use ().has_class ("B"));
   flip_TEST (Class <B>::use ().members ().size () == 5);
   flip_TEST (Class <B>::use ().name () == std::string ("B"));
   flip_TEST (Class <B>::use ().type_id (Model::use ()) == TypeId::OBJECT + 1);
   flip_TEST (Class <B>::use ().size_of () == 6);
   flip_TEST (Class <B>::use ().inherit_from (Class <A>::use ()));
   flip_TEST (!Class <B>::use ().inherit_from (Class <Root>::use ()));
   flip_TEST (Model::use ().has_class (TypeId::OBJECT + 1));
   flip_TEST (&Model::use ().get_class (TypeId::OBJECT + 1) == &Class <B>::use ());
   flip_TEST (&Model::use ().get_class ("B") == &Class <B>::use ());

   flip_TEST (Model::use ().has_class ("Root"));
   flip_TEST (Class <Root>::use ().members ().size () == 11);
   flip_TEST (Class <Root>::use ().name () == std::string ("Root"));
   flip_TEST (Class <Root>::use ().type_id (Model::use ()) == TypeId::OBJECT + 2);
   flip_TEST (Class <Root>::use ().size_of () == 19);
   flip_TEST (!Class <Root>::use ().inherit_from (Class <A>::use ()));
   flip_TEST (!Class <Root>::use ().inherit_from (Class <B>::use ()));
   flip_TEST (Model::use ().has_class (TypeId::OBJECT + 2));
   flip_TEST (&Model::use ().get_class (TypeId::OBJECT + 2) == &Class <Root>::use ());
   flip_TEST (&Model::use ().get_class ("Root") == &Class <Root>::use ());

   flip_TEST (!Model::use ().has_class ("C"));
   flip_CHECK_THROW (Model::use ().get_class ("C"));
   flip_CHECK_THROW (Model::use ().get_class (TypeId::OBJECT + 3));

   flip_TEST (Model::use ().has_enum ("C"));
   flip_TEST (Model::use ().get_enum ("C").size () == 3);
   flip_TEST (Model::use ().get_enum ("C").enumerators ().size () == 3);

   flip_TEST (Model2::use ().has_class ("A"));
   flip_TEST (!Model2::use ().has_class ("B"));
   flip_TEST (!Model2::use ().has_class ("Root"));
   flip_TEST (Model2::use ().has_class (TypeId::OBJECT));
   flip_TEST (&Model2::use ().get_class (TypeId::OBJECT) == &Class <A>::use ());
   flip_TEST (&Model2::use ().get_class ("A") == &Class <A>::use ());


   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref ref = Ref::root;

   flip_TEST (root.ref () == ref); ++ref;
   flip_TEST (root._int.ref () == ref); ++ref;
   flip_TEST (root._float.ref () == ref); ++ref;
   flip_TEST (root._a.ref () == ref); ++ref;
   flip_TEST (root._a._int.ref () == ref); ++ref;
   flip_TEST (root._a._float.ref () == ref); ++ref;
   flip_TEST (root._b.ref () == ref); ++ref;
   flip_TEST (root._b.A::_int.ref () == ref); ++ref;
   flip_TEST (root._b.A::_float.ref () == ref); ++ref;
   flip_TEST (root._b._int.ref () == ref); ++ref;
   flip_TEST (root._b._float.ref () == ref); ++ref;
   flip_TEST (root._b._coll.ref () == ref); ++ref;
   flip_TEST (root._coll_a.ref () == ref); ++ref;
   flip_TEST (root._coll_b.ref () == ref); ++ref;
   flip_TEST (root._ref_a.ref () == ref); ++ref;
   flip_TEST (root._bool.ref () == ref); ++ref;
   flip_TEST (root._blob.ref () == ref); ++ref;
   flip_TEST (root._string.ref () == ref); ++ref;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

