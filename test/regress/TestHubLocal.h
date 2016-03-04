/*****************************************************************************

      TestHubLocal.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Signal.h"



namespace flip
{



class CarrierSocketTcp;
class PortSocketTcp;

class TestHubLocal
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

   class B
   :  public A
   {
   public:
      Int         _int2;
      Float       _float2;
      Collection <A>
                  _coll;
   };

   class Root
   :  public Object
   {
   public:
      enum Sig
      {
                  Sig_FIRE
      };

                  Root () : _signal_fire (*this) {}
                  Root (const Root &) : _signal_fire (*this) {} // COV_NF_LINE

      Int         _int;
      Float       _float;
      A           _a;
      B           _b;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;

      Signal <Sig_FIRE, int>
                  _signal_fire;
   };

                  TestHubLocal () = default;
   virtual        ~TestHubLocal () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_000b ();
   void           run_001 ();
   void           run_001b ();
   void           run_002 ();
   void           run_002b ();
   void           run_003 ();
   void           run_003b ();
   void           run_004 ();
   void           run_004b ();
   void           run_005 ();
   void           run_005b ();
   void           run_006 ();
   void           run_006b ();
   void           run_007 ();
   void           run_008 ();
   void           run_009 ();

   void           wait_connect (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document);
   void           wait_backend (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document);
   void           wait_pending_txs (PortSocketTcp & port, CarrierSocketTcp & carrier, DocumentBase & document);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestHubLocal (const TestHubLocal & rhs) = delete;
   TestHubLocal & operator = (const TestHubLocal & rhs) = delete;
                  TestHubLocal (TestHubLocal && rhs) = delete;
   TestHubLocal & operator = (TestHubLocal && rhs) = delete;
   bool           operator == (const TestHubLocal & rhs) const = delete;
   bool           operator != (const TestHubLocal & rhs) const = delete;



}; // class TestHubLocal



}  // namespace flip



//#include  "flip/TestHubLocal.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

