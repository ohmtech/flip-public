/*****************************************************************************

      TestDocumentHub.h
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



class TestDocumentHub
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

                  TestDocumentHub () = default;
   virtual        ~TestDocumentHub () = default;

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
                  TestDocumentHub (const TestDocumentHub & rhs) = delete;
   TestDocumentHub &
                  operator = (const TestDocumentHub & rhs) = delete;
                  TestDocumentHub (TestDocumentHub && rhs) = delete;
   TestDocumentHub &
                  operator = (TestDocumentHub && rhs) = delete;
   bool           operator == (const TestDocumentHub & rhs) const = delete;
   bool           operator != (const TestDocumentHub & rhs) const = delete;



}; // class TestDocumentHub



}  // namespace flip



//#include  "flip/TestDocumentHub.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

