/*****************************************************************************

      TestConsumerTextOut.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestConsumerTextOut.h"

#include "flip/detail/ConsumerTextOut.h"
#include "flip/DataConsumerMemory.h"
#include "TestDef.h"

#include <limits>
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

void  TestConsumerTextOut::run ()
{
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestConsumerTextOut::run_000 ()
{
   std::vector <uint8_t> data;
   DataConsumerMemory consumer (data);
   ConsumerTextOut out (consumer);

   out.print ("");

   std::string str (data.begin (), data.end ());
   flip_TEST (str == "");
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestConsumerTextOut::run_001 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", uint8_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", uint8_t (15));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0f");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", uint8_t (0xFF));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "ff");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", uint8_t (15));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0f");
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestConsumerTextOut::run_002 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", uint32_t (0));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", uint32_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", uint32_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "00000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <uint32_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "4294967295");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <uint32_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "ffffffff");
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestConsumerTextOut::run_003 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int32_t (0));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int32_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", int32_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", int32_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "00000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int32_t (-1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "-1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <int32_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "2147483647");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <int32_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "7fffffff");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <int32_t>::min ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "-2147483648");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <int32_t>::min ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "80000000");
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestConsumerTextOut::run_004 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", uint64_t (0));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", uint64_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", uint64_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <uint64_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "18446744073709551615");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <uint64_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "ffffffffffffffff");
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestConsumerTextOut::run_005 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int64_t (0));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int64_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", int64_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", int64_t (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", int64_t (-1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "-1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <int64_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "9223372036854775807");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <int64_t>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "7fffffffffffffff");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <int64_t>::min ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "-9223372036854775808");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", std::numeric_limits <int64_t>::min ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "8000000000000000");
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestConsumerTextOut::run_006 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 0.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 1.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 1.25);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1.25");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", -1.25);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "-1.25");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 0.25);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0.25");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 1000000.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1000000");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", 1000000000.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1000000000");
   }

#if (flip_PLATFORM != flip_PLATFORM_WIN32)
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <double>::max ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368");
   }
#endif

#if (flip_PLATFORM != flip_PLATFORM_WIN32)
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", std::numeric_limits <double>::denorm_min ());

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571e-324");
   }
#endif

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", 0.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%x@", 1.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "3ff0000000000000");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", 0.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000000");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%0x@", 1.0);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "3ff0000000000000");
   }
}



/*
==============================================================================
Name : run_007
Description : 32-bit version
==============================================================================
*/

#if (flip_WORD_SIZE_BYTE == 4)
void  TestConsumerTextOut::run_007 ()
{
   static_assert (sizeof (void *) == 4, "");

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", nullptr);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000000");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (0x12345678));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000012345678");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (-1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "00000000ffffffff");
   }
}
#endif



/*
==============================================================================
Name : run_007
Description : 64-bit version
==============================================================================
*/

#if (flip_WORD_SIZE_BYTE == 8)
void  TestConsumerTextOut::run_007 ()
{
   static_assert (sizeof (void *) == 8, "");

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", nullptr);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000000");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0000000000000001");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (0x1234567890abcdef));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1234567890abcdef");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", reinterpret_cast <void *> (-1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "ffffffffffffffff");
   }
}
#endif



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestConsumerTextOut::run_008 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", "this is a test");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "this is a test");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", "this\nis\ra\ttest");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "this\\nis\\ra\\ttest");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%%%@", "this\nis\ra\ttest");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "%this\\nis\\ra\\ttest");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@%%", "abcd");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "abcd%");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      // degenerated but handled
      out.print ("%@%", "abcd");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "abcd%");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      // degenerated but handled
      out.print ("%", "abcd");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "abcd");
   }
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestConsumerTextOut::run_009 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", Ref::null);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "null");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", Ref::root);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0|fliproot|1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", Ref::root + 9);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0|fliproot|a");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", Ref::make (1, 0x6162636465666768ULL, 0x1234567890abcdefULL));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1|abcdefgh|1234567890abcdef");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@", Ref::make (0x1234567890abcdefULL, 0x6162636465666768ULL, 1));

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1234567890abcdef|abcdefgh|1");
   }
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestConsumerTextOut::run_010 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      std::array <uint8_t, 20> array;
      for (uint8_t i = 0 ; i < array.size () ; ++i) array [i] = i;

      KeyRandom key (array);

      out.print ("%@", key);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "000102030405060708090a0b0c0d0e0f10111213");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      std::array <uint8_t, 20> array;
      for (uint8_t i = 0 ; i < array.size () ; ++i) array [i] = i + 1;

      KeyRandom key (array);

      out.print ("%@", key);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "0102030405060708090a0b0c0d0e0f1011121314");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      std::array <uint8_t, 20> array;
      for (uint8_t i = 0 ; i < array.size () ; ++i) array [i] = i + 255 - 20;

      KeyRandom key (array);

      out.print ("%@", key);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "ebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfe");
   }
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestConsumerTextOut::run_011 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      out.print ("%@|%@,%@<flip>%@", 1, 2.5, Ref::null, Ref::root);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "1|2.5,null<flip>0|fliproot|1");
   }
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestConsumerTextOut::run_012 ()
{
   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("test");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    test");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("%@test", 1);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    1test");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("test%@", 1);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    test1");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("test%@test", 1);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    test1test");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("test\ntest");

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    test\n    test");
   }

   {
      std::vector <uint8_t> data;
      DataConsumerMemory consumer (data);
      ConsumerTextOut out (consumer);

      ConsumerTextOut::Indent indent (out, 4);

      out.print ("test\n%@test", 1);

      std::string str (data.begin (), data.end ());
      flip_TEST (str == "    test\n    1test");
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

