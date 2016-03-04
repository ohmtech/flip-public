/*****************************************************************************

      TestConsumerTextOut.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class TestConsumerTextOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestConsumerTextOut () = default;
   virtual        ~TestConsumerTextOut () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestConsumerTextOut (const TestConsumerTextOut & rhs) = delete;
   TestConsumerTextOut &      operator = (const TestConsumerTextOut & rhs) = delete;
                  TestConsumerTextOut (TestConsumerTextOut && rhs) = delete;
   TestConsumerTextOut &      operator = (TestConsumerTextOut && rhs) = delete;
   bool           operator == (const TestConsumerTextOut & rhs) const = delete;
   bool           operator != (const TestConsumerTextOut & rhs) const = delete;



}; // class TestConsumerTextOut



}  // namespace flip



//#include  "flip/TestConsumerTextOut.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

