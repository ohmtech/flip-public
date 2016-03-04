/*****************************************************************************

      TestAbstractClass.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/detail/def.h"

#include <cstdint>



namespace flip
{



class TestAbstractClass
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Content
   :  public Object
   {
   public:
                  Content () = default;

#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility in case of non-accessible functions
#else
                  Content (const Content & rhs) = delete;
#endif

      Int         _int;

      virtual void
                  foo () = 0;
   };

   class ContentA
   :  public Content
   {
   public:
      Int         _int_a;

      virtual void
                  foo () override;
   };

   class ContentB
   :  public Content
   {
   public:
      Int         _int_b;

      virtual void
                  foo () override;
   };

#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility in case of non-accessible functions

#else
   class ContentC
   :  public Content
   {
   public:
                  ContentC () = default;
                  ContentC (const ContentC & rhs) = delete;

      Int         _int_c;

      virtual void
                  foo () override;
   };
#endif

   using ContentColl = flip::Collection <Content>;
   using ContentArray = flip::Array <Content>;

   class Root
   :  public Object
   {
   public:
      ContentColl _coll;
      ContentArray
                  _array;
   };

   // for type traits test

   class A
   {
   public:
                  A (const A &) = default;
   };

#if (flip_COMPILER == flip_COMPILER_MSVC) && (_MSC_VER == 1800)
   // MSVC 12.0 does not detect well constructibility in case of non-accessible functions

#else
   class B
   {
   public:
                  B (const B &) = delete;
   };

   class C
   {
   private:
                  C (const C &) = default;
   };
#endif

   class D
   {
   public:
                  D (const D &) = default;
      virtual     ~D () = 0;
   };

                  TestAbstractClass () = default;
   virtual        ~TestAbstractClass () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_pre ();
   void           run_000 ();
   void           run_001 ();
   void           run_001b ();
   void           run_001c ();
   void           run_002 ();
   void           run_002b ();
   void           run_002c ();
   void           run_003 ();
   void           run_003b ();
   void           run_004 ();
   void           run_004b ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestAbstractClass (const TestAbstractClass & rhs) = delete;
   TestAbstractClass &
                  operator = (const TestAbstractClass & rhs) = delete;
                  TestAbstractClass (TestAbstractClass && rhs) = delete;
   TestAbstractClass &
                  operator = (TestAbstractClass && rhs) = delete;
   bool           operator == (const TestAbstractClass & rhs) const = delete;
   bool           operator != (const TestAbstractClass & rhs) const = delete;



}; // class TestAbstractClass



}  // namespace flip



//#include  "flip/TestAbstractClass.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

