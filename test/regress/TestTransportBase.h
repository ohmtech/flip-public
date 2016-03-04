/*****************************************************************************

      TestTransportBase.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/BackEndIR.h"
#include "flip/DataModel.h"
#include "flip/Object.h"
#include "flip/Transaction.h"
#include "flip/detail/CarrierListener.h"
#include "flip/detail/CarrierTransportBase.h"
#include "flip/detail/PortListener.h"
#include "flip/detail/PortTransportBase.h"
#include "flip/detail/SignalData.h"
#include "flip/detail/TxId.h"
#include "flip/detail/TxIdRange.h"

#include <functional>



namespace flip
{



class TestTransportBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};
   class Root : public Object {};   // COV_NF_LINE

                  TestTransportBase () = default;
   virtual        ~TestTransportBase () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   class Port;

   class Carrier
   :  public CarrierTransportBase
   {
   public:
                  Carrier (CarrierListener & listener);
      virtual     ~Carrier ();

      void        bind (Port & port);
      void        receive_from_port (const std::vector <uint8_t> & data);

      void        send_garbage_msg ();

   protected:
      // CarrierTransportBase
      virtual void
                  send (const std::vector <uint8_t> & data) override;

   private:
      Port *      _port_ptr = nullptr;

                  Carrier (const Carrier & rhs) = delete;
                  Carrier (Carrier && rhs) = delete;
      Carrier &   operator = (const Carrier & rhs) = delete;
      Carrier &   operator = (Carrier && rhs) = delete;
   };

   class Listener
   :  public CarrierListener
   ,  public PortListener
   {
   public:
                  Listener (const DataModelBase & model) : _model (model) {}
      virtual     ~Listener () = default;

      enum class Type
      {
                  None,

                  CarrierBeir,
                  CarrierLocal,
                  CarrierSquash,
                  CarrierExt,
                  CarrierAck,
                  CarrierDeny,
                  CarrierSignal,

                  PortGreet,
                  PortCommit,
                  PortSquash,
                  PortPush,
                  PortSignal,
      };

      const DataModelBase &
                  _model;

      Type        _type = Type::None;
      PortBase *  _port_ptr = nullptr;
      BackEndIR   _backend;
      Transaction _tx;
      TxIdRange   _range;
      TxId        _id;
      SignalData  _signal;

      // CarrierListener
      virtual const DataModelBase &
                  carrier_data_model () override {return _model;}
      virtual uint64_t
                  carrier_user () override {return 0ULL;}
      virtual void
                  carrier_receive_beir (const BackEndIR & backend) override;
      virtual void
                  carrier_receive_tx_local (const Transaction & /*tx*/) override {flip_FATAL;}  // COV_NF_LINE
      virtual void
                  carrier_receive_tx_squash (const TxIdRange & /*range*/, const Transaction & /*tx*/) override {flip_FATAL;}  // COV_NF_LINE
      virtual void
                  carrier_receive_tx_ext (const Transaction & tx) override;
      virtual void
                  carrier_receive_tx_ack (const TxId & tx_id) override;
      virtual void
                  carrier_receive_tx_deny (const TxId & tx_id) override;
      virtual void
                  carrier_receive_signal (const SignalData & data) override;

      virtual void
                  port_greet (PortBase & from) override;
      virtual void
                  port_commit (PortBase & /*from*/, const Transaction & /*tx*/) override {flip_FATAL;}  // COV_NF_LINE
      virtual void
                  port_squash (PortBase & /*from*/, const TxIdRange & /*range*/, const Transaction & /*tx*/) override {flip_FATAL;}  // COV_NF_LINE
      virtual void
                  port_push (PortBase & from, const Transaction & tx) override;
      virtual void
                  port_signal (PortBase & from, const SignalData & data) override;

   private:
                  Listener () = delete;
                  Listener (const Listener & rhs) = delete;
                  Listener (Listener && rhs) = delete;
      Listener &  operator = (const Listener & rhs) = delete;
      Listener &  operator = (Listener && rhs) = delete;
   };

   class Port
   :  public PortTransportBase
   {
   public:
                  Port (Listener & listener);
      virtual     ~Port ();

      void        bind (Carrier & carrier);
      void        receive_from_carrier (const std::vector <uint8_t> & data);

   protected:
      // PortTransportBase
      virtual void
                  send (const std::vector <uint8_t> & data) override;

   private:
      Listener &  _listener;
      Carrier *   _carrier_ptr = nullptr;

                  Port (const Port & rhs) = delete;
                  Port (Port && rhs) = delete;
      Port &      operator = (const Port & rhs) = delete;
      Port &      operator = (Port && rhs) = delete;
   };

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();
   void           run_007 ();
   void           run_008 ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestTransportBase (const TestTransportBase & rhs) = delete;
   TestTransportBase &
                  operator = (const TestTransportBase & rhs) = delete;
                  TestTransportBase (TestTransportBase && rhs) = delete;
   TestTransportBase &
                  operator = (TestTransportBase && rhs) = delete;
   bool           operator == (const TestTransportBase & rhs) const = delete;
   bool           operator != (const TestTransportBase & rhs) const = delete;



}; // class TestTransportBase



}  // namespace flip



//#include  "flip/TestTransportBase.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

