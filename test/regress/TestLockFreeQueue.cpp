/*****************************************************************************

      TestLockFreeQueue.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestLockFreeQueue.h"

#include "TestDef.h"

#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include <climits>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestLockFreeQueue::run ()
{
   run_000 ();
   run_001 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestLockFreeQueue::run_000 ()
{
   LockFreeQueue <int> queue;

   int miss = 0;

   std::thread thread ([&queue, &miss](){
      int i = 0;

      while (i < 100000)
      {
         int * i_ptr = queue.pop ();
         if (i_ptr != 0)
         {
            flip_TEST (i == *i_ptr);
            ++i;
         }
         else
         {
            ++miss;
         }
      }

   });

   for (int i = 0 ; i < 100000 ; ++i) queue.push (i);

   thread.join ();

#if 0
   std::cout << "run_000: miss: " << miss << std::endl;
#endif
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestLockFreeQueue::run_001 ()
{
   LockFreeQueue <int> queue;

   std::thread thread ([&queue](){
      for (int i = 0 ; i < 100000 ; ++i) queue.push (i);
   });

   int i = 0;
   int miss = 0;

   while (i < 100000)
   {
      int * i_ptr = queue.pop ();
      if (i_ptr != 0)
      {
         flip_TEST (i == *i_ptr);
         ++i;
      }
      else
      {
         ++miss;
      }
   }

   thread.join ();

#if 0
   std::cout << "run_001: miss: " << miss << std::endl;
#endif
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

