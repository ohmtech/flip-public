/*****************************************************************************

      TestArray.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Bool.h"
#include "flip/Array.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"



namespace flip
{



class TestArray
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
                  A () = default;
                  A (int64_t int_, double float_) : _int (int_), _float (float_) {}

      bool        operator < (const A & rhs) const // COV_NF_START
      {
         if (_int < rhs._int) return true;
         if (_int > rhs._int) return false;

         return _float < rhs._float;
      }  // COV_NF_END

      Int         _int;
      Float       _float;
   };

   class A2
   :  public A
   {
   public:
      Int         _int2;
   };

   class B
   :  public Object
   {
   public:
      Array <A>   _array;
      Int         _int;
   };

   class C
   :  public Object
   {
   public:
                  C (int64_t int_) : _int (int_) {}
                  C (Default &) {}
                  C (const C &) = default;

      Int         _int;
   };

   class Root
   :  public Object
   {
   public:
      Array <A>   _array;
      Array <A>   _array2;
      B           _b;
      B           _b2;
      Array <B>   _array3;
      Array <C>   _array4;
   };

                  TestArray () = default;
   virtual        ~TestArray () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           check_concept_iterator ();
   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
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
   void           run_015 ();
   void           run_016 ();
   void           run_017 ();
   void           run_018 ();
   void           run_019 ();
   void           run_020 ();
   void           run_020b ();
   void           run_020c ();
   void           run_021 ();
   void           run_022 ();
   void           run_022b ();
   void           run_023 ();
   void           run_024 ();
   void           run_025 ();
   void           run_026 ();
   void           run_027 ();
   void           run_027b ();
   void           run_027c ();
   void           run_027d ();
   void           run_027e ();
   void           run_027f ();
   void           run_028 ();
   void           run_029 ();
   void           run_030 ();
   void           run_031 ();
   void           run_032 ();
   void           run_032b ();
   void           run_033 ();
   void           run_034 ();
   void           run_037 ();
   void           run_038 ();
   void           run_039 ();
   void           run_040 ();
   void           run_041 ();
   void           run_042 ();
   void           run_043 ();
   void           run_044 ();
   void           run_045 ();
   void           run_046 ();
   void           run_048 ();
   void           run_049 ();
   void           run_050 ();
   void           run_051 ();
   void           run_052 ();
   void           run_053 ();
   void           run_054 ();
   void           run_055 ();
   void           run_056 ();
   void           run_057 ();
   void           run_058 ();
   void           run_059 ();
   void           run_060 ();
   void           run_061 ();
   void           run_062 ();
   void           run_063 ();
   void           run_064 ();
   void           run_065 ();
   void           run_065b ();
   void           run_066 ();
   void           run_066b ();
   void           run_066c ();
   void           run_066d ();
   void           run_067 ();
   void           run_068 ();
   void           run_068b ();
   void           run_068c ();
   void           run_068d ();
   void           run_069 ();
   void           run_070 ();
   void           run_071 ();
   void           run_071b ();

   /*void            document_changed (Array <A> & array);*/



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestArray (const TestArray & rhs) = delete;
   TestArray &    operator = (const TestArray & rhs) = delete;
                  TestArray (TestArray && rhs) = delete;
   TestArray &    operator = (TestArray && rhs) = delete;
   bool           operator == (const TestArray & rhs) const = delete;
   bool           operator != (const TestArray & rhs) const = delete;



}; // class TestArray



}  // namespace flip



//#include  "flip/TestArray.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

