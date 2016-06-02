/*****************************************************************************

      TestTransaction.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/DocumentValidator.h"
#include "flip/Enum.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/Message.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestTransaction
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
      Bool        _bool;
   };

   class C
   :  public Object
   {
   public:
      enum class D
      {
                  x0, x1, x2
      };

      Bool        _bool;
      Blob        _blob;
      String      _string;
      Collection <A>
                  _coll;
      Array <A>   _array;
      ObjectRef <A>
                  _ref;
      Message <>  _message;
      Enum <D>    _enum;
   };

   class Root
   :  public Object
   {
   public:
      enum class D
      {
                  x0, x1, x2
      };
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
      Bool        _bool;
      Blob        _blob;
      String      _string;
      Bool        _bool2;
      Blob        _blob2;
      String      _string2;
      Collection <C>
                  _coll_c;
      Message <uint32_t>
                  _message;
      Array <A>   _array_a;
      Enum <D>    _enum;
      Enum <D>    _enum2;
   };

   class ValidatorFail
   :  public DocumentValidator <Root>
   {
   public:
      // DocumentValidator <Root>
      virtual void
                  validate (Root & root);
      bool        called_flag = false;
   };

                  TestTransaction () = default;
   virtual        ~TestTransaction () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_pre ();
   void           run_pre2 ();

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
   void           run_039 ();

   void           run_040 ();
   void           run_041 ();
   void           run_042 ();
   void           run_043 ();
   void           run_044 ();
   void           run_045 ();
   void           run_046 ();

   void           run_047 ();
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

   void           run_066 ();
   void           run_067 ();
   void           run_068 ();
   void           run_069 ();
   void           run_070 ();
   void           run_071 ();

   void           run_072 ();
   void           run_073 ();
   void           run_074 ();
   void           run_075 ();

   void           run_076 ();
   void           run_077 ();

   void           run_078 ();
   void           run_079 ();
   void           run_080 ();

   void           run_081 ();
   void           run_082 ();
   void           run_083 ();
   void           run_084 ();
   void           run_085 ();
   void           run_086 ();
   void           run_087 ();
   void           run_088 ();
   void           run_089 ();
   void           run_090 ();

   void           run_091 ();
   void           run_092 ();

   void           run_093 ();
   void           run_094 ();

   void           run_095 ();
   void           run_096 ();

   void           run_097 ();
   void           run_098 ();

   void           run_099 ();

   void           run_100 ();

   void           run_101 ();
   void           run_101b ();
   void           run_102 ();
   void           run_103 ();

   void           run_104 ();
   void           run_105 ();
   void           run_106 ();
   void           run_107 ();
   void           run_108 ();
   void           run_109 ();
   void           run_109b ();
   void           run_110 ();
   void           run_110b ();
   void           run_111 ();
   void           run_112 ();
   void           run_113 ();
   void           run_114 ();
   void           run_115 ();
   void           run_116 ();

   void           run_117 ();
   void           run_118 ();
   void           run_119 ();
   void           run_120 ();
   void           run_121 ();
   void           run_122 ();
   void           run_123 ();
   void           run_124 ();
   void           run_125 ();
   void           run_126 ();
   void           run_127 ();
   void           run_128 ();
   void           run_129 ();
   void           run_130 ();
   void           run_131 ();
   void           run_132 ();
   void           run_133 ();
   void           run_134 ();
   void           run_135 ();

   void           run_136 ();
   void           run_137 ();
   void           run_137b ();
   void           run_138 ();
   void           run_138b ();
   void           run_139 ();
   void           run_139b ();

   void           run_140 ();
   void           run_140b ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestTransaction (const TestTransaction & rhs) = delete;
   TestTransaction &
                  operator = (const TestTransaction & rhs) = delete;
                  TestTransaction (TestTransaction && rhs) = delete;
   TestTransaction &
                  operator = (TestTransaction && rhs) = delete;
   bool           operator == (const TestTransaction & rhs) const = delete;
   bool           operator != (const TestTransaction & rhs) const = delete;



}; // class TestTransaction



}  // namespace flip



//#include  "flip/TestTransaction.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

