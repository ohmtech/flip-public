/*****************************************************************************

      TestArray.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestArray.h"

#include "flip/detail/fnc.h"
#include "flip/CarrierDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Hub.h"
#include "flip/Mold.h"
#include "flip/PortDirect.h"
#include "flip/iterator.h"
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

void  TestArray::run ()
{
   Model::version ("test.document");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <A2> ()
      .name ("A2")
      .inherit <A> ()
      .member <Int, &A2::_int2> ("int2");

   Model::declare <B> ()
      .name ("B")
      .member <Array <A>, &B::_array> ("array")
      .member <Int, &B::_int> ("int");

   Model::declare <C> ()
      .name ("C")
      .member <Int, &C::_int> ("int");

   Model::declare <Root> ()
      .name ("Root")
      .member <Array <A>, &Root::_array> ("array")
      .member <Array <A>, &Root::_array2> ("array2")
      .member <B, &Root::_b> ("b")
      .member <B, &Root::_b2> ("b2")
      .member <Array <B>, &Root::_array3> ("array3")
      .member <Array <C>, &Root::_array4> ("array4");



   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_003b ();
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
   run_020b ();
   run_020c ();
   run_021 ();
   run_022 ();
   run_022b ();
   run_023 ();
   run_024 ();
   run_025 ();
   run_026 ();
   run_027 ();
   run_027b ();
   run_027c ();
   run_027d ();
   run_027e ();
   run_027f ();
   run_028 ();
   run_029 ();
   run_030 ();
   run_031 ();
   run_032 ();
   run_032b ();
   run_033 ();
   run_034 ();
   run_037 ();
   run_038 ();
   run_039 ();
   run_040 ();
   run_041 ();
   run_042 ();
   run_043 ();
   run_044 ();
   run_045 ();
   run_046 ();
   run_048 ();
   run_049 ();
   run_050 ();
   run_051 ();
   run_052 ();
   run_053 ();
   run_054 ();
   run_055 ();
   run_056 ();
   run_057 ();
   run_058 ();
   run_059 ();
   run_060 ();
   run_061 ();
   run_062 ();
   run_063 ();
   run_064 ();
   run_065 ();
   run_065b ();
   run_066 ();
   run_066b ();
   run_066c ();
   run_066d ();
   run_067 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : check_concept_iterator
==============================================================================
*/

void  TestArray::check_concept_iterator ()   // COV_NF_START
{
   // construction/destruction
   {
      Array <A>::iterator it;
   }

   {
      Array <A>::iterator it;
      Array <A>::iterator it2 (it);
   }

   {
      Array <A>::iterator it;
      Array <A>::iterator it2;
      it2 = it;
   }

   // comparison
   {
      Array <A>::iterator it;
      Array <A>::iterator it2;
      bool a = it == it2; a = !a;
      bool b = it != it2; b = !b;
   }

   // dereference
   {
      Array <A>::iterator it;
      *it;
      int64_t a = it->_int; a = 0;
   }

   // mutability
   {
      Array <A>::iterator it;
      A a;
      *it = a;
   }

   // increment
   {
      Array <A>::iterator it;
      ++it;
      it++;
      *it++;
   }

   // decrement
   {
      Array <A>::iterator it;
      --it;
      it--;
      *it--;
   }

   // swap
   {
      Array <A>::iterator it;
      Array <A>::iterator it2;
      std::swap (it, it2);
   }

   // algorithm
   {
      std::vector <A> a_vector;
      Array <A> a_array;

      a_vector.assign (a_array.begin (), a_array.end ());
   }

   // algorithm
   {
      std::list <A> a_list;
      Array <A> a_array;

      a_list.assign (a_array.begin (), a_array.end ());
   }
}  // COV_NF_END



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestArray::run_000 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){return true;}) == 1);
   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   document.commit ();

   flip_TEST (!root._array.begin ().added ());
   flip_TEST (root._array.begin ().resident ());
   flip_TEST (root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestArray::run_001 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   BackEndIR backend1 = document.write ();

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ().removed ());

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestArray::run_002 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   auto it = root._array.begin ();

   flip_TEST (it.added ());
   flip_TEST (!it.resident ());
   flip_TEST (!it.removed ());

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   it = root._array.begin ();

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   root._array.emplace (root._array.begin ());

   flip_TEST (root._array.count_if ([](A &){return true;}) == 2);

   it = root._array.begin ();

   flip_TEST (it.added ());
   flip_TEST (!it.resident ());
   flip_TEST (!it.removed ());

   ++it;

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 2);

   it = root._array.begin ();

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   ++it;

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestArray::run_003 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 2LL;
   auto it_remove = root._array.emplace (root._array.begin ());
   A & a2 = *it_remove;
   a2._int = 3LL;

   document.commit ();

   root._array.erase (it_remove);
   A & a3 = *root._array.emplace (root._array.end ());
   a3._int = 5LL;

   document.commit ();
}



/*
==============================================================================
Name : run_003b
==============================================================================
*/

void  TestArray::run_003b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 2LL;
   auto it_remove = root._array.emplace (root._array.end ());
   A & a2 = *it_remove;
   a2._int = 3LL;

   document.commit ();

   root._array.erase (it_remove);
   A & a3 = *root._array.emplace (root._array.end ());
   a3._int = 5LL;

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestArray::run_004 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 2LL;
   auto it_remove = root._array.emplace (root._array.end ());
   A & a2 = *it_remove;
   a2._int = 3LL;

   document.commit ();

   root._array.erase (it_remove);
   A & a3 = *root._array.emplace (root._array.end ());
   a3._int = 5LL;
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestArray::run_005 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   {
      auto it = root._array.begin ();
      auto it_end = root._array.end ();

      flip_TEST (it == it_end);
   }

   {
      auto rit = root._array.rbegin ();
      auto rit_end = root._array.rend ();

      flip_TEST (rit == rit_end);
   }

   {
      const Array <A> & array = root._array;

      auto it = array.begin ();
      auto it_end = array.end ();

      flip_TEST (it == it_end);
   }

   {
      const Array <A> & array = root._array;

      auto rit = array.rbegin ();
      auto rit_end = array.rend ();

      flip_TEST (rit == rit_end);
   }

   {
      auto it = root._array.cbegin ();
      auto it_end = root._array.cend ();

      flip_TEST (it == it_end);
   }

   {
      auto rit = root._array.crbegin ();
      auto rit_end = root._array.crend ();

      flip_TEST (rit == rit_end);
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestArray::run_006 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   {
      auto it = root._array.begin ();
      auto it_end = root._array.end ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      auto rit = root._array.rbegin ();
      auto rit_end = root._array.rend ();

      flip_TEST (rit != rit_end);
      ++rit;
      flip_TEST (rit == rit_end);
   }

   {
      const Array <A> & array = root._array;

      auto it = array.begin ();
      auto it_end = array.end ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      const Array <A> & array = root._array;

      auto rit = array.rbegin ();
      auto rit_end = array.rend ();

      flip_TEST (rit != rit_end);
      ++rit;
      flip_TEST (rit == rit_end);
   }

   {
      auto it = root._array.cbegin ();
      auto it_end = root._array.cend ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      auto rit = root._array.crbegin ();
      auto rit_end = root._array.crend ();

      flip_TEST (rit != rit_end);
      ++rit;
      flip_TEST (rit == rit_end);
   }
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestArray::run_007 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestArray::run_008 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestArray::run_009 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   Transaction tx = document.commit ();

   auto data = tx.serialize ();
   Transaction tx2 (data);

   bool ok_flag = document.execute_backward (tx2);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestArray::run_010 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   document.commit ();

   root._array.erase (it);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestArray::run_011 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         123456,
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._array.emplace (root._array.end ());

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         a.ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestArray::run_012 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_erase (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::null
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         123456,
         it->ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         it->ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestArray::run_013 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         123456,
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._array.emplace (root._array.end ());

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_insert (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         a.ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestArray::run_014 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_erase (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::null
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         123456,
         it->ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._array.emplace (root._array.end ());

      KeyFloat key = it.key ();

      Transaction tx;
      tx.push_array_erase (
         root._array.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         it->ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestArray::run_015 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 2LL;

   root._array.insert (root._array.end (), a);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._array.begin ().added ());
   flip_TEST (root._array.begin ().resident ());
   flip_TEST (root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestArray::run_016 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 2LL, 0.0);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._array.begin ().added ());
   flip_TEST (root._array.begin ().resident ());
   flip_TEST (root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestArray::run_017 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   root._array.emplace (root._array.end (), mold);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._array.begin ().added ());
   flip_TEST (root._array.begin ().resident ());
   flip_TEST (root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestArray::run_018 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());
   root._array.erase (it);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);

   it = root._array.emplace (root._array.end (), 2LL, 0.0);

   flip_TEST (root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (!root._array.begin ().removed ());

   flip_TEST (root._array.begin ()->_int == 2LL);

   document.commit ();

   root._array.erase (it);

   flip_TEST (!root._array.begin ().added ());
   flip_TEST (!root._array.begin ().resident ());
   flip_TEST (!root._array.begin ()->resident ());
   flip_TEST (root._array.begin ().removed ());

   flip_TEST_NOTHING (root._array.begin ()->_int == 0LL);
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestArray::run_019 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 2LL, 3.5);
   root._array.emplace (root._array.end (), 3LL, 3.5);
   root._array.emplace (root._array.end (), 3LL, 4.5);
   root._array.emplace (root._array.end (), 2LL, 4.5);

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 2);
   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 3LL;}) == 2);
   flip_TEST (root._array.count_if ([](A & elem){return elem._float == 3.5;}) == 2);
   flip_TEST (root._array.count_if ([](A & elem){return elem._float == 4.5;}) == 2);

   flip_TEST (root._array.find_if ([](A & elem){return elem._int == 2LL;}) != root._array.end ());
   flip_TEST (root._array.find_if ([](A & elem){return elem._int == 4LL;}) == root._array.end ());
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestArray::run_020 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 2LL, 0.0);

   root._array.disable_in_undo ();

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   document.execute_backward (tx, true);

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_020b
==============================================================================
*/

void  TestArray::run_020b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end (), 2LL, 0.0);

   it->_int.disable_in_undo ();

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx, true);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx, true);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_020c
==============================================================================
*/

void  TestArray::run_020c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end (), 2LL, 0.0);

   it->disable_in_undo ();

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx, true);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx, true);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestArray::run_021 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 2LL, 0.0);
   root._array.emplace (root._array.end (), 3LL, 0.0);

   Array <A> array = root._array;

   flip_TEST (array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
   flip_TEST (array.count_if ([](A & elem){return elem._int == 3LL;}) == 1);
}



/*
==============================================================================
Name : run_022
==============================================================================
*/

void  TestArray::run_022 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._b._array.emplace (root._b._array.end (), 2LL, 0.0);
   root._b._array.emplace (root._b._array.end (), 3LL, 0.0);

   {
      Mold mold (Model::use ());
      mold.make (root._b);

      mold.cast <B> (root._b2);
      flip_TEST (root._b2._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
      flip_TEST (root._b2._array.count_if ([](A & elem){return elem._int == 3LL;}) == 1);
   }
}



/*
==============================================================================
Name : run_022b
==============================================================================
*/

void  TestArray::run_022b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._b._array.emplace (root._b._array.end (), 2LL, 0.0);
   root._b._array.emplace (root._b._array.end (), 3LL, 0.0);

   {
      Mold mold (Model::use ());
      mold.make (root._b, true);

      mold.cast <B> (root._b2);
      flip_TEST (root._b2._array.count_if ([](A & elem){return elem._int == 2LL;}) == 0);
      flip_TEST (root._b2._array.count_if ([](A & elem){return elem._int == 3LL;}) == 0);
   }
}



/*
==============================================================================
Name : run_023
==============================================================================
*/

void  TestArray::run_023 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end (), 2LL, 0.0);

   document.commit ();

   BackEndIR backend1 = document.write ();

   root._array.erase (it);
   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (root._array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
   flip_TEST (backend2.equal (backend1));
}



/*
==============================================================================
Name : run_024
==============================================================================
*/

void  TestArray::run_024 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B b;
   b._array.emplace (b._array.end (), 2LL, 0.0);

   root._array3.insert (root._array3.end (), b);

   flip_TEST (root._array3.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._array3.begin ()->_array.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_025
==============================================================================
*/

void  TestArray::run_025 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B & b = *root._array3.emplace (root._array3.end ());
   A & a = *b._array.emplace (b._array.end ());
   a._int = 2LL;

   document.commit ();
}



/*
==============================================================================
Name : run_026
==============================================================================
*/

void  TestArray::run_026 ()
{
   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         A a;
         flip_CHECK_THROW (root._array.insert (root._array.end (), a));
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._array.emplace (root._array.end ());

      document.commit ();
   }

   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         flip_CHECK_THROW (root._array.emplace (root._array.end ()));
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._array.emplace (root._array.end ());

      document.commit ();
   }

   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         Mold mold (Model::use ());
         flip_CHECK_THROW (root._array.emplace (root._array.end (), mold));
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._array.emplace (root._array.end ());

      document.commit ();
   }
}



/*
==============================================================================
Name : run_027
==============================================================================
*/

void  TestArray::run_027 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   A & a = *it;
   a._int = 2LL;

   document.commit ();

   root._array2.splice (root._array2.end (), root._array, it);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array2);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array2);

   auto tx = document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array2);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array);

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);
}



/*
==============================================================================
Name : run_027b
==============================================================================
*/

void  TestArray::run_027b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array2.emplace (root._array2.end ());

   A & a = *it;
   a._int = 2LL;

   document.commit ();

   root._array.splice (root._array.end (), root._array2, it);

   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   auto tx = document.commit ();

   flip_TEST (root._array2.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array2);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array2);

   document.commit ();

   flip_TEST (root._array2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._array2.begin ()->_int == 2LL);
   flip_TEST (&root._array2.begin ()->parent ().before <Array <A>> () == &root._array2);
   flip_TEST (&root._array2.begin ()->parent <Array <A>> () == &root._array2);
}



/*
==============================================================================
Name : run_027c
==============================================================================
*/

void  TestArray::run_027c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   A & a = *it;
   a._int = 2LL;

   document.commit ();

   root._array.splice (root._array.end (), root._array, it);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 2);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   auto tx = document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_027d
==============================================================================
*/

void  TestArray::run_027d ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;

   auto it2 = root._array.emplace (root._array.end ());

   A & a2 = *it2;
   a2._int = 2LL;

   document.commit ();

   root._array.splice (root._array.begin (), root._array, it2);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 3);

   {
      auto it = root._array.begin ();

      flip_TEST (it->_int == 2LL);
      flip_TEST (&it->parent ().before <Array <A>> () == &root._array);
      flip_TEST (&it->parent <Array <A>> () == &root._array);

      ++it;

      flip_TEST (it->_int == 3LL);
      flip_TEST (&it->parent ().before <Array <A>> () == &root._array);
      flip_TEST (&it->parent <Array <A>> () == &root._array);

      ++it;

      flip_TEST (it->_int == 2LL);
      flip_TEST (&it->parent ().before <Array <A>> () == &root._array);
      flip_TEST (&it->parent <Array <A>> () == &root._array);
   }

   document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 2);

   {
      auto it = root._array.begin ();

      flip_TEST (it->_int == 2LL);
      flip_TEST (&it->parent ().before <Array <A>> () == &root._array);
      flip_TEST (&it->parent <Array <A>> () == &root._array);

      ++it;

      flip_TEST (it->_int == 3LL);
      flip_TEST (&it->parent ().before <Array <A>> () == &root._array);
      flip_TEST (&it->parent <Array <A>> () == &root._array);
   }
}



/*
==============================================================================
Name : run_027e
==============================================================================
*/

void  TestArray::run_027e ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   A & a = *it;
   a._int = 2LL;

   root._array.splice (root._array.end (), root._array, it);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   auto tx = document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);
}



/*
==============================================================================
Name : run_027f
==============================================================================
*/

void  TestArray::run_027f ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   A & a = *it;
   a._int = 2LL;

   auto tx = document.commit ();

   root._array.splice (root._array.end (), root._array, it);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 2);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   auto tx2 = document.commit ();

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent ().before <Array <A>> () == &root._array);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);

   bool ok_flag = document.execute_backward (tx2);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx2);
   flip_TEST (ok_flag);

   flip_TEST (root._array.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (&root._array.begin ()->parent <Array <A>> () == &root._array);
}



/*
==============================================================================
Name : run_028
==============================================================================
*/

void  TestArray::run_028 ()
{
   PortDirect port;
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);
   document2.pull ();

   {
      Root & root = document.root <Root> ();
      root._array.emplace (root._array.end ());

      document.commit ();

      root._array.clear ();

      document.commit ();
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._array.count_if ([](A &){return true;}) == 0);
   }
}



/*
==============================================================================
Name : run_029
==============================================================================
*/

void  TestArray::run_029 ()
{
   Array <A> array;

   array.emplace (array.end (), 1LL, 2.5);
   array.emplace (array.end (), 3LL, 4.7);

   Array <A> array2;
   array2.emplace (array2.end (), 2LL, 7.1);

   array2 = array;

   flip_TEST (std::count_if (array2.cbegin (), array2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (array2.cbegin (), array2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (array2.cbegin (), array2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_030
==============================================================================
*/

void  TestArray::run_030 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 1LL, 2.5);
   root._array.emplace (root._array.end (), 3LL, 4.7);

   root._array2.emplace (root._array2.end (), 2LL, 7.1);

   document.commit ();

   root._array2 = root._array;

   document.commit ();

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_031
==============================================================================
*/

void  TestArray::run_031 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end (), 1LL, 2.5);
   root._array.emplace (root._array.end (), 3LL, 4.7);

   root._array2.emplace (root._array2.end (), 2LL, 7.1);

   root._array2 = root._array;

   document.commit ();

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (root._array2.cbegin (), root._array2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_032
==============================================================================
*/

void  TestArray::run_032 ()
{
   Array <A> array;
   array.emplace (array.end (), 1LL, 2.5);
   array.emplace (array.end (), 3LL, 4.7);
   array.emplace (array.end (), 6LL, 2.7);

   Array <A>::iterator it = array.begin ();
   flip_TEST (it->_int == 1LL);
   flip_TEST (it->_float == 2.5);

   ++it;
   flip_TEST (it->_int == 3LL);
   flip_TEST (it->_float == 4.7);

   ++it;
   flip_TEST (it->_int == 6LL);
   flip_TEST (it->_float == 2.7);

   ++it;
   flip_TEST (it == array.end ());

   it = array.begin ();
   flip_TEST (it->_int == 1LL);
   flip_TEST (it->_float == 2.5);

   it++;
   flip_TEST (it->_int == 3LL);
   flip_TEST (it->_float == 4.7);

   it++;
   flip_TEST (it->_int == 6LL);
   flip_TEST (it->_float == 2.7);

   it++;
   flip_TEST (it == array.end ());

   it = array.begin ();
   flip_TEST (it->_int == 1LL);
   flip_TEST (it->_float == 2.5);

   A & a = *it++;
   flip_TEST (a._int == 1LL);
   flip_TEST (a._float == 2.5);

   A & a2 = *it++;
   flip_TEST (a2._int == 3LL);
   flip_TEST (a2._float == 4.7);

   A & a3 = *it++;
   flip_TEST (a3._int == 6LL);
   flip_TEST (a3._float == 2.7);

   flip_TEST (it == array.end ());
}



/*
==============================================================================
Name : run_032b
==============================================================================
*/

void  TestArray::run_032b ()
{
   Array <A> array;
   array.emplace (array.end (), 1LL, 2.5);
   array.emplace (array.end (), 3LL, 4.7);
   array.emplace (array.end (), 6LL, 2.7);

   Array <A>::iterator it = array.end ();

   --it;
   flip_TEST (it->_int == 6LL);
   flip_TEST (it->_float == 2.7);

   --it;
   flip_TEST (it->_int == 3LL);
   flip_TEST (it->_float == 4.7);

   --it;
   flip_TEST (it->_int == 1LL);
   flip_TEST (it->_float == 2.5);

   it = array.end ();

   --it;
   flip_TEST (it->_int == 6LL);
   flip_TEST (it->_float == 2.7);

   it--;
   flip_TEST (it->_int == 3LL);
   flip_TEST (it->_float == 4.7);

   it--;
   flip_TEST (it->_int == 1LL);
   flip_TEST (it->_float == 2.5);

   it = array.end ();

   --it;

   A & a = *it--;
   flip_TEST (a._int == 6LL);
   flip_TEST (a._float == 2.7);

   A & a2 = *it--;
   flip_TEST (a2._int == 3LL);
   flip_TEST (a2._float == 4.7);
}



/*
==============================================================================
Name : run_033
==============================================================================
*/

void  TestArray::run_033 ()
{
   Array <A> array;
   array.emplace (array.end (), 1LL, 2.5);
   array.emplace (array.end (), 3LL, 4.7);
   array.emplace (array.end (), 6LL, 2.7);

   Array <A>::iterator it = array.begin ();
   ++it;

   Array <A>::iterator it2 = std::move (it);
   flip_TEST (it2->_int == 3LL);
   flip_TEST (it2->_float == 4.7);
}



/*
==============================================================================
Name : run_034
==============================================================================
*/

void  TestArray::run_034 ()
{
   Array <A> array;
   array.emplace (array.end (), 1LL, 2.5);
   array.emplace (array.end (), 3LL, 4.7);
   array.emplace (array.end (), 6LL, 2.7);

   Array <A>::iterator it = array.begin ();
   ++it;

   Array <A>::iterator it2;
   it2 = array.begin ();
   it2 = std::move (it);
   flip_TEST (it2->_int == 3LL);
   flip_TEST (it2->_float == 4.7);
}



/*
==============================================================================
Name : run_037
==============================================================================
*/

void  TestArray::run_037 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_038
==============================================================================
*/

void  TestArray::run_038 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_039
==============================================================================
*/

void  TestArray::run_039 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_040
==============================================================================
*/

void  TestArray::run_040 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_041
==============================================================================
*/

void  TestArray::run_041 ()
{
   Array <A> array;

   flip_TEST (std::distance (array.begin (), array.end ()) == 0);
   flip_TEST (std::distance (array.cbegin (), array.cend ()) == 0);
   flip_TEST (std::distance (array.rbegin (), array.rend ()) == 0);
   flip_TEST (std::distance (array.crbegin (), array.crend ()) == 0);

   array.emplace (array.end (), 1LL, 2.5);

   flip_TEST (std::distance (array.begin (), array.end ()) == 1);
   flip_TEST (std::distance (++array.begin (), array.end ()) == 0);
   flip_TEST (std::distance (array.cbegin (), array.cend ()) == 1);
   flip_TEST (std::distance (++array.cbegin (), array.cend ()) == 0);
   flip_TEST (std::distance (array.rbegin (), array.rend ()) == 1);
   flip_TEST (std::distance (++array.rbegin (), array.rend ()) == 0);
   flip_TEST (std::distance (array.crbegin (), array.crend ()) == 1);
   flip_TEST (std::distance (++array.crbegin (), array.crend ()) == 0);

   array.emplace (array.end (), 1LL, 2.5);

   flip_TEST (std::distance (array.begin (), array.end ()) == 2);
   flip_TEST (std::distance (++array.begin (), array.end ()) == 1);
   flip_TEST (std::distance (array.begin (), --array.end ()) == 1);
   flip_TEST (std::distance (++array.begin (), --array.end ()) == 0);
   flip_TEST (std::distance (array.cbegin (), array.cend ()) == 2);
   flip_TEST (std::distance (array.rbegin (), array.rend ()) == 2);
   flip_TEST (std::distance (++array.rbegin (), array.rend ()) == 1);
   flip_TEST (std::distance (array.rbegin (), --array.rend ()) == 1);
   flip_TEST (std::distance (++array.rbegin (), --array.rend ()) == 0);
   flip_TEST (std::distance (array.crbegin (), array.crend ()) == 2);
}



/*
==============================================================================
Name : run_042
==============================================================================
*/

void  TestArray::run_042 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());
   root._array.splice (root._array.end (), root._array, it);

   auto tx = document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_043
==============================================================================
*/

void  TestArray::run_043 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());
   root._array2.splice (root._array2.end (), root._array, it);

   auto tx = document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_044
==============================================================================
*/

void  TestArray::run_044 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   root._array2.splice (root._array2.end (), root._array, it);

   auto tx2 = document.commit ();
   tx.push (std::move (tx2));

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 1);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_045
==============================================================================
*/

void  TestArray::run_045 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_move (root._array2.ref (), 0, it.key (), Ref::null, it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_046
==============================================================================
*/

void  TestArray::run_046 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_move (Ref::null, 0, it.key (), root._array.ref (), it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_048
==============================================================================
*/

void  TestArray::run_048 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());
   auto it2 = root._array2.emplace (root._array2.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_move (root._array.ref (), 0, it.key (), root._array2.ref (), it2.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_049
==============================================================================
*/

void  TestArray::run_049 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());
   KeyFloat key = KeyFloat::generate (it.key (), KeyFloat::one);

   document.commit ();

   Transaction tx;
   tx.push_array_move (root._array2.ref (), 0, key, root._array.ref (), key);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_050
==============================================================================
*/

void  TestArray::run_050 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_move (root._array3.ref (), 0, it.key (), root._array.ref (), it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._array3.begin (), root._array3.end (), [](B &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_051
==============================================================================
*/

void  TestArray::run_051 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   auto tx = document.commit ();

   Transaction tx2;
   tx2.push_array_insert (
      root._array.ref (), 0, it.key (),
      Class <A>::use ().type_id (document.data_model ()), it->ref () + 1
   );

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx2);
   flip_TEST (!ok_flag);

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._array.begin (), root._array.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_052
==============================================================================
*/

void  TestArray::run_052 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A2 & a2 = dynamic_cast <A2 &> (*root._array.emplace <A2> (root._array.end ()));
   a2._int2 = 2LL;

   root._array2 = root._array;

   flip_TEST (std::count_if (root._array2.begin (), root._array2.end (), [](A & a){
      return dynamic_cast <A2 &> (a)._int2 == 2LL;
   }) == 1);
}



/*
==============================================================================
Name : run_053
==============================================================================
*/

void  TestArray::run_053 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array.emplace (root._array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_move (
      root._array.ref (), 0, it.key (), root._array.ref (), it.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_054
==============================================================================
*/

void  TestArray::run_054 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array3.emplace (root._array3.end ());

   Transaction tx;
   tx.push_array_erase (
      root._array3.ref (), 0, it.key (),
      Class <A>::use ().type_id (document.data_model ()), it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_055
==============================================================================
*/

void  TestArray::run_055 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array3.emplace (root._array3.end ());
   it->_array.emplace (it->_array.end ());

   Transaction tx;
   tx.push_array_erase (
      root._array3.ref (), 0, it.key (),
      Class <A>::use ().type_id (document.data_model ()), it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_056
==============================================================================
*/

void  TestArray::run_056 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <A> uptr = std::make_unique <A> (2, 3.5);

   root._array.insert (root._array.end (), std::move (uptr));

   flip_TEST (uptr.get () == nullptr);
   flip_TEST (&root._array.begin ()->get_class () == &Class <A>::use ());
   flip_TEST (root._array.begin ()->_int == 2LL);
   flip_TEST (root._array.begin ()->_float == 3.5);
}



/*
==============================================================================
Name : run_057
==============================================================================
*/

void  TestArray::run_057 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <A> uptr (new A2);
   A2 & a = dynamic_cast <A2 &> (*uptr);
   a._int = 3;
   a._float = 4.5;
   a._int2 = 17;

   root._array.insert (root._array.begin (), std::move (uptr));

   flip_TEST (uptr.get () == nullptr);
   flip_TEST (&root._array.begin ()->get_class () == &Class <A2>::use ());
   flip_TEST (root._array.begin ()->_int == 3LL);
   flip_TEST (root._array.begin ()->_float == 4.5);
   flip_TEST (dynamic_cast <A2 &> (*root._array.begin ())._int2 == 17LL);
}



/*
==============================================================================
Name : run_058
==============================================================================
*/

void  TestArray::run_058 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._array.emplace (root._array.end ());
   a2._int = 11LL;
   a2._float = 3.5;

   array_iterator it = root._array.begin ();
   array_iterator it_end = root._array.end ();

   int64_t a_int = 0LL;
   double a_float = 0.0;

   flip_TEST (it != it_end);
   flip_TEST (it.added ());

   auto key = it.key ();

   a_int += dynamic_cast <A &> (*it)._int;
   a_float += dynamic_cast <A &> (*it)._float;

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.added ());

   a_int += dynamic_cast <A &> (*it)._int;
   a_float += dynamic_cast <A &> (*it)._float;

   flip_TEST (a_int == 14LL);
   flip_TEST (a_float == 6.0);

   auto key2 = it.key ();

   flip_TEST (key < key2);

   ++it;

   flip_TEST (it == it_end);
}



/*
==============================================================================
Name : run_059
==============================================================================
*/

void  TestArray::run_059 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._array.emplace (root._array.end ());
   a2._int = 11LL;
   a2._float = 3.5;

   array_iterator it = root._array.rbegin ();
   array_iterator it_end = root._array.rend ();

   int64_t a_int = 0LL;
   double a_float = 0.0;

   flip_TEST (it != it_end);
   flip_TEST (it.added ());

   auto key = it.key ();

   a_int += dynamic_cast <A &> (*it)._int;
   a_float += dynamic_cast <A &> (*it)._float;

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.added ());

   a_int += dynamic_cast <A &> (*it)._int;
   a_float += dynamic_cast <A &> (*it)._float;

   flip_TEST (a_int == 14LL);
   flip_TEST (a_float == 6.0);

   auto key2 = it.key ();

   flip_TEST (key2 < key);

   ++it;

   flip_TEST (it == it_end);
}



/*
==============================================================================
Name : run_060
==============================================================================
*/

void  TestArray::run_060 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._array.emplace (root._array.end ());
   a2._int = 11LL;
   a2._float = 3.5;

   document.commit ();

   array_iterator it = root._array.begin ();
   array_iterator it_end = root._array.end ();

   flip_TEST (it != it_end);
   flip_TEST (it.resident ());

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.resident ());

   ++it;

   flip_TEST (it == it_end);

   root._array.clear ();

   it = root._array.begin ();

   flip_TEST (it != it_end);
   flip_TEST (it.removed ());

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.removed ());

   ++it;

   flip_TEST (it == it_end);

   --it;
   --it;

   flip_TEST (it == root._array.begin ());
}



/*
==============================================================================
Name : run_061
==============================================================================
*/

void  TestArray::run_061 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   array_iterator it = root._array.begin ();
   array_iterator it_end = root._array.end ();

   array_iterator it2 = std::move (it);
   array_iterator it3;
   array_iterator it4;

   flip_TEST (it2 != it_end);
   flip_TEST (it2->changed ());

   ++it2;
   flip_TEST (it2 == it_end);

   it3 = std::move (it2);
   flip_TEST (it3 == it_end);
   --it3;
   flip_TEST (it3 != it_end);
   flip_TEST (it3->changed ());
   flip_TEST (dynamic_cast <A &> (*it3)._int == 3LL);

   it4 = it3;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <A &> (*it4)._int == 3LL);

   it4++;
   it4--;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <A &> (*it4)._int == 3LL);

   array_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_062
==============================================================================
*/

void  TestArray::run_062 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   const_array_iterator it = root._array.begin ();
   const_array_iterator it_end = root._array.end ();

   const_array_iterator it2 = std::move (it);
   const_array_iterator it3;
   const_array_iterator it4;

   flip_TEST (it2 != it_end);
   flip_TEST (it2->changed ());

   ++it2;
   flip_TEST (it2 == it_end);

   it3 = std::move (it2);
   flip_TEST (it3 == it_end);
   --it3;
   flip_TEST (it3 != it_end);
   flip_TEST (it3->changed ());
   flip_TEST (dynamic_cast <const A &> (*it3)._int == 3LL);

   it4 = it3;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <const A &> (*it4)._int == 3LL);

   it4++;
   it4--;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <const A &> (*it4)._int == 3LL);

   const_array_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_063
==============================================================================
*/

void  TestArray::run_063 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   array_iterator it = root._array.gbegin ();
   array_iterator it_end = root._array.gend ();

   array_iterator it2 = std::move (it);
   array_iterator it3;
   array_iterator it4;

   flip_TEST (it2 != it_end);
   flip_TEST (it2->changed ());

   ++it2;
   flip_TEST (it2 == it_end);

   it3 = std::move (it2);
   flip_TEST (it3 == it_end);
   --it3;
   flip_TEST (it3 != it_end);
   flip_TEST (it3->changed ());
   flip_TEST (dynamic_cast <A &> (*it3)._int == 3LL);

   it4 = it3;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <A &> (*it4)._int == 3LL);

   it4++;
   it4--;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <A &> (*it4)._int == 3LL);

   array_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_064
==============================================================================
*/

void  TestArray::run_064 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._array.emplace (root._array.end ());
   a._int = 3LL;
   a._float = 2.5;

   const_array_iterator it = root._array.gcbegin ();
   const_array_iterator it_end = root._array.gcend ();

   const_array_iterator it2 = std::move (it);
   const_array_iterator it3;
   const_array_iterator it4;

   flip_TEST (it2 != it_end);
   flip_TEST (it2->changed ());

   ++it2;
   flip_TEST (it2 == it_end);

   it3 = std::move (it2);
   flip_TEST (it3 == it_end);
   --it3;
   flip_TEST (it3 != it_end);
   flip_TEST (it3->changed ());
   flip_TEST (dynamic_cast <const A &> (*it3)._int == 3LL);

   it4 = it3;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <const A &> (*it4)._int == 3LL);

   it4++;
   it4--;
   flip_TEST (it4 != it_end);
   flip_TEST (it4->changed ());
   flip_TEST (dynamic_cast <const A &> (*it4)._int == 3LL);

   const_array_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_065
==============================================================================
*/

void  TestArray::run_065 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <B> uptr = std::make_unique <B> ();
   uptr->_array.emplace (uptr->_array.end (), 2LL, 3.5);

   root._array3.insert (root._array3.end (), std::move (uptr));

   flip_TEST (uptr.get () == nullptr);

   B & b = *root._array3.begin ();

   flip_TEST (b._array.begin ()->ref () != Ref::null);
   flip_TEST (b._array.begin ()->ref () != b._int.ref ());
   flip_TEST (b._array.ref () + 1 == b._int.ref ());
}



/*
==============================================================================
Name : run_065b
==============================================================================
*/

void  TestArray::run_065b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B ob;
   ob._array.emplace (ob._array.end (), 2LL, 3.5);

   root._array3.insert (root._array3.end (), ob);

   B & b = *root._array3.begin ();

   flip_TEST (b._array.begin ()->ref () != Ref::null);
   flip_TEST (b._array.begin ()->ref () != b._int.ref ());
   flip_TEST (b._array.ref () + 1 == b._int.ref ());
}



/*
==============================================================================
Name : run_066
==============================================================================
*/

void  TestArray::run_066 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._array4.emplace (root._array4.end (), 3LL);

   C & c = *root._array4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066b
==============================================================================
*/

void  TestArray::run_066b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   C c0 (3LL);

   root._array4.insert (root._array4.end (), c0);

   C & c = *root._array4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066c
==============================================================================
*/

void  TestArray::run_066c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto cuptr = std::unique_ptr <C> (new C (3LL));

   root._array4.insert (root._array4.end (), std::move (cuptr));

   C & c = *root._array4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066d
==============================================================================
*/

void  TestArray::run_066d ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Mold mold (Model::use ());

   C c0 (3LL);
   mold.make (c0);

   root._array4.emplace (root._array4.end (), mold);

   C & c = *root._array4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_067
==============================================================================
*/

void  TestArray::run_067 ()
{
   {
      Array <A>::iterator it;
      Array <A>::const_iterator it2 (it);
   }

   {
      Array <A>::iterator it;
      Array <A>::const_iterator it2;
      it2 = it;
   }

   {
      Array <A>::iterator it;
      Array <A>::const_iterator it2 (std::move (it));
   }

   {
      Array <A>::iterator it;
      Array <A>::const_iterator it2;
      it2 = std::move (it);
   }

   //

   {
      Array <A>::reverse_iterator it;
      Array <A>::const_reverse_iterator it2 (it);
   }

   {
      Array <A>::reverse_iterator it;
      Array <A>::const_reverse_iterator it2;
      it2 = it;
   }

   {
      Array <A>::reverse_iterator it;
      Array <A>::const_reverse_iterator it2 (std::move (it));
   }

   {
      Array <A>::reverse_iterator it;
      Array <A>::const_reverse_iterator it2;
      it2 = std::move (it);
   }

   //

   {
      auto f = [](Array <A>::const_iterator){};

      Array <A>::iterator it;
      f (it);
   }

   {
      auto f = [](Array <A>::const_reverse_iterator){};

      Array <A>::reverse_iterator it;
      f (it);
   }
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

/*void   TestArray::document_changed (Array <A> & array)
{
   if (!array.changed ()) return;

   auto it = array.begin ();
   const auto it_end = array.end ();

   for (; it != it_end ; ++it)
   {
      A & a = *it;

      if (a.added ())
      {
         // 'a' was added and is a new object
      }
      else if (a.resident ())
      {
         if (it.added ())
         {
            // 'a' have moved and 'it' is the new iterator

            if (a.parent ().changed ())
            {
               // plus 'a' moved to another container
               // this is the new container

               a.parent <Array <A>> ();
            }
         }
         else if (it.resident ())
         {
            // 'a' didn't move
         }
         else if (it.removed ())
         {
            // 'a' have moved and 'it' is the old iterator

            if (a.parent ().changed ())
            {
               // plus 'a' moved to another container
               // this is the old container

               a.parent ().before <Array <A>> ();
            }
         }
      }
      else if (a.removed ())
      {
         // 'a' was removed and will be destroyed
      }
   }
}*/



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

