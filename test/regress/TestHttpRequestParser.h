/*****************************************************************************

      TestHttpRequestParser.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class TestHttpRequestParser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestHttpRequestParser () = default;
   virtual        ~TestHttpRequestParser () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestHttpRequestParser (const TestHttpRequestParser & rhs) = delete;
   TestHttpRequestParser &
                  operator = (const TestHttpRequestParser & rhs) = delete;
                  TestHttpRequestParser (TestHttpRequestParser && rhs) = delete;
   TestHttpRequestParser &
                  operator = (TestHttpRequestParser && rhs) = delete;
   bool           operator == (const TestHttpRequestParser & rhs) const = delete;
   bool           operator != (const TestHttpRequestParser & rhs) const = delete;



}; // class TestHttpRequestParser



}  // namespace flip



//#include  "flip/TestHttpRequestParser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

