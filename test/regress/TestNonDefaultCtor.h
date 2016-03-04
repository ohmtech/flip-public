/*****************************************************************************

      TestNonDefaultCtor.h
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



class TestNonDefaultCtor
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A  // COV_NF_LINE
   :  public Object
   {
   public:
                  A () : _int (2LL), _float (3.5) {}

      Int         _int;
      Float       _float;
   };

   class Root
   :  public Object
   {
   public:
      A           _a;
   };

   class Model2 : public DataModel <Model2> {};

   class A2
   :  public Object
   {
   public:
                  A2 () : _int (2LL), _float (3.5) {}

      Int         _int;
      Float       _float;
   };

   class Root2
   :  public Object
   {
   public:
      Collection <A2>
                  _coll;
      Array <A2>  _array;
   };

   class Model3 : public DataModel <Model3> {};

   class A3
   :  public Object
   {
   public:
                  A3 () : _int (2LL), _float (3.5) {}
                  A3 (Default &) {}

      Int         _int;
      Float       _float;
   };

   class Root3
   :  public Object
   {
   public:
      Collection <A3>
                  _coll;
      Array <A3>  _array;
   };

                  TestNonDefaultCtor () = default;
   virtual        ~TestNonDefaultCtor () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestNonDefaultCtor (const TestNonDefaultCtor & rhs) = delete;
   TestNonDefaultCtor &
                  operator = (const TestNonDefaultCtor & rhs) = delete;
                  TestNonDefaultCtor (TestNonDefaultCtor && rhs) = delete;
   TestNonDefaultCtor &
                  operator = (TestNonDefaultCtor && rhs) = delete;
   bool           operator == (const TestNonDefaultCtor & rhs) const = delete;
   bool           operator != (const TestNonDefaultCtor & rhs) const = delete;



}; // class TestNonDefaultCtor



}  // namespace flip



//#include  "flip/TestNonDefaultCtor.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

