/*****************************************************************************

      TestBackEndIRDiff.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Enum.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Message.h"
#include "flip/ObjectRef.h"



namespace flip
{



class TestBackEndIRDiff
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   enum E
   {
      E0 = 0,
      E1,
   };

   class A
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

   class B
   :  public A
   {
   public:
      Int         _int2;
      Float       _float2;
      Collection <A>
                  _coll;
   };

   class C
   :  public A
   {
   public:
      Enum <E>    _enum;
   };

   class Root
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
      A           _a;
      B           _b;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
      ObjectRef <A>
                  _ref_a;
      Array <A>   _array_a;
      Message <>  _message;
   };

                  TestBackEndIRDiff () = default;
   virtual        ~TestBackEndIRDiff () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();
   void           run_001b ();
   void           run_002 ();
   void           run_002b ();
   void           run_003 ();
   void           run_003b ();
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

   bool           equal (BackEndIR & lhs, BackEndIR rhs);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestBackEndIRDiff (const TestBackEndIRDiff & rhs) = delete;
   TestBackEndIRDiff &
                  operator = (const TestBackEndIRDiff & rhs) = delete;
                  TestBackEndIRDiff (TestBackEndIRDiff && rhs) = delete;
   TestBackEndIRDiff &
                  operator = (TestBackEndIRDiff && rhs) = delete;
   bool           operator == (const TestBackEndIRDiff & rhs) const = delete;
   bool           operator != (const TestBackEndIRDiff & rhs) const = delete;



}; // class TestBackEndIRDiff



}  // namespace flip



//#include  "flip/TestBackEndIRDiff.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

