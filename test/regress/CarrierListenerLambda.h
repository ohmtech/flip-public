/*****************************************************************************

      CarrierListenerLambda.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
#include "flip/detail/CarrierListener.h"

#include <functional>



namespace flip
{



class CarrierListenerLambda
:  public CarrierListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  CarrierListenerLambda () = default;
   virtual        ~CarrierListenerLambda () = default;

   void           bind_user (std::function <uint64_t ()> func);
   void           bind_receive_beir (std::function <void (const BackEndIR &)> func);
   void           bind_receive_tx_local (std::function <void (const Transaction &)> func);
   void           bind_receive_tx_squash (std::function <void (const TxIdRange &, const Transaction &)> func);
   void           bind_receive_tx_ext (std::function <void (const Transaction &)> func);
   void           bind_receive_tx_ack (std::function <void (const TxId &)> func);
   void           bind_receive_tx_deny (std::function <void (const TxId &)> func);
   void           bind_receive_signal (std::function <void (const SignalData &)> func);

   // CarrierListener
   virtual const DataModelBase &
                  carrier_data_model () override {flip_FATAL;}
   virtual uint64_t
                  carrier_user () override;
   virtual void   carrier_receive_beir (const BackEndIR & backend) override;
   virtual void   carrier_receive_tx_local (const Transaction & tx) override;
   virtual void   carrier_receive_tx_squash (const TxIdRange & range, const Transaction & tx) override;
   virtual void   carrier_receive_tx_ext (const Transaction & tx) override;
   virtual void   carrier_receive_tx_ack (const TxId & tx_id) override;
   virtual void   carrier_receive_tx_deny (const TxId & tx_id) override;
   virtual void   carrier_receive_signal (const SignalData & data) override;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::function <uint64_t ()>
                  _func_user;
   std::function <void (const BackEndIR &)>
                  _func_receive_beir;
   std::function <void (const Transaction &)>
                  _func_receive_tx_local;
   std::function <void (const TxIdRange &, const Transaction &)>
                  _func_receive_tx_squash;
   std::function <void (const Transaction &)>
                  _func_receive_tx_ext;
   std::function <void (const TxId &)>
                  _func_receive_tx_ack;
   std::function <void (const TxId &)>
                  _func_receive_tx_deny;
   std::function <void (const SignalData &)>
                  _func_receive_signal;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  CarrierListenerLambda (const CarrierListenerLambda & rhs) = delete;
   CarrierListenerLambda &
                  operator = (const CarrierListenerLambda & rhs) = delete;
                  CarrierListenerLambda (CarrierListenerLambda && rhs) = delete;
   CarrierListenerLambda &
                  operator = (CarrierListenerLambda && rhs) = delete;
   bool           operator == (const CarrierListenerLambda & rhs) const = delete;
   bool           operator != (const CarrierListenerLambda & rhs) const = delete;



}; // class CarrierListenerLambda



}  // namespace flip



//#include  "flip/CarrierListenerLambda.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

