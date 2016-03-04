/*****************************************************************************

      TestCollection.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestCollection.h"

#include "flip/detail/fnc.h"
#include "flip/Class.h"
#include "flip/CarrierDirect.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/iterator.h"
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

void  TestCollection::run ()
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
      .member <Collection <A>, &B::_coll> ("coll")
      .member <Int, &B::_int> ("int");

   Model::declare <C> ()
      .name ("C")
      .member <Int, &C::_int> ("int");

   Model::declare <Root> ()
      .name ("Root")
      .member <Collection <A>, &Root::_coll> ("coll")
      .member <Collection <A>, &Root::_coll2> ("coll2")
      .member <B, &Root::_b> ("b")
      .member <B, &Root::_b2> ("b2")
      .member <Collection <B>, &Root::_coll3> ("coll3")
      .member <Collection <C>, &Root::_coll4> ("coll4");



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
   run_028 ();
   run_029 ();
   run_030 ();
   run_031 ();
   run_032c ();
   run_032d ();
   run_033 ();
   run_034 ();
   run_037 ();
   run_038 ();
   run_039 ();
   run_040 ();
   run_042 ();
   run_043 ();
   run_044 ();
   run_045 ();
   run_046 ();
   run_047 ();
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

void  TestCollection::check_concept_iterator () // COV_NF_START
{
   // construction/destruction
   {
      Collection <A>::iterator it;
   }

   {
      Collection <A>::iterator it;
      Collection <A>::iterator it2 (it);
   }

   {
      Collection <A>::iterator it;
      Collection <A>::iterator it2;
      it2 = it;
   }

   // comparison
   {
      Collection <A>::iterator it;
      Collection <A>::iterator it2;
      bool a = it == it2; a = !a;
      bool b = it != it2; b = !b;
   }

   // dereference
   {
      Collection <A>::iterator it;
      *it;
      int64_t a = it->_int; a = 0;
   }

   // mutability
   {
      Collection <A>::iterator it;
      A a;
      *it = a;
   }

   // increment
   {
      Collection <A>::iterator it;
      ++it;
      it++;
      *it++;
   }

   // decrement
   {
      Collection <A>::iterator it;
      --it;
      it--;
      *it--;
   }

   // swap
   {
      Collection <A>::iterator it;
      Collection <A>::iterator it2;
      std::swap (it, it2);
   }

   // algorithm
   {
      std::vector <A> a_vector;
      Collection <A> a_coll;

      a_vector.assign (a_coll.begin (), a_coll.end ());
   }

   // algorithm
   {
      std::list <A> a_list;
      Collection <A> a_coll;

      a_list.assign (a_coll.begin (), a_coll.end ());
   }
}  // COV_NF_END



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestCollection::run_000 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ().removed ());

   document.commit ();

   flip_TEST (!root._coll.begin ().added ());
   flip_TEST (root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ().removed ());
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestCollection::run_001 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   BackEndIR backend1 = document.write ();

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ().removed ());

   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestCollection::run_002 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   Collection <A>::iterator it;
   it = root._coll.begin ();

   flip_TEST (it.added ());
   flip_TEST (!it.resident ());
   flip_TEST (!it.removed ());

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   it = root._coll.begin ();

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   root._coll.emplace ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 2);

   /*it = root._coll.begin ();

   flip_TEST (it.added ());
   flip_TEST (!it.resident ());
   flip_TEST (!it.removed ());

   ++it;

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 2);

   it = root._coll.begin ();

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());

   ++it;

   flip_TEST (!it.added ());
   flip_TEST (it.resident ());
   flip_TEST (!it.removed ());*/
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestCollection::run_003 ()
{
   for (int i = 0 ; i < 100 ; ++i)
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll.emplace ();
      a._int = 2LL;
      auto it_remove = root._coll.emplace ();
      A & a2 = *it_remove;
      a2._int = 3LL;

      document.commit ();

      root._coll.erase (it_remove);
      A & a3 = *root._coll.emplace ();
      a3._int = 5LL;

      document.commit ();
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestCollection::run_004 ()
{
   for (int i = 0 ; i < 100 ; ++i)
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll.emplace ();
      a._int = 2LL;
      auto it_remove = root._coll.emplace ();
      A & a2 = *it_remove;
      a2._int = 3LL;

      document.commit ();

      root._coll.erase (it_remove);
      A & a3 = *root._coll.emplace ();
      a3._int = 5LL;
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestCollection::run_005 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   {
      auto it = root._coll.begin ();
      auto it_end = root._coll.end ();

      flip_TEST (it == it_end);
   }

   {
      auto rit = root._coll.rbegin ();
      auto rit_end = root._coll.rend ();

      flip_TEST (rit == rit_end);
   }

   {
      const Collection <A> & coll = root._coll;

      auto it = coll.begin ();
      auto it_end = coll.end ();

      flip_TEST (it == it_end);
   }

   {
      const Collection <A> & coll = root._coll;

      auto rit = coll.rbegin ();
      auto rit_end = coll.rend ();

      flip_TEST (rit == rit_end);
   }

   {
      auto it = root._coll.cbegin ();
      auto it_end = root._coll.cend ();

      flip_TEST (it == it_end);
   }

   {
      auto rit = root._coll.crbegin ();
      auto rit_end = root._coll.crend ();

      flip_TEST (rit == rit_end);
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestCollection::run_006 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   {
      auto it = root._coll.begin ();
      auto it_end = root._coll.end ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      auto rit = root._coll.rbegin ();
      auto rit_end = root._coll.rend ();

      flip_TEST (rit != rit_end);
      ++rit;
      flip_TEST (rit == rit_end);
   }

   {
      const Collection <A> & coll = root._coll;

      auto it = coll.begin ();
      auto it_end = coll.end ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      const Collection <A> & coll = root._coll;

      auto rit = coll.rbegin ();
      auto rit_end = coll.rend ();

      flip_TEST (rit != rit_end);
      ++rit;
      flip_TEST (rit == rit_end);
   }

   {
      auto it = root._coll.cbegin ();
      auto it_end = root._coll.cend ();

      flip_TEST (it != it_end);
      ++it;
      flip_TEST (it == it_end);
   }

   {
      auto rit = root._coll.crbegin ();
      auto rit_end = root._coll.crend ();

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

void  TestCollection::run_007 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestCollection::run_008 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestCollection::run_009 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   Transaction tx = document.commit ();

   auto data = tx.serialize ();
   Transaction tx2 (data);

   bool ok_flag = document.execute_backward (tx2);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestCollection::run_010 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   root._coll.erase (it);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestCollection::run_011 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         123456,
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll.emplace ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         a.ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestCollection::run_012 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_erase (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::null
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         123456,
         it->ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         it->ref ()
      );

      bool ok_flag = document.execute_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestCollection::run_013 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         123456,
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll.emplace ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_insert (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         a.ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestCollection::run_014 ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_erase (
         root.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      KeyRandom key;

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::get_first (document.user (), document.actor ())
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <A>::use ().type_id (document.data_model ()),
         Ref::null
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         123456,
         it->ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      auto it = root._coll.emplace ();

      KeyRandom key = it.key ();

      Transaction tx;
      tx.push_collection_erase (
         root._coll.ref (), 0, key,
         Class <Root>::use ().type_id (document.data_model ()),
         it->ref ()
      );

      bool ok_flag = document.execute_correct_forward (tx);
      flip_TEST (!ok_flag);

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   }
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestCollection::run_015 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 2LL;

   root._coll.insert (a);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._coll.begin ().added ());
   flip_TEST (root._coll.begin ().resident ());
   flip_TEST (root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestCollection::run_016 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (2LL, 0.0);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._coll.begin ().added ());
   flip_TEST (root._coll.begin ().resident ());
   flip_TEST (root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestCollection::run_017 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A a;
   a._int = 2LL;

   Mold mold (Model::use ());
   mold.make (a);

   root._coll.emplace (mold);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);

   document.commit ();

   flip_TEST (!root._coll.begin ().added ());
   flip_TEST (root._coll.begin ().resident ());
   flip_TEST (root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestCollection::run_018 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();
   root._coll.erase (it);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);

   it = root._coll.emplace (2LL, 0.0);

   flip_TEST (root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ()->resident ());
   flip_TEST (!root._coll.begin ().removed ());

   flip_TEST (root._coll.begin ()->_int == 2LL);

   document.commit ();

   root._coll.erase (it);

   flip_TEST (!root._coll.begin ().added ());
   flip_TEST (!root._coll.begin ().resident ());
   flip_TEST (!root._coll.begin ()->resident ());
   flip_TEST (root._coll.begin ().removed ());

   flip_TEST_NOTHING (root._coll.begin ()->_int == 0LL);
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestCollection::run_019 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (2LL, 3.5);
   root._coll.emplace (3LL, 3.5);
   root._coll.emplace (3LL, 4.5);
   root._coll.emplace (2LL, 4.5);

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 2);
   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 3LL;}) == 2);
   flip_TEST (root._coll.count_if ([](A & elem){return elem._float == 3.5;}) == 2);
   flip_TEST (root._coll.count_if ([](A & elem){return elem._float == 4.5;}) == 2);

   flip_TEST (root._coll.find_if ([](A & elem){return elem._int == 2LL;}) != root._coll.end ());
   flip_TEST (root._coll.find_if ([](A & elem){return elem._int == 4LL;}) == root._coll.end ());
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestCollection::run_020 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (2LL, 0.0);

   root._coll.disable_in_undo ();

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   document.execute_backward (tx, true);

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_020b
==============================================================================
*/

void  TestCollection::run_020b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace (2LL, 0.0);

   it->_int.disable_in_undo ();

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx, true);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx, true);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_020c
==============================================================================
*/

void  TestCollection::run_020c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace (2LL, 0.0);

   it->disable_in_undo ();

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);

   Transaction tx = document.commit ();

   bool ok_flag = document.execute_backward (tx, true);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_forward (tx, true);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestCollection::run_021 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (2LL, 0.0);
   root._coll.emplace (3LL, 0.0);

   Collection <A> coll = root._coll;

   flip_TEST (coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
   flip_TEST (coll.count_if ([](A & elem){return elem._int == 3LL;}) == 1);
}



/*
==============================================================================
Name : run_022
==============================================================================
*/

void  TestCollection::run_022 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._b._coll.emplace (2LL, 0.0);
   root._b._coll.emplace (3LL, 0.0);

   {
      Mold mold (Model::use ());
      mold.make (root._b);

      mold.cast <B> (root._b2);
      flip_TEST (root._b2._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
      flip_TEST (root._b2._coll.count_if ([](A & elem){return elem._int == 3LL;}) == 1);
   }
}



/*
==============================================================================
Name : run_022b
==============================================================================
*/

void  TestCollection::run_022b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._b._coll.emplace (2LL, 0.0);
   root._b._coll.emplace (3LL, 0.0);

   {
      Mold mold (Model::use ());
      mold.make (root._b, true);

      mold.cast <B> (root._b2);
      flip_TEST (root._b2._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 0);
      flip_TEST (root._b2._coll.count_if ([](A & elem){return elem._int == 3LL;}) == 0);
   }
}



/*
==============================================================================
Name : run_023
==============================================================================
*/

void  TestCollection::run_023 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace (2LL, 0.0);

   document.commit ();

   BackEndIR backend1 = document.write ();

   root._coll.erase (it);
   document.revert ();

   BackEndIR backend2 = document.write ();

   flip_TEST (root._coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
   flip_TEST (backend2.equal (backend1));
}



/*
==============================================================================
Name : run_024
==============================================================================
*/

void  TestCollection::run_024 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B b;
   b._coll.emplace (2LL, 0.0);

   root._coll3.insert (b);

   flip_TEST (root._coll3.count_if ([](B &){return true;}) == 1);
   flip_TEST (root._coll3.begin ()->_coll.count_if ([](A & elem){return elem._int == 2LL;}) == 1);
}



/*
==============================================================================
Name : run_025
==============================================================================
*/

void  TestCollection::run_025 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B & b = *root._coll3.emplace ();
   A & a = *b._coll.emplace ();
   a._int = 2LL;

   document.commit ();
}



/*
==============================================================================
Name : run_026
==============================================================================
*/

void  TestCollection::run_026 ()
{
   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         A a;
         flip_CHECK_THROW (root._coll.insert (a));
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._coll.emplace ();

      document.commit ();
   }

   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         flip_CHECK_THROW (root._coll.emplace ());
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._coll.emplace ();

      document.commit ();
   }

   {
      DocumentObserverLambda <Root> observer ([](Root & root){
         Mold mold (Model::use ());
         flip_CHECK_THROW (root._coll.emplace (mold));
      });

      Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._coll.emplace ();

      document.commit ();
   }
}



/*
==============================================================================
Name : run_027
==============================================================================
*/

void  TestCollection::run_027 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   A & a = *it;
   a._int = 2LL;

   document.commit ();

   root._coll2.splice (root._coll, it);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll2);

   auto tx = document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll2);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll);

   document.commit ();

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll);
}



/*
==============================================================================
Name : run_027b
==============================================================================
*/

void  TestCollection::run_027b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll2.emplace ();

   A & a = *it;
   a._int = 2LL;

   document.commit ();

   root._coll.splice (root._coll2, it);

   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll);

   auto tx = document.commit ();

   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll.begin ()->parent ().before <Collection <A>> () == &root._coll);
   flip_TEST (&root._coll.begin ()->parent <Collection <A>> () == &root._coll2);

   document.commit ();

   flip_TEST (root._coll2.count_if ([](A &){return true;}) == 1);
   flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   flip_TEST (root._coll2.begin ()->_int == 2LL);
   flip_TEST (&root._coll2.begin ()->parent ().before <Collection <A>> () == &root._coll2);
   flip_TEST (&root._coll2.begin ()->parent <Collection <A>> () == &root._coll2);
}



/*
==============================================================================
Name : run_028
==============================================================================
*/

void  TestCollection::run_028 ()
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
      root._coll.emplace ();

      document.commit ();

      root._coll.clear ();

      document.commit ();
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._coll.count_if ([](A &){return true;}) == 0);
   }
}



/*
==============================================================================
Name : run_029
==============================================================================
*/

void  TestCollection::run_029 ()
{
   Collection <A> coll;

   coll.emplace (1LL, 2.5);
   coll.emplace (3LL, 4.7);

   Collection <A> coll2;
   coll2.emplace (2LL, 7.1);

   coll2 = coll;

   flip_TEST (std::count_if (coll2.cbegin (), coll2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (coll2.cbegin (), coll2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (coll2.cbegin (), coll2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_030
==============================================================================
*/

void  TestCollection::run_030 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (1LL, 2.5);
   root._coll.emplace (3LL, 4.7);

   root._coll2.emplace (2LL, 7.1);

   document.commit ();

   root._coll2 = root._coll;

   document.commit ();

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_031
==============================================================================
*/

void  TestCollection::run_031 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace (1LL, 2.5);
   root._coll.emplace (3LL, 4.7);

   root._coll2.emplace (2LL, 7.1);

   root._coll2 = root._coll;

   document.commit ();

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A &){
      return true;
   }) == 2);

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A & a){
      return a._int == 1LL && a._float == 2.5;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.cbegin (), root._coll2.cend (), [](const A & a){
      return a._int == 3LL && a._float == 4.7;
   }) == 1);
}



/*
==============================================================================
Name : run_032c
==============================================================================
*/

void  TestCollection::run_032c ()
{
   Collection <A> coll;
   coll.emplace (1LL, 2.5);
   coll.emplace (3LL, 4.7);
   coll.emplace (6LL, 2.7);

   Collection <A>::iterator it;
   it = coll.begin ();

   int64_t val = 0;

   A & a = *it++;
   val += a._int;

   A & a2 = *it++;
   val += a2._int;

   A & a3 = *it++;
   val += a3._int;

   flip_TEST (it == coll.end ());
   flip_TEST (val == 10);
}



/*
==============================================================================
Name : run_032d
==============================================================================
*/

void  TestCollection::run_032d ()
{
   Collection <A> coll;
   coll.emplace (1LL, 2.5);
   coll.emplace (3LL, 4.7);
   coll.emplace (6LL, 2.7);

   Collection <A>::iterator it = coll.end ();

   int64_t val = 0;

   --it;

   A & a = *it--;
   val += a._int;

   A & a2 = *it--;
   val += a2._int;

   A & a3 = *it;
   val += a3._int;

   flip_TEST (it == coll.begin ());
   flip_TEST (val == 10);
}



/*
==============================================================================
Name : run_033
==============================================================================
*/

void  TestCollection::run_033 ()
{
   Collection <A> coll;
   coll.emplace (1LL, 2.5);

   Collection <A>::iterator it = coll.begin ();

   Collection <A>::iterator it2 = std::move (it);
   flip_TEST (it2->_int == 1LL);
   flip_TEST (it2->_float == 2.5);
}



/*
==============================================================================
Name : run_034
==============================================================================
*/

void  TestCollection::run_034 ()
{
   Collection <A> coll;
   coll.emplace (1LL, 2.5);

   Collection <A>::iterator it = coll.begin ();

   Collection <A>::iterator it2;
   it2 = coll.end ();
   it2 = std::move (it);
   flip_TEST (it2->_int == 1LL);
   flip_TEST (it2->_float == 2.5);
}



/*
==============================================================================
Name : run_037
==============================================================================
*/

void  TestCollection::run_037 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_038
==============================================================================
*/

void  TestCollection::run_038 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_039
==============================================================================
*/

void  TestCollection::run_039 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_040
==============================================================================
*/

void  TestCollection::run_040 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll.emplace ();

   auto tx = document.commit ();

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_042
==============================================================================
*/

void  TestCollection::run_042 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();
   root._coll.splice (root._coll, it);

   auto tx = document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_043
==============================================================================
*/

void  TestCollection::run_043 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();
   root._coll2.splice (root._coll, it);

   auto tx = document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_044
==============================================================================
*/

void  TestCollection::run_044 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   auto tx = document.commit ();

   root._coll2.splice (root._coll, it);

   auto tx2 = document.commit ();
   tx.push (std::move (tx2));

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 1);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_045
==============================================================================
*/

void  TestCollection::run_045 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_move (root._coll2.ref (), 0, it.key (), Ref::null, it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_046
==============================================================================
*/

void  TestCollection::run_046 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_move (Ref::null, 0, it.key (), root._coll.ref (), it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_047
==============================================================================
*/

void  TestCollection::run_047 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_move (root._coll.ref (), 0, it.key (), root._coll.ref (), it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_048
==============================================================================
*/

void  TestCollection::run_048 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();
   auto it2 = root._coll2.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_move (root._coll.ref (), 0, it.key (), root._coll2.ref (), it2.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 1);
}



/*
==============================================================================
Name : run_049
==============================================================================
*/

void  TestCollection::run_049 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();
   KeyRandom key;

   document.commit ();

   Transaction tx;
   tx.push_collection_move (root._coll2.ref (), 0, key, root._coll.ref (), key);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_050
==============================================================================
*/

void  TestCollection::run_050 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_move (root._coll3.ref (), 0, it.key (), root._coll.ref (), it.key ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   flip_TEST (std::count_if (root._coll3.begin (), root._coll3.end (), [](B &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_051
==============================================================================
*/

void  TestCollection::run_051 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   auto tx = document.commit ();

   Transaction tx2;
   tx2.push_collection_insert (
      root._coll.ref (), 0, it.key (),
      Class <A>::use ().type_id (document.data_model ()), it->ref () + 1
   );

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx2);
   flip_TEST (!ok_flag);

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 1);

   document.commit ();

   flip_TEST (std::count_if (root._coll.begin (), root._coll.end (), [](A &){
      return true;
   }) == 0);
}



/*
==============================================================================
Name : run_052
==============================================================================
*/

void  TestCollection::run_052 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A2 & a2 = dynamic_cast <A2 &> (*root._coll.emplace <A2> ());
   a2._int2 = 2LL;

   root._coll2 = root._coll;

   flip_TEST (std::count_if (root._coll2.begin (), root._coll2.end (), [](A & a){
      return dynamic_cast <A2 &> (a)._int2 == 2LL;
   }) == 1);
}



/*
==============================================================================
Name : run_053
==============================================================================
*/

void  TestCollection::run_053 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll.emplace ();

   document.commit ();

   Transaction tx;
   KeyRandom key;
   tx.push_collection_move (
      root._coll.ref (), 0, it.key (), root._coll.ref (), key
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_054
==============================================================================
*/

void  TestCollection::run_054 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll3.emplace ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll3.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()), it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_055
==============================================================================
*/

void  TestCollection::run_055 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll3.emplace ();
   it->_coll.emplace ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll3.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()), it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_056
==============================================================================
*/

void  TestCollection::run_056 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <A> uptr = std::make_unique <A> (2, 3.5);

   root._coll.insert (std::move (uptr));

   flip_TEST (uptr.get () == nullptr);
   flip_TEST (&root._coll.begin ()->get_class () == &Class <A>::use ());
   flip_TEST (root._coll.begin ()->_int == 2LL);
   flip_TEST (root._coll.begin ()->_float == 3.5);
}



/*
==============================================================================
Name : run_057
==============================================================================
*/

void  TestCollection::run_057 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <A> uptr (new A2);
   A2 & a = dynamic_cast <A2 &> (*uptr);
   a._int = 3;
   a._float = 4.5;
   a._int2 = 17;

   root._coll.insert (std::move (uptr));

   flip_TEST (uptr.get () == nullptr);
   flip_TEST (&root._coll.begin ()->get_class () == &Class <A2>::use ());
   flip_TEST (root._coll.begin ()->_int == 3LL);
   flip_TEST (root._coll.begin ()->_float == 4.5);
   flip_TEST (dynamic_cast <A2 &> (*root._coll.begin ())._int2 == 17LL);
}



/*
==============================================================================
Name : run_058
==============================================================================
*/

void  TestCollection::run_058 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._coll.emplace ();
   a2._int = 11LL;
   a2._float = 3.5;

   collection_iterator it = root._coll.begin ();
   collection_iterator it_end = root._coll.end ();

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

void  TestCollection::run_059 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._coll.emplace ();
   a2._int = 11LL;
   a2._float = 3.5;

   collection_iterator it = root._coll.rbegin ();
   collection_iterator it_end = root._coll.rend ();

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

void  TestCollection::run_060 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   A & a2 = *root._coll.emplace ();
   a2._int = 11LL;
   a2._float = 3.5;

   document.commit ();

   collection_iterator it = root._coll.begin ();
   collection_iterator it_end = root._coll.end ();

   flip_TEST (it != it_end);
   flip_TEST (it.resident ());

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.resident ());

   ++it;

   flip_TEST (it == it_end);

   root._coll.clear ();

   it = root._coll.begin ();

   flip_TEST (it != it_end);
   flip_TEST (it.removed ());

   ++it;

   flip_TEST (it != it_end);
   flip_TEST (it.removed ());

   ++it;

   flip_TEST (it == it_end);

   --it;
   --it;

   flip_TEST (it == root._coll.begin ());
}



/*
==============================================================================
Name : run_061
==============================================================================
*/

void  TestCollection::run_061 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   collection_iterator it = root._coll.begin ();
   collection_iterator it_end = root._coll.end ();

   collection_iterator it2 = std::move (it);
   collection_iterator it3;
   collection_iterator it4;

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

   collection_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_062
==============================================================================
*/

void  TestCollection::run_062 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   const_collection_iterator it = root._coll.begin ();
   const_collection_iterator it_end = root._coll.end ();

   const_collection_iterator it2 = std::move (it);
   const_collection_iterator it3;
   const_collection_iterator it4;

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

   const_collection_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_063
==============================================================================
*/

void  TestCollection::run_063 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   collection_iterator it = root._coll.gbegin ();
   collection_iterator it_end = root._coll.gend ();

   collection_iterator it2 = std::move (it);
   collection_iterator it3;
   collection_iterator it4;

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

   collection_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_064
==============================================================================
*/

void  TestCollection::run_064 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   A & a = *root._coll.emplace ();
   a._int = 3LL;
   a._float = 2.5;

   const_collection_iterator it = root._coll.gcbegin ();
   const_collection_iterator it_end = root._coll.gcend ();

   const_collection_iterator it2 = std::move (it);
   const_collection_iterator it3;
   const_collection_iterator it4;

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

   const_collection_iterator it5;  // dtor test
}



/*
==============================================================================
Name : run_065
==============================================================================
*/

void  TestCollection::run_065 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::unique_ptr <B> uptr = std::make_unique <B> ();
   uptr->_coll.emplace (2LL, 3.5);

   root._coll3.insert (std::move (uptr));

   flip_TEST (uptr.get () == nullptr);

   B & b = *root._coll3.begin ();

   flip_TEST (b._coll.begin ()->ref () != Ref::null);
   flip_TEST (b._coll.begin ()->ref () != b._int.ref ());
   flip_TEST (b._coll.ref () + 1 == b._int.ref ());
}



/*
==============================================================================
Name : run_065b
==============================================================================
*/

void  TestCollection::run_065b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   B ob;
   ob._coll.emplace (2LL, 3.5);

   root._coll3.insert (ob);

   B & b = *root._coll3.begin ();

   flip_TEST (b._coll.begin ()->ref () != Ref::null);
   flip_TEST (b._coll.begin ()->ref () != b._int.ref ());
   flip_TEST (b._coll.ref () + 1 == b._int.ref ());
}



/*
==============================================================================
Name : run_066
==============================================================================
*/

void  TestCollection::run_066 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._coll4.emplace (3LL);

   C & c = *root._coll4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066b
==============================================================================
*/

void  TestCollection::run_066b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   C c0 (3LL);

   root._coll4.insert (c0);

   C & c = *root._coll4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066c
==============================================================================
*/

void  TestCollection::run_066c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto cuptr = std::unique_ptr <C> (new C (3LL));

   root._coll4.insert (std::move (cuptr));

   C & c = *root._coll4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_066d
==============================================================================
*/

void  TestCollection::run_066d ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Mold mold (Model::use ());

   C c0 (3LL);
   mold.make (c0);

   root._coll4.emplace (mold);

   C & c = *root._coll4.begin ();

   flip_TEST (c._int == 3LL);
}



/*
==============================================================================
Name : run_067
==============================================================================
*/

void  TestCollection::run_067 ()
{
   {
      Collection <A>::iterator it;
      Collection <A>::const_iterator it2 (it);
   }

   {
      Collection <A>::iterator it;
      Collection <A>::const_iterator it2;
      it2 = it;
   }

   {
      Collection <A>::iterator it;
      Collection <A>::const_iterator it2 (std::move (it));
   }

   {
      Collection <A>::iterator it;
      Collection <A>::const_iterator it2;
      it2 = std::move (it);
   }

   //

   {
      Collection <A>::reverse_iterator it;
      Collection <A>::const_reverse_iterator it2 (it);
   }

   {
      Collection <A>::reverse_iterator it;
      Collection <A>::const_reverse_iterator it2;
      it2 = it;
   }

   {
      Collection <A>::reverse_iterator it;
      Collection <A>::const_reverse_iterator it2 (std::move (it));
   }

   {
      Collection <A>::reverse_iterator it;
      Collection <A>::const_reverse_iterator it2;
      it2 = std::move (it);
   }

   //

   {
      auto f = [](Collection <A>::const_iterator){};

      Collection <A>::iterator it;
      f (it);
   }

   {
      auto f = [](Collection <A>::const_reverse_iterator){};

      Collection <A>::reverse_iterator it;
      f (it);
   }
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

/*void   TestCollection::document_changed (Collection <A> & coll)
{
   if (!coll.changed ()) return;

   auto it = coll.begin ();
   const auto it_end = coll.end ();

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

            flip_TEST (a.parent ().changed ());

            // 'a' has necesseraly moved to another container
            // this is the new container

            a.parent <Collection <A>> ();
         }
         else if (it.resident ())
         {
            // 'a' didn't move
         }
         else if (it.removed ())
         {
            // 'a' have moved and 'it' is the old iterator

            flip_TEST (a.parent ().changed ());

            // 'a' has necesseraly moved to another container
            // this is the old container

            a.parent ().before <Collection <A>> ();
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

