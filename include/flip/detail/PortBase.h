/*****************************************************************************

      PortBase.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/config.h"

#include <cstdint>



namespace flip
{



class BackEndIR;
class PortListener;
class Ref;
class SignalData;
class Transaction;
class TxId;
class TxIdRange;

class flip_API PortBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  PortBase () = default;
   virtual        ~PortBase ();

   virtual void   receive_backend (const BackEndIR & backend) = 0;
   virtual void   receive_commit (const Transaction & tx) = 0;
   virtual void   receive_squash (const TxIdRange & range, const Transaction & tx) = 0;
   virtual void   receive_transaction (const Transaction & tx) = 0;
   virtual void   receive_ack (const TxId & tx_id) = 0;
   virtual void   receive_deny (const TxId & tx_id) = 0;
   virtual void   receive_signal (const SignalData & data) = 0;

   uint64_t       user () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (PortListener & listener);
   void           impl_unbind (PortListener & listener);
   void           impl_activate (bool active_flag);
   bool           impl_is_active ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   void           greet (uint64_t user_id);
   void           commit (const Transaction & tx);
   void           squash (const TxIdRange & range, const Transaction & tx);
   void           push (const Transaction & tx);
   void           signal (const SignalData & data);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   PortListener * _listener_ptr = nullptr;

   uint64_t       _user_id = 0ULL;
   bool           _active_flag = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  PortBase (const PortBase & rhs) = delete;
   PortBase &     operator = (const PortBase & rhs) = delete;
                  PortBase (PortBase && rhs) = delete;
   PortBase &     operator = (PortBase && rhs) = delete;
   bool           operator == (const PortBase & rhs) const = delete;
   bool           operator != (const PortBase & rhs) const = delete;



}; // class PortBase



}  // namespace flip



//#include  "flip/detail/PortBase.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

