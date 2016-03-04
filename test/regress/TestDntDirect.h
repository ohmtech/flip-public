/*****************************************************************************

      TestDntDirect.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"

#include <functional>



namespace flip
{



class TestDntDirect
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};
   class Root
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

                  TestDntDirect () = default;
   virtual        ~TestDntDirect () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestDntDirect (const TestDntDirect & rhs) = delete;
   TestDntDirect &operator = (const TestDntDirect & rhs) = delete;
                  TestDntDirect (TestDntDirect && rhs) = delete;
   TestDntDirect &operator = (TestDntDirect && rhs) = delete;
   bool           operator == (const TestDntDirect & rhs) const = delete;
   bool           operator != (const TestDntDirect & rhs) const = delete;



}; // class TestDntDirect



}  // namespace flip



//#include  "flip/TestDntDirect.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

