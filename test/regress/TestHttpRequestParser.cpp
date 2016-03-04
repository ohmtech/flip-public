/*****************************************************************************

      TestHttpRequestParser.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestHttpRequestParser.h"

#include "TestDef.h"

#include "flip/contrib/shared/HttpRequestParser.h"

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

void  TestHttpRequestParser::run ()
{
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
Name : run_001
==============================================================================
*/

void  TestHttpRequestParser::run_001 ()
{
   std::string request;
   request += "GET / HTTP/1.1\r\n";
   request += "\r\n";

   std::vector <uint8_t> data (request.begin (), request.end ());

   HttpRequestParser parser (data);

   bool ok_flag = parser.process ();
   flip_TEST (ok_flag);

   flip_TEST (parser.method () == "GET");
   flip_TEST (parser.resource () == "/");
   flip_TEST (parser.parameters ().empty ());
   flip_TEST (parser.headers ().empty ());
   flip_TEST (parser.body ().empty ());
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestHttpRequestParser::run_002 ()
{
   std::string request;
   request += "POST validate.php HTTP/1.1\r\n";
   request += "Host: localhost\r\n";
   request += "\r\n";

   std::vector <uint8_t> data (request.begin (), request.end ());

   HttpRequestParser parser (data);

   bool ok_flag = parser.process ();
   flip_TEST (ok_flag);

   flip_TEST (parser.method () == "POST");
   flip_TEST (parser.resource () == "validate.php");
   flip_TEST (parser.parameters ().empty ());
   flip_TEST (parser.headers ().at ("Host") == "localhost");
   flip_TEST (parser.body ().empty ());
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestHttpRequestParser::run_003 ()
{
   std::string request;
   request += "GET validate.php?time=now HTTP/1.1\r\n";
   request += "Host: localhost\r\n";
   request += "Content-Length: 10\r\n";
   request += "\r\n";
   request += "0123456789";

   std::vector <uint8_t> data (request.begin (), request.end ());

   HttpRequestParser parser (data);

   bool ok_flag = parser.process ();
   flip_TEST (ok_flag);

   flip_TEST (parser.method () == "GET");
   flip_TEST (parser.resource () == "validate.php");
   flip_TEST (parser.parameters ().at ("time") == "now");
   flip_TEST (parser.headers ().at ("Host") == "localhost");
   flip_TEST (parser.headers ().at ("Content-Length") == "10");
   flip_TEST (parser.body_str () == "0123456789");
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestHttpRequestParser::run_004 ()
{
   std::string request;
   request += "POST validate.php HTTP/1.1\r\n";
   request += "Host: localhost\r\n";
   request += "Content-Length: 8\r\n";
   request += "\r\n";
   request += "time=now";

   std::vector <uint8_t> data (request.begin (), request.end ());

   HttpRequestParser parser (data);

   bool ok_flag = parser.process ();
   flip_TEST (ok_flag);

   flip_TEST (parser.method () == "POST");
   flip_TEST (parser.resource () == "validate.php");
   flip_TEST (parser.parameters ().at ("time") == "now");
   flip_TEST (parser.headers ().at ("Host") == "localhost");
   flip_TEST (parser.headers ().at ("Content-Length") == "8");
   flip_TEST (parser.body_str () == "time=now");
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

