/*****************************************************************************

      TestVector.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestVector.h"

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

void  TestVector::run ()
{
   Model::version ("test.vector");

   Model::declare <Root> ()
      .name ("Root")
      .member <Vector <double>, &Root::_vector_double> ("vector_double")
      .member <Vector <Elem>, &Root::_vector_elem> ("vector_elem")
      .member <Vector <Elem2>, &Root::_vector_elem2> ("vector_elem2");

   run_000 ();
   run_000b ();
   run_000c ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_007b ();
   run_008 ();
   run_008b ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
   run_013 ();
   run_014 ();
   run_015 ();
   run_016 ();
   run_017 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Elem::operator ==
==============================================================================
*/

bool  TestVector::Elem::operator == (const Elem & rhs) const
{
   return (a == rhs.a) && (b == rhs.b);
}



/*
==============================================================================
Name : Elem::write
==============================================================================
*/

void  TestVector::Elem::write (StreamBinOut & sbo) const
{
   sbo << a << b;
}



/*
==============================================================================
Name : Elem::read
==============================================================================
*/

void  TestVector::Elem::read (StreamBinIn & sbi)
{
   sbi >> a >> b;
}



/*
==============================================================================
Name : Elem2::Elem2
==============================================================================
*/

TestVector::Elem2::Elem2 (bool a_, double b_, char c_, float d_)
:  a (a_)
,  b (b_)
,  c (c_)
,  d (d_)
{
}



/*
==============================================================================
Name : Elem2::operator ==
==============================================================================
*/

bool  TestVector::Elem2::operator == (const Elem2 & rhs) const
{
   return (a == rhs.a) && (b == rhs.b) && (c == rhs.c) && (d == rhs.d);
}



/*
==============================================================================
Name : Elem2::write
==============================================================================
*/

void  TestVector::Elem2::write (StreamBinOut & sbo) const
{
   sbo << a << b << c << d;
}



/*
==============================================================================
Name : Elem2::read
==============================================================================
*/

void  TestVector::Elem2::read (StreamBinIn & sbi)
{
   sbi >> a >> b >> c >> d;
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestVector::run_000 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <double> data {1.0, 2.5, 3.7};

   root._vector_double.replace (root._vector_double.begin (), root._vector_double.end (), data);

   flip_TEST (root._vector_double == data);
   flip_TEST (!(root._vector_double != data));
   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_double == data);
   flip_TEST (!(root._vector_double != data));
   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before () == data);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before () == data);

   document.commit ();

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before ().empty ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before ().empty ());

   document.commit ();

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before () == data);
}



/*
==============================================================================
Name : run_000b
==============================================================================
*/

void  TestVector::run_000b ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <double> data {1.0, 2.5, 3.7};

   root._vector_double = data;

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before () == data);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before () == data);

   document.commit ();

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before ().empty ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before ().empty ());

   document.commit ();

   flip_TEST (root._vector_double.value () == data);
   flip_TEST (root._vector_double.before () == data);
}



/*
==============================================================================
Name : run_000c
==============================================================================
*/

void  TestVector::run_000c ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <double> data {1.0, 2.5, 3.7};
   std::vector <double> data2 (data);

   root._vector_double = std::move (data);

   flip_TEST (root._vector_double.value () == data2);
   flip_TEST (root._vector_double.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_double.value () == data2);
   flip_TEST (root._vector_double.before () == data2);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before () == data2);

   document.commit ();

   flip_TEST (root._vector_double.value ().empty ());
   flip_TEST (root._vector_double.before ().empty ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_double.value () == data2);
   flip_TEST (root._vector_double.before ().empty ());

   document.commit ();

   flip_TEST (root._vector_double.value () == data2);
   flip_TEST (root._vector_double.before () == data2);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestVector::run_001 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem> data {{1.0, 2.0}, {2.5, 3.5}, {3.7, 4.78}};

   root._vector_elem.replace (root._vector_elem.begin (), root._vector_elem.end (), data);

   flip_TEST (root._vector_elem.value () == data);
   flip_TEST (root._vector_elem.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_elem.value () == data);
   flip_TEST (root._vector_elem.before () == data);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem.value ().empty ());
   flip_TEST (root._vector_elem.before () == data);

   document.commit ();

   flip_TEST (root._vector_elem.value ().empty ());
   flip_TEST (root._vector_elem.before ().empty ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem.value () == data);
   flip_TEST (root._vector_elem.before ().empty ());

   document.commit ();

   flip_TEST (root._vector_elem.value () == data);
   flip_TEST (root._vector_elem.before () == data);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestVector::run_002 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2.replace (root._vector_elem2.begin (), root._vector_elem2.end (), data);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before () == data);

   document.commit ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   document.commit ();

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestVector::run_003 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2.replace (root._vector_elem2.begin (), root._vector_elem2.end (), data);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data);

   root._vector_elem2.clear ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before () == data);

   document.commit ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestVector::run_004 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2.replace (root._vector_elem2.begin (), root._vector_elem2.end (), data);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   document.revert ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestVector::run_005 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2.replace (
      root._vector_elem2.begin (), root._vector_elem2.end (),
      data.begin (), data.begin () + 2
   );

   std::vector <Elem2> data2 {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}
   };


   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before () == data2);

   root._vector_elem2.clear ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before () == data2);

   document.commit ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestVector::run_006 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2.replace (
      root._vector_elem2.begin (), root._vector_elem2.end (),
      data.begin () + 1, data.begin () + 3
   );

   std::vector <Elem2> data2 {
      {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };


   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before ().empty ());

   auto it = root._vector_elem2.begin ();
   flip_TEST (it->a == false);
   flip_TEST (it->b == 2.5);
   flip_TEST (it->c == 'O');
   flip_TEST (it->d == 55.1f);
   ++it;
   flip_TEST (it->a == true);
   flip_TEST (it->b == 3.7);
   flip_TEST (it->c == 'y');
   flip_TEST (it->d == 4.2f);
   ++it;
   flip_TEST (it == root._vector_elem2.end ());
   flip_TEST (it == root._vector_elem2.cend ());

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before () == data2);

   std::vector <Elem2> data3 (root._vector_elem2);
   flip_TEST (data3 == data2);

   root._vector_elem2.clear ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before () == data2);

   document.commit ();

   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestVector::run_007 ()
{
   std::vector <double> data {1.0, 2.5, 3.7};

   Vector <double> vec1 (data);

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   Vector <double> vec2 (vec1);

   flip_TEST (data == vec2);
   flip_TEST (vec2 == data);
   flip_TEST (vec2.value () == data);

   Vector <double> vec3 (std::move (vec2));

   flip_TEST (data == vec3);
   flip_TEST (vec3 == data);
   flip_TEST (vec3.value () == data);
}



/*
==============================================================================
Name : run_007b
==============================================================================
*/

void  TestVector::run_007b ()
{
   std::vector <double> data {1.0, 2.5, 3.7};

   Vector <double> vec1;
   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   Vector <double> vec2;
   vec2 = vec1;

   flip_TEST (data == vec2);
   flip_TEST (vec2 == data);
   flip_TEST (vec2.value () == data);

   Vector <double> vec3;
   vec3 = std::move (vec2);

   flip_TEST (data == vec3);
   flip_TEST (vec3 == data);
   flip_TEST (vec3.value () == data);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestVector::run_008 ()
{
   std::vector <double> data;

   Vector <double> vec1 (data);

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   Vector <double> vec2 (vec1);

   flip_TEST (data == vec2);
   flip_TEST (vec2 == data);
   flip_TEST (vec2.value () == data);

   Vector <double> vec3 (std::move (vec2));

   flip_TEST (data == vec3);
   flip_TEST (vec3 == data);
   flip_TEST (vec3.value () == data);
}



/*
==============================================================================
Name : run_008b
==============================================================================
*/

void  TestVector::run_008b ()
{
   std::vector <double> data;

   Vector <double> vec1;
   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   Vector <double> vec2;
   vec2 = vec1;

   flip_TEST (data == vec2);
   flip_TEST (vec2 == data);
   flip_TEST (vec2.value () == data);

   Vector <double> vec3;
   vec3 = std::move (vec2);

   flip_TEST (data == vec3);
   flip_TEST (vec3 == data);
   flip_TEST (vec3.value () == data);

   vec3.clear ();
   flip_TEST (data == vec3);
   flip_TEST (vec3 == data);
   flip_TEST (vec3.value () == data);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestVector::run_009 ()
{
   std::vector <double> data {1.0, 2.5, 3.7};

   Vector <double> vec1 (data);

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestVector::run_010 ()
{
   std::vector <double> data {1.0, 2.5, 3.7};

   Vector <double> vec1;

   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);

   vec1 = data;

   flip_TEST (data == vec1);
   flip_TEST (! (data != vec1));
   flip_TEST (vec1 == data);
   flip_TEST (vec1.value () == data);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestVector::run_011 ()
{
   std::vector <double> data {1.0, 2.5, 3.7};
   std::vector <double> data2 {2.5};

   Vector <double> vec1 (data);

   auto it = vec1.begin ();
   ++it;
   auto it2 = it;
   ++it2;

   vec1.replace (it, it2, data2.begin (), data2.end ());
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestVector::run_012 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2 = data;
   root._vector_elem2.clear ();

   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();
   flip_TEST (tx.empty ());

   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestVector::run_013 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2 = data;
   document.revert ();

   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();
   flip_TEST (tx.empty ());

   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before ().empty ());
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestVector::run_014 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2 = data;

   flip_TEST (root._vector_elem2.begin () != root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () != root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   auto tx = document.commit ();
   flip_TEST (!tx.empty ());

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.begin () == root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () == root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value ().empty ());
   flip_TEST (root._vector_elem2.before () == data);
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestVector::run_015 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };
   std::vector <Elem2> data2 {
      {false, 3.5, '!', 44.1f}
   };

   root._vector_elem2 = data;

   flip_TEST (root._vector_elem2.begin () != root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () != root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   document.commit ();

   root._vector_elem2 = data2;

   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before () == data);

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data2);
   flip_TEST (root._vector_elem2.before () == data2);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data2);
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestVector::run_016 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };
   std::vector <Elem2> data2 {
      {false, 3.5, '!', 44.1f}
   };
   std::vector <Elem2> data3 {
      {true, 1.0, 'j', 2.f}, {false, 3.5, '!', 44.1f}
   };

   root._vector_elem2 = data;

   flip_TEST (root._vector_elem2.begin () != root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () != root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   document.commit ();

   root._vector_elem2.replace (
      root._vector_elem2.begin () + 1, root._vector_elem2.end (),
      data2
   );

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data);

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data3);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data3);

   document.commit ();

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data);

   document.commit ();

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data3);
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestVector::run_017 ()
{
   Document document (Model::use (), 12345678901234, 'flip', 'test');

   Root & root = document.root <Root> ();

   std::vector <Elem2> data {
      {true, 1.0, 'j', 2.f}, {false, 2.5, 'O', 55.1f}, {true, 3.7, 'y', 4.2f}
   };
   std::vector <Elem2> data2 {
      {false, 3.5, '!', 44.1f}
   };
   std::vector <Elem2> data3 {
      {false, 3.5, '!', 44.1f}, {true, 3.7, 'y', 4.2f}
   };

   root._vector_elem2 = data;

   flip_TEST (root._vector_elem2.begin () != root._vector_elem2.end ());
   flip_TEST (root._vector_elem2.cbegin () != root._vector_elem2.cend ());
   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before ().empty ());

   document.commit ();

   root._vector_elem2.replace (
      root._vector_elem2.begin (), root._vector_elem2.begin () + 2,
      data2
   );

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data);

   auto tx = document.commit ();

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data3);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data3);

   document.commit ();

   flip_TEST (root._vector_elem2.value () == data);
   flip_TEST (root._vector_elem2.before () == data);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data);

   document.commit ();

   flip_TEST (root._vector_elem2.value () == data3);
   flip_TEST (root._vector_elem2.before () == data3);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

