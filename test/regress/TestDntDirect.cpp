/*****************************************************************************

      TestDntDirect.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDntDirect.h"

#include "flip/CarrierDirect.h"
#include "flip/Document.h"
#include "flip/DocumentServer.h"
#include "flip/DocumentValidatorVoid.h"
#include "flip/PortDirect.h"

#include "TestDef.h"

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

void  TestDntDirect::run ()
{
   Model::version ("test.dnt.direct");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float");

   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestDntDirect::run_000 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 456789ULL);

   PortDirect port;
   server.port_factory_add (port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   document.pull ();

   Root & root = document.root <Root> ();
   root._int = 10;
   root._float = 2.7;
   document.commit ();
   document.push ();
   document.pull ();

   flip_TEST (root._int == 10LL);
   flip_TEST (root._float == 2.7);

   server.port_factory_remove (port);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDntDirect::run_001 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 456789ULL);

   PortDirect port1;
   server.port_factory_add (port1);

   PortDirect port2;
   server.port_factory_add (port2);

   Document document1 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier1 (document1, port1);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier2 (document2, port2);

   {
      document1.pull ();

      Root & root = document1.root <Root> ();
      root._int = 10;
      root._float = 2.7;
      document1.commit ();
      document1.push ();
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._int == 10LL);
      flip_TEST (root._float == 2.7);
   }

   server.port_factory_remove (port1);
   server.port_factory_remove (port2);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDntDirect::run_002 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 456789ULL);

   PortDirect port1;
   server.port_factory_add (port1);

   PortDirect port2;
   server.port_factory_add (port2);

   Document document1 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier1 (document1, port1);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier2 (document2, port2);

   document1.pull ();
   document2.pull ();

   {
      Root & root = document1.root <Root> ();
      root._int = 10;
      root._float = 2.7;
      document1.commit ();
      document1.push ();
   }

   {
      Root & root = document2.root <Root> ();
      root._int = 11;
      root._float = 2.3;
      document2.commit ();
      document2.push ();
   }

   {
      document1.pull ();

      Root & root = document1.root <Root> ();

      flip_TEST (root._int == 10LL);
      flip_TEST (root._float == 2.7);
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._int == 10LL);
      flip_TEST (root._float == 2.7);
   }

   server.port_factory_remove (port1);
   server.port_factory_remove (port2);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestDntDirect::run_003 ()
{
   DocumentValidatorVoid validator;
   DocumentServer server (Model::use (), validator, 456789ULL);

   PortDirect port1;
   server.port_factory_add (port1);

   PortDirect port2;
   server.port_factory_add (port2);

   Document document1 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier1 (document1, port1);

   Document document2 (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier2 (document2, port2);

   document1.pull ();
   document2.pull ();

   {
      Root & root = document1.root <Root> ();
      root._int = 10;
      document1.commit ();
      document1.push ();
   }

   {
      Root & root = document2.root <Root> ();
      root._float = 2.3;
      document2.commit ();
      document2.push ();
   }

   {
      document1.pull ();

      Root & root = document1.root <Root> ();

      flip_TEST (root._int == 10LL);
      flip_TEST (root._float == 2.3);
   }

   {
      document2.pull ();

      Root & root = document2.root <Root> ();

      flip_TEST (root._int == 10LL);
      flip_TEST (root._float == 2.3);
   }

   server.port_factory_remove (port1);
   server.port_factory_remove (port2);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

