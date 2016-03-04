/*****************************************************************************

      TestDocument.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Enum.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/Message.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestDocument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
                  A () = default;
                  A (const A &) = default;
                  A (A && rhs);

      A &         operator = (const A &) = default;

      Int         _int;
      Float       _float;
      ObjectRef <A>
                  _ref_a;
   };

   class B
   :  public A
   {
   public:
                  B () = default;
                  B (const B &) = default;
                  B (B && rhs);

      B &         operator = (const B &) = default;

      Int         _int2;
      Float       _float2;
      Collection <A>
                  _coll;
   };

   class Root
   :  public Object
   {
   public:
      enum class C
      {
                  x0, x1
      };
      Bool        _bool;
      Int         _int;
      Float       _float;
      ObjectRef <A>
                  _ref_a;
      Blob        _blob;
      String      _string;
      A           _a;
      B           _b;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
      Array <A>   _array_a;
      Enum <C>    _enum;
   };

                  TestDocument () = default;
   virtual        ~TestDocument () = default;

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
   void           run_008 ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();
   void           run_015 ();
   void           run_016 ();
   void           run_017 ();
   void           run_018 ();
   void           run_019 ();
   void           run_020 ();
   void           run_021 ();
   void           run_022 ();
   void           run_023 ();
   void           run_024 ();
   void           run_025 ();
   void           run_026 ();
   void           run_027 ();
   void           run_028 ();
   void           run_029 ();
   void           run_030 ();
   void           run_031 ();
   void           run_032 ();
   void           run_033 ();
   void           run_034 ();
   void           run_035 ();
   void           run_036 ();
   void           run_037 ();
   void           run_038 ();

   void           test (bool) {} // COV_NF_LINE



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestDocument (const TestDocument & rhs) = delete;
   TestDocument & operator = (const TestDocument & rhs) = delete;
                  TestDocument (TestDocument && rhs) = delete;
   TestDocument & operator = (TestDocument && rhs) = delete;
   bool           operator == (const TestDocument & rhs) const = delete;
   bool           operator != (const TestDocument & rhs) const = delete;



}; // class TestDocument



}  // namespace flip



//#include  "flip/TestDocument.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

