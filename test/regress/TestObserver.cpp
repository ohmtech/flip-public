/*****************************************************************************

      TestObserver.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestObserver.h"

#include "flip/config.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
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

void  TestObserver::run ()
{
   Model::version ("test.tx");

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

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b");



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
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestObserver::run_000 ()
{
   Observer observer;
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();

   root._a._int = 4LL;
   root._a._float = 5.3;

   document.commit ();

   B & b = *root._coll_b.emplace ();
   b._int = 5LL;
   b._float = 6.789;
   b._int2 = 15LL;
   b._float2 = -46.123;
   A & a = *b._coll.emplace ();
   a._int = 12345789;
   a._float = -12345789.0;

   document.commit ();

   root._a._int = 5LL;

   document.commit ();

   root._coll_b.clear ();

   Transaction tx = document.commit ();

   bool undo_mode_flag = true;
   document.execute_backward (tx, undo_mode_flag);

   document.commit ();
}



/*
==============================================================================
Name : Observer::document_changed
==============================================================================
*/

void  TestObserver::Observer::document_changed (Root & root)
{
   if (_cnt == 0)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root.added ());
      flip_TEST (root._int.added ());
      flip_TEST (root._int == 0LL);
      flip_TEST (root._float.added ());
      flip_TEST (root._float == 0.0);
      flip_TEST (root._a.added ());
      flip_TEST (root._b.added ());
      flip_TEST (root._coll_a.added ());
      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
      flip_TEST (root._coll_b.added ());
      flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);

      flip_CHECK_THROW (root._int = 2LL);
      flip_CHECK_THROW (root._float = 2.0);
      flip_CHECK_THROW (root._coll_a.emplace ());

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      root.entity ().emplace <int> (20);
#endif
   }
   else if (_cnt == 1)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root.changed ());
      flip_TEST (!root.added ());
      flip_TEST (root._int.changed ());
      flip_TEST (!root._int.added ());
      flip_TEST (root._int == 3LL);
      flip_TEST (root._float.changed ());
      flip_TEST (!root._float.added ());
      flip_TEST (root._float == 4.3);
      flip_TEST (!root._a.added ());
      flip_TEST (!root._b.added ());
      flip_TEST (!root._coll_a.added ());
      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
      flip_TEST (!root._coll_b.added ());
      flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);

      flip_CHECK_THROW (root._int = 2LL);
      flip_CHECK_THROW (root._float = 2.0);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 20);
      root.entity ().use <int> () = 24;

      root._a.entity ().emplace <double> (1.2);
#endif
   }
   else if (_cnt == 2)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root.changed ());
      flip_TEST (!root.added ());
      flip_TEST (root._a._int.changed ());
      flip_TEST (!root._a._int.added ());
      flip_TEST (root._a._int == 4LL);
      flip_TEST (root._a._float.changed ());
      flip_TEST (!root._a._float.added ());
      flip_TEST (root._a._float == 5.3);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 24);
      flip_TEST (root._a.entity ().use <double> () == 1.2);
#endif
   }
   else if (_cnt == 3)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root._coll_b.changed ());
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.added ();}) == 1);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.removed ();}) == 0);
      B & b = *root._coll_b.begin ();
      flip_TEST (b._int == 5LL);
      flip_TEST (b._float == 6.789);
      flip_TEST (b._int2 == 15LL);
      flip_TEST (b._float2 == -46.123);
      flip_TEST (b._coll.changed ());
      flip_TEST (b._coll.count_if ([](A & elem){return elem.added ();}) == 1);
      flip_TEST (b._coll.count_if ([](A & elem){return elem.removed ();}) == 0);
      A & a = *b._coll.begin ();
      flip_TEST (a._int == 12345789LL);
      flip_TEST (a._float == -12345789.0);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 24);
      flip_TEST (root._a.entity ().use <double> () == 1.2);
#endif
   }
   else if (_cnt == 4)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root._a._int.changed ());
      flip_TEST (root._a._int == 5LL);

      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.added ();}) == 0);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.removed ();}) == 0);
      B & b = *root._coll_b.begin ();
      flip_TEST (b._coll.count_if ([](A & elem){return elem.added ();}) == 0);
      flip_TEST (b._coll.count_if ([](A & elem){return elem.removed ();}) == 0);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 24);
      flip_TEST (root._a.entity ().use <double> () == 1.2);
#endif
   }
   else if (_cnt == 5)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.added ();}) == 0);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.removed ();}) == 1);
      B & b = *root._coll_b.begin ();
      flip_TEST (b._coll.count_if ([](A & elem){return elem.added ();}) == 0);
      flip_TEST (b._coll.count_if ([](A & elem){return elem.removed ();}) == 1);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 24);
      flip_TEST (root._a.entity ().use <double> () == 1.2);
#endif
   }
   else if (_cnt == 6)
   {
      flip_TEST (root.document ().controller () == Controller::UNDO);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.added ();}) == 1);
      flip_TEST (root._coll_b.count_if ([](B & elem){return elem.removed ();}) == 0);
      B & b = *root._coll_b.begin ();
      flip_TEST (b._coll.count_if ([](A & elem){return elem.added ();}) == 1);
      flip_TEST (b._coll.count_if ([](A & elem){return elem.removed ();}) == 0);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      flip_TEST (root.entity ().use <int> () == 24);
      flip_TEST (root._a.entity ().use <double> () == 1.2);
#endif
   }
   else if (_cnt == 7)
   {
      flip_TEST (root.document ().controller () == Controller::SELF);
      flip_TEST (root.removed ());

      flip_CHECK_THROW (root._int = 2LL);

#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE)
      root.entity ().erase <int> ();
      root._a.entity ().erase <double> ();
#endif
   }
   else
   {
      flip_TEST_FAILED;   // COV_NF_LINE
   }

   ++_cnt;
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestObserver::run_001 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().commit ());
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestObserver::run_002 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().revert ());
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestObserver::run_003 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().set_label ("some label"));
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestObserver::run_004 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      Transaction tx;
      flip_CHECK_THROW (root.document ().execute_forward (tx));
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestObserver::run_005 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().squash ());
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestObserver::run_006 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().push ());
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestObserver::run_007 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      flip_CHECK_THROW (root.document ().pull ());
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestObserver::run_008 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      if (!root.removed ())
      {
         root.document ().write ();
      }
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestObserver::run_009 ()
{
   DocumentObserverLambda <Root> observer ([](Root & root){
      BackEndIR backend;
      flip_CHECK_THROW (root.document ().read (backend));
   });
   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 3LL;
   root._float = 4.3;

   document.commit ();
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

