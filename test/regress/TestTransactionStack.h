/*****************************************************************************

      TestTransactionStack.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/ObjectRef.h"
#include "flip/detail/CarrierBase.h"



namespace flip
{



class CarrierListener;

class TestTransactionStack
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model
   :  public DataModel <Model>
   {
   };

   class Root
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

                  TestTransactionStack () = default;
   virtual        ~TestTransactionStack () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   class Server
   :  public CarrierBase
   {
   public:
                  Server (CarrierListener & listener);
      virtual     ~Server ();

      void        reply_tx (const Transaction & tx);
      void        reply_tx_local (const Transaction & tx);
      void        reply_tx_ack ();
      void        reply_tx_deny ();

      // CarrierBase
      virtual void   do_greet (uint64_t /* user_id */) override {}   // COV_NF_LINE
      virtual void   do_commit (const Transaction & /* tx */) override {}
      virtual void   do_squash (const TxIdRange & /* range */, const Transaction & /* tx */) override {}   // COV_NF_LINE
      virtual void   do_push (const Transaction & tx) override;
      virtual void   do_signal (const SignalData & /* data */) override {}   // COV_NF_LINE

   private:
      bool        _ack_flag = true;
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
   void           run_015 ();
   void           run_016 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestTransactionStack (const TestTransactionStack & rhs) = delete;
   TestTransactionStack &
                  operator = (const TestTransactionStack & rhs) = delete;
                  TestTransactionStack (TestTransactionStack && rhs) = delete;
   TestTransactionStack &
                  operator = (TestTransactionStack && rhs) = delete;
   bool           operator == (const TestTransactionStack & rhs) const = delete;
   bool           operator != (const TestTransactionStack & rhs) const = delete;



}; // class TestTransactionStack



}  // namespace flip



//#include  "flip/TestTransactionStack.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

