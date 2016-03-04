/*****************************************************************************

      TestServerHttp.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestServerHttp.h"

#include "flip/Class.h"
#include "flip/DocumentServer.h"
#include "flip/DocumentValidatorVoid.h"
#include "flip/contrib/ServerHttp.h"
#include "TestDef.h"

#include <algorithm>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestServerHttp::run ()
{
   Model::version ("test");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int");

   Model::declare <B> ()
      .name ("B")
      .enumerator <B::x0> ("x0")
      .enumerator <B::x1> ("x1");

   Model::declare <Root> ()
      .name ("Root")
      .member <Bool, &Root::_bool> ("bool")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <Enum <B>, &Root::_enum> ("enum")
      .member <ObjectRef <A>, &Root::_object_ref> ("object_ref")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <Collection <A>, &Root::_coll> ("coll")
      .member <Array <A>, &Root::_array> ("array")
      .member <Message <>, &Root::_message> ("message")
      .member <A, &Root::_a> ("a");



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
   run_013 ();
   run_014 ();
   run_015 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : connect_loopback
==============================================================================
*/

Socket::Id  TestServerHttp::connect_loopback ()
{
   Socket::Id fd = Socket::create_tcp ();

   struct sockaddr_in target;
   target.sin_family = AF_INET;

flip_DISABLE_WARNINGS_TRUSTED_MACROS
   target.sin_port = htons (8080);
   target.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
flip_RESTORE_WARNINGS

   int err = ::connect (
      fd,
      reinterpret_cast <struct sockaddr *> (&target),
      sizeof (struct sockaddr)
   );
   flip_TEST (err == 0);

   return fd;
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestServerHttp::run_000 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   server.process ();
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestServerHttp::run_001 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET / HTTP/1.1\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestServerHttp::run_002 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "POST / HTTP/1.1\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestServerHttp::run_003 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET / HTTP/1.1\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();
   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestServerHttp::run_004 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET / HTTP/";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   req = "1.1\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestServerHttp::run_005 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestServerHttp::run_006 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET /\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestServerHttp::run_007 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   Root & root = document.root <Root> ();
   root._bool = true;
   root._int = 3LL;
   root._float = 2.5;
   root._enum = B::x1;
   root._object_ref = &root._a;
   root._blob = std::vector <uint8_t> {0xff, 0x01, 0x23};
   root._string = "some test";
   root._coll.emplace ();
   root._array.emplace (root._array.end ());
   root._message.send ();
   root._a._int = 5LL;

   document.commit ();

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET / HTTP/1.1\r\n\r\n";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestServerHttp::run_008 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: 14\r\n";
   req += "\r\n";
   req += "test/bool=true";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestServerHttp::run_009 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: \r\n";
   req += "\r\n";
   req += "test/bool=true";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestServerHttp::run_010 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req;
   req += "POS / HTTP/1.1\r\n";
   req += "Content-Length: 14\r\n";
   req += "\r\n";
   req += "test/bool=true";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestServerHttp::run_011 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string body;
   body += "test/bool=true";
   body += "&test/int=2";
   body += "&test/float=3.5";
   body += "&test/string=blabla+%2F";
   body += "&test/a/int=5";

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: 76\r\n";
   req += "\r\n";
   req += body;

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestServerHttp::run_012 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Root & root = document.root <Root> ();
   root._coll.emplace ();
   root._array.emplace (root._array.end ());

   Socket::Id fd = connect_loopback ();

   std::string body;
   body += "test/coll/0/int=2";
   body += "&test/array/0/int=3";

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: 36\r\n";
   req += "\r\n";
   req += body;

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestServerHttp::run_013 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req = "GET / ";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);

   server.process ();
   server.process ();
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestServerHttp::run_014 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: 12\r\n";
   req += "\r\n";
   req += "test/enum=x1";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestServerHttp::run_015 ()
{
   DocumentValidatorVoid validator;
   DocumentServer document (Model::use (), validator, 123456789ULL);

   ServerHttp server (document, 8080);

   Socket::Id fd = connect_loopback ();

   std::string req;
   req += "POST / HTTP/1.1\r\n";
   req += "Content-Length: 12\r\n";
   req += "\r\n";
   req += "test/enum=x2";

   Socket::send (fd, req.c_str (), req.size ());

   server.process ();
   server.process ();

   Socket::release (fd);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

