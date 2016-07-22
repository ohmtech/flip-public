/*****************************************************************************

      TestHubLocal.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestHubLocal.h"

#include "flip/CarrierDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentServer.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/contrib/local_tcp/CarrierSocketTcp.h"
#include "flip/contrib/local_tcp/PortSocketTcp.h"
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

void  TestHubLocal::run ()
{
   Model::version ("test.hub.local");

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
   run_001b ();
   run_002 ();
   run_002b ();
   run_003 ();
   run_003b ();
   run_004 ();
   run_004b ();
   run_005 ();
   run_005b ();
   run_006 ();
   run_006b ();
   run_007 ();
   for (int i = 0 ; i < 100 ; ++i)
   {
      run_008 ();
      run_009 ();
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestHubLocal::run_000 ()
{
   PortSocketTcp port (9090);
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

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

void  TestHubLocal::run_000b ()
{
   PortSocketTcp port (9090);
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

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

void  TestHubLocal::run_001 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

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

      while (root._int != 2LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_001b
==============================================================================
*/

void  TestHubLocal::run_001b ()
{
   //#error this fails somewhere here
   // we need to have better guarantee, in particuler to busy-wait for
   // backend

   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);

   wait_connect (port, carrier, document);

   port.process ();
   carrier.process ();

   {
      document.pull ();

      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      port.process ();
      carrier.process ();
      document.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      while (root._int != 2LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestHubLocal::run_002 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
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
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      document2.pull ();

      // COV_NF_START
      while (root._int != 2LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
      // COV_NF_END
   }
}



/*
==============================================================================
Name : run_002b
==============================================================================
*/

void  TestHubLocal::run_002b ()
{
   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

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

      while (root._int != 2LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestHubLocal::run_003 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

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

      while (root._int != 2LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
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

      while (root._int != 3LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
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

      while (root._int != 0LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_003b
==============================================================================
*/

void  TestHubLocal::run_003b ()
{
   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

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

      while (root._int != 2LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }

   Transaction tx;

   {
      auto & root = document.root <Root> ();
      root._int = 3LL;
      document.commit ();
      tx = document.squash ();
      document.push ();

      flip_TEST (root._int == 3LL);

      // COV_NF_START
      while (root._int != 3LL)
      {
         port.process ();
         carrier.process ();
         document.pull ();
      }
      // COV_NF_END
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 2LL);

      document2.pull ();

      while (root._int != 3LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
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

      while (root._int != 0LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestHubLocal::run_004 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

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
      while (!fired_flag)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_004b
==============================================================================
*/

void  TestHubLocal::run_004b ()
{
   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

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
      while (!fired_flag)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestHubLocal::run_005 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

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

      while (root._int != 2LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
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

      while (root._int != 3LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 0);
   }

   server.port_factory_remove (port3);
}



/*
==============================================================================
Name : run_005b
==============================================================================
*/

void  TestHubLocal::run_005b ()
{
   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);

   document2.pull ();


   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   wait_backend (port, carrier, document);

   document.pull ();
   document2.pull ();

   {
      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      wait_pending_txs (port, carrier, document);

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      while (root._int != 2LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }

   {
      auto & root = document.root <Root> ();
      root._int = 3LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 1);

      wait_pending_txs (port, carrier, document);

      flip_TEST (root._int == 3LL);
   }

   {
      auto & root = document2.root <Root> ();
      root._int = 4LL;
      document2.commit ();
      document2.push ();

      flip_TEST (root._int == 4LL);
      flip_TEST (document.pending_txs () == 0);

      while (root._int != 3LL)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }

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

void  TestHubLocal::run_006 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

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

      while (!signaled_flag)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
   }

   server.port_factory_remove (port3);
}



/*
==============================================================================
Name : run_006b
==============================================================================
*/

void  TestHubLocal::run_006b ()
{
   PortSocketTcp port (9090);
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierSocketTcp carrier (document, 9090);

   wait_connect (port, carrier, document);

   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierDirect carrier2 (document2, port2);

   document2.pull ();


   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   port.process ();
   carrier.process ();

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

      while (!signaled_flag)
      {
         port.process ();
         carrier.process ();
         document.pull ();
      }
   }

   {
      auto & root = document2.root <Root> ();
      bool signaled_flag = false;
      auto cnx = root._signal_fire.connect ([&signaled_flag](int val){
         flip_TEST (val == 123456);
         signaled_flag = true;
      });

      while (!signaled_flag)
      {
         port.process ();
         carrier.process ();
         document2.pull ();
      }
   }

   server.port_factory_remove (port3);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestHubLocal::run_007 ()
{
   PortDirect port;
   PortSocketTcp port2 (9090);
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui2');
   CarrierSocketTcp carrier2 (document2, 9090);

   wait_connect (port2, carrier2, document2);

   document2.pull ();


   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;
   PortDirect port4;

   server.port_factory_add (port3);
   server.port_factory_add (port4);

   CarrierDirect carrier3 (hub, port3);

   Document document3 (Model::use (), 123456790ULL, 'appl', 'gui2');
   CarrierDirect carrier4 (document3, port4);

   document.pull ();
   document2.pull ();
   document3.pull ();

   {
      auto & root = document3.root <Root> ();
      root._int = 2LL;
      document3.commit ();
      document3.push ();

      flip_TEST (root._int == 2LL);

      document3.pull ();

      flip_TEST (root._int == 2LL);
   }

   {
      auto & root = document2.root <Root> ();

      flip_TEST (root._int == 0LL);

      while (root._int != 2LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }
   }

   {
      auto & root = document3.root <Root> ();
      root._int = 3LL;
      document3.commit ();
      document3.push ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document3.pending_txs () == 1);

      document3.pull ();

      flip_TEST (root._int == 3LL);
      flip_TEST (document3.pending_txs () == 0);
   }

   {
      auto & root = document2.root <Root> ();
      root._int = 4LL;
      document2.commit ();
      document2.push ();

      flip_TEST (root._int == 4LL);
      flip_TEST (document.pending_txs () == 0);

      while (root._int != 3LL)
      {
         port2.process ();
         carrier2.process ();
         document2.pull ();
      }

      flip_TEST (root._int == 3LL);
      flip_TEST (document.pending_txs () == 0);
   }

   server.port_factory_remove (port3);
   server.port_factory_remove (port4);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestHubLocal::run_008 ()
{
   PortSocketTcp port (9090);
   Hub hub (Model::use (), 123456789ULL, port);

   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierSocketTcp carrier (document, 9090);

      wait_connect (port, carrier, document);

      document.pull ();

      auto & root = document.root <Root> ();
      root._int = 2LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 2LL);

      wait_pending_txs (port, carrier, document);

      flip_TEST (root._int == 2LL);
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierSocketTcp carrier (document, 9090);

      wait_connect (port, carrier, document);

      document.pull ();

      auto & root = document.root <Root> ();

      flip_TEST (root._int == 2LL);

      root._int = 3LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 3LL);

      wait_pending_txs (port, carrier, document);

      flip_TEST (root._int == 3LL);
   }

   server.port_factory_remove (port3);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestHubLocal::run_009 ()
{
   PortSocketTcp port (9090);
   Hub hub (Model::use (), 123456789ULL, port);

   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 987654321ULL);
   PortDirect port3;

   server.port_factory_add (port3);

   CarrierDirect carrier3 (hub, port3);

   Document * document_ptr = nullptr;
   CarrierSocketTcp * carrier_ptr = nullptr;

   {
      document_ptr = new Document (Model::use (), 123456789ULL, 'appl', 'gui ');
      carrier_ptr = new CarrierSocketTcp (*document_ptr, 9090);

      wait_connect (port, *carrier_ptr, *document_ptr);

      document_ptr->pull ();

      auto & root = document_ptr->root <Root> ();
      root._int = 2LL;
      document_ptr->commit ();
      document_ptr->push ();

      flip_TEST (root._int == 2LL);

      wait_pending_txs (port, *carrier_ptr, *document_ptr);

      flip_TEST (root._int == 2LL);

      auto socket = carrier_ptr->socket ();
      Socket::release (socket);
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierSocketTcp carrier (document, 9090);

      wait_connect (port, carrier, document);

      document.pull ();

      auto & root = document.root <Root> ();

      flip_TEST (root._int == 2LL);

      root._int = 3LL;
      document.commit ();
      document.push ();

      flip_TEST (root._int == 3LL);

      wait_pending_txs (port, carrier, document);

      flip_TEST (root._int == 3LL);
   }

   server.port_factory_remove (port3);

   delete carrier_ptr;
   carrier_ptr = nullptr;

   delete document_ptr;
   document_ptr = nullptr;
}



/*
==============================================================================
Name : wait_connect
==============================================================================
*/

void  TestHubLocal::wait_connect (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document)
{
   while (port.sockets ().size () != 1)
   {
      port.process ();
      carrier.process ();
   }

   wait_backend (port, carrier, document);
}



/*
==============================================================================
Name : wait_backend
==============================================================================
*/

void  TestHubLocal::wait_backend (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document)
{
   while (document.pull_stack ().size () == 0)
   {
      port.process ();
      carrier.process ();
   }

   // don't pull
   // test will handle it, and it is part of tests
}



/*
==============================================================================
Name : wait_pending_txs
==============================================================================
*/

void  TestHubLocal::wait_pending_txs (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document)
{
   while (document.pending_txs () != 0)
   {
      port.process ();
      carrier.process ();
      document.pull ();
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

