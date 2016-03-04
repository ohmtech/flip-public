/*****************************************************************************

      TestBackEndMlCodec.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestBackEndMlCodec.h"

#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "flip/detail/BackEndMlCodec.h"
#include "TestDef.h"


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

void  TestBackEndMlCodec::run ()
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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestBackEndMlCodec::run_000 ()
{
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x00) == "00");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x10) == "10");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x01) == "01");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x23) == "23");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x45) == "45");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x67) == "67");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x89) == "89");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0xab) == "ab");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0xcd) == "cd");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0xef) == "ef");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0x0f) == "0f");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0xf0) == "f0");
   flip_TEST (BackEndMlCodec::encode_hexadecimal (0xff) == "ff");
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestBackEndMlCodec::run_001 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ()) == "Hexadecimal ()"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0x00})) == "Hexadecimal (00)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0x0f})) == "Hexadecimal (0f)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0xf0})) == "Hexadecimal (f0)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0x01, 0x23, 0x45, 0x67})) == "Hexadecimal (01234567)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0x89, 0xab})) == "Hexadecimal (89ab)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0xcd, 0xef, 0x00})) == "Hexadecimal (cdef00)"
   );
   flip_TEST (BackEndMlCodec::encode_hexadecimal (
      std::vector <uint8_t> ({0x01, 0x23, 0x67, 0x45, 0x89, 0x9a, 0xda, 0xbc, 0xef}))
      == "Hexadecimal (01236745899adabcef)"
   );

#endif
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestBackEndMlCodec::run_002 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ()) == "EscapedAscii ()"
   );
   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ({'t', 'e', 's', 't'})) == "EscapedAscii (test)"
   );
   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ({' ', '~', '\\'})) == "EscapedAscii ( ~\\\\)"
   );
   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ({'\r', '\n', '\t'})) == "EscapedAscii (\\r\\n\\t)"
   );
   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ({'\0', '\x1f', '\x7f'})) == "EscapedAscii (\\x00\\x1f\\x7f)"
   );
   flip_TEST (BackEndMlCodec::encode_escaped_ascii (
      std::vector <uint8_t> ({'(', '(', ')', ')'})) == "EscapedAscii ((()))"
   );

#endif
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestBackEndMlCodec::run_003 ()
{
   flip_TEST (BackEndMlCodec::encode_base64 (0) == 'A');
   flip_TEST (BackEndMlCodec::encode_base64 (1) == 'B');
   flip_TEST (BackEndMlCodec::encode_base64 (24) == 'Y');
   flip_TEST (BackEndMlCodec::encode_base64 (25) == 'Z');
   flip_TEST (BackEndMlCodec::encode_base64 (26) == 'a');
   flip_TEST (BackEndMlCodec::encode_base64 (27) == 'b');
   flip_TEST (BackEndMlCodec::encode_base64 (50) == 'y');
   flip_TEST (BackEndMlCodec::encode_base64 (51) == 'z');
   flip_TEST (BackEndMlCodec::encode_base64 (52) == '0');
   flip_TEST (BackEndMlCodec::encode_base64 (53) == '1');
   flip_TEST (BackEndMlCodec::encode_base64 (60) == '8');
   flip_TEST (BackEndMlCodec::encode_base64 (61) == '9');
   flip_TEST (BackEndMlCodec::encode_base64 (62) == '+');
   flip_TEST (BackEndMlCodec::encode_base64 (63) == '/');
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestBackEndMlCodec::run_004 ()
{
   {
      std::string str;
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 ()");
   }

   {
      std::string str ("a");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (YQ==)");
   }

   {
      std::string str ("b");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (Yg==)");
   }

   {
      std::string str ("bc");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (YmM=)");
   }

   {
      std::string str ("bcd");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (YmNk)");
   }

   {
      std::string str ("this is a test");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (dGhpcyBpcyBhIHRlc3Q=)");
   }

   {
      std::string str ("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
      std::vector <uint8_t> data (str.begin (), str.end ());

      flip_TEST (BackEndMlCodec::encode_base64 (data) == "Base64 (TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdWEuIFV0IGVuaW0gYWQgbWluaW0gdmVuaWFtLCBxdWlzIG5vc3RydWQgZXhlcmNpdGF0aW9uIHVsbGFtY28gbGFib3JpcyBuaXNpIHV0IGFsaXF1aXAgZXggZWEgY29tbW9kbyBjb25zZXF1YXQuIER1aXMgYXV0ZSBpcnVyZSBkb2xvciBpbiByZXByZWhlbmRlcml0IGluIHZvbHVwdGF0ZSB2ZWxpdCBlc3NlIGNpbGx1bSBkb2xvcmUgZXUgZnVnaWF0IG51bGxhIHBhcmlhdHVyLiBFeGNlcHRldXIgc2ludCBvY2NhZWNhdCBjdXBpZGF0YXQgbm9uIHByb2lkZW50LCBzdW50IGluIGN1bHBhIHF1aSBvZmZpY2lhIGRlc2VydW50IG1vbGxpdCBhbmltIGlkIGVzdCBsYWJvcnVtLg==)");
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestBackEndMlCodec::run_005 ()
{
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('0') == 0x0);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('1') == 0x1);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('9') == 0x9);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('a') == 0xa);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('b') == 0xb);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('e') == 0xe);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('f') == 0xf);
   flip_CHECK_THROW (BackEndMlCodec::decode_hexadecimal ('z'));

   flip_TEST (BackEndMlCodec::decode_hexadecimal ('0', '0') == 0x00);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('0', '1') == 0x01);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('1', '0') == 0x10);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('2', '3') == 0x23);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('4', '5') == 0x45);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('6', '7') == 0x67);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('8', '9') == 0x89);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('a', 'b') == 0xab);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('c', 'd') == 0xcd);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('e', 'f') == 0xef);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('f', '0') == 0xf0);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('0', 'f') == 0x0f);
   flip_TEST (BackEndMlCodec::decode_hexadecimal ('f', 'f') == 0xff);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestBackEndMlCodec::run_006 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

  flip_TEST (BackEndMlCodec::decode_hexadecimal ("") == std::vector <uint8_t> ());
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("00")
      == std::vector <uint8_t> ({0x00})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("0")
      == std::vector <uint8_t> ({0x00})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("01")
      == std::vector <uint8_t> ({0x01})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("10")
      == std::vector <uint8_t> ({0x10})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("1")
      == std::vector <uint8_t> ({0x10})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("123")
      == std::vector <uint8_t> ({0x12, 0x30})
   );
   flip_TEST (
      BackEndMlCodec::decode_hexadecimal ("0123456789abcdef")
      == std::vector <uint8_t> ({0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef})
   );

#endif
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestBackEndMlCodec::run_007 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   flip_TEST (BackEndMlCodec::decode_escaped_ascii ("") == std::vector <uint8_t> ());
   flip_TEST (
      BackEndMlCodec::decode_escaped_ascii ("test")
      == std::vector <uint8_t> ({'t', 'e', 's', 't'})
   );
   flip_TEST (
      BackEndMlCodec::decode_escaped_ascii (" ~\\\\")
      == std::vector <uint8_t> ({' ', '~', '\\'})
   );
   flip_TEST (
      BackEndMlCodec::decode_escaped_ascii ("\\r\\n\\t")
      == std::vector <uint8_t> ({'\r', '\n', '\t'})
   );
   flip_TEST (
      BackEndMlCodec::decode_escaped_ascii ("\\x00\\x1f\\x7f")
      == std::vector <uint8_t> ({'\0', '\x1f', '\x7f'})
   );
   flip_TEST (
      BackEndMlCodec::decode_escaped_ascii ("(())")
      == std::vector <uint8_t> ({'(', '(', ')', ')'})
   );

#endif
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestBackEndMlCodec::run_008 ()
{
   flip_TEST (BackEndMlCodec::decode_base64 ('A') == 0);
   flip_TEST (BackEndMlCodec::decode_base64 ('B') == 1);
   flip_TEST (BackEndMlCodec::decode_base64 ('Y') == 24);
   flip_TEST (BackEndMlCodec::decode_base64 ('Z') == 25);
   flip_TEST (BackEndMlCodec::decode_base64 ('a') == 26);
   flip_TEST (BackEndMlCodec::decode_base64 ('b') == 27);
   flip_TEST (BackEndMlCodec::decode_base64 ('y') == 50);
   flip_TEST (BackEndMlCodec::decode_base64 ('z') == 51);
   flip_TEST (BackEndMlCodec::decode_base64 ('0') == 52);
   flip_TEST (BackEndMlCodec::decode_base64 ('1') == 53);
   flip_TEST (BackEndMlCodec::decode_base64 ('8') == 60);
   flip_TEST (BackEndMlCodec::decode_base64 ('9') == 61);
   flip_TEST (BackEndMlCodec::decode_base64 ('+') == 62);
   flip_TEST (BackEndMlCodec::decode_base64 ('/') == 63);
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ('='));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ('A' - 1));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ('Z' + 1));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ('a' - 1));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ('z' + 1));
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestBackEndMlCodec::run_009 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   flip_TEST (BackEndMlCodec::decode_base64 ("") == std::vector <uint8_t> ());
   flip_TEST (BackEndMlCodec::decode_base64 ("YQ==")
      == std::vector <uint8_t> ({'a'})
   );
   flip_TEST (BackEndMlCodec::decode_base64 ("Yg==")
      == std::vector <uint8_t> ({'b'})
   );
   flip_TEST (BackEndMlCodec::decode_base64 ("YmM=")
      == std::vector <uint8_t> ({'b', 'c'})
   );
   flip_TEST (BackEndMlCodec::decode_base64 ("YmNk")
      == std::vector <uint8_t> ({'b', 'c', 'd'})
   );

#endif

   {
      std::vector <uint8_t> data = BackEndMlCodec::decode_base64 ("dGhpcyBpcyBhIHRlc3Q=");
      std::string str (data.begin (), data.end ());
      flip_TEST (str == "this is a test");
   }

   {
      std::vector <uint8_t> data = BackEndMlCodec::decode_base64 ("TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdWEuIFV0IGVuaW0gYWQgbWluaW0gdmVuaWFtLCBxdWlzIG5vc3RydWQgZXhlcmNpdGF0aW9uIHVsbGFtY28gbGFib3JpcyBuaXNpIHV0IGFsaXF1aXAgZXggZWEgY29tbW9kbyBjb25zZXF1YXQuIER1aXMgYXV0ZSBpcnVyZSBkb2xvciBpbiByZXByZWhlbmRlcml0IGluIHZvbHVwdGF0ZSB2ZWxpdCBlc3NlIGNpbGx1bSBkb2xvcmUgZXUgZnVnaWF0IG51bGxhIHBhcmlhdHVyLiBFeGNlcHRldXIgc2ludCBvY2NhZWNhdCBjdXBpZGF0YXQgbm9uIHByb2lkZW50LCBzdW50IGluIGN1bHBhIHF1aSBvZmZpY2lhIGRlc2VydW50IG1vbGxpdCBhbmltIGlkIGVzdCBsYWJvcnVtLg==");
      std::string str (data.begin (), data.end ());
      flip_TEST (str == "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
   }

   flip_CHECK_THROW (BackEndMlCodec::decode_base64 (" "));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ("a"));
   flip_CHECK_THROW (BackEndMlCodec::decode_base64 ("ab"));
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

