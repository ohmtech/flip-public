/*****************************************************************************

      TestRef.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestRef.h"

#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "TestDef.h"

#include "flip/Ref.h"

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

void  TestRef::run ()
{
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestRef::run_000 ()
{
   Ref ref = Ref::get_first (4567, 123);

   flip_TEST (ref.user () == 4567);
   flip_TEST (ref.actor () == 123);
   flip_TEST (ref.obj () == 1);

   Ref ref2 = Ref::get_first (4567, 123);

   flip_TEST (ref2.user () == 4567);
   flip_TEST (ref2.actor () == 123);
   flip_TEST (ref2.obj () == 1);

   flip_TEST (ref == ref2);

   Ref ref3 = Ref::get_first (4568, 123);

   flip_TEST (ref3.user () == 4568);
   flip_TEST (ref3.actor () == 123);
   flip_TEST (ref3.obj () == 1);

   flip_TEST (ref != ref3);

   Ref ref4 = Ref::get_first (4567, 124);

   flip_TEST (ref4.user () == 4567);
   flip_TEST (ref4.actor () == 124);
   flip_TEST (ref4.obj () == 1);

   flip_TEST (ref != ref4);

   auto ref5 = ref;

   flip_TEST (ref == ref5);

   auto ref6 = std::move (ref);

   flip_TEST (ref == ref6);

   ++ref6;

   flip_TEST (ref6.user () == 4567);
   flip_TEST (ref6.actor () == 123);
   flip_TEST (ref6.obj () == 2);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestRef::run_001 ()
{
   Ref ref7 = Ref::get_first (ULLONG_MAX, ULLONG_MAX);
   flip_TEST (ref7.user () == ULLONG_MAX);
   flip_TEST (ref7.actor () == ULLONG_MAX);
   flip_TEST (ref7.obj () == 1);

   ++ref7;

   flip_TEST (ref7.user () == ULLONG_MAX);
   flip_TEST (ref7.actor () == ULLONG_MAX);
   flip_TEST (ref7.obj () == 2);

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      ref7.write (sbo);
      size_t i = 0;
      for (; i < 8 ; ++i) // user
      {
         flip_TEST (data [i] == 255);
      }

      for (; i < 8 + 8 ; ++i) // actor
      {
         flip_TEST (data [i] == 255);
      }

      for (; i < 8 + 8 + 7 ; ++i) // obj
      {
         flip_TEST (data [i] == 0);
      }

      for (; i < 8 + 8 + 8 ; ++i) // obj
      {
         flip_TEST (data [i] == 2);
      }

      StreamBinIn sbi (data);

      Ref ref7b;
      ref7b.read (sbi);

      flip_TEST (ref7b.user () == ULLONG_MAX);
      flip_TEST (ref7b.actor () == ULLONG_MAX);
      flip_TEST (ref7b.obj () == 2);
      flip_TEST (ref7 == ref7b);
      flip_TEST (! (ref7 != ref7b));
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestRef::run_002 ()
{
   Ref ref8 = Ref::get_first (0x0123456789abcdef, 0);

   flip_TEST (ref8.user () == 0x0123456789abcdef);
   flip_TEST (ref8.actor () == 0);
   flip_TEST (ref8.obj () == 1);

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      ref8.write (sbo);

      flip_TEST (data [0] == 0x01);
      flip_TEST (data [1] == 0x23);
      flip_TEST (data [7] == 0xef);

      size_t i = 0;
      for (; i < 8 ; ++i) // user
      {
         uint8_t x = uint8_t (((2 * i) << 4) | (2 * i + 1));

         flip_TEST (data [i] == x);
      }


      for (; i < 8 + 8 ; ++i) // actor
      {
         flip_TEST (data [i] == 0);
      }

      for (; i < 8 + 8 + 7 ; ++i) // obj
      {
         flip_TEST (data [i] == 0);
      }

      for (; i < 8 + 8 + 8 ; ++i) // obj
      {
         flip_TEST (data [i] == 1);
      }

      StreamBinIn sbi (data);

      Ref ref8b;
      ref8b.read (sbi);

      flip_TEST (ref8b.user () == 0x0123456789abcdef);
      flip_TEST (ref8b.actor () == 0);
      flip_TEST (ref8b.obj () == 1);
      flip_TEST (ref8 == ref8b);
      flip_TEST (! (ref8 != ref8b));
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestRef::run_003 ()
{
   Ref ref9 = Ref::get_first (1, 0x0123456789abcdef);

   flip_TEST (ref9.user () == 1);
   flip_TEST (ref9.actor () == 0x0123456789abcdef);
   flip_TEST (ref9.obj () == 1);

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      ref9.write (sbo);

      flip_TEST (data [8] == 0x01);
      flip_TEST (data [9] == 0x23);
      flip_TEST (data [15] == 0xef);

      size_t i = 0;

      for (; i < 7 ; ++i) // user
      {
         flip_TEST (data [i] == 0);
      }

      for (; i < 8 ; ++i) // user
      {
         flip_TEST (data [i] == 1);
      }

      for (; i < 8 + 8 ; ++i) // actor
      {
         uint8_t x = uint8_t (((2 * (i - 8)) << 4) | (2 * (i - 8) + 1));

         flip_TEST (data [i] == x);
      }

      for (; i < 8 + 8 + 7 ; ++i) // obj
      {
         flip_TEST (data [i] == 0);
      }

      for (; i < 8 + 8 + 8 ; ++i) // obj
      {
         flip_TEST (data [i] == 1);
      }

      StreamBinIn sbi (data);

      Ref ref9b;
      ref9b.read (sbi);

      flip_TEST (ref9b.user () == 1);
      flip_TEST (ref9b.actor () == 0x0123456789abcdef);
      flip_TEST (ref9b.obj () == 1);
      flip_TEST (ref9 == ref9b);
      flip_TEST (! (ref9 != ref9b));
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestRef::run_004 ()
{
   Ref ref10 = Ref::null;

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      ref10.write (sbo);

      size_t i = 0;
      for (; i < 3 * 8 ; ++i) // user
      {
         flip_TEST (data [i] == 0);
      }

      StreamBinIn sbi (data);

      Ref ref10b;
      ref10b.read (sbi);

      flip_TEST (ref10b.user () == 0);
      flip_TEST (ref10b.actor () == 0);
      flip_TEST (ref10b.obj () == 0);
      flip_TEST (ref10 == ref10b);
      flip_TEST (! (ref10 != ref10b));
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestRef::run_005 ()
{
   {
      Ref ref = Ref::make (0, Ref::get_root_actor (), ULLONG_MAX);
      flip_CHECK_THROW (++ref);
   }

   {
      Ref ref = Ref::make (1, 0, ULLONG_MAX);
      flip_CHECK_THROW (ref + 1);
   }

   {
      Ref ref = Ref::make (0, Ref::get_root_actor (), ULLONG_MAX);
      flip_CHECK_THROW (ref += 1);
   }

   {
      Ref ref = Ref::make (1, 0, ULLONG_MAX - 1ULL);
      flip_CHECK_THROW (ref + 2);
   }

   {
      Ref ref = Ref::make (0, Ref::get_root_actor (), ULLONG_MAX - 1ULL);
      flip_CHECK_THROW (ref += 2);
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestRef::run_006 ()
{
   {
      flip_TEST (!(Ref::make (1, 0, 1) < Ref::make (1, 0, 1)));
      flip_TEST (Ref::make (0, 0, 0) < Ref::make (1, 0, 1));
      flip_TEST (!(Ref::make (1, 0, 1) < Ref::make (0, 0, 0)));

      flip_TEST (!(Ref::make (0, Ref::get_root_actor (), 1) < Ref::make (0, Ref::get_root_actor (), 1)));
      flip_TEST (Ref::make (0, 0, 0) < Ref::make (0, Ref::get_root_actor (), 1));
      flip_TEST (!(Ref::make (0, Ref::get_root_actor (), 1) < Ref::make (0, 0, 0)));

      flip_TEST (!(Ref::make (0, Ref::get_root_actor (), 1) < Ref::make (0, Ref::get_root_actor (), 1)));
      flip_TEST (Ref::make (0, 0, 0) < Ref::make (0, Ref::get_root_actor (), 1));
      flip_TEST (!(Ref::make (0, Ref::get_root_actor (), 1) < Ref::make (0, 0, 0)));
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

