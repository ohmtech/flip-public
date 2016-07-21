/*****************************************************************************

      TestServerSimple.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/DataModel.h"
#include "flip/Float.h"
#include "flip/Object.h"



namespace flip
{



class CarrierTransportSocketTcp;
class ServerSimple;

class TestServerSimple
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Root
   :  public Object
   {
   public:
      Float       _tempo;
   };

                  TestServerSimple () = default;
   virtual        ~TestServerSimple () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           wait_transfer_backend (CarrierTransportSocketTcp & carrier, ServerSimple & server);

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
   void           run_012b ();
   void           run_013 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestServerSimple (const TestServerSimple & rhs) = delete;
   TestServerSimple &
                  operator = (const TestServerSimple & rhs) = delete;
                  TestServerSimple (TestServerSimple && rhs) = delete;
   TestServerSimple &
                  operator = (TestServerSimple && rhs) = delete;
   bool           operator == (const TestServerSimple & rhs) const = delete;
   bool           operator != (const TestServerSimple & rhs) const = delete;



}; // class TestServerSimple



}  // namespace flip



//#include  "flip/TestServerSimple.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

