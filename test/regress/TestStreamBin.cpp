/*****************************************************************************

      TestStreamBin.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestStreamBin.h"

#include "flip/Ref.h"
#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "TestDef.h"

#include <limits>
#include <utility>
#include <vector>

#include <cmath>
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

void  TestStreamBin::run ()
{
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   // run_007 (); // removed (was size_t)
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_011b ();
   run_012 ();
   run_013 ();
   run_014 ();
   run_015 ();
   run_016 ();
   run_017 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestStreamBin::run_000 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << false;
      flip_TEST (data [0] == 0);

      sbo << true;
      flip_TEST (data [1] == 1);
   }

   {
      StreamBinIn sbi (data);

      bool val = true;
      sbi >> val;
      flip_TEST (val == false);

      sbi >> val;
      flip_TEST (val == true);
   }

   {
      data.clear ();
      data.emplace_back (uint8_t (2));

      StreamBinIn sbi (data);

      bool val;

      flip_CHECK_THROW (sbi >> val;)
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestStreamBin::run_001 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << char (0);
      flip_TEST (data [0] == 0);

      sbo << 'H';
      flip_TEST (data [1] == 'H');
   }

   {
      StreamBinIn sbi (data);

      char val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 'H');

      flip_CHECK_THROW (sbi >> val;)
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestStreamBin::run_002 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << uint8_t (0);
      flip_TEST (data [0] == 0);

      sbo << uint8_t (255);
      flip_TEST (data [1] == 255);

      sbo << uint8_t (7);
      flip_TEST (data [2] == 7);
   }

   {
      StreamBinIn sbi (data);

      uint8_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 255);

      sbi >> val;
      flip_TEST (val == 7);

      flip_CHECK_THROW (sbi >> val;)
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestStreamBin::run_003 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << int32_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << int32_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << int32_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << int32_t (305419896);
      flip_TEST (data [pos++] == 0x12);
      flip_TEST (data [pos++] == 0x34);
      flip_TEST (data [pos++] == 0x56);
      flip_TEST (data [pos++] == 0x78);
   }

   {
      StreamBinIn sbi (data);

      int32_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == -1);

      sbi >> val;
      flip_TEST (val == 305419896);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      int32_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestStreamBin::run_004 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << uint32_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << uint32_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << uint32_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << uint32_t (305419896);
      flip_TEST (data [pos++] == 0x12);
      flip_TEST (data [pos++] == 0x34);
      flip_TEST (data [pos++] == 0x56);
      flip_TEST (data [pos++] == 0x78);
   }

   {
      StreamBinIn sbi (data);

      uint32_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == uint32_t (-1));

      sbi >> val;
      flip_TEST (val == 305419896);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      uint32_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestStreamBin::run_005 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << int64_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << int64_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << int64_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << int64_t (81985529216486895);
      flip_TEST (data [pos++] == 0x01);
      flip_TEST (data [pos++] == 0x23);
      flip_TEST (data [pos++] == 0x45);
      flip_TEST (data [pos++] == 0x67);
      flip_TEST (data [pos++] == 0x89);
      flip_TEST (data [pos++] == 0xab);
      flip_TEST (data [pos++] == 0xcd);
      flip_TEST (data [pos++] == 0xef);
   }

   {
      StreamBinIn sbi (data);

      int64_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == -1);

      sbi >> val;
      flip_TEST (val == 81985529216486895);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      int64_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestStreamBin::run_006 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << uint64_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << uint64_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << uint64_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << uint64_t (81985529216486895);
      flip_TEST (data [pos++] == 0x01);
      flip_TEST (data [pos++] == 0x23);
      flip_TEST (data [pos++] == 0x45);
      flip_TEST (data [pos++] == 0x67);
      flip_TEST (data [pos++] == 0x89);
      flip_TEST (data [pos++] == 0xab);
      flip_TEST (data [pos++] == 0xcd);
      flip_TEST (data [pos++] == 0xef);
   }

   {
      StreamBinIn sbi (data);

      uint64_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == uint64_t (-1));

      sbi >> val;
      flip_TEST (val == 81985529216486895);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      uint64_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestStreamBin::run_008 ()
{
   std::vector <uint8_t> data;

   const std::string token ("\tthis is a test!\r\n");

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << token;

      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == token.size ());

      flip_TEST (data [pos++] == '\t');
      flip_TEST (data [pos++] == 't');
      flip_TEST (data [pos++] == 'h');
      flip_TEST (data [pos++] == 'i');
      flip_TEST (data [pos++] == 's');
      flip_TEST (data [pos++] == ' ');
      flip_TEST (data [pos++] == 'i');
      flip_TEST (data [pos++] == 's');
      flip_TEST (data [pos++] == ' ');
      flip_TEST (data [pos++] == 'a');
      flip_TEST (data [pos++] == ' ');
      flip_TEST (data [pos++] == 't');
      flip_TEST (data [pos++] == 'e');
      flip_TEST (data [pos++] == 's');
      flip_TEST (data [pos++] == 't');
      flip_TEST (data [pos++] == '!');
      flip_TEST (data [pos++] == '\r');
      flip_TEST (data [pos++] == '\n');
   }

   {
      StreamBinIn sbi (data);

      std::string val;
      sbi >> val;
      flip_TEST (val == token);

      uint8_t val2;
      flip_CHECK_THROW (sbi >> val2;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      std::string val2;

      flip_CHECK_THROW (sbi >> val2;)  // size of string becomes too big
   }
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestStreamBin::run_009 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << 1.0;
      sbo << -1.0;
      sbo << std::numeric_limits<double>::max ();
      sbo << std::numeric_limits<double>::min ();
      sbo << std::numeric_limits<double>::lowest ();
      sbo << std::numeric_limits<double>::denorm_min ();
      sbo << std::numeric_limits<double>::infinity ();
      sbo << std::numeric_limits<double>::epsilon ();
   }

   {
      StreamBinIn sbi (data);

      double val = 0.0;
      sbi >> val;
      flip_TEST (val == 1.0);

      sbi >> val;
      flip_TEST (val == -1.0);

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::max ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::min ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::lowest ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::denorm_min ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::infinity ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<double>::epsilon ());
   }

   {
      data.clear ();
      data.emplace_back (uint8_t (2));

      StreamBinIn sbi (data);

      double val;

      flip_CHECK_THROW (sbi >> val);
   }
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestStreamBin::run_010 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      flip_CHECK_THROW (sbo << std::nan ("1"));
   }

   data.clear ();

   data.push_back (0x7f);
   data.push_back (0xf0);
   data.push_back (0x00);
   data.push_back (0x00);
   data.push_back (0x00);
   data.push_back (0x00);
   data.push_back (0x00);
   data.push_back (0x01);
   // nan (1)

   {
      StreamBinIn sbi (data);

      double val;
      flip_CHECK_THROW (sbi >> val);
   }
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestStreamBin::run_011 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      std::vector <double> val {1.0, 2.0, 4.0, 7.0};

      sbo << val;
   }

   {
      StreamBinIn sbi (data);

      std::vector <double> val;
      sbi >> val;

      std::vector <double> val2 {1.0, 2.0, 4.0, 7.0};
      flip_TEST (val == val2);
   }
}



/*
==============================================================================
Name : run_011b
==============================================================================
*/

void  TestStreamBin::run_011b ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      std::list <double> val {1.0, 2.0, 4.0, 7.0};

      sbo << val;
   }

   {
      StreamBinIn sbi (data);

      std::list <double> val;
      sbi >> val;

      std::list <double> val2 {1.0, 2.0, 4.0, 7.0};
      flip_TEST (val == val2);
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestStreamBin::run_012 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      std::map <uint32_t, double> val;
      val [1] = 1.0;
      val [3] = 4.0;
      val [7] = 4.0;

      sbo << val;
   }

   {
      StreamBinIn sbi (data);

      std::map <uint32_t, double> val;
      sbi >> val;

      std::map <uint32_t, double> val2;
      val2 [1] = 1.0;
      val2 [3] = 4.0;
      val2 [7] = 4.0;
      flip_TEST (val == val2);
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestStreamBin::run_013 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      std::vector <uint8_t> val = {1, 2, 4, 7, 11, 8, 10, 0};

      sbo << val;
   }

   {
      StreamBinIn sbi (data);

      std::vector <uint8_t> val;
      sbi >> val;

      std::vector <uint8_t> val2 = {1, 2, 4, 7, 11, 8, 10, 0};
      flip_TEST (val == val2);
   }
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestStreamBin::run_014 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << 1.f;
      sbo << -1.f;
      sbo << std::numeric_limits<float>::max ();
      sbo << std::numeric_limits<float>::min ();
      sbo << std::numeric_limits<float>::lowest ();
      sbo << std::numeric_limits<float>::denorm_min ();
      sbo << std::numeric_limits<float>::infinity ();
      sbo << std::numeric_limits<float>::epsilon ();
   }

   {
      StreamBinIn sbi (data);

      float val = 0.f;
      sbi >> val;
      flip_TEST (val == 1.f);

      sbi >> val;
      flip_TEST (val == -1.f);

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::max ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::min ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::lowest ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::denorm_min ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::infinity ());

      sbi >> val;
      flip_TEST (val == std::numeric_limits<float>::epsilon ());
   }

   {
      data.clear ();
      data.emplace_back (uint8_t (2));

      StreamBinIn sbi (data);

      float val;

      flip_CHECK_THROW (sbi >> val);
   }
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestStreamBin::run_015 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << std::vector <uint8_t> ({0x00, 0xff, 0xae});
   }

   {
      StreamBinIn sbi (data);

      uint64_t val_size;
      sbi >> val_size;
      flip_TEST (val_size == 3);

      const uint8_t * val_ptr = sbi.pull (3);

      flip_TEST (val_ptr [0] == 0x00);
      flip_TEST (val_ptr [1] == 0xff);
      flip_TEST (val_ptr [2] == 0xae);
   }

   {
      StreamBinIn sbi (data);

      uint64_t val_size;
      sbi >> val_size;
      flip_TEST (val_size == 3);

      flip_CHECK_THROW (sbi.pull (4));
   }
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestStreamBin::run_016 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << int16_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << int16_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << int16_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << int16_t (4660);
      flip_TEST (data [pos++] == 0x12);
      flip_TEST (data [pos++] == 0x34);
   }

   {
      StreamBinIn sbi (data);

      int16_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == -1);

      sbi >> val;
      flip_TEST (val == 4660);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      int16_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestStreamBin::run_017 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      size_t pos = 0;

      sbo << uint16_t (0);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 0);

      sbo << uint16_t (1);
      flip_TEST (data [pos++] == 0);
      flip_TEST (data [pos++] == 1);

      sbo << uint16_t (-1);
      flip_TEST (data [pos++] == 0xff);
      flip_TEST (data [pos++] == 0xff);

      sbo << uint16_t (4660);
      flip_TEST (data [pos++] == 0x12);
      flip_TEST (data [pos++] == 0x34);
   }

   {
      StreamBinIn sbi (data);

      uint16_t val = 1;
      sbi >> val;
      flip_TEST (val == 0);

      sbi >> val;
      flip_TEST (val == 1);

      sbi >> val;
      flip_TEST (val == uint16_t (-1));

      sbi >> val;
      flip_TEST (val == 4660);

      flip_CHECK_THROW (sbi >> val;)
   }

   {
      StreamBinIn sbi (data);

      uint8_t val;
      sbi >> val;

      uint16_t val2;
      sbi >> val2;
      sbi >> val2;
      sbi >> val2;

      flip_CHECK_THROW (sbi >> val2;)
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

