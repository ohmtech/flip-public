/*****************************************************************************

      TestDataConsumerProvider.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDataConsumerProvider.h"

#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/contrib/DataConsumerFile.h"
#include "flip/contrib/DataProviderFile.h"
#include "flip/detail/def.h"
#include "TestDef.h"

#include <limits>
#include <utility>

#if (flip_PLATFORM == flip_PLATFORM_IOS)
   // this file is required to be compiled as a Objective-C++ source file
   #import <Foundation/Foundation.h>
#endif

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

void  TestDataConsumerProvider::run ()
{
   run_000 ();
#if (flip_PLATFORM == flip_PLATFORM_IOS)
   run_001 (
      [[NSTemporaryDirectory() stringByAppendingPathComponent:@"test"] UTF8String]
   );

   run_001 (
      [[NSTemporaryDirectory() stringByAppendingPathComponent:@"\xE2\x99\xA5"] UTF8String]
   );
#else
   run_001 ("test");
   run_001 ("\xE2\x99\xA5");  // BLACK HEART SUIT
#endif
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestDataConsumerProvider::run_000 ()
{
   std::vector <uint8_t> data;

   {
      DataConsumerMemory consumer (data);

      consumer << true << false << 'a' << '\0' << uint8_t (0) << uint8_t (255);

      consumer << int32_t (0) << int32_t (1) << int32_t (INT_MIN) << int32_t (INT_MAX);
      consumer << uint32_t (0) << uint32_t (1) << uint32_t (UINT_MAX);

      consumer << int64_t (0) << int64_t (1) << int64_t (LLONG_MIN) << int64_t (LLONG_MAX);
      consumer << uint64_t (0) << uint64_t (1) << uint64_t (ULLONG_MAX);

      consumer << double (0.0) << double (1.0) << double (-1.0);
      consumer << std::numeric_limits <double>::max ();
      consumer << std::numeric_limits <double>::min ();
      consumer << std::numeric_limits <double>::lowest ();
      consumer << std::numeric_limits <double>::denorm_min ();
      consumer << std::numeric_limits <double>::epsilon ();
      consumer << std::numeric_limits <double>::infinity ();
      consumer << - std::numeric_limits <double>::infinity ();

      consumer << uint64_t (0) << uint64_t (ULONG_MAX);

      consumer << "this is a test";
      consumer << std::string ("this is another test");
   }

   {
      DataProviderMemory provider (data);

      flip_TEST (provider.tell () == 0);

      {
         bool b0, b1;
         char c0, c1;
         uint8_t u0, u1;

         provider >> b0 >> b1 >> c0 >> c1 >> u0 >> u1;
         flip_TEST (b0 == true);
         flip_TEST (b1 == false);
         flip_TEST (c0 == 'a');
         flip_TEST (c1 == '\0');
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 255);

         flip_TEST (provider.tell () == 6);
      }

      {
         int32_t i0, i1, i2, i3;
         uint32_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == INT_MIN);
         flip_TEST (i3 == INT_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == UINT_MAX);
      }

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }

      {
         double d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;

         provider >> d0 >> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7 >> d8 >> d9;
         flip_TEST (d0 == 0.0);
         flip_TEST (d1 == 1.0);
         flip_TEST (d2 == -1.0);
         flip_TEST (d3 == std::numeric_limits <double>::max ());
         flip_TEST (d4 == std::numeric_limits <double>::min ());
         flip_TEST (d5 == std::numeric_limits <double>::lowest ());
         flip_TEST (d6 == std::numeric_limits <double>::denorm_min ());
         flip_TEST (d7 == std::numeric_limits <double>::epsilon ());
         flip_TEST (d8 == std::numeric_limits <double>::infinity ());
         flip_TEST (d9 == - std::numeric_limits <double>::infinity ());
      }

      {
         uint64_t s0, s1;

         provider >> s0 >> s1;
         flip_TEST (s0 == 0);
         flip_TEST (s1 == ULONG_MAX);
      }

      {
         std::string s = provider.read_string (14);
         flip_TEST (s == "this is a test");
      }

      {
         std::string s = provider.read_string (20);
         flip_TEST (s == "this is another test");
      }

      provider.seek_start (0);
      flip_TEST (provider.tell () == 0);

      {
         bool b0, b1;
         char c0, c1;
         uint8_t u0, u1;

         provider >> b0 >> b1 >> c0 >> c1 >> u0 >> u1;
         flip_TEST (b0 == true);
         flip_TEST (b1 == false);
         flip_TEST (c0 == 'a');
         flip_TEST (c1 == '\0');
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 255);
      }

      provider.seek_start (34);
      flip_TEST (provider.tell () == 34);

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }


      provider.seek_start (0);
      provider.seek_relative (34);

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }

      provider.seek_relative (- (8 * 7 + 4 * 7));

      {
         int32_t i0, i1, i2, i3;
         uint32_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == INT_MIN);
         flip_TEST (i3 == INT_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == UINT_MAX);
      }

      provider.seek_start (0);
      flip_TEST (provider.tell () == 0);
      flip_CHECK_THROW (provider.seek_relative (-1));
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDataConsumerProvider::run_001 (const char * file_0)
{
   std::vector <uint8_t> data;

   {
      DataConsumerFile consumer (file_0);

      consumer << true << false << 'a' << '\0' << uint8_t (0) << uint8_t (255);

      consumer << int32_t (0) << int32_t (1) << int32_t (INT_MIN) << int32_t (INT_MAX);
      consumer << uint32_t (0) << uint32_t (1) << uint32_t (UINT_MAX);

      consumer << int64_t (0) << int64_t (1) << int64_t (LLONG_MIN) << int64_t (LLONG_MAX);
      consumer << uint64_t (0) << uint64_t (1) << uint64_t (ULLONG_MAX);

      consumer << double (0.0) << double (1.0) << double (-1.0);
      consumer << std::numeric_limits <double>::max ();
      consumer << std::numeric_limits <double>::min ();
      consumer << std::numeric_limits <double>::lowest ();
      consumer << std::numeric_limits <double>::denorm_min ();
      consumer << std::numeric_limits <double>::epsilon ();
      consumer << std::numeric_limits <double>::infinity ();
      consumer << - std::numeric_limits <double>::infinity ();

      consumer << uint64_t (0) << uint64_t (ULONG_MAX);

      consumer << "this is a test";
      consumer << std::string ("this is another test");
   }

   {
      DataProviderFile provider (file_0);

      flip_TEST (provider.tell () == 0);

      {
         bool b0, b1;
         char c0, c1;
         uint8_t u0, u1;

         provider >> b0 >> b1 >> c0 >> c1 >> u0 >> u1;
         flip_TEST (b0 == true);
         flip_TEST (b1 == false);
         flip_TEST (c0 == 'a');
         flip_TEST (c1 == '\0');
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 255);

         flip_TEST (provider.tell () == 6);
      }

      {
         int32_t i0, i1, i2, i3;
         uint32_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == INT_MIN);
         flip_TEST (i3 == INT_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == UINT_MAX);
      }

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }

      {
         double d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;

         provider >> d0 >> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7 >> d8 >> d9;
         flip_TEST (d0 == 0.0);
         flip_TEST (d1 == 1.0);
         flip_TEST (d2 == -1.0);
         flip_TEST (d3 == std::numeric_limits <double>::max ());
         flip_TEST (d4 == std::numeric_limits <double>::min ());
         flip_TEST (d5 == std::numeric_limits <double>::lowest ());
         flip_TEST (d6 == std::numeric_limits <double>::denorm_min ());
         flip_TEST (d7 == std::numeric_limits <double>::epsilon ());
         flip_TEST (d8 == std::numeric_limits <double>::infinity ());
         flip_TEST (d9 == - std::numeric_limits <double>::infinity ());
      }

      {
         uint64_t s0, s1;

         provider >> s0 >> s1;
         flip_TEST (s0 == 0);
         flip_TEST (s1 == ULONG_MAX);
      }

      {
         std::string s = provider.read_string (14);
         flip_TEST (s == "this is a test");
      }

      {
         std::string s = provider.read_string (20);
         flip_TEST (s == "this is another test");
      }

      provider.seek_start (0);
      flip_TEST (provider.tell () == 0);

      {
         bool b0, b1;
         char c0, c1;
         uint8_t u0, u1;

         provider >> b0 >> b1 >> c0 >> c1 >> u0 >> u1;
         flip_TEST (b0 == true);
         flip_TEST (b1 == false);
         flip_TEST (c0 == 'a');
         flip_TEST (c1 == '\0');
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 255);
      }

      provider.seek_start (34);
      flip_TEST (provider.tell () == 34);

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }

      provider.seek_start (0);
      provider.seek_relative (34);

      {
         int64_t i0, i1, i2, i3;
         uint64_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == LLONG_MIN);
         flip_TEST (i3 == LLONG_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == ULLONG_MAX);
      }

      provider.seek_relative (- (8 * 7 + 4 * 7));

      {
         int32_t i0, i1, i2, i3;
         uint32_t u0, u1, u2;

         provider >> i0 >> i1 >> i2 >> i3 >> u0 >> u1 >> u2;
         flip_TEST (i0 == 0);
         flip_TEST (i1 == 1);
         flip_TEST (i2 == INT_MIN);
         flip_TEST (i3 == INT_MAX);
         flip_TEST (u0 == 0);
         flip_TEST (u1 == 1);
         flip_TEST (u2 == UINT_MAX);
      }
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

