/*****************************************************************************

      TestEnum.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestEnum.h"

#include "flip/BackEndBinary.h"
#include "flip/BackEndMl.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Mold.h"
#include "flip/contrib/Utml.h"
#include "flip/detail/ExecFlags.h"

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

void  TestEnum::run ()
{
   Model::version ("test.document");

   Model::declare <Enum1> ()
      .name ("Enum1")
      .enumerator <Value0> ("Value0")
      .enumerator <Value1> ("Value1");

   Model::declare <Enum2> ()
      .name ("Enum2")
      .enumerator <Enum2::Value0> ("Value0")
      .enumerator <Enum2::Value1> ("Value1");

   Model::declare <Root> ()
      .name ("Root")
      .member <Enum <Enum1>, &Root::_enum1> ("enum1")
      .member <Enum <Enum2>, &Root::_enum2> ("enum2");


   Model2::declare <EnumWrong1> ()
      .name ("EnumWrong1")
      .enumerator <EnumWrong1_Value0> ("Value0");

   flip_CHECK_THROW (Model2::use ());

   Model3::declare <EnumWrong2> ()
      .name ("EnumWrong2")
      .enumerator <EnumWrong2_Value0> ("Value0")
      .enumerator <EnumWrong2_Value1> ("Value1");

   flip_CHECK_THROW (Model3::use ());

   auto & dm = Model4::declare <Root4> ()
      .name ("Root4");

   flip_CHECK_THROW ((dm.member <Enum <EnumUndefined>, &Root4::_enum> ("enum")));

   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestEnum::run_000 ()
{
   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   root._enum1 = Enum1::Value0;

   flip_TEST (root._enum1.get_before () == 0LL);
   flip_TEST (root._enum1 == Enum1::Value0);

   document.commit ();

   flip_TEST (root._enum1.before () == Enum1::Value0);
   flip_TEST (root._enum1 == Enum1::Value0);

   root._enum1 = Enum1::Value1;

   flip_TEST (root._enum1.before () == Enum1::Value0);
   flip_TEST (root._enum1 == Enum1::Value1);

   auto tx = document.commit ();

   flip_TEST (root._enum1.before () == Enum1::Value1);
   flip_TEST (root._enum1 == Enum1::Value1);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum1.before () == Enum1::Value1);
   flip_TEST (root._enum1 == Enum1::Value0);

   document.commit ();

   flip_TEST (root._enum1.before () == Enum1::Value0);
   flip_TEST (root._enum1 == Enum1::Value0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum1.before () == Enum1::Value0);
   flip_TEST (root._enum1 == Enum1::Value1);

   document.commit ();

   flip_TEST (root._enum1.before () == Enum1::Value1);
   flip_TEST (root._enum1 == Enum1::Value1);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestEnum::run_001 ()
{
   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   root._enum2 = Enum2::Value0;

   flip_TEST (root._enum2.get_before () == 0LL);
   flip_TEST (root._enum2 == Enum2::Value0);

   document.commit ();

   flip_TEST (root._enum2.before () == Enum2::Value0);
   flip_TEST (root._enum2 == Enum2::Value0);

   root._enum2 = Enum2::Value1;

   flip_TEST (root._enum2.before () == Enum2::Value0);
   flip_TEST (root._enum2 == Enum2::Value1);

   auto tx = document.commit ();

   flip_TEST (root._enum2.before () == Enum2::Value1);
   flip_TEST (root._enum2 == Enum2::Value1);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum2.before () == Enum2::Value1);
   flip_TEST (root._enum2 == Enum2::Value0);

   document.commit ();

   flip_TEST (root._enum2.before () == Enum2::Value0);
   flip_TEST (root._enum2 == Enum2::Value0);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum2.before () == Enum2::Value0);
   flip_TEST (root._enum2 == Enum2::Value1);

   document.commit ();

   flip_TEST (root._enum2.before () == Enum2::Value1);
   flip_TEST (root._enum2 == Enum2::Value1);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestEnum::run_002 ()
{
   BackEndIR backend;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      root._enum1 = Enum1::Value1;
      root._enum2 = Enum2::Value1;

      backend = document.write ();
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      document.read (backend);

      Root & root = document.root <Root> ();

      flip_TEST (root._enum1 == Enum1::Value1);
      flip_TEST (root._enum2 == Enum2::Value1);
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestEnum::run_003 ()
{
   std::vector <uint8_t> data;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      root._enum1 = Enum1::Value1;
      root._enum2 = Enum2::Value1;

      BackEndIR backend = document.write ();
      DataConsumerMemory consumer (data);

      backend.write <BackEndBinary> (consumer);
   }

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      DataProviderMemory provider (data);

      BackEndIR backend;
      backend.register_backend <BackEndBinary> ();
      backend.read (provider);

      document.read (backend);

      Root & root = document.root <Root> ();

      flip_TEST (root._enum1 == Enum1::Value1);
      flip_TEST (root._enum2 == Enum2::Value1);
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestEnum::run_004 ()
{
   std::vector <uint8_t> data;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      root._enum1 = Enum1::Value1;
      root._enum2 = Enum2::Value1;

      BackEndIR backend = document.write ();
      DataConsumerMemory consumer (data);

      backend.write <BackEndMl> (consumer);
   }

   //printf ("%s", std::string (data.begin (), data.end ()).c_str ());

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      DataProviderMemory provider (data);

      BackEndIR backend;
      backend.register_backend <BackEndMl> ();
      backend.read (provider);

      document.read (backend);

      Root & root = document.root <Root> ();

      flip_TEST (root._enum1 == Enum1::Value1);
      flip_TEST (root._enum2 == Enum2::Value1);
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestEnum::run_005 ()
{
   std::vector <uint8_t> data;

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
      Root & root = document.root <Root> ();

      root._enum1 = Enum1::Value1;
      root._enum2 = Enum2::Value1;

      BackEndIR backend = document.write ();
      DataConsumerMemory consumer (data);

      Utml::write (consumer, backend);
   }

   //printf ("%s", std::string (data.begin (), data.end ()).c_str ());

   {
      Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

      DataProviderMemory provider (data);

      BackEndIR backend = Utml::read (provider, Model::use ());

      document.read (backend);

      Root & root = document.root <Root> ();

      flip_TEST (root._enum1 == Enum1::Value1);
      flip_TEST (root._enum2 == Enum2::Value1);
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestEnum::run_006 ()
{
   {
      Enum <Enum1> val;
      flip_TEST (val == Enum1::Value0);
      flip_TEST (val.value () == Enum1::Value0);
      flip_TEST (val.before () == Enum1::Value0);
      flip_TEST (Enum1::Value0 == val);
      flip_TEST (Enum1::Value1 != val);
   }

   {
      Enum <Enum1> val (Enum1::Value1);
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
      flip_TEST (Enum1::Value1 == val);
      flip_TEST (Enum1::Value0 != val);
   }

   {
      Enum <Enum1> val = Enum1::Value1;
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val (other);
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val = other;
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val (std::move (other));
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val = std::move (other);
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val;
      val = other;
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }

   {
      Enum <Enum1> other (Enum1::Value1);

      Enum <Enum1> val;
      val = std::move (other);
      flip_TEST (val == Enum1::Value1);
      flip_TEST (val.value () == Enum1::Value1);
      flip_TEST (val.before () == Enum1::Value0);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

