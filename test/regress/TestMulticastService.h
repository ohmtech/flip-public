/*****************************************************************************

      TestMulticastService.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"


namespace flip
{



class TestMulticastService
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

   class Root
   :  public Object
   {
   public:
      A           _a;
   };

                  TestMulticastService () = default;
   virtual        ~TestMulticastService () = default;

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
   void           run_003 (const std::vector <uint8_t> & data);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestMulticastService (const TestMulticastService & rhs) = delete;
   TestMulticastService &
                  operator = (const TestMulticastService & rhs) = delete;
                  TestMulticastService (TestMulticastService && rhs) = delete;
   TestMulticastService &
                  operator = (TestMulticastService && rhs) = delete;
   bool           operator == (const TestMulticastService & rhs) const = delete;
   bool           operator != (const TestMulticastService & rhs) const = delete;



}; // class TestMulticastService



}  // namespace flip



//#include  "flip/TestMulticastService.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

