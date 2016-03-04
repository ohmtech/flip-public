/*****************************************************************************

      TestLockFreeQueue.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/LockFreeQueue.h"



namespace flip
{



class TestLockFreeQueue
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestLockFreeQueue () = default;
   virtual        ~TestLockFreeQueue () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestLockFreeQueue (const TestLockFreeQueue & rhs) = delete;
   TestLockFreeQueue &
                  operator = (const TestLockFreeQueue & rhs) = delete;
                  TestLockFreeQueue (TestLockFreeQueue && rhs) = delete;
   TestLockFreeQueue &
                  operator = (TestLockFreeQueue && rhs) = delete;
   bool           operator == (const TestLockFreeQueue & rhs) const = delete;
   bool           operator != (const TestLockFreeQueue & rhs) const = delete;



}; // class TestLockFreeQueue



}  // namespace flip



//#include  "flip/TestLockFreeQueue.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

