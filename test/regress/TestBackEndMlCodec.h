/*****************************************************************************

      TestBackEndMlCodec.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class TestBackEndMlCodec
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestBackEndMlCodec () = default;
   virtual        ~TestBackEndMlCodec () = default;

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



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestBackEndMlCodec (const TestBackEndMlCodec & rhs) = delete;
   TestBackEndMlCodec &    operator = (const TestBackEndMlCodec & rhs) = delete;
                  TestBackEndMlCodec (TestBackEndMlCodec && rhs) = delete;
   TestBackEndMlCodec &    operator = (TestBackEndMlCodec && rhs) = delete;
   bool           operator == (const TestBackEndMlCodec & rhs) const = delete;
   bool           operator != (const TestBackEndMlCodec & rhs) const = delete;



}; // class TestBackEndMlCodec



}  // namespace flip



//#include  "flip/TestBackEndMlCodec.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

