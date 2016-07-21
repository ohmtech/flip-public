/*****************************************************************************

      TestTransportSocket.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestTransportSocket.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentServer.h"
#include "flip/Hub.h"
#include "flip/contrib/transport_tcp/CarrierTransportSocketTcp.h"
#include "flip/contrib/transport_tcp/PortTransportServerTcp.h"
#include "flip/contrib/transport_tcp/PortTransportSocketTcp.h"
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

void  TestTransportSocket::run ()
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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : wait_transfer_backend
==============================================================================
*/

void  TestTransportSocket::wait_transfer_backend (CarrierTransportSocketTcp & carrier, PortTransportServerTcp & server)
{
   flip_TEST (carrier.is_idle ());

   bool loop_flag = true;

   carrier.listen_transfer_backend ([&loop_flag](size_t cur, size_t total){
      loop_flag = cur != total;
   });

   while (loop_flag)
   {
      server.process ();
      carrier.process ();
   }

   flip_TEST (carrier.is_connected ());
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestTransportSocket::run_000 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document_server (Model::use (), validator, 1234567890123ULL);
   PortTransportServerTcp port_tcp (document_server, 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 1234567890123ULL, "127.0.0.1", 9090);
   flip_TEST (carrier.socket () == Socket::invalid_id);

   CarrierBase::Transition transition = CarrierBase::Transition::Disconnected;

   carrier.listen_state_transition ([&transition](CarrierBase::Transition sub_transition, int err){
      if (transition == CarrierBase::Transition::Disconnected)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Connecting);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
      else if (transition == CarrierBase::Transition::Connecting)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Connected);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
      else if (transition == CarrierBase::Transition::Connected)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Disconnected);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
   });

   flip_TEST (transition == CarrierBase::Transition::Disconnected);

   wait_transfer_backend (carrier, port_tcp);

   flip_TEST (transition == CarrierBase::Transition::Connected);

   flip_TEST (carrier.socket () != Socket::invalid_id);

   document.pull ();

   auto & root = document.root <Root> ();
   root._int = 2LL;
   document.commit ();
   document.push ();
   port_tcp.process ();
   carrier.process ();
   port_tcp.process ();

   flip_TEST (root._int == 2LL);

   carrier.process ();
   document.pull ();

   flip_TEST (root._int == 2LL);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestTransportSocket::run_001 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document_server (Model::use (), validator, 1234567890123ULL);
   PortTransportServerTcp port_tcp (document_server, 9090);

   Document document1 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier1 (document1, 1234567890123ULL, "127.0.0.1", 9090);
   flip_TEST (carrier1.socket () == Socket::invalid_id);
   wait_transfer_backend (carrier1, port_tcp);
   flip_TEST (carrier1.socket () != Socket::invalid_id);
   document1.pull ();

   Document document2 (Model::use (), 123456790ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier2 (document2, 1234567890123ULL, "127.0.0.1", 9090);
   flip_TEST (carrier2.socket () == Socket::invalid_id);
   wait_transfer_backend (carrier2, port_tcp);
   flip_TEST (carrier2.socket () != Socket::invalid_id);
   document2.pull ();

   auto & root1 = document1.root <Root> ();
   root1._int = 2LL;
   document1.commit ();
   document1.push ();

   auto & root2 = document2.root <Root> ();
   root2._int = 3LL;
   document2.commit ();
   document2.push ();

   port_tcp.process ();
   carrier1.process ();
   port_tcp.process ();

   port_tcp.process ();
   carrier2.process ();
   port_tcp.process ();

   flip_TEST (root1._int == 2LL);
   flip_TEST (root2._int == 3LL);

   carrier1.process ();
   document1.pull ();
   carrier2.process ();
   document2.pull ();

   flip_TEST (root1._int == 2LL);
   flip_TEST (root1._int == 2LL);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestTransportSocket::run_002 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document_server (Model::use (), validator, 1234567890123ULL);
   PortTransportServerTcp port_tcp (document_server, 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 1234567890123ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, port_tcp);

   document.pull ();

   auto & root_server = document_server.root <Root> ();
   root_server._int = 2LL;
   auto tx = document_server.commit ();
   document_server.push ();

   document_server.send_tx_if (tx, [](PortBase &){return true;});

   size_t transfer_cnt = 0;

   carrier.listen_transfer_transaction ([&transfer_cnt](size_t cur, size_t total){
      flip_TEST (total > 0);
      if (cur == total)
      {
         transfer_cnt = total;
      }
   });

   port_tcp.process ();
   carrier.process ();
   port_tcp.process ();

   auto & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   while (transfer_cnt == 0)
   {
      // COV_NF_START
      port_tcp.process ();
      carrier.process ();
      document.pull ();
      // COV_NF_END
   }

   document.pull ();

   flip_TEST (root._int == 2LL);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestTransportSocket::run_003 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document_server (Model::use (), validator, 1234567890123ULL);
   PortTransportServerTcp port_tcp (document_server, 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 1234567890123ULL, "127.0.0.1", 9090);

   auto & root = document.root <Root> ();

   bool signalled_flag = false;

   auto cnx = root._server_to_client.connect ([&signalled_flag](int val){
      flip_TEST (val == 123456);
      signalled_flag = true;
   });

   wait_transfer_backend (carrier, port_tcp);

   document.pull ();

   auto & root_server = document_server.root <Root> ();
   SignalData data = root_server._server_to_client.make (123456);

   document_server.send_signal_if (data, [](PortBase &){return true;});

   size_t transfer_cnt = 0;

   carrier.listen_transfer_signal ([&transfer_cnt](size_t cur, size_t total){
      flip_TEST (total > 0);
      if (cur == total)
      {
         transfer_cnt = total;
      }
   });

   while (transfer_cnt == 0)
   {
      // COV_NF_START
      port_tcp.process ();
      carrier.process ();
      document.pull ();
      // COV_NF_END
   }

   document.pull ();

   flip_TEST (signalled_flag);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestTransportSocket::run_004 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document_server (Model::use (), validator, 1234567890123ULL);
   PortTransportServerTcp port_tcp (document_server, 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 1234567890123ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, port_tcp);

   bool signalled_flag = false;

   CarrierBase::Transition transition = CarrierBase::Transition::Disconnected;

   carrier.listen_state_transition ([&signalled_flag, &transition](CarrierBase::Transition sub_transition, int err){
      if (transition == CarrierBase::Transition::Disconnected)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Connecting);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
      else if (transition == CarrierBase::Transition::Connecting)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Connected);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
      else if (transition == CarrierBase::Transition::Connected)
      {
         flip_TEST (sub_transition == CarrierBase::Transition::Disconnected);
         flip_TEST (err == 0);
         transition = sub_transition;
      }
      signalled_flag = true;
   });

   document.pull ();

   flip_TEST (signalled_flag);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

