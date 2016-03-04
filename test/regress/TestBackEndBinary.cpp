/*****************************************************************************

      TestBackEndBinary.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestBackEndBinary.h"

#include "flip/BackEndBinary.h"
#include "flip/BackEndIR.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "TestDef.h"

#include <limits>

#include <cmath>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestBackEndBinary::run ()
{
   Model::version ("test.backend");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <B> ()
      .name ("B")
      .inherit <A> ()
      .member <Int, &B::_int2> ("int2")
      .member <Float, &B::_float2> ("float2")
      .member <Collection <A>, &B::_coll> ("coll");

   Model::declare <Root> ()
      .name ("Root")
      .member <Bool, &Root::_bool> ("bool")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <Array <A>, &Root::_array_a> ("array_a")
      .member <Message <uint32_t>, &Root::_message> ("message");



   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestBackEndBinary::run_000 ()
{
   std::vector <uint8_t> data;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._bool = true;
      root._int = 3LL;
      root._float = 3.5;
      root._blob = std::vector <uint8_t> ({0x00, 0x01, 0xff});
      root._string = " this is a test ";

      root._a._bool = false;
      root._a._int = 4LL;
      root._a._float = 4.5;

      root._ref_a = &root._a;

      root._b._int = 17LL;
      root._b._float = 17.5;
      root._b._int2 = 19LL;
      root._b._float2 = 1.0 / 7.0;
      root._b._coll.emplace (15LL, -1.2);
      root._b._coll.emplace (15LL, -1.2);
      root._b._coll.emplace (
         std::numeric_limits<int64_t>::max (), std::numeric_limits<double>::max ()
      );
      root._b._coll.emplace (
         std::numeric_limits<int64_t>::min (), std::numeric_limits<double>::min ()
      );
      root._b._coll.emplace (
         std::numeric_limits<int64_t>::min (), std::numeric_limits<double>::lowest ()
      );

      root._coll_a.emplace (
         0LL, std::numeric_limits<double>::denorm_min ()
      );
      root._coll_a.emplace (
         -1LL, std::numeric_limits<double>::infinity ()
      );

      {
         B & b = *root._coll_b.emplace (
            123456LL, std::numeric_limits<double>::epsilon (), -13LL, 1.0 / 3.0
         );

         b._coll.emplace (-12LL, 0.25);
         b._coll.emplace (-12LL, 0.25);
      }

      root._array_a.emplace (
         root._array_a.end (),
         0LL, std::numeric_limits<double>::denorm_min ()
      );
      root._array_a.emplace (
         root._array_a.end (),
         -2LL, std::numeric_limits<double>::infinity ()
      );

      document.commit ();

      DataConsumerMemory consumer (data);

      BackEndIR backend = document.write ();
      backend.write <BackEndBinary> (consumer);
   }

   {
      DataProviderMemory provider (data);

      BackEndIR backend;
      backend.register_backend <BackEndBinary> ();

      bool ok_flag = backend.read (provider);
      flip_TEST (ok_flag);

      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      document.read (backend);
      document.commit ();

      Root & root = document.root <Root> ();

      flip_TEST (root._bool == true);
      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 3.5);
      flip_TEST (root._blob == std::vector <uint8_t> ({0x00, 0x01, 0xff}));
      flip_TEST (root._string == " this is a test ");

      flip_TEST (root._a._bool == false);
      flip_TEST (root._a._int == 4LL);
      flip_TEST (root._a._float == 4.5);

      flip_TEST (root._ref_a == &root._a);

      flip_TEST (root._b._int == 17LL);
      flip_TEST (root._b._float == 17.5);
      flip_TEST (root._b._int2 == 19LL);
      flip_TEST (root._b._float2 == 1.0 / 7.0);

      flip_TEST (root._b._coll.count_if ([](A &){return true;}) == 5);
      flip_TEST (root._b._coll.count_if ([](A & elem){
         return (elem._int == 15LL) && (elem._float == -1.2);
      }) == 2);
      flip_TEST (root._b._coll.count_if ([](A & elem){
         return (elem._int == std::numeric_limits<int64_t>::max ())
         && (elem._float == std::numeric_limits<double>::max ());
      }) == 1);
      flip_TEST (root._b._coll.count_if ([](A & elem){
         return (elem._int == std::numeric_limits<int64_t>::min ())
         && (elem._float == std::numeric_limits<double>::min ());
      }) == 1);
      flip_TEST (root._b._coll.count_if ([](A & elem){
         return (elem._int == std::numeric_limits<int64_t>::min ())
         && (elem._float == std::numeric_limits<double>::lowest ());
      }) == 1);

      flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == 0LL)
         && (elem._float == std::numeric_limits<double>::denorm_min ());
      }) == 1);
      flip_TEST (root._coll_a.count_if ([](A & elem){
         return (elem._int == -1LL)
         && (elem._float == std::numeric_limits<double>::infinity ());
      }) == 1);

      {
         flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
         flip_TEST (root._coll_b.count_if ([](B & elem){
            return (elem._int == 123456LL)
            && (elem._float == std::numeric_limits<double>::epsilon ())
            && (elem._int2 == -13LL)
            && (elem._float2 == 1.0 / 3.0);
         }) == 1);
         B & b = *root._coll_b.begin ();
         flip_TEST (b._coll.count_if ([](A &){return true;}) == 2);
         flip_TEST (b._coll.count_if ([](A & elem){
            return (elem._int == -12LL)
            && (elem._float == 0.25);
         }) == 2);
      }

      flip_TEST (root._array_a.count_if ([](A &){return true;}) == 2);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == 0LL)
         && (elem._float == std::numeric_limits<double>::denorm_min ());
      }) == 1);
      flip_TEST (root._array_a.count_if ([](A & elem){
         return (elem._int == -2LL)
         && (elem._float == std::numeric_limits<double>::infinity ());
      }) == 1);
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestBackEndBinary::run_001 ()
{
   std::vector <uint8_t> data;

   bool throw_flag = false;

   try
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._float = std::nan ("1");
   }
   catch (...)
   {
      throw_flag = true;
   }

   flip_TEST (throw_flag);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestBackEndBinary::run_002 ()
{
   std::vector <uint8_t> data;

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndBinary> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestBackEndBinary::run_003 ()
{
   std::vector <uint8_t> data;
   data.push_back ('j');
   data.push_back ('o');
   data.push_back ('y');
   data.push_back ('!');
   data.push_back ('x');
   data.push_back ('l');
   data.push_back ('i');
   data.push_back ('p');
   data.push_back (0);

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndBinary> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestBackEndBinary::run_004 ()
{
   std::vector <uint8_t> data;
   data.push_back ('j');
   data.push_back ('o');
   data.push_back ('y');
   data.push_back ('@');
   data.push_back ('x');
   data.push_back ('l');
   data.push_back ('i');
   data.push_back ('p');

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndBinary> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestBackEndBinary::run_005 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Root & root = document.root <Root> ();

      root._bool = true;
      root._int = 3LL;
      root._float = 3.5;
      root._blob = std::vector <uint8_t> ({0x00, 0x01, 0xff});
      root._string = " this is a test ";

      root._a._bool = false;
      root._a._int = 4LL;
      root._a._float = 4.5;

      root._ref_a = &root._a;

      root._b._int = 17LL;
      root._b._float = 17.5;
      root._b._int2 = 19LL;
      root._b._float2 = 1.0 / 7.0;

      document.commit ();

      backend = document.write ();
   }

   {
      BackEndIR backend2 = std::move (backend);

      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      document.read (backend2);
      document.commit ();

      Root & root = document.root <Root> ();

      flip_TEST (root._bool == true);
      flip_TEST (root._int == 3LL);
      flip_TEST (root._float == 3.5);
      flip_TEST (root._blob == std::vector <uint8_t> ({0x00, 0x01, 0xff}));
      flip_TEST (root._string == " this is a test ");

      flip_TEST (root._a._bool == false);
      flip_TEST (root._a._int == 4LL);
      flip_TEST (root._a._float == 4.5);

      flip_TEST (root._ref_a == &root._a);

      flip_TEST (root._b._int == 17LL);
      flip_TEST (root._b._float == 17.5);
      flip_TEST (root._b._int2 == 19LL);
      flip_TEST (root._b._float2 == 1.0 / 7.0);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

