/*****************************************************************************

      TestDocumentIO.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/ObjectRef.h"



namespace flip
{



class TestDocumentIO
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model
   :  public DataModel <Model>
   {
   };

   class A
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

   class B
   :  public Object
   {
   public:
      Int         _int;
   };

   class C
   :  public A
   {
   public:
      Float       _float;
      B           _b;
      ObjectRef <B>
                  _b_ref;
      Collection <B>
                  _b_coll;
   };

   class Root
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
      A           _a;
      ObjectRef <A>
                  _a_ref;
      Collection <A>
                  _a_coll;
      B           _b;
      ObjectRef <B>
                  _b_ref;
      Collection <B>
                  _b_coll;
      C           _c;
      ObjectRef <C>
                  _c_ref;
      Collection <C>
                  _c_coll;
   };

                  TestDocumentIO () = default;
   virtual        ~TestDocumentIO () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestDocumentIO (const TestDocumentIO & rhs) = delete;
   TestDocumentIO &
                  operator = (const TestDocumentIO & rhs) = delete;
                  TestDocumentIO (TestDocumentIO && rhs) = delete;
   TestDocumentIO &
                  operator = (TestDocumentIO && rhs) = delete;
   bool           operator == (const TestDocumentIO & rhs) const = delete;
   bool           operator != (const TestDocumentIO & rhs) const = delete;



}; // class TestDocumentIO



}  // namespace flip



//#include  "flip/TestDocumentIO.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

