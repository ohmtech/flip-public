/*****************************************************************************

      TestClass.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Enum.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"




namespace flip
{



class TestClass
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};
   class Model2 : public DataModel <Model2> {};

   class A  // 1 + 2 = 3
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

   class B  // 1 + (3 - 1) + 3 = 6
   :  public A // inheritance only 2, not 3
   {
   public:
      Int         _int;
      Float       _float;
      Collection <A>
                  _coll;
   };

   enum class C
   {
                  x0, x1, x2,
   };

   class Root  // 1 + 1 + 1 + 3 + 6 + 1 + 1 + 1 + 1 + 1 + 1 + 1 = 19
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
      A           _a;   // aggregation, full size_of
      B           _b;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
      ObjectRef <A>
                  _ref_a;
      Bool        _bool;
      Blob        _blob;
      String      _string;
      Enum <C>    _enum;
   };

                  TestClass () = default;
   virtual        ~TestClass () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestClass (const TestClass & rhs) = delete;
   TestClass &    operator = (const TestClass & rhs) = delete;
                  TestClass (TestClass && rhs) = delete;
   TestClass &    operator = (TestClass && rhs) = delete;
   bool           operator == (const TestClass & rhs) const = delete;
   bool           operator != (const TestClass & rhs) const = delete;



}; // class TestClass



}  // namespace flip



//#include  "flip/TestClass.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

