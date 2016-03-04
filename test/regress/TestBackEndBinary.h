/*****************************************************************************

      TestBackEndBinary.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Message.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestBackEndBinary
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
                  A () = default;
                  A (int64_t vint, double vfloat) : _int (vint), _float (vfloat) {}

      Bool        _bool;
      Int         _int;
      Float       _float;
   };

   class B
   :  public A
   {
   public:
                  B () = default;
                  B (int64_t vint, double vfloat, int64_t vint2, double vfloat2) : A (vint, vfloat), _int2 (vint2), _float2 (vfloat2) {}

      Int         _int2;
      Float       _float2;
      Collection <A>
                  _coll;
   };

   class Root
   :  public Object
   {
   public:
      Bool        _bool;
      Int         _int;
      Float       _float;
      Blob        _blob;
      String      _string;
      A           _a;
      B           _b;
      ObjectRef <A>
                  _ref_a;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
      Array <A>   _array_a;
      Message <uint32_t>
                  _message;
   };

                  TestBackEndBinary () = default;
   virtual        ~TestBackEndBinary () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestBackEndBinary (const TestBackEndBinary & rhs) = delete;
   TestBackEndBinary &
                  operator = (const TestBackEndBinary & rhs) = delete;
                  TestBackEndBinary (TestBackEndBinary && rhs) = delete;
   TestBackEndBinary &
                  operator = (TestBackEndBinary && rhs) = delete;
   bool           operator == (const TestBackEndBinary & rhs) const = delete;
   bool           operator != (const TestBackEndBinary & rhs) const = delete;



}; // class TestBackEndBinary



}  // namespace flip



//#include  "flip/TestBackEndBinary.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

