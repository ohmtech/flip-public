/*****************************************************************************

      TestBackEndIRDiff.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestBackEndIRDiff.h"

#include "flip/BackEndBinary.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/Document.h"
#include "flip/detail/ExecFlags.h"
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

void  TestBackEndIRDiff::run ()
{
   Model::version ("test.backend");

   Model::declare <E> ()
      .name ("E")
      .enumerator <E0> ("E0")
      .enumerator <E1> ("E1");

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

   Model::declare <C> ()
      .name ("C")
      .inherit <A> ()
      .member <Enum <E>, &C::_enum> ("enum");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Array <A>, &Root::_array_a> ("array_a")
      .member <Message <>, &Root::_message> ("message");



   run_000 ();
   run_001 ();
   run_001b ();
   run_002 ();
   run_002b ();
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
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestBackEndIRDiff::run_000 ()
{
   BackEndIR dst;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      root._int = 3LL;
      root._float = 4.3;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'beir');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;

   Transaction tx2;
   tx2.push_int64_set (Ref::root + 1, flags, 0LL, 3LL);
   tx2.push_float64_set (Ref::root + 2, flags, 0.0, 4.3);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestBackEndIRDiff::run_001 ()
{
   BackEndIR dst;
   KeyRandom key;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      root._coll_a.emplace ();
      key = root._coll_a.begin ().base ()->first;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'beir');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), document.actor ());

   Transaction tx2;
   tx2.push_collection_insert (Ref::root + 12, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_001b
==============================================================================
*/

void  TestBackEndIRDiff::run_001b ()
{
   BackEndIR dst;
   KeyFloat key;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      root._array_a.emplace (root._array_a.end ());
      key = root._array_a.begin ().base ()->first;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'beir');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), document.actor ());

   Transaction tx2;
   tx2.push_array_insert (Ref::root + 15, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestBackEndIRDiff::run_002 ()
{
   BackEndIR dst;
   KeyRandom key;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      key = root._coll_a.begin ().base ()->first;
      a._int = 3LL;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'beir');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), document.actor ());

   Transaction tx2;
   tx2.push_collection_insert (Ref::root + 12, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);
   tx2.push_int64_set (ref + 1, flags, 0LL, 3LL);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_002b
==============================================================================
*/

void  TestBackEndIRDiff::run_002b ()
{
   BackEndIR dst;
   KeyFloat key;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._array_a.emplace (root._array_a.end ());
      key = root._array_a.begin ().base ()->first;
      a._int = 3LL;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'beir');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), document.actor ());

   Transaction tx2;
   tx2.push_array_insert (Ref::root + 15, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);
   tx2.push_int64_set (ref + 1, flags, 0LL, 3LL);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestBackEndIRDiff::run_003 ()
{
   BackEndIR dst;
   KeyRandom key;
   uint64_t actor;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');
      actor = document.actor ();

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      key = root._coll_a.begin ().base ()->first;
      a._int = 3LL;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), actor);

   Transaction tx2;
   tx2.push_collection_insert (Ref::root + 12, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);
   tx2.push_int64_set (ref + 1, flags, 0LL, 3LL);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_003b
==============================================================================
*/

void  TestBackEndIRDiff::run_003b ()
{
   BackEndIR dst;
   KeyFloat key;
   uint64_t actor;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');
      actor = document.actor ();

      Root & root = document.root <Root> ();

      A & a = *root._array_a.emplace (root._array_a.end ());
      key = root._array_a.begin ().base ()->first;
      a._int = 3LL;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), actor);

   Transaction tx2;
   tx2.push_array_insert (Ref::root + 15, flags, key, Class <A>::use ().type_id (document.data_model ()), ref);
   tx2.push_int64_set (ref + 1, flags, 0LL, 3LL);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestBackEndIRDiff::run_004 ()
{
   BackEndIR dst;
   KeyRandom key1;
   KeyRandom key2;
   uint64_t actor;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');
      actor = document.actor ();

      Root & root = document.root <Root> ();

      B & b = *root._coll_b.emplace ();
      key1 = root._coll_b.begin ().base ()->first;
      A & a = *b._coll.emplace ();
      key2 = b._coll.begin ().base ()->first;
      a._int = 3LL;

      document.commit ();

      dst = document.write ();
   }

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Transaction tx = substract (dst, document);

   uint8_t flags = ExecFlags::OP_IN_UNDO;
   Ref ref = Ref::get_first (document.user (), actor);

   Transaction tx2;
   tx2.push_collection_insert (Ref::root + 13, flags, key1, Class <B>::use ().type_id (document.data_model ()), ref);
   tx2.push_collection_insert (ref + 5, flags, key2, Class <A>::use ().type_id (document.data_model ()), ref + 6);
   tx2.push_int64_set (ref + 7, flags, 0LL, 3LL);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestBackEndIRDiff::run_005 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      root._int = 3LL;
      root._float = 2.3;
      root._a._int = 4LL;
      root._a._float = 5.7;
      root._b._int = 5LL;
      root._b._float = 7.7;
      root._ref_a = &root._a;

      document.commit ();

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._int = 1LL;
      root._float = 7.3;
      root._a._int = 9LL;
      root._a._float = 1.7;
      root._b._int = 4LL;
      root._b._float = 1.3;
      root._ref_a = &root._b;

      document.commit ();

      document.read (backend);
      document.commit ();

      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 2.3);
      flip_TEST (root._a._int == 4LL);
      flip_TEST (root._a._float == 5.7);
      flip_TEST (root._b._int == 5LL);
      flip_TEST (root._b._float == 7.7);
      flip_TEST (root._ref_a == &root._a);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestBackEndIRDiff::run_006 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      a._int = 2LL;

      document.commit ();

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 2LL);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestBackEndIRDiff::run_007 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      a._int = 2LL;

      document.read (backend);
      document.commit ();

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestBackEndIRDiff::run_008 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      a._int = 2LL;

      document.commit ();

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      a._int = 3LL;

      document.commit ();

      document.read (backend);
      document.commit ();

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
      flip_TEST (root._coll_a.begin ()->_int == 2LL);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestBackEndIRDiff::run_009 ()
{
   BackEndIR backend;
   BackEndIR backend2;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._coll_a.emplace ();
      a._int = 2LL;

      auto it = root._coll_a.emplace ();
      A & a2 = *it;
      a2._int = 3LL;

      document.commit ();

      backend = document.write ();

      root._coll_a.erase (it);

      A & a3 = *root._coll_a.emplace ();
      a3._int = 5LL;

      document.commit ();

      backend2 = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (equal (backend, document.write ()));

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      document.read (backend2);
      document.commit ();

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == 5LL);
      }) == 1);

      flip_TEST (equal (backend2, document.write ()));
   }
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestBackEndIRDiff::run_010 ()
{
   for (int i = 0 ; i < 100 ; ++i)
   {
      BackEndIR backend;
      BackEndIR backend2;

      {
         Document document (Model::use (), 123456789UL, 'appl', 'beir');

         Root & root = document.root <Root> ();

         A & a = *root._coll_a.emplace ();
         a._int = 2LL;

         auto it = root._coll_a.emplace ();
         A & a2 = *it;
         a2._int = 3LL;

         document.commit ();

         backend = document.write ();

         root._coll_a.erase (it);

         A & a3 = *root._coll_a.emplace ();
         a3._int = 5LL;

         document.commit ();

         backend2 = document.write ();
      }

      {
         Document document (Model::use (), 123456789UL, 'appl', 'gui ');

         Root & root = document.root <Root> ();

         document.read (backend);
         document.commit ();

         flip_TEST (equal (backend, document.write ()));

         flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 2);
         flip_TEST (root._coll_a.count_if ([](A & elem){
            return (elem._int == 2LL);
         }) == 1);
         flip_TEST (root._coll_a.count_if ([](A & elem){
            return (elem._int == 3LL);
         }) == 1);

         document.read (backend2);
         document.revert ();

         flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 2);
         flip_TEST (root._coll_a.count_if ([](A & elem){
            return (elem._int == 2LL);
         }) == 1);
         flip_TEST (root._coll_a.count_if ([](A & elem){
            return (elem._int == 3LL);
         }) == 1);

         flip_TEST (equal (backend, document.write ()));
      }
   }
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestBackEndIRDiff::run_011 ()
{
   BackEndIR backend;
   BackEndIR backend2;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._array_a.emplace (root._array_a.end ());
      a._int = 2LL;

      auto it = root._array_a.emplace (root._array_a.end ());
      A & a2 = *it;
      a2._int = 3LL;

      document.commit ();

      backend = document.write ();

      root._array_a.erase (it);

      A & a3 = *root._array_a.emplace (root._array_a.end ());
      a3._int = 5LL;

      document.commit ();

      backend2 = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (equal (backend, document.write ()));

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      document.read (backend2);
      document.revert ();

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestBackEndIRDiff::run_012 ()
{
   BackEndIR backend;
   BackEndIR backend2;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._array_a.emplace (root._array_a.begin ());
      a._int = 2LL;

      auto it = root._array_a.emplace (root._array_a.begin ());
      A & a2 = *it;
      a2._int = 3LL;

      document.commit ();

      backend = document.write ();

      root._array_a.erase (it);

      A & a3 = *root._array_a.emplace (root._array_a.begin ());
      a3._int = 5LL;

      document.commit ();

      backend2 = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (equal (backend, document.write ()));

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      document.read (backend2);
      document.revert ();

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestBackEndIRDiff::run_013 ()
{
   BackEndIR backend;
   BackEndIR backend2;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      A & a = *root._array_a.emplace (root._array_a.begin ());
      a._int = 2LL;

      A & a2 = *root._array_a.emplace (root._array_a.begin ());
      a2._int = 3LL;

      document.commit ();

      backend = document.write ();

      root._array_a.clear ();

      document.commit ();

      backend2 = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (equal (backend, document.write ()));

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      document.read (backend2);
      document.revert ();

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 2LL);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 3LL);
      }) == 1);

      flip_TEST (equal (backend, document.write ()));
   }
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestBackEndIRDiff::run_014 ()
{
   BackEndIR backend;
   BackEndIR backend2;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'beir');

      Root & root = document.root <Root> ();

      C & c = dynamic_cast <C &> (*root._array_a.emplace <C> (root._array_a.begin ()));
      c._enum = E0;

      C & c2 = dynamic_cast <C &> (*root._array_a.emplace <C> (root._array_a.begin ()));
      c2._enum = E1;

      document.commit ();

      backend = document.write ();

      root._array_a.clear ();

      document.commit ();

      backend2 = document.write ();
   }

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      document.read (backend);
      document.commit ();

      flip_TEST (equal (backend, document.write ()));

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (dynamic_cast <C &> (elem)._enum == E0);
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (dynamic_cast <C &> (elem)._enum == E1);
      }) == 1);

      document.read (backend2);
      document.commit ();

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 0);
   }
}



/*
==============================================================================
Name : equal
==============================================================================
*/

bool  TestBackEndIRDiff::equal (BackEndIR & lhs, BackEndIR rhs)
{
   std::vector <uint8_t> ldata;

   {
      DataConsumerMemory consumer (ldata);

      lhs.write <BackEndBinary> (consumer);
   }

   std::vector <uint8_t> rdata;

   {
      DataConsumerMemory consumer (rdata);

      rhs.write <BackEndBinary> (consumer);
   }

   return ldata == rdata;
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

