/*****************************************************************************

      PortListenerLambda.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/PortListener.h"

#include <functional>



namespace flip
{



class PortListenerLambda
:  public PortListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  PortListenerLambda () = default;
   virtual        ~PortListenerLambda () = default;

   void           bind_greet (std::function <void (PortBase &)> func);
   void           bind_commit (std::function <void (PortBase &, const Transaction &)> func);
   void           bind_squash (std::function <void (PortBase &, const TxIdRange &, const Transaction &)> func);
   void           bind_push (std::function <void (PortBase &, const Transaction &)> func);
   void           bind_signal (std::function <void (PortBase &, const SignalData &)> func);

   // PortListener
   virtual void   port_greet (PortBase & from) override;
   virtual void   port_commit (PortBase & from, const Transaction & tx) override;
   virtual void   port_squash (PortBase & from, const TxIdRange & range, const Transaction & tx) override;
   virtual void   port_push (PortBase & from, const Transaction & tx) override;
   virtual void   port_signal (PortBase & from, const SignalData & data) override;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::function <void (PortBase &)>
                  _func_greet;
   std::function <void (PortBase &, const Transaction &)>
                  _func_commit;
   std::function <void (PortBase &, const TxIdRange &, const Transaction &)>
                  _func_squash;
   std::function <void (PortBase &, const Transaction &)>
                  _func_push;
   std::function <void (PortBase &, const SignalData &)>
                  _func_signal;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  PortListenerLambda (const PortListenerLambda & rhs) = delete;
   PortListenerLambda &
                  operator = (const PortListenerLambda & rhs) = delete;
                  PortListenerLambda (PortListenerLambda && rhs) = delete;
   PortListenerLambda &
                  operator = (PortListenerLambda && rhs) = delete;
   bool           operator == (const PortListenerLambda & rhs) const = delete;
   bool           operator != (const PortListenerLambda & rhs) const = delete;



}; // class PortListenerLambda



}  // namespace flip



//#include  "flip/PortListenerLambda.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

