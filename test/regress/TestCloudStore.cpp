/*****************************************************************************

      TestCloudStore.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestCloudStore.h"

#include "flip/contrib/cloud_store/ApiDropbox.h"
#include "flip/contrib/cloud_store/ApiDropboxServerEmulation.h"
#include "flip/contrib/cloud_store/CurlEasy.h"
#include "flip/contrib/cloud_store/CurlEasyPool.h"
#include "flip/contrib/cloud_store/CurlEasyQueue.h"
#include "flip/contrib/cloud_store/CurlMulti.h"
#include "flip/contrib/cloud_store/CloudStoreDropbox.h"
#include "flip/contrib/cloud_store/CloudStoreFilesystem.h"
#include "flip/contrib/cloud_store/TransportCloudStore.h"
#include "flip/detail/def.h"
#include "flip/detail/fnc.h"

#include "TestDef.h"

#include <chrono>
#include <iostream>
#include <thread>

#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   #include <direct.h>
#else
   #include <sys/stat.h>
   #include <unistd.h>
#endif

#include <cassert>



flip_DISABLE_WARNINGS_FOUR_CHAR_CONSTANTS

#define flip_CHRONO_START(x) \
   std::chrono::time_point <std::chrono::system_clock> flip_chrono_start##x, flip_chrono_end##x;   \
   flip_chrono_start##x = std::chrono::system_clock::now ();


#define flip_CHRONO_END(x) \
   flip_chrono_end##x = std::chrono::system_clock::now ();  \
   std::chrono::duration <double> flip_chrono_elapsed##x = flip_chrono_end##x - flip_chrono_start##x; \
   if (display_flag) std::cout << "      " #x " in " << flip_chrono_elapsed##x.count () * 1000.0 << " ms" << std::endl;



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestCloudStore::run ()
{
   Model::version ("test.usecase");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Float, &Clip::_position> ("position")
      .member <Float, &Clip::_duration> ("duration");

   Model::declare <Track> ()
      .name ("Track")
      .member <Clips, &Track::_clips> ("clips");

   Model::declare <Song> ()
      .name ("Song")
      .member <Tracks, &Song::_tracks> ("tracks");

   // filesystem
   run_f001 ();
   run_f002 ();
   run_f003 ();
   run_f004 ();

   // emulation
   run_s001 ();
   run_s002 ();
   run_s003 ();
   run_s004 ();
   run_s005 ();
   run_s006 ();
   run_s007 ();
   run_s008 ();
   run_s009 ();   // long

   // real thing
   run_r001 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : AutoApiDropboxServer::ctor
==============================================================================
*/

TestCloudStore::AutoApiDropboxServer::AutoApiDropboxServer (int error_period, int longpoll_timeout)
:  _error_period (error_period)
,  _longpoll_timeout (longpoll_timeout)
,  _thread ([this](){init ();})
{
   std::unique_lock <std::mutex> lock (_mutex);

   _cond.wait (lock, [this](){return _ready_flag;});
}



/*
==============================================================================
Name : AutoApiDropboxServer::dtor
==============================================================================
*/

TestCloudStore::AutoApiDropboxServer::~AutoApiDropboxServer ()
{
   _loop_flag = false;
   _thread.join ();

   std::swap (_base_api, ApiDropbox::base_api);
   std::swap (_base_api_notify, ApiDropbox::base_api_notify);
   std::swap (_base_api_content, ApiDropbox::base_api_content);
}



/*
==============================================================================
Name : AutoApiDropboxServer::init
==============================================================================
*/

void  TestCloudStore::AutoApiDropboxServer::init ()
{
   _base_api = "http://localhost:9090";
   _base_api_notify = "http://localhost:9090";
   _base_api_content = "http://localhost:9090";

   std::swap (_base_api, ApiDropbox::base_api);
   std::swap (_base_api_notify, ApiDropbox::base_api_notify);
   std::swap (_base_api_content, ApiDropbox::base_api_content);

   _server_uptr = std::make_unique <ApiDropboxServerEmulation> (uint16_t (9090));

   if (_error_period > 0)
   {
      for (int i = 0 ; i < 200 ; ++i)
      {
         _server_uptr->set_error (
            i * _error_period,
            ApiDropboxServerEmulation::ErrorType::Transient_500
         );
      }
   }

   _server_uptr->set_longpoll_timeout (_longpoll_timeout);

   {
      std::lock_guard <std::mutex> lock (_mutex);

      _ready_flag = true;
   }

   _cond.notify_one ();

   while (_loop_flag)
   {
      _server_uptr->process ();
   }
}



/*
==============================================================================
Name : run_f001
==============================================================================
*/

void  TestCloudStore::run_f001 ()
{
#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   // ignore errors
   _mkdir ("tcs_001");
#else
   ::system ("rm -rfd tcs_001");
   ::mkdir ("tcs_001", 0755);
#endif

   CloudStoreFilesystem store ("tcs_001"); // current path

   auto object_set = store.fetch ();
   flip_TEST (object_set.empty ());

   std::vector <uint8_t> data {0x01};
   store.put ("key", data);

   object_set = store.fetch ();
   flip_TEST (object_set.size () == 1);
   flip_TEST (object_set.begin ()->key == "key");
   flip_TEST (object_set.begin ()->timestamp != 0ULL);

   object_set = store.fetch ();
   flip_TEST (object_set.empty ());

   data = store.get ("key");
   flip_TEST (data.size () == 1);
   flip_TEST (data [0] == 0x01);

   store.remove ("key");

   object_set = store.fetch ();
   flip_TEST (object_set.size () == 1);
   flip_TEST (object_set.begin ()->key == "key");
   flip_TEST (object_set.begin ()->timestamp == 0ULL);

   object_set = store.fetch ();
   flip_TEST (object_set.empty ());
}



/*
==============================================================================
Name : run_f002
==============================================================================
*/

void  TestCloudStore::run_f002 ()
{
#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   // ignore errors
   _mkdir ("tcs_002");
#else
   ::system ("rm -rfd tcs_002");
   ::mkdir ("tcs_002", 0755);
#endif

   Listener listener;

   CloudStoreFilesystem store1 ("tcs_002"); // current path

   TransportCloudStore::create (store1, Model::use ());

   Document document1 (Model::use (), 123456789ULL, 'flip', 'test');
   TransportCloudStore transport1 (listener, document1, store1);
   transport1.limit_rate (std::chrono::seconds (0));

   CloudStoreFilesystem store2 ("tcs_002");
   Document document2 (Model::use (), 12345ULL, 'flip', 'test');
   TransportCloudStore transport2 (listener, document2, store2);
   transport2.limit_rate (std::chrono::seconds (0));

   {
      auto & song = document1.root <Song> ();
      song._tracks.emplace (song._tracks.end ());
      document1.commit ();
      document1.push ();
   }

   {
      auto & song = document2.root <Song> ();
      song._tracks.emplace (song._tracks.end ());
      document2.commit ();
      document2.push ();
   }

   bool loop_flag = true;

   while (loop_flag)
   {
      transport1.process ();
      transport2.process ();

      loop_flag = false;

      {
         document1.pull ();

         auto & song = document1.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 2;
      }

      {
         document2.pull ();

         auto & song = document2.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 2;
      }
   }
}



/*
==============================================================================
Name : run_f003
==============================================================================
*/

void  TestCloudStore::run_f003 ()
{
#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   // ignore errors
   _mkdir ("tcs_003");
#else
   ::system ("rm -rfd tcs_003");
   ::mkdir ("tcs_003", 0755);
#endif

   Listener listener;

   CloudStoreFilesystem store1 ("tcs_003"); // current path

   TransportCloudStore::create (store1, Model::use ());

   Document document1 (Model::use (), 123456789ULL, 'flip', 'test');
   TransportCloudStore transport1 (listener, document1, store1);
   transport1.limit_rate (std::chrono::seconds (0));

   CloudStoreFilesystem store2 ("tcs_003");
   Document document2 (Model::use (), 12345ULL, 'flip', 'test');
   TransportCloudStore transport2 (listener, document2, store2);
   transport2.limit_rate (std::chrono::seconds (0));

   bool loop_flag = true;

   auto start_time = std::chrono::steady_clock::now ();

   size_t track_nbr1 = 0;
   size_t track_nbr2 = 0;

   while (loop_flag)
   {
      transport1.process ();
      transport2.process ();

      auto now_time = std::chrono::steady_clock::now ();
      std::chrono::duration <double> diff_time = now_time - start_time;

      // nbr of target tracks depending on time
      auto x = diff_time.count () / 15.0;  // running 15 seconds
      auto accel = x * x * x * x;

      size_t target_track_nbr1 = size_t (std::floor (100.0 * accel));
      target_track_nbr1 = std::min (target_track_nbr1, size_t (100));

      size_t target_track_nbr2 = size_t (std::floor (57.0 * accel));
      target_track_nbr2 = std::min (target_track_nbr2, size_t (57));

      {
         auto & song = document1.root <Song> ();

         for (; track_nbr1 < target_track_nbr1 ; ++track_nbr1)
         {
            song._tracks.emplace (song._tracks.end ());
         }

         document1.commit ();
         document1.push ();
      }

      {
         auto & song = document2.root <Song> ();

         for (; track_nbr2 < target_track_nbr2 ; ++track_nbr2)
         {
            song._tracks.emplace (song._tracks.end ());
         }

         document2.commit ();
         document2.push ();
      }

      loop_flag = false;

      {
         document1.pull ();

         auto & song = document1.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }

      {
         document2.pull ();

         auto & song = document2.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }
   }
}



/*
==============================================================================
Name : run_f004
==============================================================================
*/

void  TestCloudStore::run_f004 ()
{
#if (flip_PLATFORM == flip_PLATFORM_WIN32)
   // ignore errors
   _mkdir ("tcs_004");
#else
   ::system ("rm -rfd tcs_004");
   ::mkdir ("tcs_004", 0755);
#endif

   Listener listener;

   CloudStoreFilesystem store1 ("tcs_004"); // current path

   TransportCloudStore::create (store1, Model::use ());

   Document document1 (Model::use (), 123456789ULL, 'flip', 'test');
   TransportCloudStore transport1 (listener, document1, store1);
   transport1.limit_rate (std::chrono::seconds (0));

   CloudStoreFilesystem store2 ("tcs_004");
   Document document2 (Model::use (), 12345ULL, 'flip', 'test');
   TransportCloudStore transport2 (listener, document2, store2);
   transport2.limit_rate (std::chrono::seconds (0));

   bool loop_flag = true;

   auto start_time = std::chrono::steady_clock::now ();

   size_t track_nbr1 = 0;
   size_t track_nbr2 = 0;

   while (loop_flag)
   {
      transport1.process ();

      auto now_time = std::chrono::steady_clock::now ();
      std::chrono::duration <double> diff_time = now_time - start_time;

      // nbr of target tracks depending on time
      auto x = diff_time.count () / 15.0;  // running 15 seconds

      if (x > 0.5)
      {
         transport2.process ();
      }

      auto accel = x * x * x * x;

      size_t target_track_nbr1 = size_t (std::floor (100.0 * accel));
      target_track_nbr1 = std::min (target_track_nbr1, size_t (100));

      size_t target_track_nbr2 = size_t (std::floor (57.0 * accel));
      target_track_nbr2 = std::min (target_track_nbr2, size_t (57));

      {
         auto & song = document1.root <Song> ();

         for (; track_nbr1 < target_track_nbr1 ; ++track_nbr1)
         {
            song._tracks.emplace (song._tracks.end ());
         }

         document1.commit ();
         document1.push ();
      }

      {
         auto & song = document2.root <Song> ();

         for (; track_nbr2 < target_track_nbr2 ; ++track_nbr2)
         {
            song._tracks.emplace (song._tracks.end ());
         }

         document2.commit ();
         document2.push ();
      }

      loop_flag = false;

      {
         document1.pull ();

         auto & song = document1.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }

      {
         document2.pull ();

         auto & song = document2.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }
   }
}



/*
==============================================================================
Name : run_s001
==============================================================================
*/

void  TestCloudStore::run_s001 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   {
      CurlEasy curl;
      std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
      ApiDropbox::files_put (curl, token, "test.txt", data);

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);
   }

   std::string cursor;

   {
      CurlEasy curl;
      ApiDropbox::delta (curl, token, cursor);

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);

      ApiDropbox::ReplyDelta reply;
      ApiDropbox::parse_delta (reply, curl);
      flip_TEST (!reply.has_more);
      flip_TEST (!reply.cursor.empty ());

      flip_TEST (std::count_if (
         reply.entries.begin (),
         reply.entries.end (),
         [](const ApiDropbox::ReplyDelta::Entry & e){
            return
               (e.path == "/test.txt")
               && (!e.deleted)
               && (!e.modified.empty ());
         }
      ) == 1);

      cursor = reply.cursor;
   }

   {
      CurlEasy curl;
      std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
      ApiDropbox::files (curl, token, "test.txt");

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);
      flip_TEST (curl.response_body () == data);
   }

   {
      CurlEasy curl;
      ApiDropbox::fileops_delete (curl, token, "test.txt");

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);
   }

   {
      CurlEasy curl;
      ApiDropbox::longpoll_delta (curl, cursor);

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);

      bool changes_flag = false;
      ApiDropbox::parse_longpoll_delta (changes_flag, curl);
      flip_TEST (changes_flag);
   }

   {
      CurlEasy curl;
      ApiDropbox::delta (curl, token, cursor);

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);

      ApiDropbox::ReplyDelta reply;
      ApiDropbox::parse_delta (reply, curl);
      flip_TEST (!reply.has_more);
      flip_TEST (!reply.cursor.empty ());

      flip_TEST (std::count_if (
         reply.entries.begin (),
         reply.entries.end (),
         [](const ApiDropbox::ReplyDelta::Entry & e){
            return
               (e.path == "/test.txt")
               && (e.deleted)
               && (e.modified.empty ());
         }
      ) == 1);
   }
}



/*
==============================================================================
Name : run_s002
==============================================================================
*/

void  TestCloudStore::run_s002 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   {
      CurlEasyPool pool;
      auto curl_uptr = pool.take ();

      std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
      ApiDropbox::files_put (*curl_uptr, token, "test.txt", data);

      bool loop_flag = true;

      curl_uptr->bind ([&loop_flag](CurlEasy & curl){
         long code = curl.response_code ();
         flip_TEST (code == 200);

         loop_flag = false;
      });

      CurlEasyQueue queue;
      curl_uptr->bind (queue);

      CurlMulti multi;
      multi.push (std::move (curl_uptr));

      while (loop_flag)
      {
         multi.process ();
      }
   }
}



/*
==============================================================================
Name : run_s003
==============================================================================
*/

void  TestCloudStore::run_s003 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   CurlEasy curl;

   {
      curl.impl_reset ();
      std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
      ApiDropbox::files_put (curl, token, "test.txt", data);

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);
   }

   {
      curl.impl_reset ();
      std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
      ApiDropbox::files (curl, token, "test.txt");

      curl.process ();
      long code = curl.response_code ();
      flip_TEST (code == 200);
      flip_TEST (curl.response_body () == data);
   }
}



/*
==============================================================================
Name : run_s004
==============================================================================
*/

void  TestCloudStore::run_s004 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   CloudStoreDropbox store (token);

   store.remove ("test.txt");
   store.remove ("test2.txt");
   store.remove ("test3.txt");

   std::set <CloudStoreDropbox::Object> object_set;

   bool display_flag = true;

   flip_CHRONO_START (fetch1);
   object_set = store.fetch ();
   flip_CHRONO_END (fetch1);

   std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};

   flip_CHRONO_START (put);
   store.put ("test2.txt", data);
   flip_CHRONO_END (put);

   flip_CHRONO_START (get);
   auto data2 = store.get ("test2.txt");
   flip_CHRONO_END (get);

   flip_TEST (data == data2);

   flip_CHRONO_START (put2);
   store.put ("test3.txt", data);
   flip_CHRONO_END (put2);

   flip_CHRONO_START (get2);
   auto data3 = store.get ("test3.txt");
   flip_CHRONO_END (get2);

   flip_TEST (data == data3);

   object_set.clear ();

   do
   {
      //flip_CHRONO_START (fetch2);
      auto sub_object_set = store.fetch ();
      //flip_CHRONO_END (fetch2);

      //usleep (1000);

      object_set.insert (sub_object_set.begin (), sub_object_set.end ());
   }
   while (object_set.size () != 2);

   flip_TEST (std::count_if (object_set.begin (), object_set.end (), [](const CloudStoreDropbox::Object & object){
      return (object.key == "test2.txt") && (object.timestamp != 0ULL);
   }) == 1);
   flip_TEST (std::count_if (object_set.begin (), object_set.end (), [](const CloudStoreDropbox::Object & object){
      return (object.key == "test3.txt") && (object.timestamp != 0ULL);
   }) == 1);

   flip_CHRONO_START (remove);
   store.remove ("test2.txt");
   flip_CHRONO_END (remove);

   flip_CHRONO_START (remove2);
   store.remove ("test3.txt");
   flip_CHRONO_END (remove2);
}



/*
==============================================================================
Name : run_s005
==============================================================================
*/

void  TestCloudStore::run_s005 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   CloudStoreDropbox store (token);

   std::set <CloudStoreDropbox::Object> object_set;

   object_set = store.fetch ();
   object_set.clear ();

   store.turn_async ();

   std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
   store.put ("test2.txt", data);

   bool loop_flag = true;

   while (loop_flag)
   {
      store.process ();

      object_set = store.fetch ();

      loop_flag = object_set.empty ();
   }

   flip_TEST (std::count_if (object_set.begin (), object_set.end (), [](const CloudStoreDropbox::Object & object){
      return (object.key == "test2.txt") && (object.timestamp != 0ULL);
   }) == 1);
}



/*
==============================================================================
Name : run_s006
==============================================================================
*/

void  TestCloudStore::run_s006 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   CloudStoreDropbox store (token);

   std::set <CloudStoreDropbox::Object> object_set;

   object_set = store.fetch ();
   object_set.clear ();

   store.turn_async ();

   std::vector <uint8_t> data {'s', 'o', 'm', 'e', ' ', 't', 'e', 's', 't'};
   store.put ("test2.txt", data);
   store.put ("test3.txt", data);

   bool loop_flag = true;

   while (loop_flag)
   {
      store.process ();

      auto sub_object_set = store.fetch ();
      object_set.insert (sub_object_set.begin (), sub_object_set.end ());

      loop_flag = object_set.size () != 2;
   }

   flip_TEST (std::count_if (object_set.begin (), object_set.end (), [](const CloudStoreDropbox::Object & object){
      return (object.key == "test2.txt") && (object.timestamp != 0ULL);
   }) == 1);
   flip_TEST (std::count_if (object_set.begin (), object_set.end (), [](const CloudStoreDropbox::Object & object){
      return (object.key == "test3.txt") && (object.timestamp != 0ULL);
   }) == 1);
}



/*
==============================================================================
Name : run_s007
==============================================================================
*/

void  TestCloudStore::run_s007 ()
{
   int error_period = 7;
   AutoApiDropboxServer server (error_period);

   std::string token;   // not used

   Listener listener;

   CloudStoreDropbox store (token);

   TransportCloudStore::create (store, Model::use ());

   Document document (Model::use (), 123456789ULL, 0, 0xbeef);
   TransportCloudStore transport (listener, document, store);
   transport.limit_rate (std::chrono::seconds (1));

   bool loop_flag = true;
   size_t loop_nbr = 0;

   size_t track_nbr = 0;
   size_t cnt = 0;

   std::chrono::microseconds process_max = std::chrono::microseconds::zero ();
   std::chrono::microseconds process_avg = std::chrono::microseconds::zero ();

   while (loop_flag)
   {
      auto start = std::chrono::steady_clock::now ();

      transport.process ();

      auto duration = std::chrono::duration_cast <std::chrono::microseconds> (
         std::chrono::steady_clock::now () - start
      );

      process_max = std::max (process_max, duration);
      process_avg += duration;

      size_t target_nbr_track = cnt;
      ++cnt;

      target_nbr_track = std::min (target_nbr_track, size_t (10));

      auto & song = document.root <Song> ();

      for (; track_nbr < target_nbr_track ; ++track_nbr)
      {
         song._tracks.emplace (song._tracks.end ());
      }

      document.commit ();
      document.push ();

      document.pull ();

      size_t pending = document.pending_txs ();

      loop_flag = (track_nbr != 10) || (pending != 0);
      ++loop_nbr;
   }

   process_avg /= std::chrono::microseconds::rep (loop_nbr);

   flip_TEST (process_max < std::chrono::milliseconds {100});
   flip_TEST (process_avg < std::chrono::microseconds {50});
}



/*
==============================================================================
Name : run_s008
==============================================================================
*/

void  TestCloudStore::run_s008 ()
{
   AutoApiDropboxServer server;

   std::string token;   // not used

   Listener listener;

   CloudStoreDropbox store1 (token);

   TransportCloudStore::create (store1, Model::use ());

   Document document1 (Model::use (), 123456789ULL, 0, 0xbeef);
   TransportCloudStore transport1 (listener, document1, store1);
   transport1.limit_rate (std::chrono::seconds (1));

   CloudStoreDropbox store2 (token);
   Document document2 (Model::use (), 12345ULL, 0, 0xcafe);
   TransportCloudStore transport2 (listener, document2, store2);
   transport2.limit_rate (std::chrono::seconds (1));

   bool loop_flag = true;

   auto start_time = std::chrono::steady_clock::now ();

   size_t track_nbr1 = 0;
   size_t track_nbr2 = 0;

   while (loop_flag)
   {
      transport1.process ();

      auto now_time = std::chrono::steady_clock::now ();
      std::chrono::duration <double> diff_time = now_time - start_time;

      // nbr of target tracks depending on time
      auto x = diff_time.count () / 15.0;  // running 15 seconds

      if (x > 0.5)
      {
         transport2.process ();
      }

      auto accel = x * x * x * x;

      size_t target_track_nbr1 = size_t (std::floor (100.0 * accel));
      target_track_nbr1 = std::min (target_track_nbr1, size_t (100));

      size_t target_track_nbr2 = size_t (std::floor (57.0 * accel));
      target_track_nbr2 = std::min (target_track_nbr2, size_t (57));

      {
         auto & song = document1.root <Song> ();

         for (; track_nbr1 < target_track_nbr1 ; ++track_nbr1)
         {
            //printf ("1> +track\n");
            song._tracks.emplace (song._tracks.end ());
         }

         document1.commit ();
         document1.push ();
      }

      {
         auto & song = document2.root <Song> ();

         for (; track_nbr2 < target_track_nbr2 ; ++track_nbr2)
         {
            //printf ("2> +track\n");
            song._tracks.emplace (song._tracks.end ());
         }

         document2.commit ();
         document2.push ();
      }

      loop_flag = false;

      {
         document1.pull ();

         auto & song = document1.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }

      {
         document2.pull ();

         auto & song = document2.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }
   }
}



/*
==============================================================================
Name : run_s009
==============================================================================
*/

void  TestCloudStore::run_s009 ()
{
   AutoApiDropboxServer server (0, 1);

   std::string token;   // not used

   Listener listener;

   CloudStoreDropbox store (token);

   TransportCloudStore::create (store, Model::use ());

   Document document (Model::use (), 123456789ULL, 0, 0xbeef);
   TransportCloudStore transport (listener, document, store);

   transport.process ();

   // start

   std::this_thread::sleep_for (std::chrono::seconds (60));

   {
      auto & song = document.root <Song> ();

      song._tracks.emplace (song._tracks.end ());

      document.commit ();
      document.push ();
   }

   bool loop_flag = true;

   while (loop_flag)
   {
      transport.process ();

      /*auto & song = document.root <Song> ();

      loop_flag = std::count_if (
         song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
      ) != 1;*/
   }
}



/*
==============================================================================
Name : run_r001
==============================================================================
*/

void  TestCloudStore::run_r001 ()
{
   std::string token = "VjtjJL0wdVAAAAAAAAAADz6zGJUEOmGrYT15h4C9BFHRX9dE1vC67Nhx8qvERDEc";

   Listener listener;

   CloudStoreDropbox store1 (token);

   TransportCloudStore::create (store1, Model::use ());

   Document document1 (Model::use (), 123456789ULL, 0, 0xbeef);
   TransportCloudStore transport1 (listener, document1, store1);
   transport1.limit_rate (std::chrono::seconds (10));

   CloudStoreDropbox store2 (token);
   Document document2 (Model::use (), 12345ULL, 0, 0xcafe);
   TransportCloudStore transport2 (listener, document2, store2);
   transport2.limit_rate (std::chrono::seconds (10));

   bool loop_flag = true;

   auto start_time = std::chrono::steady_clock::now ();

   size_t track_nbr1 = 0;
   size_t track_nbr2 = 0;

   while (loop_flag)
   {
      transport1.process ();

      auto now_time = std::chrono::steady_clock::now ();
      std::chrono::duration <double> diff_time = now_time - start_time;

      // nbr of target tracks depending on time
      auto x = diff_time.count () / 15.0;  // running 15 seconds

      if (x > 0.5)
      {
         transport2.process ();
      }

      auto accel = x * x * x * x;

      size_t target_track_nbr1 = size_t (std::floor (100.0 * accel));
      target_track_nbr1 = std::min (target_track_nbr1, size_t (100));

      size_t target_track_nbr2 = size_t (std::floor (57.0 * accel));
      target_track_nbr2 = std::min (target_track_nbr2, size_t (57));

      {
         auto & song = document1.root <Song> ();

         for (; track_nbr1 < target_track_nbr1 ; ++track_nbr1)
         {
            //printf ("1> +track\n");
            song._tracks.emplace (song._tracks.end ());
         }

         document1.commit ();
         document1.push ();
      }

      {
         auto & song = document2.root <Song> ();

         for (; track_nbr2 < target_track_nbr2 ; ++track_nbr2)
         {
            //printf ("2> +track\n");
            song._tracks.emplace (song._tracks.end ());
         }

         document2.commit ();
         document2.push ();
      }

      loop_flag = false;

      {
         document1.pull ();

         auto & song = document1.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }

      {
         document2.pull ();

         auto & song = document2.root <Song> ();
         loop_flag |= std::count_if (
            song._tracks.begin (), song._tracks.end (), [](const Track &){return true;}
         ) != 157;
      }
   }
}



}  // namespace flip



flip_RESTORE_WARNINGS



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

