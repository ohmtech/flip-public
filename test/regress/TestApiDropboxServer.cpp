/*****************************************************************************

      TestApiDropboxServer.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestApiDropboxServer.h"

#include "TestDef.h"

#include "flip/contrib/cloud_store/ApiDropboxServerEmulation.h"
#include "flip/contrib/cloud_store/CurlEasy.h"

#include <thread>
#include <utility>
#include <vector>

#include <climits>

#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   #include <direct.h>
#else
   #include <sys/stat.h>
#endif

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestApiDropboxServer::run ()
{
   AutoBaseApiSwap auto_base_api_swap;

   run_001 ();
   run_002 ();
   run_003 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : AutoBaseApiSwap::ctor
==============================================================================
*/

TestApiDropboxServer::AutoBaseApiSwap::AutoBaseApiSwap ()
:  _base_api (ApiDropbox::base_api)
,  _base_api_notify (ApiDropbox::base_api_notify)
,  _base_api_content (ApiDropbox::base_api_content)
{
   ApiDropbox::base_api = "http://localhost:9090";
   ApiDropbox::base_api_notify = "http://localhost:9090";
   ApiDropbox::base_api_content = "http://localhost:9090";
}



/*
==============================================================================
Name : AutoBaseApiSwap::dtor
==============================================================================
*/

TestApiDropboxServer::AutoBaseApiSwap::~AutoBaseApiSwap ()
{
   std::swap (_base_api, ApiDropbox::base_api);
   std::swap (_base_api_notify, ApiDropbox::base_api_notify);
   std::swap (_base_api_content, ApiDropbox::base_api_content);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestApiDropboxServer::run_001 ()
{
   ApiDropboxServerEmulation server (9090);

   std::string cursor;

   long http_code = 0;
   ApiDropbox::ReplyDelta reply_delta;
   std::string reply_str;

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (reply_delta.cursor == "init");
   flip_TEST (reply_delta.entries.empty ());

   http_code = call_files_put (server, "test", "Hello, World!");

   flip_TEST (http_code == 200);

   http_code = call_files (reply_str, server, "test");

   flip_TEST (http_code == 200);
   flip_TEST (reply_str == "Hello, World!");

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (!reply_delta.cursor.empty ());
   flip_TEST (reply_delta.entries.size () == 1);
   flip_TEST (reply_delta.entries.front ().path == "/test");
   flip_TEST (reply_delta.entries.front ().deleted == false);
   flip_TEST (reply_delta.entries.front ().modified != "");

   http_code = call_fileops_delete (server, "test");

   flip_TEST (http_code == 200);

   http_code = call_files (reply_str, server, "test");

   flip_TEST (http_code == 404);

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (!reply_delta.cursor.empty ());
   flip_TEST (reply_delta.entries.size () == 1);
   flip_TEST (reply_delta.entries.front ().path == "/test");
   flip_TEST (reply_delta.entries.front ().deleted == true);
   flip_TEST (reply_delta.entries.front ().modified == "");
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestApiDropboxServer::run_002 ()
{
   ApiDropboxServerEmulation server (9090);

   std::string cursor;

   long http_code = 0;
   ApiDropbox::ReplyDelta reply_delta;
   std::string reply_str;

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (reply_delta.cursor == "init");
   flip_TEST (reply_delta.entries.empty ());

   http_code = call_files_put (server, "test", "Hello, World!");

   flip_TEST (http_code == 200);

   http_code = call_files_put (server, "test2", "Hello, World2!");

   flip_TEST (http_code == 200);

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (!reply_delta.cursor.empty ());
   flip_TEST (reply_delta.entries.size () == 2);
   flip_TEST (std::count_if (reply_delta.entries.begin (), reply_delta.entries.end (), [](const ApiDropbox::ReplyDelta::Entry & entry){
      return (entry.path == "/test") && (entry.deleted == false) && (entry.modified != "");
   }) == 1);
   flip_TEST (std::count_if (reply_delta.entries.begin (), reply_delta.entries.end (), [](const ApiDropbox::ReplyDelta::Entry & entry){
      return (entry.path == "/test2") && (entry.deleted == false) && (entry.modified != "");
   }) == 1);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestApiDropboxServer::run_003 ()
{
   ApiDropboxServerEmulation server (9090);

   std::string cursor;

   long http_code = 0;
   ApiDropbox::ReplyDelta reply_delta;
   std::string reply_str;

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (reply_delta.cursor == "init");
   flip_TEST (reply_delta.entries.empty ());

   http_code = call_files_put (server, "test", "Hello, World!");

   flip_TEST (http_code == 200);

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (!reply_delta.cursor.empty ());
   flip_TEST (reply_delta.entries.size () == 1);
   flip_TEST (std::count_if (reply_delta.entries.begin (), reply_delta.entries.end (), [](const ApiDropbox::ReplyDelta::Entry & entry){
      return (entry.path == "/test") && (entry.deleted == false) && (entry.modified != "");
   }) == 1);

   http_code = call_files_put (server, "test2", "Hello, World2!");

   flip_TEST (http_code == 200);

   http_code = call_delta (reply_delta, server, cursor);

   flip_TEST (http_code == 200);
   flip_TEST (reply_delta.has_more == false);
   flip_TEST (!reply_delta.cursor.empty ());
   flip_TEST (reply_delta.entries.size () == 1);
   flip_TEST (std::count_if (reply_delta.entries.begin (), reply_delta.entries.end (), [](const ApiDropbox::ReplyDelta::Entry & entry){
      return (entry.path == "/test2") && (entry.deleted == false) && (entry.modified != "");
   }) == 1);
}



/*
==============================================================================
Name : call_delta
==============================================================================
*/

long  TestApiDropboxServer::call_delta (ApiDropbox::ReplyDelta & reply, ApiDropboxServerEmulation & server, std::string & cursor)
{
   long http_code = 0;

   std::thread thread ([&reply, &cursor, &http_code](){
      CurlEasy curl;
      ApiDropbox::delta (curl, "", cursor);
      curl.process ();

      http_code = curl.response_code ();
      ApiDropbox::parse_delta (reply, curl);
      cursor = reply.cursor;
   });

   while (http_code == 0)
   {
      server.process ();
   }

   thread.join ();

   return http_code;
}



/*
==============================================================================
Name : call_files_put
==============================================================================
*/

long  TestApiDropboxServer::call_files_put (ApiDropboxServerEmulation & server, std::string path, std::string content)
{
   long http_code = 0;

   std::thread thread ([&path, &content, &http_code](){
      CurlEasy curl;
      std::vector <uint8_t> data (content.begin (), content.end ());
      ApiDropbox::files_put (curl, "", path, data);
      curl.process ();

      http_code = curl.response_code ();
   });

   while (http_code == 0)
   {
      server.process ();
   }

   thread.join ();

   return http_code;
}



/*
==============================================================================
Name : call_files
==============================================================================
*/

long  TestApiDropboxServer::call_files (std::string & reply, ApiDropboxServerEmulation & server, std::string path)
{
   long http_code = 0;

   std::thread thread ([&reply, &path, &http_code](){
      CurlEasy curl;
      ApiDropbox::files (curl, "", path);
      curl.process ();

      http_code = curl.response_code ();
      reply = curl.response_body_str ();
   });

   while (http_code == 0)
   {
      server.process ();
   }

   thread.join ();

   return http_code;
}



/*
==============================================================================
Name : call_fileops_delete
==============================================================================
*/

long  TestApiDropboxServer::call_fileops_delete (ApiDropboxServerEmulation & server, std::string path)
{
   long http_code = 0;

   std::thread thread ([&path, &http_code](){
      CurlEasy curl;
      curl.impl_reset ();
      ApiDropbox::fileops_delete (curl, "", path);
      curl.process ();

      http_code = curl.response_code ();
   });

   while (http_code == 0)
   {
      server.process ();
   }

   thread.join ();

   return http_code;
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

