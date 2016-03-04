/*****************************************************************************

      TestTransportBase.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestTransportBase.h"

#include "flip/Document.h"
#include "flip/Transaction.h"
#include "flip/detail/StreamBinOut.h"

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

void  TestTransportBase::run ()
{
   Model::version ("test.transport");

   Model::declare <Root> ()
      .name ("Root");

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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Carrier::ctor
==============================================================================
*/

TestTransportBase::Carrier::Carrier (CarrierListener & listener)
:  CarrierTransportBase (listener)
{
}



/*
==============================================================================
Name : Carrier::dtor
==============================================================================
*/

TestTransportBase::Carrier::~Carrier ()
{
   notify_disconnected (0);
}



/*
==============================================================================
Name : Carrier::bind
==============================================================================
*/

void  TestTransportBase::Carrier::bind (Port & port)
{
   _port_ptr = &port;

   notify_connecting ();
   notify_connected ();
}



/*
==============================================================================
Name : Carrier::receive_from_port
==============================================================================
*/

void  TestTransportBase::Carrier::receive_from_port (const std::vector <uint8_t> & data)
{
   flip_TEST (data.size () > 0);

   for (size_t i = 0 ; i < data.size () - 1 ; ++i)
   {
      peek (data.data (), i, data.size ());
   }

   recv (data.data (), data.size ());
}



/*
==============================================================================
Name : Carrier::send_garbage_msg
==============================================================================
*/

void  TestTransportBase::Carrier::send_garbage_msg ()
{
   flip_TEST (_port_ptr != nullptr);

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);

   sbo << flip_CC4 ('f', 'a', 'k', 'e');
   sbo << uint8_t (1);

   send (data);
}



/*
==============================================================================
Name : Carrier::send
==============================================================================
*/

void  TestTransportBase::Carrier::send (const std::vector <uint8_t> & data)
{
   flip_TEST (_port_ptr != nullptr);

   _port_ptr->receive_from_carrier (data);
}



/*
==============================================================================
Name : Listener::carrier_receive_beir
==============================================================================
*/

void  TestTransportBase::Listener::carrier_receive_beir (const BackEndIR & backend)
{
   _type = Type::CarrierBeir;
   _port_ptr = nullptr;
   _backend = backend;
}



/*
==============================================================================
Name : Listener::carrier_receive_tx_ext
==============================================================================
*/

void  TestTransportBase::Listener::carrier_receive_tx_ext (const Transaction & tx)
{
   _type = Type::CarrierExt;
   _port_ptr = nullptr;
   _tx = tx;
}



/*
==============================================================================
Name : Listener::carrier_receive_tx_ack
==============================================================================
*/

void  TestTransportBase::Listener::carrier_receive_tx_ack (const TxId & tx_id)
{
   _type = Type::CarrierAck;
   _port_ptr = nullptr;
   _id = tx_id;
}



/*
==============================================================================
Name : Listener::carrier_receive_tx_deny
==============================================================================
*/

void  TestTransportBase::Listener::carrier_receive_tx_deny (const TxId & tx_id)
{
   _type = Type::CarrierDeny;
   _port_ptr = nullptr;
   _id = tx_id;
}



/*
==============================================================================
Name : Listener::carrier_receive_signal
==============================================================================
*/

void  TestTransportBase::Listener::carrier_receive_signal (const SignalData & data)
{
   _type = Type::CarrierSignal;
   _port_ptr = nullptr;
   _signal = data;
}



/*
==============================================================================
Name : Listener::port_greet
==============================================================================
*/

void  TestTransportBase::Listener::port_greet (PortBase & from)
{
   _type = Type::PortGreet;
   _port_ptr = &from;
}



/*
==============================================================================
Name : Listener::port_push
==============================================================================
*/

void  TestTransportBase::Listener::port_push (PortBase & from, const Transaction & tx)
{
   _type = Type::PortPush;
   _port_ptr = &from;
   _tx = tx;
}



/*
==============================================================================
Name : Listener::port_signal
==============================================================================
*/

void  TestTransportBase::Listener::port_signal (PortBase & from, const SignalData & data)
{
   _type = Type::PortSignal;
   _port_ptr = &from;
   _signal = data;
}



/*
==============================================================================
Name : Port::ctor
==============================================================================
*/

TestTransportBase::Port::Port (Listener & listener)
:  _listener (listener)
{
   impl_bind (_listener);
}



/*
==============================================================================
Name : Port::dtor
==============================================================================
*/

TestTransportBase::Port::~Port ()
{
   impl_unbind (_listener);
}



/*
==============================================================================
Name : Port::bind
==============================================================================
*/

void  TestTransportBase::Port::bind (Carrier & carrier)
{
   _carrier_ptr = &carrier;
}



/*
==============================================================================
Name : Port::receive_from_carrier
==============================================================================
*/

void  TestTransportBase::Port::receive_from_carrier (const std::vector <uint8_t> & data)
{
   flip_TEST (data.size () > 0);

   receive (data.data (), data.size ());
}



/*
==============================================================================
Name : Port::send
==============================================================================
*/

void  TestTransportBase::Port::send (const std::vector <uint8_t> & data)
{
   flip_TEST (_carrier_ptr != nullptr);

   _carrier_ptr->receive_from_port (data);
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestTransportBase::run_000 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   flip_TEST (carrier.is_idle ());

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   carrier.commit (tx);

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
   flip_TEST (listener._tx.empty ());
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestTransportBase::run_001 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   carrier.push (tx);

   flip_TEST (listener._type == Listener::Type::PortPush);
   flip_TEST (listener._port_ptr == &port);
   flip_TEST (listener._tx.empty ());
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestTransportBase::run_002 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   tx.push_bool_set (Ref::make (1, 2, 3), 0, false, true);
   tx.push_float64_set (Ref::make (45, 67, 89), 1, 2.3, 3.4);
   carrier.push (tx);

   flip_TEST (listener._type == Listener::Type::PortPush);
   flip_TEST (listener._port_ptr == &port);
   flip_TEST (listener._tx.equal (tx));
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestTransportBase::run_003 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   port.receive_transaction (tx);

   flip_TEST (listener._type == Listener::Type::CarrierExt);
   flip_TEST (listener._port_ptr == nullptr);
   flip_TEST (listener._tx.equal (tx));
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestTransportBase::run_004 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   tx.push_bool_set (Ref::make (1, 2, 3), 0, false, true);
   tx.push_float64_set (Ref::make (45, 67, 89), 1, 2.3, 3.4);
   port.receive_transaction (tx);

   flip_TEST (listener._type == Listener::Type::CarrierExt);
   flip_TEST (listener._port_ptr == nullptr);
   flip_TEST (listener._tx.equal (tx));
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestTransportBase::run_005 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Transaction tx;
   TxIdRange range (1, 2, 3, 4);
   tx.push_bool_set (Ref::make (1, 2, 3), 0, false, true);
   tx.push_float64_set (Ref::make (45, 67, 89), 1, 2.3, 3.4);
   carrier.squash (range, tx);

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestTransportBase::run_006 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   SignalData signal_data;
   carrier.signal (signal_data);

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestTransportBase::run_007 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   carrier.enable_signal_passthrough <Root> (123);

   SignalData signal_data;
   signal_data.type_id = Class <Root>::use ().type_id (Model::use ());
   signal_data.ref = Ref::root;
   signal_data.type = 123;
   carrier.signal (signal_data);

   flip_TEST (listener._type == Listener::Type::PortSignal);
   flip_TEST (listener._port_ptr == &port);
   flip_TEST (listener._signal.type_id == Class <Root>::use ().type_id (Model::use ()));
   flip_TEST (listener._signal.ref == Ref::root);
   flip_TEST (listener._signal.type == 123);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestTransportBase::run_008 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   carrier.enable_signal_passthrough <Root> (123);

   SignalData signal_data;
   signal_data.type_id = Class <Root>::use ().type_id (Model::use ()) + 1;
   signal_data.ref = Ref::root;
   signal_data.type = 123;
   carrier.signal (signal_data);

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestTransportBase::run_009 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   carrier.enable_signal_passthrough <Root> (123);

   SignalData signal_data;
   signal_data.type_id = Class <Root>::use ().type_id (Model::use ());
   signal_data.ref = Ref::root;
   signal_data.type = 124;
   carrier.signal (signal_data);

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestTransportBase::run_010 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   SignalData signal_data;
   port.receive_signal (signal_data);

   flip_TEST (listener._type == Listener::Type::CarrierSignal);
   flip_TEST (listener._port_ptr == nullptr);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestTransportBase::run_011 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   flip_CHECK_THROW (carrier.send_garbage_msg ());

   flip_TEST (listener._type == Listener::Type::PortGreet);
   flip_TEST (listener._port_ptr == &port);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestTransportBase::run_012 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   Document document (Model::use (), 123456789ULL, 'flip', 'test');
   BackEndIR backend = document.write ();

   port.receive_backend (backend);

   flip_TEST (listener._type == Listener::Type::CarrierBeir);
   flip_TEST (listener._port_ptr == nullptr);
   flip_TEST (listener._backend.equal (backend));
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestTransportBase::run_013 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   TxId tx_id (123456789ULL, 98765498765464ULL, 6514684160510ULL);

   port.receive_ack (tx_id);

   flip_TEST (listener._type == Listener::Type::CarrierAck);
   flip_TEST (listener._port_ptr == nullptr);
   flip_TEST (listener._id == tx_id);
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestTransportBase::run_014 ()
{
   Listener listener (Model::use ());
   Carrier carrier (listener);
   Port port (listener);

   carrier.bind (port);
   port.bind (carrier);

   TxId tx_id (123456789ULL, 98765498765464ULL, 6514684160510ULL);

   port.receive_deny (tx_id);

   flip_TEST (listener._type == Listener::Type::CarrierDeny);
   flip_TEST (listener._port_ptr == nullptr);
   flip_TEST (listener._id == tx_id);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

