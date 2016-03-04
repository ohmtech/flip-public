/*****************************************************************************

      TestKeyFloat.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestKeyFloat.h"

#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "TestDef.h"

#include <utility>
#include <set>

#include <climits>
#include <cassert>



flip_DISABLE_WARNINGS_BINARY_LITERALS



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestKeyFloat::run ()
{
   run_pre_01 ();
   run_pre_02 ();

   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre_01
==============================================================================
*/

void  TestKeyFloat::run_pre_01 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // binary literal support

   flip_TEST (mask_pre (0b00000000, 0b10000000) == 0b00000000);
   flip_TEST (mask_pre (0b01000000, 0b01110000) == 0b11000000);
   flip_TEST (mask_pre (0b00100000, 0b00110000) == 0b11100000);
   flip_TEST (mask_pre (0b00010000, 0b00011001) == 0b11110000);
   flip_TEST (mask_pre (0b00001000, 0b00001111) == 0b11111000);
   flip_TEST (mask_pre (0b00000101, 0b00000111) == 0b11111100);
   flip_TEST (mask_pre (0b00000010, 0b00000011) == 0b11111110);

#endif
}



/*
==============================================================================
Name : mask_pre
Description :
   Returns the mask for the most significant identical bits
==============================================================================
*/

uint8_t  TestKeyFloat::mask_pre (uint8_t l, uint8_t r)
{
   flip_TEST (l < r);

#if defined (__GNUC__) || defined (__clang__)
   uint8_t p = uint8_t (__builtin_clz (uint8_t (l ^ r)) - 24);
   // number of zero's in 8-bit

   uint8_t mask = uint8_t (~ ((1U << (8U - p)) - 1U));

   return mask;

#elif defined (_MSC_VER)
   // http://stackoverflow.com/questions/355967/how-to-use-msvc-intrinsics-to-get-the-equivalent-of-this-gcc-code

   unsigned long idx;
   _BitScanForward (&idx, uint8_t (l ^ r));

   uint8_t mask = uint8_t (~ ((1U << (8U - uint8_t ((31 - idx) - 24))) - 1U));

   return mask;

#endif
}



/*
==============================================================================
Name : run_pre_02
==============================================================================
*/

void  TestKeyFloat::run_pre_02 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // binary literal support

   test_pre ({}, 0);
   test_pre ({0b10000000}, 1);
   test_pre ({0b01000000}, 2);
   test_pre ({0b00100000}, 3);
   test_pre ({0b00010000}, 4);
   test_pre ({0b00001000}, 5);
   test_pre ({0b00000100}, 6);
   test_pre ({0b00000010}, 7);
   test_pre ({0b00000001}, 8);
   test_pre ({0b00000000, 0b10000000}, 9);

   // zero
   flip_CHECK_THROW (test_pre ({0x0}, 0));
   flip_CHECK_THROW (test_pre ({}, 1));

   // one
   flip_CHECK_THROW (test_pre ({0b10000001}, 8));
   flip_CHECK_THROW (test_pre ({0b10000000, 0b10000000}, 9));

   // least
   flip_CHECK_THROW (test_pre ({0b00000001}, 7));
   flip_CHECK_THROW (test_pre ({0b00000111}, 7));
   flip_CHECK_THROW (test_pre ({0b00000111}, 6));
   flip_CHECK_THROW (test_pre ({0b00000110}, 8));
   flip_CHECK_THROW (test_pre ({0b00000100}, 7));

#endif
}



/*
==============================================================================
Name : test_pre
==============================================================================
*/

KeyFloat TestKeyFloat::test_pre (std::vector <uint8_t> data, size_t nbr_bits)
{
   std::vector <uint8_t> kdata;
   StreamBinOut sbo (kdata);
   sbo << uint64_t (nbr_bits);
   sbo << data;

   StreamBinIn sbi (kdata);

   KeyFloat ret;
   ret.read (sbi);

   return ret;
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestKeyFloat::run_000 ()
{
   flip_TEST (KeyFloat::zero < KeyFloat::one);
   flip_TEST (! (KeyFloat::zero == KeyFloat::one));
   flip_TEST (KeyFloat::zero != KeyFloat::one);

   flip_TEST (KeyFloat::zero.is_valid ());
   flip_TEST (KeyFloat::one.is_valid ());

#if (flip_COMPILER != flip_COMPILER_MSVC) // binary literal support

   flip_TEST (generate ({0b00100000}).is_valid ());
   flip_TEST (generate ({0b00000000, 0b00000001}).is_valid ());

   flip_CHECK_THROW (generate ({0b00000000}));
   flip_CHECK_THROW (generate ({0b10000001}));
   flip_CHECK_THROW (generate ({0b10000000, 0b00000001}));

#endif
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestKeyFloat::run_001 ()
{
   {
      test (KeyFloat::zero, KeyFloat::one);
   }

#if (flip_COMPILER != flip_COMPILER_MSVC) // binary literal support

   {
      KeyFloat rkey = generate ({0b01100000});
      KeyFloat lkey = generate ({0b01000000});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b01100001});
      KeyFloat lkey = generate ({0b01100000});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b01100010});
      KeyFloat lkey = generate ({0b01100001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b01100001});
      KeyFloat lkey = generate ({0b01100000});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000010});
      KeyFloat lkey = generate ({0b00000001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000001, 0b10000000});
      KeyFloat lkey = generate ({0b00000001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000001, 0b00000000, 0b00000001});
      KeyFloat lkey = generate ({0b00000001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000001});
      KeyFloat lkey = generate ({0b00000000, 0b00000000, 0b00000001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000001});
      KeyFloat lkey = generate ({0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000001});

      test (lkey, rkey, 100);
   }

   {
      KeyFloat rkey = generate ({0b00000001, 0b11000000});
      KeyFloat lkey = generate ({0b00000001, 0b10000001});

      test (lkey, rkey, 100);
   }

#endif
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestKeyFloat::run_002 ()
{
   run_002 (KeyFloat::zero, KeyFloat::one, 8);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestKeyFloat::run_002 (const KeyFloat & left, const KeyFloat & right, size_t depth)
{
   if (depth == 0)
   {
      return;
   }

   KeyFloat key = test (left, right);

   run_002 (left, key, depth - 1);
   run_002 (key, right, depth - 1);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestKeyFloat::run_003 ()
{
   KeyFloat key = KeyFloat::one;

   for (int i = 0 ; i < 1000 ; ++i)
   {
      key = test (KeyFloat::zero, key);
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestKeyFloat::run_004 ()
{
   KeyFloat key = KeyFloat::zero;

   for (int i = 0 ; i < 1000 ; ++i)
   {
      key = test (key, KeyFloat::one);
   }
}



/*
==============================================================================
Name : generate
==============================================================================
*/

KeyFloat TestKeyFloat::generate (std::vector <uint8_t> data)
{
   size_t nbr_trailing_zero = 0;

   if (!data.empty ())
   {
      uint8_t last = data.back ();

      for (int i = 0 ; i < 8 ; ++i)
      {
         if ((last & 1U) != 0) break;

         ++nbr_trailing_zero;
         last >>= 1U;
      }
   }

   std::vector <uint8_t> kdata;
   StreamBinOut sbo (kdata);
   sbo << uint64_t (data.size () * 8 - nbr_trailing_zero);
   sbo << data;

   StreamBinIn sbi (kdata);

   KeyFloat ret;
   ret.read (sbi);

   return ret;
}



/*
==============================================================================
Name : test
==============================================================================
*/

KeyFloat TestKeyFloat::test (const KeyFloat & left, const KeyFloat & right)
{
   flip_TEST (left.is_valid ());
   flip_TEST (right.is_valid ());
   flip_TEST (left < right);

   KeyFloat key = KeyFloat::generate (left, right);

   flip_TEST (key.is_valid ());

   flip_TEST (left < key);
   flip_TEST (key < right);

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << key;

   StreamBinIn sbi (data);
   KeyFloat key2;
   sbi >> key2;

   flip_TEST (key == key2);

   return key;
}



/*
==============================================================================
Name : test
==============================================================================
*/

void  TestKeyFloat::test (const KeyFloat & left, const KeyFloat & right, int nbr)
{
   for (int i = 0 ; i < nbr ; ++i)
   {
      test (left, right);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

