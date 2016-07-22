/*****************************************************************************

      TestCodec.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestCodec.h"

#include "flip/detail/def.h"
#include "flip/detail/Codec.h"
#include "flip/detail/SignalData.h"
#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"
#include "flip/detail/TxId.h"
#include "flip/Document.h"
#include "flip/BackEndBinary.h"
#include "flip/DataConsumerMemory.h"

#include "TestDef.h"

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

void  TestCodec::run ()
{
   Model::version ("test.codec");

   Model::declare <Root> ()
      .name ("Root");

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

void  TestCodec::run_000 ()
{
   uint64_t user_id = 0x0123456789abcdefULL;
   uint64_t session_id = 0xfedcba9876543210ULL;
   std::string metadata = "this is a test";
   std::vector <uint8_t> data;

   {
      Document document (Model::use (), user_id, 'appl', 'gui ');

      StreamBinOut sbo (data);

      Codec::encode_greet (sbo, document.user (), session_id, metadata);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_greet);

      auto tuple = Codec::decode_greet (sbi);
      flip_TEST (std::get <0> (tuple) == user_id);
      flip_TEST (std::get <1> (tuple) == session_id);
      flip_TEST (std::get <2> (tuple) == metadata);
   }
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestCodec::run_001 ()
{
   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   BackEndIR backend = document.write ();

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      Codec::encode_backend (sbo, backend);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_backend);

      BackEndIR sub_backend = Codec::decode_backend (sbi);

      std::vector <uint8_t> data1;
      DataConsumerMemory consumer1 (data1);
      backend.write <BackEndBinary> (consumer1);

      std::vector <uint8_t> data2;
      DataConsumerMemory consumer2 (data2);
      sub_backend.write <BackEndBinary> (consumer2);

      flip_TEST (data1 == data2);
      flip_TEST (backend.equal (sub_backend));
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestCodec::run_002 ()
{
   Transaction tx (1234ULL, Ref::make_actor ('some', 'tx  '), 987ULL);
   tx.push_bool_set (
      Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL),
      1, false, true
   );
   tx.push_int64_set (
      Ref::make (123123456789ULL, Ref::make_actor ('app2', 'gui2'), 987987654321ULL),
      0, 456123456789ULL, 4561234506540ULL
   );
   tx.push_float64_set (
      Ref::make (124560540456789ULL, Ref::make_actor ('3pp2', '4ui2'), 987065404321ULL),
      1, 1.0 / 7.0, 3.0 / 11.0
   );

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      Codec::encode_tx (sbo, tx);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_tx);

      Transaction sub_tx = Codec::decode_tx (sbi);
      flip_TEST (sub_tx.serialize () == tx.serialize ());
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestCodec::run_003 ()
{
   TxId tx_id (1654068401321068404ULL, Ref::make_actor ('some', 'tx23'), 6504984056105404ULL);

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      Codec::encode_tx_ack (sbo, tx_id);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_tx_ack);

      TxId sub_tx_id = Codec::decode_tx_ack (sbi);
      flip_TEST (tx_id == sub_tx_id);
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestCodec::run_004 ()
{
   TxId tx_id (165654065401068404ULL, Ref::make_actor ('more', 'tx79'), 65049987409870404ULL);

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      Codec::encode_tx_deny (sbo, tx_id);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_tx_deny);

      TxId sub_tx_id = Codec::decode_tx_deny (sbi);
      flip_TEST (tx_id == sub_tx_id);
   }
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestCodec::run_005 ()
{
   SignalData signal_data;
   signal_data.type_id = 123456789UL;
   signal_data.ref = Ref::make (123456789ULL, Ref::make_actor ('appl', 'gui '), 987654321ULL);
   signal_data.type = 987654321UL;
   signal_data.data = std::vector <uint8_t> {0xff, 0x01, 0x23};

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      Codec::encode_signal (sbo, signal_data);
   }

   {
      StreamBinIn sbi (data);

      uint32_t msg = Codec::decode_msg (sbi);
      flip_TEST (msg == Codec::msg_signal);

      SignalData sub_signal_data = Codec::decode_signal (sbi);
      flip_TEST (signal_data.type_id == sub_signal_data.type_id);
      flip_TEST (signal_data.ref == sub_signal_data.ref);
      flip_TEST (signal_data.type == sub_signal_data.type);
      flip_TEST (signal_data.data == sub_signal_data.data);
   }
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestCodec::run_006 ()
{
   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);

      sbo << uint32_t ('test');
   }

   {
      StreamBinIn sbi (data);

      flip_CHECK_THROW (Codec::decode_msg (sbi));
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
