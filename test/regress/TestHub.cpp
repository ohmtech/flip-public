/*****************************************************************************

      TestHub.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestHub.h"

#include "flip/CarrierDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentServer.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/detail/def.h"
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

void  TestHub::run ()
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
   run_000b ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestHub::run_000 ()
{
   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   document.pull ();

   auto & root = document.root <Root> ();
   root._int = 2LL;
   document.commit ();

   flip_TEST (root._int == 2LL);

   document.pull ();

   flip_TEST (root._int == 2LL);
}



/*
==============================================================================
Name : run_000b
==============================================================================
*/

void  TestHub::run_000b ()
{
   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   document.pull ();

   auto & root = document.root <Root> ();
   root._int = 2LL;
   document.commit ();

   flip_TEST (root._int == 2LL);

   document.push ();

   flip_TEST (root._int == 2LL);

   document.pull ();

   flip_TEST (root._int == 2LL);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestHub::run_001 ()
{
   PortDirect port;
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);

   {
      document.pull ();

      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      document.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      document2.pull ();

      flip_TEST (root._int == 2LL);
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestHub::run_002 ()
{
   PortDirect port;
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   {
      document.pull ();

      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      document.pull ();

      flip_TEST (root._int == 2LL);
   }

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      document2.pull ();

      flip_TEST (root._int == 2LL);
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestHub::run_003 ()
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
      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();

      flip_TEST (root._int == 2LL);

      document.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      document2.pull ();

      flip_TEST (root._int == 2LL);
   }

   Transaction tx;

   {
      auto & root = document.root <Root> ();
      root._int = 3LL;
      document.commit ();
      tx = document.squash ();
      document.push ();

      flip_TEST (root._int == 3LL);

      document.pull ();

      flip_TEST (root._int == 3LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 2LL);

      document2.pull ();

      flip_TEST (root._int == 3LL);
   }

   {
      bool ok_flag = document.execute_backward (tx);
      flip_TEST (ok_flag);

      document.commit ();

      auto & root = document.root <Root> ();

      flip_TEST (root._int == 0LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 3LL);

      document2.pull ();

      flip_TEST (root._int == 0LL);
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestHub::run_004 ()
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

   bool fired_flag = false;

   SignalConnection cnx = document2.root <Root> ()._signal_fire.connect ([&fired_flag](int val){
      flip_TEST (val == 7);
      fired_flag = true;
   });

   {
      auto & root = document.root <Root> ();
      root._signal_fire (7);
   }

   {
      document2.pull ();

      flip_TEST (fired_flag);
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestHub::run_005 ()
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


   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   document.pull ();
   document2.pull ();

   {
      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      document.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      document2.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document.root <Root> ();
      root._int = 3LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 1);

      document.pull ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 0);
   }

   {
      auto & root = document2.root <Root> ();
      root._int = 4LL;
      document2.commit ();
      document2.push ();

      flip_TEST (root._int == 4LL);
      flip_TEST (document.pending_txs () == 0);

      document2.pull ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 0);
   }

   server.port_factory_remove (port3);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestHub::run_006 ()
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


   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   document.pull ();
   document2.pull ();

   {
      auto & root = server.root <Root> ();
      SignalData data = root._signal_fire.make (123456);

      server.send_signal_if (data, [](PortBase &){return true;});
   }

   {
      auto & root = document.root <Root> ();
      bool signaled_flag = false;
      auto cnx = root._signal_fire.connect ([&signaled_flag](int val){
         flip_TEST (val == 123456);
         signaled_flag = true;
      });

      document.pull ();
      flip_TEST (signaled_flag);
   }

   {
      auto & root = document2.root <Root> ();
      bool signaled_flag = false;
      auto cnx = root._signal_fire.connect ([&signaled_flag](int val){
         flip_TEST (val == 123456);
         signaled_flag = true;
      });

      document2.pull ();
      flip_TEST (signaled_flag);
   }

   server.port_factory_remove (port3);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

