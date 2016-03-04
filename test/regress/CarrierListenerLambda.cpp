/*****************************************************************************

      CarrierListenerLambda.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "CarrierListenerLambda.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : bind_user
==============================================================================
*/

void  CarrierListenerLambda::bind_user (std::function <uint64_t ()> func)
{
   _func_user = func;
}



/*
==============================================================================
Name : bind_receive_beir
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_beir (std::function <void (const BackEndIR &)> func)
{
   _func_receive_beir = func;
}



/*
==============================================================================
Name : bind_receive_tx_local
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_tx_local (std::function <void (const Transaction &)> func)
{
   _func_receive_tx_local = func;
}



/*
==============================================================================
Name : bind_receive_tx_squash
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_tx_squash (std::function <void (const TxIdRange &, const Transaction &)> func)
{
   _func_receive_tx_squash = func;
}



/*
==============================================================================
Name : bind_receive_tx_ext
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_tx_ext (std::function <void (const Transaction &)> func)
{
   _func_receive_tx_ext = func;
}



/*
==============================================================================
Name : bind_receive_tx_ack
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_tx_ack (std::function <void (const TxId & tx_id)> func)
{
   _func_receive_tx_ack = func;
}



/*
==============================================================================
Name : bind_receive_tx_deny
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_tx_deny (std::function <void (const TxId & tx_id)> func)
{
   _func_receive_tx_deny = func;
}



/*
==============================================================================
Name : bind_receive_signal
==============================================================================
*/

void  CarrierListenerLambda::bind_receive_signal (std::function <void (const SignalData & data)> func)
{
   _func_receive_signal = func;
}



/*
==============================================================================
Name : carrier_user
==============================================================================
*/

uint64_t CarrierListenerLambda::carrier_user ()
{
   return _func_user ();
}



/*
==============================================================================
Name : carrier_receive_beir
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_beir (const BackEndIR & backend)
{
   _func_receive_beir (backend);
}



/*
==============================================================================
Name : carrier_receive_tx_local
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_tx_local (const Transaction & tx)
{
   _func_receive_tx_local (tx);
}



/*
==============================================================================
Name : carrier_receive_tx_squash
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_tx_squash (const TxIdRange & range, const Transaction & tx)
{
   _func_receive_tx_squash (range, tx);
}



/*
==============================================================================
Name : carrier_receive_tx_ext
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_tx_ext (const Transaction & tx)
{
   _func_receive_tx_ext (tx);
}



/*
==============================================================================
Name : carrier_receive_tx_ack
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_tx_ack (const TxId & tx_id)
{
   _func_receive_tx_ack (tx_id);
}



/*
==============================================================================
Name : carrier_receive_tx_deny
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_tx_deny (const TxId & tx_id)
{
   _func_receive_tx_deny (tx_id);
}



/*
==============================================================================
Name : carrier_receive_signal
==============================================================================
*/

void  CarrierListenerLambda::carrier_receive_signal (const SignalData & data)
{
   _func_receive_signal (data);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

