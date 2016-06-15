/*****************************************************************************

      TestTransaction.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestTransaction.h"

#include "flip/Document.h"
#include "flip/DocumentValidatorVoid.h"
#include "flip/detail/Direction.h"
#include "flip/detail/ExecFlags.h"
#include "flip/detail/TxId.h"
#include "flip/detail/TxIdRange.h"
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

void  TestTransaction::run ()
{
   Model::version ("test.tx");

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

   Model::declare <C::D> ()
      .name ("D")
      .enumerator <C::D::x0> ("x0")
      .enumerator <C::D::x1> ("x1")
      .enumerator <C::D::x2> ("x2");

   Model::declare <C> ()
      .name ("C")
      .member <Bool, &C::_bool> ("bool")
      .member <Blob, &C::_blob> ("blob")
      .member <String, &C::_string> ("string")
      .member <Collection <A>, &C::_coll> ("coll")
      .member <Array <A>, &C::_array> ("array")
      .member <ObjectRef <A>, &C::_ref> ("ref")
      .member <Message <>, &C::_message> ("message")
      .member <Enum <C::D>, &C::_enum> ("enum");

   Model::declare <Root::D> ()
      .name ("D")
      .enumerator <Root::D::x0> ("x0")
      .enumerator <Root::D::x1> ("x1")
      .enumerator <Root::D::x2> ("x2");

   Model::declare <Root> ()
      .name ("Root")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <A, &Root::_a> ("a")
      .member <B, &Root::_b> ("b")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Bool, &Root::_bool> ("bool")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <Bool, &Root::_bool2> ("bool2")
      .member <Blob, &Root::_blob2> ("blob2")
      .member <String, &Root::_string2> ("string2")
      .member <Collection <C>, &Root::_coll_c> ("coll_c")
      .member <Message <uint32_t>, &Root::_message> ("message")
      .member <Array <A>, &Root::_array_a> ("array_a")
      .member <Enum <Root::D>, &Root::_enum> ("enum")
      .member <Enum <Root::D>, &Root::_enum2> ("enum2");

   Model::use (); // force post-processing

   run_pre ();
   run_pre2 ();

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

   run_016 ();
   run_017 ();
   run_018 ();
   run_019 ();
   run_020 ();

   run_021 ();
   run_022 ();
   run_023 ();

   run_024 ();
   run_025 ();
   run_026 ();

   run_027 ();
   run_028 ();
   run_029 ();

   run_030 ();
   run_031 ();
   run_032 ();

   run_033 ();
   run_034 ();
   run_035 ();
   run_036 ();
   run_037 ();
   run_038 ();
   run_039 ();

   run_040 ();
   run_041 ();
   run_042 ();
   run_043 ();
   run_044 ();
   run_045 ();
   run_046 ();

   run_047 ();
   run_048 ();
   run_049 ();
   run_050 ();
   run_051 ();
   run_052 ();
   run_053 ();

   run_054 ();
   run_055 ();
   run_056 ();
   run_057 ();
   run_058 ();
   run_059 ();

   run_060 ();
   run_061 ();
   run_062 ();
   run_063 ();
   run_064 ();
   run_065 ();

   run_066 ();
   run_067 ();
   run_068 ();
   run_069 ();
   run_070 ();
   run_071 ();

   run_072 ();
   run_073 ();
   run_074 ();
   run_075 ();

   run_076 ();
   run_077 ();

   run_078 ();
   run_079 ();
   run_080 ();

   run_081 ();
   run_082 ();
   run_083 ();
   run_084 ();
   run_085 ();
   run_086 ();
   run_087 ();
   run_088 ();
   run_089 ();
   run_090 ();

   run_091 ();
   run_092 ();

   run_093 ();
   run_094 ();

   run_095 ();
   run_096 ();

   run_097 ();
   run_098 ();

   run_099 ();

   run_100 ();

   run_101 ();
   run_101b ();
   run_102 ();
   run_103 ();

   run_104 ();
   run_105 ();
   run_106 ();
   run_107 ();
   run_108 ();
   run_109 ();
   run_109b ();
   run_110 ();
   run_110b ();
   run_111 ();
   run_112 ();
   run_113 ();
   run_114 ();
   run_115 ();
   run_116 ();

   run_117 ();
   run_118 ();
   run_119 ();
   run_120 ();
   run_121 ();
   run_122 ();
   run_123 ();
   run_124 ();
   run_125 ();
   run_126 ();
   run_127 ();
   run_128 ();
   run_129 ();
   run_130 ();
   run_131 ();
   run_132 ();
   run_133 ();
   run_134 ();
   run_135 ();

   run_136 ();
   run_137 ();
   run_137b ();
   run_138 ();
   run_138b ();
   run_139 ();
   run_139b ();

   run_140 ();
   run_140b ();

   run_141 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre
==============================================================================
*/

void  TestTransaction::run_pre ()
{
   {
      TxId tx_id;
      TxId tx_id2 (1, 0, 0);

      flip_TEST (tx_id != tx_id2);
   }

   {
      TxId tx_id;
      TxId tx_id2 (0, 4, 0);

      flip_TEST (tx_id != tx_id2);
   }

   {
      TxId tx_id;
      TxId tx_id2 (0, 0, 7);

      flip_TEST (tx_id != tx_id2);
   }

   {
      TxId tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id == tx_id2);
      flip_TEST (! (tx_id != tx_id2));
   }

   {
      TxId tx_id (123456789ULL, 654987321ULL, 198557540ULL);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id == tx_id2);
      flip_TEST (! (tx_id != tx_id2));
   }

   {
      TxId tx_id (123456789ULL, 654987321ULL, 198557540ULL);
      TxId tx_id3 = tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id == tx_id2);
      flip_TEST (! (tx_id != tx_id2));
   }

   {
      TxId tx_id (123456789ULL, 654987321ULL, 198557540ULL);
      TxId tx_id3 = std::move (tx_id);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id3 == tx_id2);
      flip_TEST (! (tx_id3 != tx_id2));
   }

   {
      TxId tx_id (123456789ULL, 654987321ULL, 198557540ULL);
      TxId tx_id3;
      tx_id3 = tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id == tx_id2);
      flip_TEST (! (tx_id != tx_id2));
   }

   {
      TxId tx_id (123456789ULL, 654987321ULL, 198557540ULL);
      TxId tx_id3;
      tx_id3 = std::move (tx_id);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxId tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id3 == tx_id2);
      flip_TEST (! (tx_id3 != tx_id2));
   }
}



/*
==============================================================================
Name : run_pre2
==============================================================================
*/

void  TestTransaction::run_pre2 ()
{
   {
      TxIdRange tx_id (1, 2, 3, 4);

      flip_TEST (tx_id.user_id == 1);
      flip_TEST (tx_id.actor_id == 2);
      flip_TEST (tx_id.nbr_id_first == 3);
      flip_TEST (tx_id.nbr_id_last == 4);
   }

   {
      TxIdRange tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id.user_id == tx_id2.user_id);
      flip_TEST (tx_id.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id.nbr_id_last == tx_id2.nbr_id_last);
   }

   {
      TxIdRange tx_id (123456789ULL, 654987321ULL, 198557540ULL, 460409854601ULL);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id.user_id == tx_id2.user_id);
      flip_TEST (tx_id.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id.nbr_id_last == tx_id2.nbr_id_last);
   }

   {
      TxIdRange tx_id (123456789ULL, 654987321ULL, 198557540ULL, 460409854601ULL);
      TxIdRange tx_id3 = tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id.user_id == tx_id2.user_id);
      flip_TEST (tx_id.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id.nbr_id_last == tx_id2.nbr_id_last);
   }

   {
      TxIdRange tx_id (123456789ULL, 654987321ULL, 198557540ULL, 460409854601ULL);
      TxIdRange tx_id3 = std::move (tx_id);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id3.user_id == tx_id2.user_id);
      flip_TEST (tx_id3.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id3.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id3.nbr_id_last == tx_id2.nbr_id_last);
   }

   {
      TxIdRange tx_id (123456789ULL, 654987321ULL, 198557540ULL, 460409854601ULL);
      TxIdRange tx_id3;
      tx_id3 = tx_id;

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id.user_id == tx_id2.user_id);
      flip_TEST (tx_id.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id.nbr_id_last == tx_id2.nbr_id_last);
   }

   {
      TxIdRange tx_id (123456789ULL, 654987321ULL, 198557540ULL, 460409854601ULL);
      TxIdRange tx_id3;
      tx_id3 = std::move (tx_id);

      std::vector <uint8_t> data;
      StreamBinOut sbo (data);

      sbo << tx_id3;

      TxIdRange tx_id2;
      StreamBinIn sbi (data);

      sbi >> tx_id2;

      flip_TEST (tx_id3.user_id == tx_id2.user_id);
      flip_TEST (tx_id3.actor_id == tx_id2.actor_id);
      flip_TEST (tx_id3.nbr_id_first == tx_id2.nbr_id_first);
      flip_TEST (tx_id3.nbr_id_last == tx_id2.nbr_id_last);
   }
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestTransaction::run_000 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 19LL);
   flip_TEST (root._int != 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);
   flip_TEST (root._int != 19LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

   tx.clear ();
   flip_TEST (tx.empty ());
   flip_TEST (tx.user () == 0);
   flip_TEST (tx.actor () == 0);
   flip_TEST (tx.nbr () == 0);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestTransaction::run_001 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);

   Transaction tx2 (document.user (), document.actor (), 2);
   tx2.push_int64_set (root_int_ref, 0, 19LL, 23LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 19LL);

   ok_flag = tx2.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 23LL);

   ok_flag = tx2.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 19LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestTransaction::run_002 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 19LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

   tx.clear ();
   flip_TEST (tx.empty ());
   flip_TEST (tx.user () == 0);
   flip_TEST (tx.actor () == 0);
   flip_TEST (tx.nbr () == 0);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestTransaction::run_003 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);
   tx.push_int64_set (root_int_ref, 0, 19LL, 23LL);
   tx.push_int64_set (root_int_ref, 0, 23LL, 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestTransaction::run_004 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);
   tx.push_int64_set (root_int_ref, 0, 20LL, 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestTransaction::run_005 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_float_ref, 0, 0.0, 19.5);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 19.5);
   flip_TEST (root._float != 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);
   flip_TEST (root._float != 19.5);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestTransaction::run_006 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_float_ref, 0, 0.0, 19.5);

   Transaction tx2 (document.user (), document.actor (), 2);
   tx2.push_float64_set (root_float_ref, 0, 19.5, 27.2397);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 19.5);

   ok_flag = tx2.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 27.2397);

   ok_flag = tx2.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 19.5);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestTransaction::run_007 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_float_ref, 0, 0.0, 19.5);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 19.5);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 19.5);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestTransaction::run_008 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_float_ref, 0, 0.0, 19.5);
   tx.push_float64_set (root_float_ref, 0, 19.5, 27.2397);
   tx.push_float64_set (root_float_ref, 0, 27.2397, 0.0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestTransaction::run_009 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_float_ref, 0, 0.0, 19.5);
   tx.push_float64_set (root_float_ref, 0, 20.0, 0.0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestTransaction::run_010 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 1ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_int_ref, 0, 0.0, 19.5);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestTransaction::run_011 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_float_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestTransaction::run_012 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 123456ULL;

   bool ok_flag = false;

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestTransaction::run_013 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_int_ref = root_ref + 4ULL;

   bool ok_flag = false;

   flip_TEST (root._a._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root_int_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._a._int == 19LL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._a._int == 0LL);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestTransaction::run_014 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_coll_ref = root_ref + 12ULL;

   bool ok_flag = false;

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   KeyRandom key;
   uint32_t type_id = Class <A>::use ().type_id (document.data_model ());
   Ref elem_ref = Ref::make (document.user (), document.actor (), 1234ULL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (root_coll_ref, 0, key, type_id, elem_ref);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestTransaction::run_015 ()
{
   KeyRandom key;

   Transaction tx;
   tx.push_int64_set (Ref::root + 1, 0, 0LL, 1LL);
   tx.push_float64_set (Ref::root + 2, 0, 0.0, 0.23);
   tx.push_collection_insert (Ref::root + 3, 0, key, 1000, Ref::root + 4);
   tx.push_collection_erase (Ref::root + 3, 0, key, 1000, Ref::root + 4);

   Transaction tx2;
   tx2.push_int64_set (Ref::root + 1, 0, 1LL, 7LL);
   tx2.push_float64_set (Ref::root + 2, 0, 0.23, 0.47);
   tx.push (std::move (tx2));

   std::vector <uint8_t> data = tx.serialize ();

   Transaction tx3 (data);

   flip_TEST (tx.equal (tx3));
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestTransaction::run_016 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_obj_ref = root_ref + 14ULL;

   bool ok_flag = false;

   flip_TEST (root._ref_a.get () == Ref::null);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root_obj_ref, 0, Ref::null, root_ref + 3ULL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 3ULL);
   flip_TEST (root._ref_a == &root._a);
   flip_TEST (root._ref_a != &root._b);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestTransaction::run_017 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_obj_ref = root_ref + 14ULL;

   bool ok_flag = false;

   flip_TEST (root._ref_a.get () == Ref::null);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root_obj_ref, 0, Ref::null, root_ref + 3ULL);

   Transaction tx2 (document.user (), document.actor (), 2);
   tx2.push_object_ref_set (root_obj_ref, 0, root_ref + 3ULL, root_ref + 4ULL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 3ULL);

   ok_flag = tx2.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 4ULL);

   ok_flag = tx2.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 3ULL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestTransaction::run_018 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_obj_ref = root_ref + 14ULL;

   bool ok_flag = false;

   flip_TEST (root._ref_a.get () == Ref::null);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root_obj_ref, 0, Ref::null, root_ref + 3ULL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 3ULL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == root_ref + 3ULL);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestTransaction::run_019 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_obj_ref = root_ref + 14ULL;

   bool ok_flag = false;

   flip_TEST (root._ref_a.get () == Ref::null);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root_obj_ref, 0, Ref::null, root_ref + 3ULL);
   tx.push_object_ref_set (root_obj_ref, 0, root_ref + 3ULL, root_ref + 4ULL);
   tx.push_object_ref_set (root_obj_ref, 0, root_ref + 4ULL, Ref::null);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestTransaction::run_020 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_obj_ref = root_ref + 14ULL;

   bool ok_flag = false;

   flip_TEST (root._ref_a.get () == Ref::null);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root_obj_ref, 0, Ref::null, root_ref + 3ULL);
   tx.push_object_ref_set (root_obj_ref, 0, root_ref + 4ULL, Ref::null);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a.get () == Ref::null);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestTransaction::run_021 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root.ref () + 1, 0, 1LL, 19LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 19LL);

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_int64_set (root.ref () + 1, 0, 0LL, 19LL);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_022
==============================================================================
*/

void  TestTransaction::run_022 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root.ref () + 2, 0, 1.0, 4.5);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 4.5);

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_float64_set (root.ref () + 2, 0, 0.0, 4.5);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_023
==============================================================================
*/

void  TestTransaction::run_023 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._ref_a == nullptr);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root.ref () + 14, 0, root.ref () + 3, root.ref () + 6);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a == nullptr);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a == &root._b);

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_object_ref_set (root.ref () + 14, 0, Ref::null, root.ref () + 6);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_024
==============================================================================
*/

void  TestTransaction::run_024 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root.ref () + 1, 0, 1LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_025
==============================================================================
*/

void  TestTransaction::run_025 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root.ref () + 2, 0, 1.0, 0.0);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_026
==============================================================================
*/

void  TestTransaction::run_026 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._ref_a == nullptr);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root.ref () + 14, 0, root.ref () + 3, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a == nullptr);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a == nullptr);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_027
==============================================================================
*/

void  TestTransaction::run_027 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root.ref () + 1, 0, 0LL, 1LL);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_028
==============================================================================
*/

void  TestTransaction::run_028 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root.ref () + 2, 0, 0.0, 1.0);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_029
==============================================================================
*/

void  TestTransaction::run_029 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._ref_a == nullptr);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root.ref () + 14, 0, Ref::null, root.ref () + 3);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a == nullptr);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a == nullptr);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_030
==============================================================================
*/

void  TestTransaction::run_030 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._int == 0LL);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root.ref (), 0, 1LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._int == 0LL);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._int == 0LL);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_031
==============================================================================
*/

void  TestTransaction::run_031 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root.ref (), 0, 1.0, 0.0);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._float == 0.0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_032
==============================================================================
*/

void  TestTransaction::run_032 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._ref_a == nullptr);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root.ref (), 0, root.ref () + 3, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._ref_a == nullptr);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._ref_a == nullptr);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_033
==============================================================================
*/

void  TestTransaction::run_033 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (root.ref (), 0, KeyRandom (), 1000, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_034
==============================================================================
*/

void  TestTransaction::run_034 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto key = root._coll_a.emplace ().key ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (root._coll_a.ref (), 0, key, 1000, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_035
==============================================================================
*/

void  TestTransaction::run_035 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (root._coll_a.ref (), 0, KeyRandom (), 123456, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_036
==============================================================================
*/

void  TestTransaction::run_036 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), Class <Root>::use ().type_id (document.data_model ()), Ref::null
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);
}



/*
==============================================================================
Name : run_037
==============================================================================
*/

void  TestTransaction::run_037 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (
      root._coll_b.ref (), 0, KeyRandom (), Class <A>::use ().type_id (document.data_model ()), Ref::null
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 0);
}



/*
==============================================================================
Name : run_038
==============================================================================
*/

void  TestTransaction::run_038 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), Class <A>::use ().type_id (document.data_model ()), Ref::root
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_039
==============================================================================
*/

void  TestTransaction::run_039 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), Class <A>::use ().type_id (document.data_model ()), Ref::null
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_040
==============================================================================
*/

void  TestTransaction::run_040 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (root.ref (), 0, KeyRandom (), 1000, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_041
==============================================================================
*/

void  TestTransaction::run_041 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (root._coll_a.ref (), 0, KeyRandom (), 1000, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_042
==============================================================================
*/

void  TestTransaction::run_042 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();
   KeyRandom key = it.key ();
   Ref elem_ref = it->ref ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (root._coll_a.ref (), 0, key, 123456, elem_ref);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_043
==============================================================================
*/

void  TestTransaction::run_043 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();
   KeyRandom key = it.key ();
   Ref elem_ref = it->ref ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (
      root._coll_a.ref (), 0, key, Class <Root>::use ().type_id (document.data_model ()), elem_ref
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_044
==============================================================================
*/

void  TestTransaction::run_044 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_b.emplace ();
   KeyRandom key = it.key ();
   Ref elem_ref = it->ref ();

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (
      root._coll_b.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()), elem_ref
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_b.count_if ([](B &){return true;}) == 1);
}



/*
==============================================================================
Name : run_045
==============================================================================
*/

void  TestTransaction::run_045 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   KeyRandom key = root._coll_a.emplace ().key ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (
      root._coll_a.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()), Ref::root
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_046
==============================================================================
*/

void  TestTransaction::run_046 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   KeyRandom key = root._coll_a.emplace ().key ();

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_collection_erase (
      root._coll_a.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()), Ref::null
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._coll_a.count_if ([](A &){return true;}) == 1);
}



/*
==============================================================================
Name : run_047
==============================================================================
*/

void  TestTransaction::run_047 ()
{
   {
      Opcode opcode (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode3 (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode3 (Ref::root, 0, 4LL, 3LL, Opcode::Integral::NATURAL);
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_048
==============================================================================
*/

void  TestTransaction::run_048 ()
{
   {
      Opcode opcode (Ref::root, 0, 3.7, 2.3);
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 3.7, 2.3);
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 3.7, 2.3);
      Opcode opcode3 (Ref::root, 0, 3.7, 2.3);
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, 3.7, 2.3);
      Opcode opcode3 (Ref::root, 0, 3.7, 2.3);
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_049
==============================================================================
*/

void  TestTransaction::run_049 ()
{
   {
      Opcode opcode (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode3 (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode3 (Ref::root, 0, Ref::root + 1, Ref::root + 3);
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_050
==============================================================================
*/

void  TestTransaction::run_050 ()
{
   {
      Opcode opcode (
         Ref::root, 0, KeyRandom (), 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (
         Ref::root, 0, KeyRandom (), 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      KeyRandom key;

      Opcode opcode (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode3 (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      KeyRandom key;

      Opcode opcode (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode3 (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::INSERT
      );
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_051
==============================================================================
*/

void  TestTransaction::run_051 ()
{
   {
      Opcode opcode (
         Ref::root, 0, KeyRandom (), 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (
         Ref::root, 0, KeyRandom (), 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      KeyRandom key;

      Opcode opcode (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode3 (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      KeyRandom key;

      Opcode opcode (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode3 (
         Ref::root, 0, key, 123456UL, Ref::root + 1, Opcode::Variant::ERASE
      );
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_052
==============================================================================
*/

void  TestTransaction::run_052 ()
{
   {
      Opcode opcode (Ref::root, 0, true, false);
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, true, false);
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, true, false);
      Opcode opcode3 (Ref::root, 0, true, false);
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, true, false);
      Opcode opcode3 (Ref::root, 0, true, false);
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }
}



/*
==============================================================================
Name : run_053
==============================================================================
*/

void  TestTransaction::run_053 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   typedef std::vector <uint8_t> BlobType;

   {
      Opcode opcode (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode2 (opcode);
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode2;
      opcode2 = opcode;
      flip_TEST (opcode.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode3 (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode2 (std::move (opcode));
      flip_TEST (opcode3.equal (opcode2));
   }

   {
      Opcode opcode (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode3 (Ref::root, 0, BlobType ({0x00}), BlobType ({0xff}));
      Opcode opcode2;
      opcode2 = std::move (opcode);
      flip_TEST (opcode3.equal (opcode2));
   }

#endif
}



/*
==============================================================================
Name : run_054
==============================================================================
*/

void  TestTransaction::run_054 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root.ref (), 0, true, false);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_055
==============================================================================
*/

void  TestTransaction::run_055 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root.ref () + 15, 0, true, false);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_056
==============================================================================
*/

void  TestTransaction::run_056 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root.ref () + 15, 0, true, true);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._bool == false);
   flip_TEST (root._bool != true);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._bool);
   flip_TEST (root._bool == true);
   flip_TEST (root._bool != false);

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_bool_set (root.ref () + 15, 0, false, true);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_057
==============================================================================
*/

void  TestTransaction::run_057 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_bool_ref = root_ref + 15ULL;

   bool ok_flag = false;

   flip_TEST (root._bool == false);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root_bool_ref, 0, false, true);
   tx.push_bool_set (root_bool_ref, 0, true, false);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._bool == false);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_058
==============================================================================
*/

void  TestTransaction::run_058 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);

   root._bool = true;
   root._bool = root._bool2;

   flip_TEST (!root._bool);
}



/*
==============================================================================
Name : run_059
==============================================================================
*/

void  TestTransaction::run_059 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   C c;
   c._bool = true;

   flip_TEST (c._bool == true);

   root._coll_c.insert (c);
   flip_TEST (root._coll_c.count_if ([](C &) {return true;}) == 1);
   flip_TEST (root._coll_c.begin ()->_bool == true);
}



/*
==============================================================================
Name : run_060
==============================================================================
*/

void  TestTransaction::run_060 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref (), 0, BlobType ({0x00}), BlobType ({0x00}));

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_061
==============================================================================
*/

void  TestTransaction::run_061 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref () + 16, 0, BlobType ({0x00}), BlobType ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_062
==============================================================================
*/

void  TestTransaction::run_062 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref () + 16, 0, BlobType ({0x01}), BlobType ({0x00}));

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._blob == BlobType ());
   flip_TEST (root._blob != BlobType ({0x00}));

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ({0x00}));
   flip_TEST (root._blob != BlobType ());

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_blob_set (root.ref () + 16, 0, BlobType (), BlobType ({0x00}));

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_063
==============================================================================
*/

void  TestTransaction::run_063 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   Ref root_ref = root.ref ();
   Ref root_blob_ref = root_ref + 16ULL;

   bool ok_flag = false;

   flip_TEST (root._blob == BlobType ());

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root_blob_ref, 0, BlobType (), BlobType ({0xff}));
   tx.push_blob_set (root_blob_ref, 0, BlobType ({0xff}), BlobType ());

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._blob == BlobType ());

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_064
==============================================================================
*/

void  TestTransaction::run_064 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._blob == BlobType ());

   root._blob = BlobType ({0x0f});
   root._blob = root._blob2;

   flip_TEST (root._blob == BlobType ());

#endif
}



/*
==============================================================================
Name : run_065
==============================================================================
*/

void  TestTransaction::run_065 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   C c;
   c._blob = BlobType ({0xf1});

   flip_TEST (c._blob == BlobType ({0xf1}));

   root._coll_c.insert (c);
   flip_TEST (root._coll_c.count_if ([](C &) {return true;}) == 1);
   flip_TEST (root._coll_c.begin ()->_blob == BlobType ({0xf1}));

#endif
}



/*
==============================================================================
Name : run_066
==============================================================================
*/

void  TestTransaction::run_066 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._string == "");
   flip_TEST (root._string != "a");

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref (), 0, BlobType ({0xf1}), BlobType ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._string == "");
   flip_TEST (root._string != "b");

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");
   flip_TEST (root._string != "this");

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_067
==============================================================================
*/

void  TestTransaction::run_067 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._string == "");
   flip_TEST (root._string != "q");

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref () + 17, 0, BlobType ({0xf1}), BlobType ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._string == "");
   flip_TEST (root._string != "b");

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");
   flip_TEST (root._string != "wow");

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_068
==============================================================================
*/

void  TestTransaction::run_068 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   flip_TEST (root._string == "");
   flip_TEST (root._string != "f");

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root.ref () + 17, 0, BlobType ({'c'}), BlobType ({'b'}));

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._string == "");
   flip_TEST (root._string != "b");

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "b");
   flip_TEST (root._string != "c");

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_blob_set (root.ref () + 17, 0, BlobType (), BlobType ({'b'}));

   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_069
==============================================================================
*/

void  TestTransaction::run_069 ()
{
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support

   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   typedef std::vector <uint8_t> BlobType;

   Ref root_ref = root.ref ();
   Ref root_string_ref = root_ref + 17ULL;

   bool ok_flag = false;

   flip_TEST (root._string == "");

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root_string_ref, 0, BlobType (), BlobType ({'b'}));
   tx.push_blob_set (root_string_ref, 0, BlobType ({'b'}), BlobType ());

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._string == "");

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

#endif
}



/*
==============================================================================
Name : run_070
==============================================================================
*/

void  TestTransaction::run_070 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._string == "");

   root._string = "a";
   root._string = root._string2;

   flip_TEST (root._string == "");

   std::string str ("this is a test");

   root._string = str;

   flip_TEST (root._string == "this is a test");
}



/*
==============================================================================
Name : run_071
==============================================================================
*/

void  TestTransaction::run_071 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   C c;
   c._string = "this test";

   flip_TEST (c._string == "this test");

   root._coll_c.insert (c);
   flip_TEST (root._coll_c.count_if ([](C &) {return true;}) == 1);
   flip_TEST (root._coll_c.begin ()->_string == "this test");
}



/*
==============================================================================
Name : run_072
==============================================================================
*/

void  TestTransaction::run_072 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 2LL;
   root._float = 3.4;

   auto tx = document.commit ();

   tx.invert_direction ();

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   tx.invert_direction ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_073
==============================================================================
*/

void  TestTransaction::run_073 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> tx_data;

   {
      root._int = 2LL;
      root._float = 3.4;

      auto tx = document.commit ();

      tx.invert_direction ();

      tx_data = tx.serialize ();
   }

   Transaction tx (tx_data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   tx.invert_direction ();

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_074
==============================================================================
*/

void  TestTransaction::run_074 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 2LL;
   root._float = 3.4;

   auto tx = document.commit ();

   tx.invert_direction ();

   auto tx2 = std::move (tx);

   bool ok_flag = document.execute_forward (tx2);
   flip_TEST (ok_flag);

   tx2.invert_direction ();

   ok_flag = document.execute_forward (tx2);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_075
==============================================================================
*/

void  TestTransaction::run_075 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._int = 2LL;
   root._float = 3.4;

   auto tx = document.commit ();

   tx.invert_direction ();

   Transaction tx2;
   tx2 = std::move (tx);

   bool ok_flag = document.execute_forward (tx2);
   flip_TEST (ok_flag);

   tx2.invert_direction ();

   ok_flag = document.execute_forward (tx2);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_076
==============================================================================
*/

void  TestTransaction::run_076 ()
{
   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (tx.equal (tx2));
   }

   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root, 0, key, Ref::root + 1, key);

      Transaction tx2;
      tx2.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root, 0, key, Ref::root, key2);

      Transaction tx2;
      tx2.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root, 0, key2, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root + 1, 0, key, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyRandom key;
      KeyRandom key2;

      Transaction tx;
      tx.push_collection_move (Ref::root, 0, key, Ref::root + 1, key2);

      std::vector <uint8_t> data = tx.serialize ();

      Transaction tx2 (data);

      flip_TEST (tx.equal (tx2));
   }
}



/*
==============================================================================
Name : run_077
==============================================================================
*/

void  TestTransaction::run_077 ()
{
   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (tx.equal (tx2));
   }

   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root, 0, key, Ref::root + 1, key);

      Transaction tx2;
      tx2.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root, 0, key, Ref::root, key2);

      Transaction tx2;
      tx2.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root, 0, key2, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root + 1, 0, key, Ref::root + 1, key2);

      Transaction tx2;
      tx2.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
      KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

      Transaction tx;
      tx.push_array_move (Ref::root, 0, key, Ref::root + 1, key2);

      std::vector <uint8_t> data = tx.serialize ();

      Transaction tx2 (data);

      flip_TEST (tx.equal (tx2));
   }
}



/*
==============================================================================
Name : run_078
==============================================================================
*/

void  TestTransaction::run_078 ()
{
   {
      std::vector <uint8_t> data {0x00, 0x01, 0xff, 0x70, 0x07};

      Transaction tx;
      tx.push_message_push (Ref::root, 0, data);

      Transaction tx2;
      tx2.push_message_push (Ref::root, 0, data);

      flip_TEST (tx.equal (tx2));
   }

   {
      std::vector <uint8_t> data {0x00, 0x01, 0xff, 0x70, 0x07};
      std::vector <uint8_t> data2 {0x00, 0x02, 0xff, 0x70, 0x07};

      Transaction tx;
      tx.push_message_push (Ref::root, 0, data);

      Transaction tx2;
      tx2.push_message_push (Ref::root, 0, data2);

      flip_TEST (!tx.equal (tx2));
   }

   {
      std::vector <uint8_t> data {0x00, 0x01, 0xff, 0x70, 0x07};

      Transaction tx;
      tx.push_message_push (Ref::root + 1, 0, data);

      Transaction tx2;
      tx2.push_message_push (Ref::root, 0, data);

      flip_TEST (!tx.equal (tx2));
   }

   {
      std::vector <uint8_t> val {0x00, 0x01, 0xff, 0x70, 0x07};

      Transaction tx;
      tx.push_message_push (Ref::root, 0, val);

      std::vector <uint8_t> data = tx.serialize ();

      Transaction tx2 (data);

      flip_TEST (tx.equal (tx2));
   }
}



/*
==============================================================================
Name : run_079
==============================================================================
*/

void  TestTransaction::run_079 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();

   bool ok_flag = false;

   std::vector <uint8_t> data;

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_message_push (root.ref (), 0, data);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_080
==============================================================================
*/

void  TestTransaction::run_080 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();

   bool ok_flag = false;

   std::vector <uint8_t> data;

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_message_push (root.ref (), 0, data);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_081
==============================================================================
*/

void  TestTransaction::run_081 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root._bool.ref (), 0, false, false);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_082
==============================================================================
*/

void  TestTransaction::run_082 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_bool_set (root._bool.ref (), 0, true, true);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_083
==============================================================================
*/

void  TestTransaction::run_083 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root._int.ref (), 0, 0LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_084
==============================================================================
*/

void  TestTransaction::run_084 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_int64_set (root._int.ref (), 0, 2LL, 2LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_085
==============================================================================
*/

void  TestTransaction::run_085 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root._float.ref (), 0, 0.0, 0.0);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_086
==============================================================================
*/

void  TestTransaction::run_086 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root._float.ref (), 0, 2.5, 2.5);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_087
==============================================================================
*/

void  TestTransaction::run_087 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root._ref_a.ref (), 0, Ref::null, Ref::null);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_088
==============================================================================
*/

void  TestTransaction::run_088 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_object_ref_set (root._ref_a.ref (), 0, root._ref_a.ref (), root._ref_a.ref ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_089
==============================================================================
*/

void  TestTransaction::run_089 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root._blob.ref (), 0, data, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_090
==============================================================================
*/

void  TestTransaction::run_090 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data = {0x00, 0x02, 0xca, 0xff};

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_blob_set (root._blob.ref (), 0, data, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_091
==============================================================================
*/

void  TestTransaction::run_091 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array_a.emplace (root._array_a.end ());

   auto tx = document.commit ();
   auto tx2 = tx;
   tx.push (std::move (tx2));

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_092
==============================================================================
*/

void  TestTransaction::run_092 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();

   auto tx = document.commit ();
   auto tx2 = tx;
   tx.push (std::move (tx2));

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_093
Description :
   Try to insert an object into a collection owned by an object which was
   erased but not yet synchronised.
==============================================================================
*/

void  TestTransaction::run_093 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array_a.emplace <B> (root._array_a.end ());

   document.commit ();

   B & b = dynamic_cast <B &> (*it);

   KeyRandom key;

   Transaction tx;
   tx.push_array_erase (
      root._array_a.ref (), 0, it.key (), b.get_class ().type_id (document.data_model ()), b.ref ()
   );
   tx.push_collection_insert (
      b._coll.ref (), 0,
      key, Class <A>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.revert ();
}



/*
==============================================================================
Name : run_094
Description :
   Try to insert an object into a collection owned by an object which was
   erased but not yet synchronised.
==============================================================================
*/

void  TestTransaction::run_094 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array_a.emplace <B> (root._array_a.end ());

   document.commit ();

   B & b = dynamic_cast <B &> (*it);

   root._array_a.erase (it);

   flip_CHECK_THROW (b._coll.emplace ());
}



/*
==============================================================================
Name : run_095
==============================================================================
*/

void  TestTransaction::run_095 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array_a.emplace <B> (root._array_a.end ());
   B & b = dynamic_cast <B &> (*it);

   document.commit ();

   KeyFloat key = KeyFloat::generate (it.key (), KeyFloat::one);
   KeyFloat key2 = KeyFloat::generate (key, KeyFloat::one);

   Transaction tx;
   tx.push_array_erase (
      root._array_a.ref (), 0, it.key (), b.get_class ().type_id (document.data_model ()), b.ref ()
   );
   tx.push_array_insert (
      root._array_a.ref (), 0,
      key, b.get_class ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );
   tx.push_array_move (
      root._array_a.ref (), 0,
      key2, root._array_a.ref (), it.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.revert ();
}



/*
==============================================================================
Name : run_096
==============================================================================
*/

void  TestTransaction::run_096 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace <B> ();
   B & b = dynamic_cast <B &> (*it);

   document.commit ();

   KeyRandom key;
   KeyRandom key2;

   Transaction tx;
   tx.push_collection_erase (
      root._coll_a.ref (), 0, it.key (), b.get_class ().type_id (document.data_model ()), b.ref ()
   );
   tx.push_collection_insert (
      root._coll_a.ref (), 0,
      key, b.get_class ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );
   tx.push_collection_move (
      root._b._coll.ref (), 0,
      key2, root._coll_a.ref (), it.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.revert ();
}



/*
==============================================================================
Name : run_097
==============================================================================
*/

void  TestTransaction::run_097 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   flip_CHECK_THROW (tx.push_bool_set (root._bool.ref (), 2, false, true));
   flip_CHECK_THROW (tx.push_int64_set (root._int.ref (), 4, 1LL, 2LL));
   flip_CHECK_THROW (tx.push_float64_set (root._float.ref (), 8, 0.5, 2.5));
   flip_CHECK_THROW (tx.push_object_ref_set (
      root._ref_a.ref (), 8,
      Ref::make (document.user (), document.actor (), 123456),
      Ref::make (document.user (), document.actor (), 123457)
   ));
   std::vector <uint8_t> data1 {0xff};
   std::vector <uint8_t> data2 {0xfe};
   flip_CHECK_THROW (tx.push_blob_set (root._blob.ref (), 16, data1, data2));
   flip_CHECK_THROW (tx.push_collection_insert (
      root._coll_a.ref (), 32, KeyRandom (), 10,
      Ref::make (document.user (), document.actor (), 123456)
   ));
   flip_CHECK_THROW (tx.push_collection_erase (
      root._coll_a.ref (), 32, KeyRandom (), 10,
      Ref::make (document.user (), document.actor (), 123456)
   ));
   flip_CHECK_THROW (tx.push_collection_move (
      root._coll_a.ref (), 32, KeyRandom (),
      Ref::make (document.user (), document.actor (), 123456),
      KeyRandom ()
   ));
   KeyFloat key1 = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   KeyFloat key2 = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   flip_CHECK_THROW (tx.push_array_insert (
      root._coll_a.ref (), 64, key1, 10,
      Ref::make (document.user (), document.actor (), 123456)
   ));
   flip_CHECK_THROW (tx.push_array_erase (
      root._coll_a.ref (), 64, key1, 10,
      Ref::make (document.user (), document.actor (), 123456)
   ));
   flip_CHECK_THROW (tx.push_array_move (
      root._coll_a.ref (), 64, key1,
      Ref::make (document.user (), document.actor (), 123456),
      key2
   ));
   flip_CHECK_THROW (tx.push_message_push (root._blob.ref (), 128, data1));
}



/*
==============================================================================
Name : run_098
==============================================================================
*/

void  TestTransaction::run_098 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_int64_set (root._int.ref (), 0, 1LL, 2LL);
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), 1000,
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_099
==============================================================================
*/

void  TestTransaction::run_099 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), Class <A>::use ().type_id (document.data_model ()),
      Ref::make (0, 0, 0)
   );

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A &){return true;}
   ) == 0);
}



/*
==============================================================================
Name : run_100
==============================================================================
*/

void  TestTransaction::run_100 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_a.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_collection_erase (
      root._coll_a.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_101
==============================================================================
*/

void  TestTransaction::run_101 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   it->_bool = true;

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_101b
==============================================================================
*/

void  TestTransaction::run_101b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._array_a.emplace (root._array_a.end ());

   it->_int = 1;

   document.commit ();

   Transaction tx;
   tx.push_array_erase (
      root._array_a.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._array_a.begin (), root._array_a.end (), [](A &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_102
==============================================================================
*/

void  TestTransaction::run_102 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   std::vector <uint8_t> value = {0x01, 0x48, 0xff};
   it->_blob = value;

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_103
==============================================================================
*/

void  TestTransaction::run_103 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   it->_string = "some string";

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_104
==============================================================================
*/

void  TestTransaction::run_104 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_bool_set (
      it->_bool.ref (), 0, false, true
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_105
==============================================================================
*/

void  TestTransaction::run_105 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   std::vector <uint8_t> old_val;
   std::vector <uint8_t> new_val = {0x42, 0x0f};
   tx.push_blob_set (
      it->_blob.ref (), 0, old_val, new_val
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_106
==============================================================================
*/

void  TestTransaction::run_106 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   std::vector <uint8_t> old_val;
   std::vector <uint8_t> new_val = {'j', 'o', 'y'};
   tx.push_blob_set (
      it->_string.ref (), 0, old_val, new_val
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_107
==============================================================================
*/

void  TestTransaction::run_107 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_a.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_int64_set (
      it->_int.ref (), 0, 0LL, 1LL
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_108
==============================================================================
*/

void  TestTransaction::run_108 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_a.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_a.ref (), 0, it.key (), Class <A>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_float64_set (
      it->_float.ref (), 0, 0.0, 1.5
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_109
==============================================================================
*/

void  TestTransaction::run_109 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyRandom key;
   tx.push_collection_insert (
      it->_coll.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_109b
==============================================================================
*/

void  TestTransaction::run_109b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyRandom key;
   tx.push_collection_erase (
      it->_coll.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_110
==============================================================================
*/

void  TestTransaction::run_110 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   tx.push_array_insert (
      it->_array.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_110b
==============================================================================
*/

void  TestTransaction::run_110b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   tx.push_array_erase (
      it->_array.ref (), 0, key, Class <A>::use ().type_id (document.data_model ()),
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_111
==============================================================================
*/

void  TestTransaction::run_111 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_object_ref_set (
      it->_ref.ref (), 0, Ref::null, root._a.ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_112
==============================================================================
*/

void  TestTransaction::run_112 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   std::vector <uint8_t> val;
   tx.push_message_push (
      it->_message.ref (), 0, val
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_113
==============================================================================
*/

void  TestTransaction::run_113 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();
   auto it2 = root._coll_c.emplace ();
   auto ite = it->_coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      it->_coll.ref (), 0, ite.key (), Class <A>::use ().type_id (document.data_model ()),
      ite->ref ()
   );
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyRandom key;
   tx.push_collection_move (
      it2->_coll.ref (), 0, key, it->_coll.ref (), ite.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();
}



/*
==============================================================================
Name : run_114
==============================================================================
*/

void  TestTransaction::run_114 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();
   auto it2 = root._coll_c.emplace ();
   auto ite = it->_coll.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      it->_coll.ref (), 0, ite.key (), Class <A>::use ().type_id (document.data_model ()),
      ite->ref ()
   );
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it2.key (), Class <C>::use ().type_id (document.data_model ()),
      it2->ref ()
   );
   KeyRandom key;
   tx.push_collection_move (
      it2->_coll.ref (), 0, key, it->_coll.ref (), ite.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();
}



/*
==============================================================================
Name : run_115
==============================================================================
*/

void  TestTransaction::run_115 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();
   auto it2 = root._coll_c.emplace ();
   auto ite = it->_array.emplace (it->_array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_erase (
      it->_array.ref (), 0, ite.key (), Class <A>::use ().type_id (document.data_model ()),
      ite->ref ()
   );
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   tx.push_array_move (
      it2->_array.ref (), 0, key, it->_array.ref (), ite.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();
}



/*
==============================================================================
Name : run_116
==============================================================================
*/

void  TestTransaction::run_116 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();
   auto it2 = root._coll_c.emplace ();
   auto ite = it->_array.emplace (it->_array.end ());

   document.commit ();

   Transaction tx;
   tx.push_array_erase (
      it->_array.ref (), 0, ite.key (), Class <A>::use ().type_id (document.data_model ()),
      ite->ref ()
   );
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it2.key (), Class <C>::use ().type_id (document.data_model ()),
      it2->ref ()
   );
   KeyFloat key = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   tx.push_array_move (
      it2->_array.ref (), 0, key, it->_array.ref (), ite.key ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();
}



/*
==============================================================================
Name : run_117
==============================================================================
*/

void  TestTransaction::run_117 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 1LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x1);
   flip_TEST (root._enum != Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);
   flip_TEST (root._enum != Root::D::x1);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

   tx.clear ();
   flip_TEST (tx.empty ());
   flip_TEST (tx.user () == 0);
   flip_TEST (tx.actor () == 0);
   flip_TEST (tx.nbr () == 0);
}



/*
==============================================================================
Name : run_118
==============================================================================
*/

void  TestTransaction::run_118 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 1LL);

   Transaction tx2 (document.user (), document.actor (), 2);
   tx2.push_enum_set (root_enum_ref, 0, 1LL, 2LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x1);

   ok_flag = tx2.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x2);

   ok_flag = tx2.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x1);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);
}



/*
==============================================================================
Name : run_119
==============================================================================
*/

void  TestTransaction::run_119 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 1LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x1);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x1);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));

   tx.clear ();
   flip_TEST (tx.empty ());
   flip_TEST (tx.user () == 0);
   flip_TEST (tx.actor () == 0);
   flip_TEST (tx.nbr () == 0);
}



/*
==============================================================================
Name : run_120
==============================================================================
*/

void  TestTransaction::run_120 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 1LL);
   tx.push_enum_set (root_enum_ref, 0, 1LL, 2LL);
   tx.push_enum_set (root_enum_ref, 0, 2LL, 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_121
==============================================================================
*/

void  TestTransaction::run_121 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 1LL);
   tx.push_enum_set (root_enum_ref, 0, 2LL, 0LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_122
==============================================================================
*/

void  TestTransaction::run_122 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root._enum.ref ();

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_float64_set (root_enum_ref, 0, 0.0, 19.5);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_123
==============================================================================
*/

void  TestTransaction::run_123 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_float_ref = root_ref + 2ULL;

   bool ok_flag = false;

   flip_TEST (root._float == 0.0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_float_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._float == 0.0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_124
==============================================================================
*/

void  TestTransaction::run_124 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Ref root_ref = root.ref ();
   Ref root_enum_ref = root_ref + 123456ULL;

   bool ok_flag = false;

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root_enum_ref, 0, 0LL, 19LL);

   ok_flag = tx.execute (document, validator, Direction::FORWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = tx.execute (document, validator, Direction::BACKWARD, 0);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   std::vector <uint8_t> data = tx.serialize ();
   Transaction tx2 (data);
   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_125
==============================================================================
*/

void  TestTransaction::run_125 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 1LL, 2LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x2);

   Transaction tx2 (document.user (), document.actor (), 1);
   tx2.push_enum_set (root._enum.ref (), 0, 0LL, 2LL);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_126
==============================================================================
*/

void  TestTransaction::run_126 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 1LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_127
==============================================================================
*/

void  TestTransaction::run_127 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 0LL, 1LL);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_128
==============================================================================
*/

void  TestTransaction::run_128 ()
{
   DocumentValidatorVoid validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root.ref (), 0, 1LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (root._enum == Root::D::x0);

   Transaction tx2 (document.user (), document.actor (), 1);

   flip_TEST (tx2.equal (tx));
}



/*
==============================================================================
Name : run_129
==============================================================================
*/

void  TestTransaction::run_129 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 0LL, 0LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_130
==============================================================================
*/

void  TestTransaction::run_130 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 2LL, 2LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_131
==============================================================================
*/

void  TestTransaction::run_131 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_enum_set (root._enum.ref (), 0, 1LL, 2LL);
   tx.push_collection_insert (
      root._coll_a.ref (), 0, KeyRandom (), 1000,
      Ref::make (document.user (), document.actor (), 123456)
   );

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_132
==============================================================================
*/

void  TestTransaction::run_132 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   it->_enum = C::D::x1;

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_133
==============================================================================
*/

void  TestTransaction::run_133 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   auto it = root._coll_c.emplace ();

   document.commit ();

   Transaction tx;
   tx.push_collection_erase (
      root._coll_c.ref (), 0, it.key (), Class <C>::use ().type_id (document.data_model ()),
      it->ref ()
   );
   tx.push_enum_set (
      it->_enum.ref (), 0, 0LL, 1LL
   );

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);

   document.commit ();

   flip_TEST (std::count_if (
      root._coll_c.begin (), root._coll_c.end (), [](C &){return true;}
   ) == 1);
}



/*
==============================================================================
Name : run_134
==============================================================================
*/

void  TestTransaction::run_134 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 0LL, -1LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_135
==============================================================================
*/

void  TestTransaction::run_135 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx (document.user (), document.actor (), 1);
   tx.push_enum_set (root._enum.ref (), 0, 0LL, 19LL);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_136
==============================================================================
*/

void  TestTransaction::run_136 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   std::vector <uint8_t> data1;
   data1.push_back (0x22);
   data1.push_back (0x4a);

   std::vector <uint8_t> data2;
   data1.push_back (0x0f);
   data1.push_back (0x1f);
   data1.push_back (0x23);

   KeyRandom key_random1;
   KeyRandom key_random2;

   KeyFloat key_float1 = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);
   KeyFloat key_float2 = KeyFloat::generate (KeyFloat::zero, KeyFloat::one);

   Transaction tx;
   tx.push_bool_set (root._bool.ref (), 1, false, true);
   tx.push_bool_set (root._bool.ref (), 0, true, false);
   tx.push_int64_set (root._int.ref (), 1, 2, 3);
   tx.push_float64_set (root._float.ref (), 0, 4.5, 2.3);
   tx.push_enum_set (root._enum.ref (), 0, 1, 19);
   tx.push_object_ref_set (root._ref_a.ref (), 0, root._bool.ref (), root._int.ref ());
   tx.push_blob_set (root._blob.ref (), 1, data1, data2);
   tx.push_collection_insert (root._coll_a.ref (), 0, key_random1, 34, root._blob.ref ());
   tx.push_collection_erase (root._coll_b.ref (), 1, key_random2, 57, root._int.ref ());
   tx.push_collection_move (root._coll_a.ref (), 0, key_random1, root._coll_b.ref (), key_random2);
   tx.push_array_insert (root._array_a.ref (), 1, key_float1, 34, root._blob.ref ());
   tx.push_array_erase (root._coll_b.ref (), 0, key_float2, 57, root._bool.ref ());
   tx.push_array_move (root._array_a.ref (), 1, key_float1, root._coll_b.ref (), key_float2);
   tx.push_message_push (root._message.ref (), 1, data1);

   tx.invert_inplace ();

   Transaction tx2;
   tx2.push_message_push (root._message.ref (), 1, data1);
   tx2.push_array_move (root._coll_b.ref (), 1, key_float2, root._array_a.ref (), key_float1);
   tx2.push_array_insert (root._coll_b.ref (), 0, key_float2, 57, root._bool.ref ());
   tx2.push_array_erase (root._array_a.ref (), 1, key_float1, 34, root._blob.ref ());
   tx2.push_collection_move (root._coll_b.ref (), 0, key_random2, root._coll_a.ref (), key_random1);
   tx2.push_collection_insert (root._coll_b.ref (), 1, key_random2, 57, root._int.ref ());
   tx2.push_collection_erase (root._coll_a.ref (), 0, key_random1, 34, root._blob.ref ());
   tx2.push_blob_set (root._blob.ref (), 1, data2, data1);
   tx2.push_object_ref_set (root._ref_a.ref (), 0, root._int.ref (), root._bool.ref ());
   tx2.push_enum_set (root._enum.ref (), 0, 19, 1);
   tx2.push_float64_set (root._float.ref (), 0, 2.3, 4.5);
   tx2.push_int64_set (root._int.ref (), 1, 3, 2);
   tx2.push_bool_set (root._bool.ref (), 0, false, true);
   tx2.push_bool_set (root._bool.ref (), 1, true, false);

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_137
==============================================================================
*/

void  TestTransaction::run_137 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & a = *root._coll_a.emplace ();
   auto tx = document.commit ();

   a._int = 2;
   document.commit ();

   bool ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._coll_a.begin () == root._coll_a.end ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll_a.begin () == root._coll_a.end ());
}



/*
==============================================================================
Name : run_137b
==============================================================================
*/

void  TestTransaction::run_137b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & a = *root._array_a.emplace (root._array_a.end ());
   auto tx = document.commit ();

   a._int = 2;
   document.commit ();

   bool ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._array_a.begin (), root._array_a.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._array_a.begin () == root._array_a.end ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._array_a.begin (), root._array_a.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._array_a.begin () == root._array_a.end ());
}



/*
==============================================================================
Name : run_138
==============================================================================
*/

void  TestTransaction::run_138 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & a = *root._coll_a.emplace ();
   auto tx = document.commit ();
   tx.invert_inplace ();

   a._int = 2;
   document.commit ();

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._coll_a.begin () == root._coll_a.end ());

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._coll_a.begin (), root._coll_a.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll_a.begin () == root._coll_a.end ());
}



/*
==============================================================================
Name : run_138b
==============================================================================
*/

void  TestTransaction::run_138b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & a = *root._array_a.emplace (root._array_a.end ());
   auto tx = document.commit ();
   tx.invert_inplace ();

   a._int = 2;
   document.commit ();

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._array_a.begin (), root._array_a.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._array_a.begin () == root._array_a.end ());

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._array_a.begin (), root._array_a.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._array_a.begin () == root._array_a.end ());
}



/*
==============================================================================
Name : run_139
==============================================================================
*/

void  TestTransaction::run_139 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & b = *root._coll_b.emplace ();
   auto tx = document.commit ();

   b._int = 2;
   b._int2 = 5;
   auto & a = *b._coll.emplace ();
   a._int = 7;
   document.commit ();

   bool ok_flag = document.execute_correct_backward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._coll_b.begin (), root._coll_b.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._coll_b.begin () == root._coll_b.end ());

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._coll_b.begin (), root._coll_b.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   auto & b2 = *root._coll_b.begin ();
   flip_TEST (b2._int == 2);
   flip_TEST (b2._int2 == 5);

   flip_TEST (std::count_if (
      b2._coll.begin (), b2._coll.end (), [](A & elem){return elem._int == 7;}
   ) == 1);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll_b.begin () == root._coll_b.end ());
}



/*
==============================================================================
Name : run_139b
==============================================================================
*/

void  TestTransaction::run_139b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   auto & b = *root._coll_b.emplace ();
   auto tx = document.commit ();
   tx.invert_inplace ();

   b._int = 2;
   b._int2 = 5;
   auto & a = *b._coll.emplace ();
   a._int = 7;
   document.commit ();

   bool ok_flag = document.execute_correct_forward (tx);
   flip_TEST (ok_flag);

   flip_TEST (std::count_if (
      root._coll_b.begin (), root._coll_b.end (), [](A & elem){return elem.removed ();}
   ) == 1);

   document.commit ();

   flip_TEST (root._coll_b.begin () == root._coll_b.end ());

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (std::count_if (
      root._coll_b.begin (), root._coll_b.end (), [](A & elem){return elem._int == 2;}
   ) == 1);

   auto & b2 = *root._coll_b.begin ();
   flip_TEST (b2._int == 2);
   flip_TEST (b2._int2 == 5);

   flip_TEST (std::count_if (
      b2._coll.begin (), b2._coll.end (), [](A & elem){return elem._int == 7;}
   ) == 1);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);
   document.commit ();

   flip_TEST (root._coll_b.begin () == root._coll_b.end ());
}



/*
==============================================================================
Name : ValidatorFail::validate
==============================================================================
*/

void  TestTransaction::ValidatorFail::validate (Root & root)
{
   if (root.removed ()) return;  // abort

   called_flag = true;

   if (root._int != 0)
   {
      flip_VALIDATION_FAILED ("test");
   }
}



/*
==============================================================================
Name : run_140
==============================================================================
*/

void  TestTransaction::run_140 ()
{
   ValidatorFail validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   validator.called_flag = false;

   Transaction tx;
   tx.push_int64_set (root._int.ref (), 0, 0, 17);

   flip_CHECK_THROW (document.impl_execute_no_error (tx, Direction::FORWARD));
   flip_TEST (validator.called_flag == true);
}



/*
==============================================================================
Name : run_140b
==============================================================================
*/

void  TestTransaction::run_140b ()
{
   ValidatorFail validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   validator.called_flag = false;

   Transaction tx;
   tx.push_int64_set (root._int.ref (), 0, 17, 0);

   flip_CHECK_THROW (document.impl_execute_no_error (tx, Direction::BACKWARD));
   flip_TEST (validator.called_flag == true);
}



/*
==============================================================================
Name : run_141
==============================================================================
*/

void  TestTransaction::run_141 ()
{
   ValidatorFail validator;
   Document document (Model::use (), validator, 123456789UL, 'appl', 'gui ');
   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << uint64_t (1) << uint64_t (1) << uint64_t (0);

   StreamBinIn sbi (data);

   Ref ref;
   ref.read (sbi);

   Transaction tx;
   tx.push_object_ref_set (root._ref_a.ref (), 0, Ref::null, ref);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (!ok_flag);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

