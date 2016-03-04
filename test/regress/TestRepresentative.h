/*****************************************************************************

      TestRepresentative.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/Object.h"
#include "flip/detail/Type.h"



namespace flip
{



class TestRepresentative
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestRepresentative () = default;
   virtual        ~TestRepresentative () = default;

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

   class ABase
   :  public Object
   {
   public:
      Int         _int_base;
      Float       _float_base;
   };

   class A
   :  public ABase
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
      Float       _float;
      Collection <A>
                  _coll;
      A           _obj;
   };



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestRepresentative (const TestRepresentative & rhs) = delete;
   TestRepresentative &    operator = (const TestRepresentative & rhs) = delete;
                  TestRepresentative (TestRepresentative && rhs) = delete;
   TestRepresentative &    operator = (TestRepresentative && rhs) = delete;
   bool           operator == (const TestRepresentative & rhs) const = delete;
   bool           operator != (const TestRepresentative & rhs) const = delete;



}; // class TestRepresentative



}  // namespace flip



//#include  "flip/TestRepresentative.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

