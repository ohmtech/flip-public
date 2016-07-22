/*****************************************************************************

      TestServerSimple.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestServerSimple.h"

#include "flip/Document.h"
#include "flip/contrib/transport_tcp/CarrierTransportSocketTcp.h"
#include "flip/contrib/ServerSimple.h"
#include "flip/detail/fnc.h"
#include "TestDef.h"

#include <memory>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestServerSimple::run ()
{
   Model::version ("test.server.simple");

   Model::declare <Root> ()
      .name ("Root")
      .member <Float, &Root::_tempo> ("tempo");


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
   run_012b ();
   run_013 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : wait_transfer_backend
==============================================================================
*/

void  TestServerSimple::wait_transfer_backend (CarrierTransportSocketTcp & carrier, ServerSimple & server)
{
   flip_TEST (carrier.is_idle ());

   bool loop_flag = true;

   carrier.listen_transfer_backend ([&loop_flag](size_t cur, size_t total){
      loop_flag = cur != total;
   });

   while (loop_flag)
   {
      server.process ();
      carrier.process ();
   }

   flip_TEST (carrier.is_connected ());
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestServerSimple::run_001 ()
{
   ServerSimple server (Model::use (), 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestServerSimple::run_002 ()
{
   ServerSimple server (Model::use (), 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   Document document2 (Model::use (), 123456900ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);
   wait_transfer_backend (carrier2, server);

   {
      auto & root = document.root <Root> ();
      root._tempo = 120.0;
      document.commit ();
      document.push ();
   }

   bool loop_flag = true;

   while (loop_flag)
   {
      carrier.process ();
      carrier2.process ();
      server.process ();

      document2.pull ();

      auto & root = document2.root <Root> ();

      loop_flag = root._tempo != 120.0;
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestServerSimple::run_003 ()
{
   ServerSimple server (Model::use (), 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   Document document2 (Model::use (), 123456900ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

   Document document3 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier3 (document3, 1354321ULL, "127.0.0.1", 9090);

   Document document4 (Model::use (), 123456900ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier4 (document4, 1354321ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);
   wait_transfer_backend (carrier2, server);
   wait_transfer_backend (carrier3, server);
   wait_transfer_backend (carrier4, server);

   {
      auto & root = document.root <Root> ();
      root._tempo = 120.0;
      document.commit ();
      document.push ();
   }

   {
      auto & root = document3.root <Root> ();
      root._tempo = 140.0;
      document3.commit ();
      document3.push ();
   }

   bool loop_flag = true;

   while (loop_flag)
   {
      carrier.process ();
      carrier2.process ();
      carrier3.process ();
      carrier4.process ();
      server.process ();

      document2.pull ();
      document4.pull ();

      auto & root = document2.root <Root> ();
      auto & root2 = document4.root <Root> ();

      loop_flag = false;
      loop_flag |= root._tempo != 120.0;
      loop_flag |= root2._tempo != 140.0;
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestServerSimple::run_004 ()
{
   ServerSimple server (Model::use (), 9090);

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

      wait_transfer_backend (carrier, server);
   }

   while (server.nbr_sessions () != 0)
   {
      server.process ();
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestServerSimple::run_005 ()
{
   ServerSimple server (Model::use (), 9090);

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

      Document document2 (Model::use (), 123456790ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

      wait_transfer_backend (carrier, server);
      wait_transfer_backend (carrier2, server);
   }

   while (server.nbr_sessions () != 0)
   {
      server.process ();
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestServerSimple::run_006 ()
{
   ServerSimple server (Model::use (), 9090);

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

      Document document2 (Model::use (), 123456790ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

      Document document3 (Model::use (), 123456791ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier3 (document3, 465413ULL, "127.0.0.1", 9090);

      Document document4 (Model::use (), 123456792ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier4 (document4, 465413ULL, "127.0.0.1", 9090);

      wait_transfer_backend (carrier, server);
      wait_transfer_backend (carrier2, server);
      wait_transfer_backend (carrier3, server);
      wait_transfer_backend (carrier4, server);
   }

   while (server.nbr_sessions () != 0)
   {
      server.process ();
   }
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestServerSimple::run_007 ()
{
   ServerSimple server (Model::use (), 9090);

   bool validator_notify_called_flag = false;
   bool validator_dtor_called_flag = false;

   class Validator
   :  public DocumentValidatorBase
   {
   public:
      Validator (bool & validator_notify_called_flag_, bool & validator_dtor_called_flag_) : _validator_notify_called_flag (validator_notify_called_flag_), _validator_dtor_called_flag (validator_dtor_called_flag_) {}
      virtual ~Validator () {_validator_dtor_called_flag = true;}

      virtual void   notify_validate (uint64_t user_id, Object & /* object */) override
      {
         _validator_notify_called_flag = true;
         flip_TEST ((user_id == 123456789ULL) || (user_id == 1));
      }

      bool & _validator_notify_called_flag;
      bool & _validator_dtor_called_flag;
   };

   server.bind_validator_factory ([&validator_notify_called_flag, &validator_dtor_called_flag](uint64_t session_id){
      flip_TEST (session_id == 987654ULL);

      return std::make_unique <Validator> (validator_notify_called_flag, validator_dtor_called_flag);
   });

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

      wait_transfer_backend (carrier, server);

      {
         auto & root = document.root <Root> ();
         root._tempo = 120.0;
         document.commit ();
         document.push ();
      }

      while (!validator_notify_called_flag)
      {
         server.process ();
         carrier.process ();
      }

      flip_TEST (!validator_dtor_called_flag);
   }

   while (server.nbr_sessions () != 0)
   {
      server.process ();
   }

   flip_TEST (validator_dtor_called_flag);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestServerSimple::run_008 ()
{
   ServerSimple server (Model::use (), 9090);

   server.bind_init ([](uint64_t session_id, DocumentBase & document){
      flip_TEST (session_id == 987654ULL);

      Root & root = document.root <Root> ();
      root._tempo = 120.0;
   });

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);

   document.pull ();

   auto & root = document.root <Root> ();

   flip_TEST (root._tempo == 120.0);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestServerSimple::run_009 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 1ULL, 'appl', 'gui ');

      Root & root = document.root <Root> ();
      root._tempo = 120.0;
      document.commit ();
      document.push ();

      backend = document.write ();
   }

   ServerSimple server (Model::use (), 9090);

   server.bind_read ([&backend](uint64_t session_id){
      flip_TEST (session_id == 987654ULL);

      return backend;
   });

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);

   document.pull ();

   auto & root = document.root <Root> ();

   flip_TEST (root._tempo == 120.0);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestServerSimple::run_010 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 1ULL, 'appl', 'gui ');

      backend = document.write ();
   }

   ServerSimple server (Model::use (), 9090);

   server.bind_read ([&backend](uint64_t session_id){
      flip_TEST (session_id == 987654ULL);

      return backend;
   });

   server.bind_read ([&backend](uint64_t session_id){
      flip_TEST (session_id == 987654ULL);

      auto & pair = backend.root.members.front ();
      flip_TEST (pair.first == "tempo");
      pair.second.value.float_num = 120.0;

      return backend;
   });

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);

   document.pull ();

   auto & root = document.root <Root> ();

   flip_TEST (root._tempo == 120.0);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestServerSimple::run_011 ()
{
   ServerSimple server (Model::use (), 9090);

   bool write_called_flag = false;

   server.bind_write ([&write_called_flag](uint64_t session_id, const BackEndIR & backend){
      flip_TEST (session_id == 987654ULL);
      flip_TEST (backend.root.members.size () == 1);
      auto & pair = backend.root.members.front ();
      flip_TEST (pair.first == "tempo");
      flip_TEST (pair.second.value.float_num == 120.0);
      write_called_flag = true;
   });

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

      Document document2 (Model::use (), 123456900ULL, 'appl', 'gui ');
      CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

      wait_transfer_backend (carrier, server);

      document.pull ();

      {
         auto & root = document.root <Root> ();
         root._tempo = 120.0;
         document.commit ();
         document.push ();
      }

      bool loop_flag = true;

      while (loop_flag)
      {
         carrier.process ();
         carrier2.process ();
         server.process ();

         document2.pull ();

         auto & root = document2.root <Root> ();

         loop_flag = root._tempo != 120.0;
      }
   }

   while (server.nbr_sessions () != 0)
   {
      server.process ();
   }

   flip_TEST (write_called_flag);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestServerSimple::run_012 ()
{
   ServerSimple server (Model::use (), 9090);

   bool auth_called_flag = false;
   const std::string secret = "most likely a date, and a hash of user id, session id and date";

   server.bind_authenticate ([&auth_called_flag, &secret](uint64_t user_id, uint64_t session_id, std::string metadata){
      flip_TEST (user_id == 123456789ULL);
      flip_TEST (session_id == 987654ULL);
      flip_TEST (metadata == secret);

      auth_called_flag = true;

      return true;
   });

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, secret, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);

   flip_TEST (auth_called_flag);
}



/*
==============================================================================
Name : run_012b
==============================================================================
*/

void  TestServerSimple::run_012b ()
{
   ServerSimple server (Model::use (), 9090);

   bool auth_called_flag = false;

   server.bind_authenticate ([&auth_called_flag](uint64_t user_id, uint64_t session_id, std::string metadata){
      flip_TEST (user_id == 123456789ULL);
      flip_TEST (session_id == 987654ULL);
      flip_TEST (metadata == "");

      auth_called_flag = true;

      return false;
   });

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   while (!auth_called_flag)
   {
      carrier.process ();
      server.process ();
   }
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestServerSimple::run_013 ()
{
   ServerSimple server (Model::use (), 9090);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier (document, 987654ULL, "127.0.0.1", 9090);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierTransportSocketTcp carrier2 (document2, 987654ULL, "127.0.0.1", 9090);

   wait_transfer_backend (carrier, server);

   flip_TEST (carrier2.is_idle ());

   bool loop_flag = true;
   bool connecting_flag = false;
   bool connected_flag = false;
   bool disconnected_flag = false;

   carrier2.listen_state_transition ([&loop_flag, &connecting_flag, &connected_flag, &disconnected_flag](CarrierBase::Transition t, int err){
      connecting_flag |= t == CarrierBase::Transition::Connecting;
      connected_flag |= t == CarrierBase::Transition::Connected;
      disconnected_flag |= t == CarrierBase::Transition::Disconnected;

      if (t == CarrierBase::Transition::Disconnected)
      {
         flip_TEST (err == 0);
      }

      loop_flag = ! (connecting_flag && connected_flag && disconnected_flag);
   });

   while (loop_flag)
   {
      server.process ();
      carrier2.process ();
   }

   flip_TEST (carrier2.is_idle ());
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

