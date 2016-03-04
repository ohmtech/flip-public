/*****************************************************************************

      PortListenerLambda.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "PortListenerLambda.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : bind_greet
==============================================================================
*/

void  PortListenerLambda::bind_greet (std::function <void (PortBase &)> func)
{
   _func_greet = func;
}



/*
==============================================================================
Name : bind_commit
==============================================================================
*/

void  PortListenerLambda::bind_commit (std::function <void (PortBase &, const Transaction &)> func)
{
   _func_commit = func;
}



/*
==============================================================================
Name : bind_squash
==============================================================================
*/

void  PortListenerLambda::bind_squash (std::function <void (PortBase &, const TxIdRange &, const Transaction &)> func)
{
   _func_squash = func;
}



/*
==============================================================================
Name : bind_push
==============================================================================
*/

void  PortListenerLambda::bind_push (std::function <void (PortBase &, const Transaction &)> func)
{
   _func_push = func;
}



/*
==============================================================================
Name : bind_signal
==============================================================================
*/

void  PortListenerLambda::bind_signal (std::function <void (PortBase &, const SignalData &)> func)
{
   _func_signal = func;
}



/*
==============================================================================
Name : port_greet
==============================================================================
*/

void  PortListenerLambda::port_greet (PortBase & from)
{
   _func_greet (from);
}



/*
==============================================================================
Name : port_commit
==============================================================================
*/

void  PortListenerLambda::port_commit (PortBase & from, const Transaction & tx)
{
   _func_commit (from, tx);
}



/*
==============================================================================
Name : port_squash
==============================================================================
*/

void  PortListenerLambda::port_squash (PortBase & from, const TxIdRange & range, const Transaction & tx)
{
   _func_squash (from, range, tx);
}



/*
==============================================================================
Name : port_push
==============================================================================
*/

void  PortListenerLambda::port_push (PortBase & from, const Transaction & tx)
{
   _func_push (from, tx);
}



/*
==============================================================================
Name : port_signal
==============================================================================
*/

void  PortListenerLambda::port_signal (PortBase & from, const SignalData & data)
{
   _func_signal (from, data);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

