/*****************************************************************************

      TestTransactionStack.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestTransactionStack.h"

#include "flip/CarrierDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/detail/def.h"
#include "flip/detail/ExecFlags.h"
#include "flip/detail/TransactionStack.h"
#include "flip/detail/TxId.h"
#include "flip/detail/TxIdRange.h"
#include "TestDef.h"

#include <iostream>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestTransactionStack::run ()
{
   Model::version ("test.tx_stack");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float");

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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Server::ctor
==============================================================================
*/

TestTransactionStack::Server::Server (CarrierListener & listener)
:  CarrierBase (listener)
{
}



/*
==============================================================================
Name : Server::dtor
==============================================================================
*/

TestTransactionStack::Server::~Server ()
{
}



/*
==============================================================================
Name : Server::reply_tx
==============================================================================
*/

void  TestTransactionStack::Server::reply_tx (const Transaction & tx)
{
   receive_tx_ext (tx);
}



/*
==============================================================================
Name : Server::reply_tx_local
==============================================================================
*/

void  TestTransactionStack::Server::reply_tx_local (const Transaction & tx)
{
   receive_tx_local (tx);
}



/*
==============================================================================
Name : Server::reply_tx_ack
==============================================================================
*/

void  TestTransactionStack::Server::reply_tx_ack ()
{
   _ack_flag = true;
}



/*
==============================================================================
Name : Server::reply_tx_deny
==============================================================================
*/

void  TestTransactionStack::Server::reply_tx_deny ()
{
   _ack_flag = false;
}



/*
==============================================================================
Name : Server::do_push
==============================================================================
*/

void  TestTransactionStack::Server::do_push (const Transaction & tx)
{
   if (_ack_flag)
   {
      receive_tx_ack (tx.id ());
   }
   else
   {
      receive_tx_deny (tx.id ());
   }
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestTransactionStack::run_000 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');
   Root & root = document.root <Root> ();

   Server server (document);

   root._int = 1;
   document.commit ();

   server.reply_tx_ack ();
   document.push ();

   flip_TEST (root._int == 1LL);

   root._int = 2;
   document.commit ();

   server.reply_tx_deny ();
   document.push ();

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, ExecFlags::OP_IN_UNDO, 1LL, 3LL);

   server.reply_tx (tx);
   document.pull ();

   flip_TEST (root._int == 3LL);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestTransactionStack::run_001 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');
   Root & root = document.root <Root> ();

   Server server (document);

   root._int = 1;
   document.commit ();

   server.reply_tx_ack ();
   document.push ();

   flip_TEST (root._int == 1LL);

   root._int = 2;
   document.commit ();

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, ExecFlags::OP_IN_UNDO, 1LL, 3LL);

   server.reply_tx (tx);

   server.reply_tx_deny ();
   document.push ();

   document.pull ();

   flip_TEST (root._int == 3LL);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestTransactionStack::run_002 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');
   Root & root = document.root <Root> ();

   Document document2 (Model::use (), 123456789ULL, 'flip', 'tes2');
   Root & root2 = document2.root <Root> ();

   Server server (document);

   root2._float = 2.5;
   Transaction tx = document2.commit ();

   server.reply_tx_local (tx);

   document.pull ();

   flip_TEST (root._float == 2.5);

   root._int = 1;
   document.commit ();

   server.reply_tx_ack ();
   document.push ();

   document.pull ();

   flip_TEST (root._int == 1LL);
   flip_TEST (root._float == 2.5);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestTransactionStack::run_003 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');
   Root & root = document.root <Root> ();

   Document document2 (Model::use (), 123456789ULL, 'flip', 'tes2');
   Root & root2 = document2.root <Root> ();

   Server server (document);

   root2._float = 2.5;
   Transaction tx = document2.commit ();

   server.reply_tx_local (tx);

   document.pull ();

   flip_TEST (root._float == 2.5);

   root._int = 1;
   document.commit ();

   server.reply_tx_deny ();
   document.push ();

   document.pull ();

   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 2.5);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestTransactionStack::run_004 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document_gui (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document_gui, port_gui);
   Root & root_gui = document_gui.root <Root> ();

   Document document_auen (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document_auen, port_auen);

   Server server (hub);

   document_gui.pull ();
   document_auen.pull ();

   root_gui._int = 1;
   document_gui.commit ();

   server.reply_tx_ack ();
   document_gui.push ();

   flip_TEST (root_gui._int == 1LL);

   root_gui._int = 2;
   document_gui.commit ();

   server.reply_tx_deny ();
   document_gui.push ();

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, ExecFlags::OP_IN_UNDO, 1LL, 3LL);

   server.reply_tx (tx);

   flip_TEST (root_gui._int == 2LL);

   document_gui.pull ();

   flip_TEST (root_gui._int == 3LL);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestTransactionStack::run_005 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document_gui (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document_gui, port_gui);
   Root & root_gui = document_gui.root <Root> ();

   Document document_auen (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document_auen, port_auen);
   Root & root_auen = document_auen.root <Root> ();

   Server server (hub);

   document_gui.pull ();
   document_auen.pull ();

   root_gui._int = 1;
   document_gui.commit ();

   server.reply_tx_ack ();
   document_gui.push ();

   document_gui.pull ();

   flip_TEST (root_gui._int == 1LL);

   root_gui._int = 2;
   document_gui.commit ();

   server.reply_tx_deny ();
   document_gui.push ();

   document_gui.pull ();

   flip_TEST (root_gui._int == 1LL);

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, ExecFlags::OP_IN_UNDO, 1LL, 3LL);

   server.reply_tx (tx);

   document_gui.pull ();

   flip_TEST (root_gui._int == 3LL);

   document_auen.pull ();

   flip_TEST (root_auen._int == 3LL);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestTransactionStack::run_006 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document_gui (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document_gui, port_gui);
   Root & root_gui = document_gui.root <Root> ();

   Document document_auen (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document_auen, port_auen);
   Root & root_auen = document_auen.root <Root> ();

   Server server (hub);

   document_gui.pull ();
   document_auen.pull ();

   root_gui._int = 1;
   document_gui.commit ();

   server.reply_tx_ack ();
   document_gui.push ();

   document_gui.pull ();

   flip_TEST (root_gui._int == 1LL);

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, ExecFlags::OP_IN_UNDO, 1LL, 3LL);

   server.reply_tx (tx);

   document_auen.pull ();
   flip_TEST (root_auen._int == 3LL);

   root_gui._int = 2;
   document_gui.commit ();

   document_gui.push ();
   document_gui.pull ();

   flip_TEST (root_gui._int == 3LL);

   document_auen.pull ();

   flip_TEST (root_auen._int == 3LL);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestTransactionStack::run_007 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document_gui (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document_gui, port_gui);
   Root & root_gui = document_gui.root <Root> ();

   Document document_auen (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document_auen, port_auen);
   Root & root_auen = document_auen.root <Root> ();

   Server server (hub);

   document_gui.pull ();
   document_auen.pull ();

   root_gui._int = 1;
   Transaction tx = document_gui.commit ();

   server.reply_tx_ack ();
   document_gui.push ();

   document_gui.pull ();
   document_auen.pull ();

   flip_TEST (root_gui._int == 1LL);
   flip_TEST (root_auen._int == 1LL);

   root_auen._float = 1.0;
   document_auen.commit ();
   document_auen.push ();

   bool ok_flag = document_gui.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root_gui._int == 0LL);

   document_gui.commit ();
   document_gui.push ();

   flip_TEST (root_gui._int == 0LL);

   document_gui.pull ();
   document_auen.pull ();

   flip_TEST (root_gui._int == 0LL);
   flip_TEST (root_auen._int == 0LL);

   flip_TEST (root_gui._float == 1.0);
   flip_TEST (root_auen._float == 1.0);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestTransactionStack::run_008 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document1 (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document1, port_gui);
   Root & root1 = document1.root <Root> ();

   Document document2 (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document2, port_auen);
   Root & root2 = document2.root <Root> ();

   document1.pull ();
   document2.pull ();

   root1._int = 3LL;
   // don't commit

   root2._float = 3.5;
   document2.commit ();
   document2.push ();

   flip_TEST (root1._int == 3LL);
   flip_TEST (root1._float == 0.0);

   document1.pull ();

   flip_TEST (root1._int == 3LL);
   flip_TEST (root1._float == 3.5);

   document1.commit ();
   document1.push ();

   document2.pull ();

   flip_TEST (root2._int == 3LL);
   flip_TEST (root2._float == 3.5);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestTransactionStack::run_009 ()
{
   PortDirect port_gui;
   PortDirect port_auen;
   Hub hub (Model::use (), 123456789ULL, port_gui, port_auen);

   Document document1 (Model::use (), 123456789ULL, 'flip', 'gui ');
   CarrierDirect carrier_gui (document1, port_gui);
   Root & root1 = document1.root <Root> ();

   Document document2 (Model::use (), 123456789ULL, 'flip', 'auen');
   CarrierDirect carrier_auen (document2, port_auen);
   Root & root2 = document2.root <Root> ();

   document1.pull ();
   document2.pull ();

   root1._int = 3LL;
   // don't commit

   root2._int = 2LL;
   document2.commit ();
   document2.push ();

   flip_TEST (root1._int == 3LL);

   document1.pull ();

   flip_TEST (root1._int == 2LL);

   document1.commit ();
   document1.push ();

   document2.pull ();

   flip_TEST (root2._int == 2LL);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestTransactionStack::run_010 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestTransactionStack::run_011 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      stack.acknowledge (TxId (document.user (), document.actor (), 1ULL));
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestTransactionStack::run_012 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      stack.deny (TxId (document.user (), document.actor (), 1ULL));
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 0LL);
      flip_TEST (document.root <Root> ()._int.before () == 0LL);
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestTransactionStack::run_013 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      Transaction tx (document.user (), document.actor () + 1, 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 2LL);

      stack.external (tx);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 2LL);
      flip_TEST (document.root <Root> ()._int.before () == 2LL);
   }
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestTransactionStack::run_014 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      Transaction tx (document.user (), document.actor (), 2ULL);
      tx.push_int64_set (Ref::root + 1, 0, 1LL, 2LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 2LL);
      flip_TEST (document.root <Root> ()._int.before () == 2LL);
   }

   {
      Transaction tx (document.user (), document.actor (), 3ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 2LL);

      stack.squash (tx, TxIdRange (document.user (), document.actor (), 1ULL, 2ULL));
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 2LL);
      flip_TEST (document.root <Root> ()._int.before () == 2LL);
   }
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestTransactionStack::run_015 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      Transaction tx (document.user (), document.actor (), 2ULL);
      tx.push_int64_set (Ref::root + 1, 0, 1LL, 2LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 2LL);
      flip_TEST (document.root <Root> ()._int.before () == 2LL);
   }

   {
      Transaction tx (document.user (), document.actor (), 3ULL);
      tx.push_int64_set (Ref::root + 1, 0, 2LL, 3LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 3LL);
      flip_TEST (document.root <Root> ()._int.before () == 3LL);
   }

   {
      Transaction tx (document.user (), document.actor (), 4ULL);
      tx.push_int64_set (Ref::root + 1, 0, 1LL, 3LL);

      stack.squash (tx, TxIdRange (document.user (), document.actor (), 2ULL, 3ULL));
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 3LL);
      flip_TEST (document.root <Root> ()._int.before () == 3LL);
   }
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestTransactionStack::run_016 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'test');

   TransactionStack stack (document);

   {
      Transaction tx (document.user (), document.actor (), 1ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 1LL);
      flip_TEST (document.root <Root> ()._int.before () == 1LL);
   }

   {
      Transaction tx (document.user (), document.actor () + 1, 1ULL);
      tx.push_float64_set (Ref::root + 2, 0, 0.0, 1.5);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._float == 1.5);
      flip_TEST (document.root <Root> ()._float.before () == 1.5);
   }

   {
      Transaction tx (document.user (), document.actor (), 2ULL);
      tx.push_int64_set (Ref::root + 1, 0, 1LL, 3LL);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 3LL);
      flip_TEST (document.root <Root> ()._int.before () == 3LL);
   }

   {
      Transaction tx (document.user (), document.actor () + 1, 2ULL);
      tx.push_float64_set (Ref::root + 2, 0, 1.5, 3.5);

      stack.push_local (tx, false);
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._float == 3.5);
      flip_TEST (document.root <Root> ()._float.before () == 3.5);
   }

   {
      Transaction tx (document.user (), document.actor (), 3ULL);
      tx.push_int64_set (Ref::root + 1, 0, 0LL, 3LL);

      stack.squash (tx, TxIdRange (document.user (), document.actor (), 1ULL, 2ULL));
      stack.finish ();
      document.root <Root> ().impl_synchronize ();

      flip_TEST (document.root <Root> ()._int == 3LL);
      flip_TEST (document.root <Root> ()._int.before () == 3LL);
      flip_TEST (document.root <Root> ()._float == 3.5);
      flip_TEST (document.root <Root> ()._float.before () == 3.5);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

