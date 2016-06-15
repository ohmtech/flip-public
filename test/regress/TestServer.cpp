/*****************************************************************************

      TestServer.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestServer.h"

#include "flip/BackEndIR.h"
#include "flip/CarrierDirect.h"
#include "flip/PortDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentObserverVoid.h"
#include "flip/DocumentValidatorVoid.h"
#include "flip/detail/fnc.h"
#include "TestDef.h"

#include <memory>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestServer::run ()
{
   Model::version ("test.server");

   Model::declare <Client> ()
      .name ("Client")
      .member <Int, &Client::_user_id> ("user_id")
      .member <Float, &Client::_scroll> ("scroll");

   Model::declare <Root> ()
      .name ("Root")
      .member <Collection <Client>, &Root::_clients> ("clients")
      .member <Float, &Root::_tempo> ("tempo");


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



/*
==============================================================================
Name : Client::ctor
==============================================================================
*/

TestServer::Client::Client (uint64_t user_id)
:  _user_id (reinterpret_cast <int64_t &> (user_id))
,  _signal_test (Signal_TEST, *this)
{

}



/*
==============================================================================
Name : Client::user
==============================================================================
*/

uint64_t TestServer::Client::user () const
{
   int64_t tmp = _user_id;

   return reinterpret_cast <uint64_t &> (tmp);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init
==============================================================================
*/

void  TestServer::init (DocumentServer & server, BackEndIR & backend)
{
   server.listen_connecting ([&server](PortBase & port){
      Root & root = server.root <Root> ();

      if (root._clients.count_if ([&port](Client & client){
         return client.user () == port.user ();
      }) == 0)
      {
         root._clients.emplace (port.user ());
      }

      Transaction tx = server.commit ();
      server.send_tx_if (tx, [](PortBase &){return true;});
   });

   if (backend.empty ())
   {
      // initialize default

      Root & root = server.root <Root> ();
      root._tempo = 120.0;

      server.commit ();
   }
   else
   {
      server.read (backend);

      // convert

      // tweak
   }
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestServer::run_000 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;
   init (server, backend);

   //

   bool connected_flag = false;
   server.listen_connected ([&connected_flag](PortBase &){
      connected_flag = true;
   });

   bool disconnected_flag = false;
   server.listen_disconnected ([&disconnected_flag](PortBase &){
      disconnected_flag = true;
   });

   //

   PortDirect port_01;
   flip_TEST (!connected_flag);
   server.port_factory_add (port_01);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);
   flip_TEST (connected_flag);

   document_01.pull ();
   Root & root = document_01.root <Root> ();
   flip_TEST (root._tempo == 120.0);

   flip_TEST (!disconnected_flag);
   server.port_factory_remove (port_01);
   flip_TEST (disconnected_flag);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestServer::run_001 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;
   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root = document_01.root <Root> ();
   flip_TEST (root._tempo == 120.0);

   //

   root._tempo = 130.0;
   document_01.commit ();
   document_01.push ();

   //

   flip_TEST (document_01.pending_txs () == 1);
   document_01.pull ();
   flip_TEST (document_01.pending_txs () == 0);
   flip_TEST (root._tempo == 130.0);

   server.port_factory_remove (port_01);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestServer::run_002 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;
   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   PortDirect port_02;
   server.port_factory_add (port_02);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root_01 = document_01.root <Root> ();
   flip_TEST (root_01._tempo == 120.0);

   Document document_02 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_02 (document_02, port_02);

   document_02.pull ();
   Root & root_02 = document_02.root <Root> ();
   flip_TEST (root_02._tempo == 120.0);

   //

   root_01._tempo = 130.0;
   document_01.commit ();
   document_01.push ();

   //

   flip_TEST (document_01.pending_txs () == 1);
   document_01.pull ();
   flip_TEST (document_01.pending_txs () == 0);
   flip_TEST (root_01._tempo == 130.0);

   //

   flip_TEST (document_02.pending_txs () == 0);
   document_02.pull ();
   flip_TEST (document_02.pending_txs () == 0);
   flip_TEST (root_02._tempo == 130.0);

   server.port_factory_remove (port_01);
   server.port_factory_remove (port_02);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestServer::run_003 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;
   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   PortDirect port_02;
   server.port_factory_add (port_02);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root_01 = document_01.root <Root> ();
   flip_TEST (root_01._tempo == 120.0);

   Document document_02 (Model::use (), 987654321ULL, 'appl', 'gui ');
   CarrierDirect carrier_02 (document_02, port_02);

   document_02.pull ();
   Root & root_02 = document_02.root <Root> ();
   flip_TEST (root_02._tempo == 120.0);

   //

   root_01._tempo = 130.0;
   document_01.commit ();
   document_01.push ();

   root_01._tempo = 140.0;
   document_01.commit ();
   document_01.push ();

   //

   document_01.pull ();
   flip_TEST (root_01._tempo == 140.0);

   //

   document_02.pull ();
   flip_TEST (root_02._tempo == 140.0);

   server.port_factory_remove (port_01);
   server.port_factory_remove (port_02);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestServer::run_004 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;

   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   PortDirect port_02;
   server.port_factory_add (port_02);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root_01 = document_01.root <Root> ();
   flip_TEST (root_01._tempo == 120.0);

   Document document_02 (Model::use (), 987654321ULL, 'appl', 'gui ');
   CarrierDirect carrier_02 (document_02, port_02);

   document_02.pull ();
   Root & root_02 = document_02.root <Root> ();
   flip_TEST (root_02._tempo == 120.0);

   //

   root_01._tempo = 130.0;
   document_01.commit ();
   document_01.push ();

   root_02._tempo = 140.0;
   document_02.commit ();
   document_02.push ();

   //

   document_01.pull ();
   flip_TEST (root_01._tempo == 130.0);

   //

   document_02.pull ();
   flip_TEST (root_02._tempo == 130.0);

   server.port_factory_remove (port_01);
   server.port_factory_remove (port_02);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestServer::run_005 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;

   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   PortDirect port_02;
   server.port_factory_add (port_02);

   Document document_01 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root_01 = document_01.root <Root> ();
   flip_TEST (root_01._tempo == 120.0);

   Document document_02 (Model::use (), 987654321ULL, 'appl', 'gui ');
   CarrierDirect carrier_02 (document_02, port_02);

   document_02.pull ();
   Root & root_02 = document_02.root <Root> ();
   flip_TEST (root_02._tempo == 120.0);

   //

   root_01._tempo = 130.0;
   document_01.commit ();
   document_01.push ();

   root_02._tempo = 140.0;
   document_02.commit ();
   document_02.push ();

   //

   document_01.pull ();
   flip_TEST (root_01._tempo == 130.0);

   //

   document_02.pull ();
   flip_TEST (root_02._tempo == 130.0);

   //

   root_02._tempo = 140.0;
   document_02.commit ();
   document_02.push ();

   root_01._tempo = 120.0;
   document_01.commit ();
   document_01.push ();

   //

   document_01.pull ();
   flip_TEST (root_01._tempo == 140.0);

   //

   document_02.pull ();
   flip_TEST (root_02._tempo == 140.0);

   server.port_factory_remove (port_01);
   server.port_factory_remove (port_02);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestServer::run_006 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123ULL, 'appl', 'gui ');

      Root & root = document.root <Root> ();
      root._tempo = 140.0;
      root._clients.emplace (123ULL);

      backend = document.write ();
   }

   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   Document document_01 (Model::use (), 123456789UL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root = document_01.root <Root> ();
   flip_TEST (root._tempo == 140.0);

   server.port_factory_remove (port_01);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestServer::run_007 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   BackEndIR backend;
   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   Document document_01 (Model::use (), 123456789UL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   document_01.pull ();
   Root & root = document_01.root <Root> ();
   flip_TEST (root._tempo == 120.0);

   flip_TEST (root._clients.count_if ([](Client &){return true;}) == 1);
   root._clients.begin ()->_signal_test ();

   server.port_factory_remove (port_01);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestServer::run_008 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);
   Root & root_server = server.root <Root> ();

   bool server_signal_flag = false;

   SignalConnection cnx_server = root_server._signal_from_client.connect ([&server_signal_flag, &root_server, &server](){
      server_signal_flag = true;

      SignalData data = root_server._signal_to_client.make ();

      server.reply_signal (data);

      // or broadcast
      // server.send_signal_if (data, [](){return true;});
   });

   BackEndIR backend;
   init (server, backend);

   //

   PortDirect port_01;
   server.port_factory_add (port_01);

   Document document_01 (Model::use (), 123456789UL, 'appl', 'gui ');
   CarrierDirect carrier_01 (document_01, port_01);

   //carrier_01.enable_signal_passthrough <Root> (Root::Signal_FROM_CLIENT);

   document_01.pull ();
   Root & root = document_01.root <Root> ();

   bool client_signal_flag = false;

   SignalConnection cnx = root._signal_to_client.connect ([&client_signal_flag](){
      client_signal_flag = true;
   });

   root._signal_from_client ();

   flip_TEST (server_signal_flag);
   flip_TEST (!client_signal_flag);

   document_01.pull ();

   flip_TEST (client_signal_flag);

   server.port_factory_remove (port_01);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestServer::run_009 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._tempo = 120.0;
   document.commit ();
   document.push ();

   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 123456789ULL);

   PortDirect port;
   server.port_factory_add (port);

   CarrierDirect carrier (document, port);

   root._tempo = 130.0;
   document.commit ();
   document.push ();

   document.pull ();

   flip_TEST (root._tempo == 0.0);

   server.port_factory_remove (port);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

