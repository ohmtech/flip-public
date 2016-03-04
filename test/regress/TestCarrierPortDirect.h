/*****************************************************************************

      TestCarrierPortDirect.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Object.h"

#include <functional>



namespace flip
{



class TestCarrierPortDirect
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};
   class Root : public Object {};   // COV_NF_LINE

                  TestCarrierPortDirect () = default;
   virtual        ~TestCarrierPortDirect () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();
   void           run_007 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestCarrierPortDirect (const TestCarrierPortDirect & rhs) = delete;
   TestCarrierPortDirect &
                  operator = (const TestCarrierPortDirect & rhs) = delete;
                  TestCarrierPortDirect (TestCarrierPortDirect && rhs) = delete;
   TestCarrierPortDirect &
                  operator = (TestCarrierPortDirect && rhs) = delete;
   bool           operator == (const TestCarrierPortDirect & rhs) const = delete;
   bool           operator != (const TestCarrierPortDirect & rhs) const = delete;



}; // class TestCarrierPortDirect



}  // namespace flip



//#include  "flip/TestCarrierPortDirect.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

