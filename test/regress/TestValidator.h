/*****************************************************************************

      TestValidator.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/DataModel.h"
#include "flip/DocumentValidator.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"



namespace flip
{



class TestValidator
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Root
   :  public Object
   {
   public:
      Int         _number;
      Float       _distance;
   };

   class Validator
   :  public DocumentValidator <Root>
   {
   public:
                  Validator () = default;
      virtual     ~Validator () = default;

      virtual void
                  validate (Root & root) override;
   };

                  TestValidator () = default;
   virtual        ~TestValidator () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestValidator (const TestValidator & rhs) = delete;
   TestValidator &   operator = (const TestValidator & rhs) = delete;
                  TestValidator (TestValidator && rhs) = delete;
   TestValidator &   operator = (TestValidator && rhs) = delete;
   bool           operator == (const TestValidator & rhs) const = delete;
   bool           operator != (const TestValidator & rhs) const = delete;



}; // class TestValidator



}  // namespace flip



//#include  "flip/TestValidator.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

