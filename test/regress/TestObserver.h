/*****************************************************************************

      TestObserver.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"



namespace flip
{



class TestObserver
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

   class B
   :  public A
   {
   public:
      Int         _int2;
      Float       _float2;
      Collection <A>
                  _coll;
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
   };

   class Observer
   :  public DocumentObserver <Root>
   {
   public:
      // DocumentObserver <Root>
      virtual void
                  document_changed (Root & root);

   private:
      size_t      _cnt = 0;
   };

                  TestObserver () = default;
   virtual        ~TestObserver () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestObserver (const TestObserver & rhs) = delete;
   TestObserver & operator = (const TestObserver & rhs) = delete;
                  TestObserver (TestObserver && rhs) = delete;
   TestObserver & operator = (TestObserver && rhs) = delete;
   bool           operator == (const TestObserver & rhs) const = delete;
   bool           operator != (const TestObserver & rhs) const = delete;



}; // class TestObserver



}  // namespace flip



//#include  "flip/TestObserver.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

