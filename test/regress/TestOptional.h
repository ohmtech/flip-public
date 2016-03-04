/*****************************************************************************

      TestOptional.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/Optional.h"

#include <cstdint>



namespace flip
{



class TestOptional
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Content
   :  public Object
   {
   public:
      Int         _int;
   };

   class ContentA
   :  public Content
   {
   public:
      Int         _int_a;
   };

   class ContentB
   :  public Content
   {
   public:
      Int         _int_b;
   };

   class ContentC
   :  public Content
   {
   public:
                  ContentC (int64_t val) : _int_c (val) {}
                  ContentC (Default &) {}
      Int         _int_c;
   };

   class ContentOptional
   :  public Object
   {
   public:
      Optional <Content>
                  _optional;
   };

   using ContentOptionalColl = flip::Collection <ContentOptional>;

   class Root
   :  public Object
   {
   public:
      ContentOptionalColl
                  _coll;
   };

                  TestOptional () = default;
   virtual        ~TestOptional () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_pre ();
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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestOptional (const TestOptional & rhs) = delete;
   TestOptional &  operator = (const TestOptional & rhs) = delete;
                  TestOptional (TestOptional && rhs) = delete;
   TestOptional &  operator = (TestOptional && rhs) = delete;
   bool           operator == (const TestOptional & rhs) const = delete;
   bool           operator != (const TestOptional & rhs) const = delete;



}; // class TestOptional



}  // namespace flip



//#include  "flip/TestOptional.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

