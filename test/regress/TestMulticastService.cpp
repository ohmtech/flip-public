/*****************************************************************************

      TestMulticastService.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestMulticastService.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/contrib/MulticastService.h"
#include "flip/contrib/MulticastServiceExplorer.h"
#include "flip/contrib/MulticastServiceProvider.h"
#include "TestDef.h"

#if (flip_PLATFORM == flip_PLATFORM_WIN32)

#else
   #include <unistd.h>

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

void  TestMulticastService::run ()
{
   Model::version ("test.multicast");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <Root> ()
      .name ("Root")
      .member <A, &Root::_a> ("a");

   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();

   // reset to default values
   MulticastService::use ().set_ip (0xefeefe89);
   MulticastService::use ().set_port_range (59150, 59169);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestMulticastService::run_000 ()
{
   MulticastService::use ().set_ip (0xefeefe89);
   MulticastService::use ().set_port_range (59150, 59169);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::map <std::string, std::string> metadata;
   metadata ["name"] = "Some test session";
   metadata ["date"] = "2015/05/06";

   MulticastServiceProvider provider (1234, document, metadata);

   MulticastServiceExplorer explorer;
   explorer.set_update_period (0.1);   // 100 ms timeout for test

   bool loop_flag = true;

   while (loop_flag)
   {
      explorer.process ();
      provider.process ();

      loop_flag = explorer.begin () == explorer.end ();
   }

   flip_TEST (std::count_if (explorer.begin (), explorer.end (), [](const MulticastServiceExplorer::Session & session){
      return
         (session.ip != 0)
         && (session.port == 1234)
         && (session.version == "test.multicast")
         ;
   }) == 1);

   for (auto && session : explorer)
   {
      if (session.version == "test.multicast")
      {
         auto it = session.metadata.find ("name");
         flip_TEST (it != session.metadata.end ());
         flip_TEST (it->second == "Some test session");

         auto it2 = session.metadata.find ("date");
         flip_TEST (it2 != session.metadata.end ());
         flip_TEST (it2->second == "2015/05/06");
      }
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestMulticastService::run_001 ()
{
   MulticastService::use ().set_ip (0xefeefe89);
   MulticastService::use ().set_port_range (59150, 59151);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::map <std::string, std::string> metadata;
   metadata ["name"] = "Some test session";
   metadata ["date"] = "2015/05/06";

   MulticastServiceProvider provider (1234, document, metadata);
   flip_CHECK_THROW (MulticastServiceProvider provider2 (1234, document, metadata));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestMulticastService::run_002 ()
{
   MulticastService::use ().set_ip (0xefeefe89);
   MulticastService::use ().set_port_range (59150, 59151);

   MulticastServiceExplorer explorer;
   flip_CHECK_THROW (MulticastServiceExplorer explorer2);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestMulticastService::run_003 ()
{
   {
      std::vector <uint8_t> data = {0xff};
      run_003 (data);
   }

   {
      std::vector <uint8_t> data;
      data.resize (24, 0);
      run_003 (data);
   }

   {
      std::vector <uint8_t> data;
      data.resize (25, 255);
      run_003 (data);
   }

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << 'joy!' << 'flip' << 'serv';
      sbo << uint8_t (32);

      run_003 (data);
   }

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << 'joy!' << 'flip' << 'serv';
      sbo << uint16_t (10000);
      sbo << uint32_t (1234567);
      sbo << uint32_t (1234567);
      sbo << uint32_t (1234567);

      run_003 (data);
   }

   {
      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << 'joy!' << 'flip' << 'serv';
      sbo << uint16_t (10000);
      sbo << std::string ("version");
      sbo << uint32_t (1234567);

      run_003 (data);
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestMulticastService::run_003 (const std::vector <uint8_t> & data)
{
   MulticastService::use ().set_ip (0xefeefe89);
   MulticastService::use ().set_port_range (59150, 59169);

   MulticastServiceSocket socket (0xefeefe89, 59150);

   MulticastServiceExplorer explorer;

   bool loop_flag = true;

   while (loop_flag)
   {
      explorer.process ();

      loop_flag = !socket.has_receive ();
   }

   uint32_t ip = 0;
   uint16_t port = 0;
   std::vector <uint8_t> recv_data;

   socket.receive (ip, port, recv_data);
   socket.send (ip, port, data);

   while (!explorer.impl_socket ().has_receive ())
   {
      // busy loop
   }

   explorer.process ();
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

