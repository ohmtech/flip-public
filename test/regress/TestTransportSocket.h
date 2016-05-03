/*****************************************************************************

      TestTransportSocket.h
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



class CarrierTransportSocketTcp;
class PortTransportServerTcp;

class TestTransportSocket
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
      enum
      {
                  Test_SERVER_TO_CLIENT = 0,
      };
                  Root () : _server_to_client (Test_SERVER_TO_CLIENT, *this) {}

      Signal <int>
                  _server_to_client;

      Int         _int;
      Float       _float;
      A           _a;
      B           _b;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
   };

                  TestTransportSocket () = default;
   virtual        ~TestTransportSocket () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           wait_transfer_backend (CarrierTransportSocketTcp & carrier, PortTransportServerTcp & server);

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestTransportSocket (const TestTransportSocket & rhs) = delete;
   TestTransportSocket &
                  operator = (const TestTransportSocket & rhs) = delete;
                  TestTransportSocket (TestTransportSocket && rhs) = delete;
   TestTransportSocket &
                  operator = (TestTransportSocket && rhs) = delete;
   bool           operator == (const TestTransportSocket & rhs) const = delete;
   bool           operator != (const TestTransportSocket & rhs) const = delete;



}; // class TestTransportSocket



}  // namespace flip



//#include  "flip/TestTransportSocket.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

