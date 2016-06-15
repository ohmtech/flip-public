/*****************************************************************************

      TestServer.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentServer.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/Signal.h"



namespace flip
{



class BackEndIR;
class DocumentServer;

class TestServer
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Client   // COV_NF_LINE
   :  public Object
   {
   public:
      enum
      {
                  Signal_TEST,
      };

                  Client () : Client (0ULL) {}
                  Client (uint64_t user_id);
                  Client (const Client & rhs) : Client (uint64_t (rhs._user_id)) {} // COV_NF_LINE
      virtual     ~Client () = default;

      uint64_t    user () const;

      Int         _user_id;
      Float       _scroll;

      Signal <>   _signal_test;
   };

   class Root
   :  public Object
   {
   public:
      enum
      {
                  Signal_FROM_CLIENT,
                  Signal_TO_CLIENT,
      };
                  Root () : _signal_from_client (Signal_FROM_CLIENT, *this), _signal_to_client (Signal_TO_CLIENT, *this) {}
                  Root (const Root & other) : Object (other), _signal_from_client (Signal_FROM_CLIENT, *this), _signal_to_client (Signal_TO_CLIENT, *this) {} // COV_NF_LINE

      Collection <Client>
                  _clients;

      Float       _tempo;

      Signal <>   _signal_from_client;
      Signal <>   _signal_to_client;
   };

                  TestServer () = default;
   virtual        ~TestServer () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           init (DocumentServer & server, BackEndIR & backend);

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestServer (const TestServer & rhs) = delete;
   TestServer &   operator = (const TestServer & rhs) = delete;
                  TestServer (TestServer && rhs) = delete;
   TestServer &   operator = (TestServer && rhs) = delete;
   bool           operator == (const TestServer & rhs) const = delete;
   bool           operator != (const TestServer & rhs) const = delete;



}; // class TestServer



}  // namespace flip



//#include  "flip/TestServer.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

