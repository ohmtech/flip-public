/*****************************************************************************

      TestInt.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Int.h"
#include "flip/DataModel.h"
#include "flip/Object.h"

#include <vector>
#include <list>
#include <map>

#include <cstdint>



namespace flip
{



class TestInt
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Root
   :  public Object
   {
   public:
      Int         _int;
   };

                  TestInt () = default;
   virtual        ~TestInt () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_pre ();
   void           run_000 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestInt (const TestInt & rhs) = delete;
   TestInt &     operator = (const TestInt & rhs) = delete;
                  TestInt (TestInt && rhs) = delete;
   TestInt &     operator = (TestInt && rhs) = delete;
   bool           operator == (const TestInt & rhs) const = delete;
   bool           operator != (const TestInt & rhs) const = delete;



}; // class TestInt



}  // namespace flip



//#include  "flip/TestInt.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

