/*****************************************************************************

      TestCarrierPortDirect.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestCarrierPortDirect.h"

#include "CarrierListenerLambda.h"
#include "PortListenerLambda.h"

#include "flip/detail/def.h"
#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "flip/CarrierDirect.h"
#include "flip/Document.h"
#include "flip/BackEndBinary.h"
#include "flip/DataConsumerMemory.h"
#include "flip/PortDirect.h"

#include "TestDef.h"

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

void  TestCarrierPortDirect::run ()
{
   Model::version ("test.direct");

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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestCarrierPortDirect::run_000 ()
{
   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestCarrierPortDirect::run_001 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_commit ([&port, &tx](PortBase & from, const Transaction & sub_tx){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (sub_tx.serialize () == tx.serialize ());

      from.receive_commit (sub_tx);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_tx_local ([&tx](const Transaction & sub_tx){
      flip_TEST (sub_tx.serialize () == tx.serialize ());
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.commit (tx);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestCarrierPortDirect::run_002 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   TxIdRange range;
   range.user_id = 123123456789ULL;
   range.actor_id = Ref::make_actor ('7pa1', '3uf0');
   range.nbr_id_first = 1234ULL;
   range.nbr_id_last = 5689ULL;

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_squash ([&port, &tx, &range](PortBase & from, const TxIdRange & sub_range, const Transaction & sub_tx){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (sub_tx.serialize () == tx.serialize ());
      flip_TEST (range.user_id == sub_range.user_id);
      flip_TEST (range.actor_id == sub_range.actor_id);
      flip_TEST (range.nbr_id_first == sub_range.nbr_id_first);
      flip_TEST (range.nbr_id_last == sub_range.nbr_id_last);

      from.receive_squash (sub_range, sub_tx);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_tx_squash ([&tx, &range](const TxIdRange & sub_range, const Transaction & sub_tx){
      flip_TEST (sub_tx.serialize () == tx.serialize ());
      flip_TEST (range.user_id == sub_range.user_id);
      flip_TEST (range.actor_id == sub_range.actor_id);
      flip_TEST (range.nbr_id_first == sub_range.nbr_id_first);
      flip_TEST (range.nbr_id_last == sub_range.nbr_id_last);
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.squash (range, tx);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestCarrierPortDirect::run_003 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_push ([&port, &tx](PortBase & from, const Transaction & sub_tx){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (sub_tx.serialize () == tx.serialize ());

      from.receive_transaction (sub_tx);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_tx_ext ([&tx](const Transaction & sub_tx){
      flip_TEST (sub_tx.serialize () == tx.serialize ());
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.push (tx);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestCarrierPortDirect::run_004 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_push ([&port, &tx](PortBase & from, const Transaction & sub_tx){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (sub_tx.serialize () == tx.serialize ());

      from.receive_ack (sub_tx.id ());
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_tx_ack ([&tx](const TxId & sub_tx_id){
      flip_TEST (sub_tx_id == tx.id ());
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.push (tx);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestCarrierPortDirect::run_005 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_push ([&port, &tx](PortBase & from, const Transaction & sub_tx){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (sub_tx.serialize () == tx.serialize ());

      from.receive_deny (sub_tx.id ());
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_tx_deny ([&tx](const TxId & sub_tx_id){
      flip_TEST (sub_tx_id == tx.id ());
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.push (tx);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestCarrierPortDirect::run_006 ()
{
   SignalData signal_data;
   signal_data.type_id = 123456789UL;
   signal_data.ref = Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL);
   signal_data.type = 987654321UL;
   signal_data.data = std::vector <uint8_t> {0xff, 0x01, 0x23};

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
   });
   port_listener.bind_signal ([&port, &signal_data](PortBase & from, const SignalData & sub_signal_data){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);
      flip_TEST (signal_data.type_id == sub_signal_data.type_id);
      flip_TEST (signal_data.ref == sub_signal_data.ref);
      flip_TEST (signal_data.type == sub_signal_data.type);
      flip_TEST (signal_data.data == sub_signal_data.data);

      from.receive_signal (signal_data);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });
   carrier_listener.bind_receive_signal ([&signal_data](const SignalData & sub_signal_data){
      flip_TEST (signal_data.type_id == sub_signal_data.type_id);
      flip_TEST (signal_data.ref == sub_signal_data.ref);
      flip_TEST (signal_data.type == sub_signal_data.type);
      flip_TEST (signal_data.data == sub_signal_data.data);
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());

   carrier.signal (signal_data);

   flip_TEST (carrier.is_connected ());

   port.PortBase::impl_unbind (port_listener);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestCarrierPortDirect::run_007 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   BackEndIR backend = document.write ();

   PortDirect port;
   PortListenerLambda port_listener;
   port_listener.bind_greet ([&port, &backend](PortBase & from){
      flip_TEST (&port == &from);
      flip_TEST (from.user () == 65451123456789ULL);

      from.receive_backend (backend);
   });
   port.PortBase::impl_bind (port_listener);

   CarrierListenerLambda carrier_listener;
   carrier_listener.bind_user ([](){
      return 65451123456789ULL;
   });

   bool received_beir_flag = false;

   carrier_listener.bind_receive_beir ([&backend, &received_beir_flag](const BackEndIR & sub_backend){
      flip_TEST (backend.equal (sub_backend));
      received_beir_flag = true;
   });

   CarrierDirect carrier (carrier_listener, port);

   flip_TEST (carrier.is_connected ());
   flip_TEST (received_beir_flag);

   port.PortBase::impl_unbind (port_listener);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

