/*****************************************************************************

      TestDataModel.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDataModel.h"

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

void  TestDataModel::run ()
{
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
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDataModel::run_001 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class A : public Object
   {
   public:
      Int _int;
   };

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 2);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDataModel::run_002 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class A : public Object
   {
   public:
      Int _int;
      Float _float;
   };

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 2);
   flip_TEST (Class <A>::use ().size_of () == 3);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestDataModel::run_003 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class A : public Object {};

   Model::declare <A> ()
      .name ("A");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 0);
   flip_TEST (Class <A>::use ().size_of () == 1);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestDataModel::run_004 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class A : public Object {};

   Model::declare <A> ()
      .name ("A");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 0);
   flip_TEST (Class <A>::use ().size_of () == 1);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestDataModel::run_005 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class B : public Object
   {
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <B> ()
      .name ("B");

   Model::declare <A> ()
      .name ("A")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 2);
   flip_TEST (Class <B>::use ().members ().size () == 0);
   flip_TEST (Class <B>::use ().size_of () == 1);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestDataModel::run_006 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class B : public Object
   {
   public:
      Int _int;
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <B> ()
      .name ("B")
      .member <Int, &B::_int> ("int");

   Model::declare <A> ()
      .name ("A")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 3);
   flip_TEST (Class <B>::use ().members ().size () == 1);
   flip_TEST (Class <B>::use ().size_of () == 2);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestDataModel::run_007 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class C : public Object
   {
   public:
      Int _int;
   };

   class B : public Object
   {
   public:
      C c;
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <C> ()
      .name ("C")
      .member <Int, &C::_int> ("int");

   Model::declare <B> ()
      .name ("B")
      .member <C, &B::c> ("c");

   Model::declare <A> ()
      .name ("A")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 4);
   flip_TEST (Class <B>::use ().members ().size () == 1);
   flip_TEST (Class <B>::use ().size_of () == 3);
   flip_TEST (Class <C>::use ().members ().size () == 1);
   flip_TEST (Class <C>::use ().size_of () == 2);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestDataModel::run_008 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class D : public Object
   {
   public:
      Float _float;
   };

   class C : public D
   {
   public:
      Int _int;
   };

   class B : public Object
   {
   public:
      C c;
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <D> ()
      .name ("D")
      .member <Float, &C::_float> ("float");

   Model::declare <C> ()
      .name ("C")
      .inherit <D> ()
      .member <Int, &C::_int> ("int");

   Model::declare <B> ()
      .name ("B")
      .member <C, &B::c> ("c");

   Model::declare <A> ()
      .name ("A")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 5);
   flip_TEST (Class <B>::use ().members ().size () == 1);
   flip_TEST (Class <B>::use ().size_of () == 4);
   flip_TEST (Class <C>::use ().members ().size () == 2);
   flip_TEST (Class <C>::use ().size_of () == 3);
   flip_TEST (Class <D>::use ().members ().size () == 1);
   flip_TEST (Class <D>::use ().size_of () == 2);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestDataModel::run_009 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class C : public Object
   {
   public:
      Float _float;
   };

   class D : public C
   {
   public:
      Int _int;
   };

   class B : public Object
   {
   public:
      D d;
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <C> ()
      .name ("C")
      .member <Float, &C::_float> ("float");

   Model::declare <D> ()
      .name ("D")
      .inherit <C> ()
      .member <Int, &D::_int> ("int");

   Model::declare <B> ()
      .name ("B")
      .member <D, &B::d> ("d");

   Model::declare <A> ()
      .name ("A")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 5);
   flip_TEST (Class <B>::use ().members ().size () == 1);
   flip_TEST (Class <B>::use ().size_of () == 4);
   flip_TEST (Class <C>::use ().members ().size () == 1);
   flip_TEST (Class <C>::use ().size_of () == 2);
   flip_TEST (Class <D>::use ().members ().size () == 2);
   flip_TEST (Class <D>::use ().size_of () == 3);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestDataModel::run_010 ()
{
   class Model : public DataModel <Model> {};

   Model::version ("test");

   class C : public Object
   {
   public:
      Float _float;
   };

   class D : public C
   {
   public:
      Int _int;
   };

   class B : public Object
   {
   public:
      D d;
   };

   class A : public Object
   {
   public:
      B b;
   };

   Model::declare <C> ()
      .name ("C")
      .member <Float, &C::_float> ("float");

   Model::declare <D> ()
      .name ("D")
      .inherit <C> ()
      .member <Int, &D::_int> ("int");

   Model::declare <B> ()
      .name ("A")
      .member <D, &B::d> ("d");

   Model::declare <A> ()
      .name ("B")
      .member <B, &A::b> ("b");

   Model::use ();

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);
   flip_TEST (Class <A>::use ().size_of () == 5);
   flip_TEST (Class <B>::use ().members ().size () == 1);
   flip_TEST (Class <B>::use ().size_of () == 4);
   flip_TEST (Class <C>::use ().members ().size () == 1);
   flip_TEST (Class <C>::use ().size_of () == 2);
   flip_TEST (Class <D>::use ().members ().size () == 2);
   flip_TEST (Class <D>::use ().size_of () == 3);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestDataModel::run_011 ()
{
   class Model : public DataModel <Model> {};

   std::vector <char> chars;
   for (uint8_t i = 0 ; i <= 0x20 ; ++i) chars.push_back (char (i));
   for (uint8_t i = 0x7f ; i != 0x00 ; ++i) chars.push_back (char (i));

   //

   flip_CHECK_THROW (Model::version (""));

   for (auto c : chars)
   {
      std::string str;
      str += c;
      flip_CHECK_THROW (Model::version (str));
   }

   //

   class A0 : public Object {};
   class A1 : public Object {};
   class A2 : public Object {};
   class A3 : public Object {};
   class A4 : public Object {};
   class A5 : public Object {};
   class A6 : public Object {};
   class A7 : public Object {};

   flip_CHECK_THROW (Model::declare <A0> ().name (""));
   flip_CHECK_THROW (Model::declare <A1> ().name ("\0"));   // same
   flip_CHECK_THROW (Model::declare <A2> ().name ("\x1f"));
   flip_CHECK_THROW (Model::declare <A3> ().name (" "));
   flip_CHECK_THROW (Model::declare <A4> ().name ("\x7f"));
   flip_CHECK_THROW (Model::declare <A5> ().name ("\x80"));
   flip_CHECK_THROW (Model::declare <A6> ().name ("\xfe"));
   flip_CHECK_THROW (Model::declare <A7> ().name ("\xff"));

   //

   class B : public Object
   {
   public:
      Int x;
   };

   auto & class_ = Model::declare <B> ().name ("B");

   for (auto c : chars)
   {
      std::string str;
      str += c;
      flip_CHECK_THROW ((class_.member <Int, &B::x> (str.c_str ())));
   }

   //

   enum E0 {};
   enum E1 {};
   enum E2 {};
   enum E3 {};
   enum E4 {};
   enum E5 {};
   enum E6 {};
   enum E7 {};

   flip_CHECK_THROW (Model::declare <E0> ().name (""));
   flip_CHECK_THROW (Model::declare <E1> ().name ("\0"));   // same
   flip_CHECK_THROW (Model::declare <E2> ().name ("\x1f"));
   flip_CHECK_THROW (Model::declare <E3> ().name (" "));
   flip_CHECK_THROW (Model::declare <E4> ().name ("\x7f"));
   flip_CHECK_THROW (Model::declare <E5> ().name ("\x80"));
   flip_CHECK_THROW (Model::declare <E6> ().name ("\xfe"));
   flip_CHECK_THROW (Model::declare <E7> ().name ("\xff"));

   //

   enum E {E0,};

   auto & enum_ = Model::declare <E> ().name ("E");

   for (auto c : chars)
   {
      std::string str;
      str += c;
      flip_CHECK_THROW (enum_.enumerator <E::E0> (str.c_str ()));
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestDataModel::run_012 ()
{
   class Model : public DataModel <Model> {};

   class A : public Object
   {
   public:
      Int x;
   };

   Class <A>::declare ()
      .name ("A")
      .member <Int, &A::x> ("x");

   flip_TEST (!Class <A>::use ().abstract ());
   flip_TEST (Class <A>::use ().members ().size () == 1);

   Model::add <A> ();

   flip_TEST (Model::use ().has_class ("A"));
   flip_TEST (!Model::use ().has_enum ("A"));
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestDataModel::run_013 ()
{
   class Model : public DataModel <Model> {};

   enum class A
   {
      A0,
   };

   EnumClass <A>::declare ()
      .name ("A")
      .enumerator <A::A0> ("A0");

   flip_TEST (EnumClass <A>::use ().size () == 1);

   Model::add <A> ();

   flip_TEST (!Model::use ().has_class ("A"));
   flip_TEST (Model::use ().has_enum ("A"));
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

