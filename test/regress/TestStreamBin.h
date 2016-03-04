/*****************************************************************************

      TestStreamBin.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class TestStreamBin
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestStreamBin () = default;
   virtual        ~TestStreamBin () = default;

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
   void           run_008 ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_011b ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();
   void           run_015 ();
   void           run_016 ();
   void           run_017 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestStreamBin (const TestStreamBin & rhs) = delete;
   TestStreamBin &operator = (const TestStreamBin & rhs) = delete;
                  TestStreamBin (TestStreamBin && rhs) = delete;
   TestStreamBin &operator = (TestStreamBin && rhs) = delete;
   bool           operator == (const TestStreamBin & rhs) const = delete;
   bool           operator != (const TestStreamBin & rhs) const = delete;



}; // class TestStreamBin



}  // namespace flip



//#include  "flip/TestStreamBin.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

