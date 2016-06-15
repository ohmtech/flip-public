/*****************************************************************************

      TestRepresentative.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestRepresentative.h"

#include "flip/Ref.h"
#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
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

void  TestRepresentative::run ()
{
   Model::version ("test.representative");

   Model::declare <ABase> ()
      .name ("ABase")
      .member <Int, &ABase::_int_base> ("int_base")
      .member <Float, &ABase::_float_base> ("float_base");

   Model::declare <A> ()
      .name ("A")
      .inherit <ABase> ()
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <B> ()
      .name ("B")
      .member <Int, &B::_int> ("int")
      .member <Float, &B::_float> ("float")
      .member <Collection <A>, &B::_coll> ("coll")
      .member <A, &B::_obj> ("obj");

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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestRepresentative::run_000 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_abase.from (a_base));

   vint = 3;

   flip_TEST (a_base._int_base == 3LL);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestRepresentative::run_001 ()
{
   Representative rep_abase;
   rep_abase.set <Float, ABase, &ABase::_float_base> ();

   ABase a_base;
   flip_TEST (a_base._float_base == 0.0);
   Float & vfloat = dynamic_cast <Float &> (rep_abase.from (a_base));

   vfloat = 1.0 / 7.0;

   flip_TEST (a_base._float_base == 1.0 / 7.0);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestRepresentative::run_002 ()
{
   Representative rep_a;
   rep_a.set <Int, A, &A::_int> ();

   A a;
   flip_TEST (a._int == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_a.from (a));

   vint = 3;

   flip_TEST (a._int == 3LL);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestRepresentative::run_003 ()
{
   Representative rep_a;
   rep_a.set <Float, A, &A::_float> ();

   A a;
   flip_TEST (a._float == 0.0);
   Float & vfloat = dynamic_cast <Float &> (rep_a.from (a));

   vfloat = 1.0 / 11.0;

   flip_TEST (a._float == 1.0 / 11.0);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestRepresentative::run_004 ()
{
   Representative rep_a;
   rep_a.set <Int, ABase, &ABase::_int_base> ();

   A a;
   flip_TEST (a._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_a.from (a));

   vint = 3;

   flip_TEST (a._int_base == 3LL);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestRepresentative::run_005 ()
{
   Representative rep_b;
   rep_b.set <Int, A, &A::_int> ();

   B b;
   flip_CHECK_THROW (rep_b.from (b));
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestRepresentative::run_006 ()
{
   Representative rep_b;
   rep_b.set <Collection <A>, B, &B::_coll> ();

   B b;
   flip_TEST (b._coll.count_if ([] (A &) {return true;}) == 0);

   Collection <A> & coll = dynamic_cast <Collection <A> &> (rep_b.from (b));

   coll.emplace ();
   coll.emplace ();
   coll.emplace ();

   flip_TEST (b._coll.count_if ([] (A &) {return true;}) == 3);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestRepresentative::run_007 ()
{
   Representative rep_b;
   rep_b.set <A, B, &B::_obj> ();

   B b;
   flip_TEST (b._obj._int == 0LL);

   A & a = dynamic_cast <A &> (rep_b.from (b));

   a._int = 11;

   flip_TEST (b._obj._int == 11LL);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestRepresentative::run_008 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   const Int & vint = dynamic_cast <const Int &> (rep_abase.cfrom (a_base));

   flip_TEST (vint == 0LL);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestRepresentative::run_009 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   Representative rep_abase2 = rep_abase;

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_abase2.from (a_base));

   flip_TEST (vint == 0LL);
   vint = 2LL;

   flip_TEST (a_base._int_base == 2LL);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestRepresentative::run_010 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   Representative rep_abase2;
   rep_abase2 = rep_abase;

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_abase2.from (a_base));

   flip_TEST (vint == 0LL);
   vint = 2LL;

   flip_TEST (a_base._int_base == 2LL);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestRepresentative::run_011 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   Representative rep_abase2 = std::move (rep_abase);

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_abase2.from (a_base));

   flip_TEST (vint == 0LL);
   vint = 2LL;

   flip_TEST (a_base._int_base == 2LL);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestRepresentative::run_012 ()
{
   Representative rep_abase;
   rep_abase.set <Int, ABase, &ABase::_int_base> ();

   Representative rep_abase2;
   rep_abase2 = std::move (rep_abase);

   ABase a_base;
   flip_TEST (a_base._int_base == 0LL);
   Int & vint = dynamic_cast <Int &> (rep_abase2.from (a_base));

   flip_TEST (vint == 0LL);
   vint = 2LL;

   flip_TEST (a_base._int_base == 2LL);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

