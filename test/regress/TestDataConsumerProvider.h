/*****************************************************************************

      TestDataConsumerProvider.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class TestDataConsumerProvider
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestDataConsumerProvider () = default;
   virtual        ~TestDataConsumerProvider () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 (const char * file_0);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestDataConsumerProvider (const TestDataConsumerProvider & rhs) = delete;
   TestDataConsumerProvider &
                  operator = (const TestDataConsumerProvider & rhs) = delete;
                  TestDataConsumerProvider (TestDataConsumerProvider && rhs) = delete;
   TestDataConsumerProvider &
                  operator = (TestDataConsumerProvider && rhs) = delete;
   bool           operator == (const TestDataConsumerProvider & rhs) const = delete;
   bool           operator != (const TestDataConsumerProvider & rhs) const = delete;



}; // class TestDataConsumerProvider



}  // namespace flip



//#include  "flip/TestDataConsumerProvider.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

