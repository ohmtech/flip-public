/*****************************************************************************

      TestUtml.h
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
#include "flip/Message.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"
#include "flip/Variant.h"



namespace flip
{



class TestUtml
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
      Bool        _bool;
      Int         _int;
      Float       _float;
      ObjectRef <A>
                  _ref_a;
      Blob        _blob;
   };

   class B
   :  public A
   {
   public:
      Bool        _bool2;
      Int         _int2;
      Float       _float2;
      Blob        _blob2;
      A           _a2;
      Message <>  _message2;
      Collection <A>
                  _coll;
      Variant <A> _variant;
   };

   class C
   :  public Object
   {
   public:
      B           _b;
   };

   class Root
   :  public Object
   {
   public:
      Bool        _bool;
      Int         _int;
      Float       _float;
      ObjectRef <A>
                  _ref_a;
      Blob        _blob;
      String      _string;
      A           _a;
      Collection <A>
                  _coll_a;
      Collection <B>
                  _coll_b;
      Array <A>   _array_a;
      Collection <C>
                  _coll_c;
      Message <>  _message;
   };

                  TestUtml () = default;
   virtual        ~TestUtml () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_002b ();
   void           run_002c ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_005b ();
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
   void           run_015b ();
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

   std::string    transform_whitespaces (const std::string & str);
   bool           contains (const std::string & text, const std::string & pattern);

   void           read (DocumentBase & document, const std::string & text);
   void           test_parsing_error (DocumentBase & document, const std::string & text, size_t line, size_t column);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestUtml (const TestUtml & rhs) = delete;
   TestUtml & operator = (const TestUtml & rhs) = delete;
                  TestUtml (TestUtml && rhs) = delete;
   TestUtml & operator = (TestUtml && rhs) = delete;
   bool           operator == (const TestUtml & rhs) const = delete;
   bool           operator != (const TestUtml & rhs) const = delete;



}; // class TestUtml



}  // namespace flip



//#include  "flip/TestUtml.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

