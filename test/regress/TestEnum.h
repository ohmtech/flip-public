/*****************************************************************************

      TestEnum.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Enum.h"
#include "flip/DataModel.h"
#include "flip/Object.h"

#include <vector>
#include <list>
#include <map>

#include <cstdint>



namespace flip
{



class TestEnum
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   enum Enum1
   {
                  Value0,
                  Value1,
   };

   enum class Enum2
   {
                  Value0,
                  Value1,
   };

   class Root
   :  public Object
   {
   public:
      Enum <Enum1>
                  _enum1;
      Enum <Enum2>
                  _enum2;
   };

   class Model2 : public DataModel <Model2> {};

   enum EnumWrong1
   {
                  EnumWrong1_Value0 = 1,
   };

   class Model3 : public DataModel <Model3> {};

   enum EnumWrong2
   {
                  EnumWrong2_Value0,
                  EnumWrong2_Value1 = 2,
   };

   class Model4 : public DataModel <Model4> {};

   enum EnumUndefined
   {
                  EnumUndefined_Value,
   };

   class Root4
   :  public Object
   {
   public:
      Enum <EnumUndefined>
                  _enum;
   };


                  TestEnum () = default;
   virtual        ~TestEnum () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestEnum (const TestEnum & rhs) = delete;
   TestEnum &     operator = (const TestEnum & rhs) = delete;
                  TestEnum (TestEnum && rhs) = delete;
   TestEnum &     operator = (TestEnum && rhs) = delete;
   bool           operator == (const TestEnum & rhs) const = delete;
   bool           operator != (const TestEnum & rhs) const = delete;



}; // class TestEnum



}  // namespace flip



//#include  "flip/TestEnum.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

