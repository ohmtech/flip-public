/*****************************************************************************

      TestMessage.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestMessage.h"

#include "flip/detail/ExecFlags.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/DocumentObserverLambda.h"
#include "flip/Mold.h"
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

void  TestMessage::run ()
{
   Model::version ("test.document");

   Model::declare <Root> ()
      .name ("Root")
      .member <Message <>, &Root::_msg_void> ("msg_void")
      .member <Message <int32_t>, &Root::_msg_int> ("msg_int")
      .member <Message <double, int32_t>, &Root::_msg_double_int> ("msg_double_int")
      .member <Message <float, double, int32_t>, &Root::_msg_float_double_int> ("msg_float_double_int")
      .member <Message <Info>, &Root::_msg_info> ("msg_info")
      .member <Message <Info>, &Root::_msg_cr_info> ("msg_cr_info")
      .member <Message <std::vector <Info>>, &Root::_msg_vector_info> ("msg_vector_info")
      .member <Message <std::list <Info>>, &Root::_msg_list_info> ("msg_list_info")
      .member <Message <std::map <double, Info>>, &Root::_msg_map_double_info> ("msg_map_double_info")
      .member <Message <std::vector <uint8_t>>, &Root::_msg_data> ("msg_data");



   run_000 ();
   run_000b ();
   run_000c ();
   run_000d ();
   run_000e ();
   run_000f ();
   run_000g ();
   run_000h ();
   run_001 ();
   run_001b ();
   run_001c ();
   run_001d ();
   run_001e ();
   run_001f ();
   run_001g ();
   run_001h ();
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



/*
==============================================================================
Name : Info::write
==============================================================================
*/

void  TestMessage::Info::write (StreamBinOut & sbo) const
{
   sbo << _val_1;
   sbo << _val_2;
}



/*
==============================================================================
Name : Info::read
==============================================================================
*/

void  TestMessage::Info::read (StreamBinIn & sbi)
{
   sbi >> _val_1;
   sbi >> _val_2;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestMessage::run_000 ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_void.send ();

   document.commit ();

   flip_TEST (fired_cnt == 1);
}



/*
==============================================================================
Name : run_000b
==============================================================================
*/

void  TestMessage::run_000b ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   BackEndIR backend1 = document.write ();

   root._msg_void.send ();
   root._msg_void.send ();

   document.commit ();

   BackEndIR backend2 = document.write ();

   flip_TEST (fired_cnt == 2);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_000c
==============================================================================
*/

void  TestMessage::run_000c ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   BackEndIR backend1 = document.write ();

   Root & root = document.root <Root> ();

   root._msg_void.send ();
   root._msg_void.send ();
   root._msg_void.send ();

   document.commit ();

   BackEndIR backend2 = document.write ();

   flip_TEST (fired_cnt == 3);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_000d
==============================================================================
*/

void  TestMessage::run_000d ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_message_push (root._msg_void.ref (), 0, std::vector <uint8_t> ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
}



/*
==============================================================================
Name : run_000e
==============================================================================
*/

void  TestMessage::run_000e ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      // COV_NF_START
      root._msg_void.get ([&](bool /*forward_flag*/){
         flip_TEST_FAILED;
      });
      // COV_NF_END
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_message_push (root._msg_void.ref (), 0, std::vector <uint8_t> ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 0);
}



/*
==============================================================================
Name : run_000f
==============================================================================
*/

void  TestMessage::run_000f ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_message_push (root._msg_void.ref (), 0, std::vector <uint8_t> ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
}



/*
==============================================================================
Name : run_000g
==============================================================================
*/

void  TestMessage::run_000g ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_message_push (root._msg_void.ref (), 0, std::vector <uint8_t> ());

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 2);
}



/*
==============================================================================
Name : run_000h
==============================================================================
*/

void  TestMessage::run_000h ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_void.changed ()) return;

      root._msg_void.get ([&](bool forward_flag){
         flip_TEST (!forward_flag);
         fired_cnt += 1;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Transaction tx;
   tx.push_message_push (root._msg_void.ref (), 0, std::vector <uint8_t> ());

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestMessage::run_001 ()
{
   bool fired_flag = false;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_int.send (35);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value == 35);
}



/*
==============================================================================
Name : run_001b
==============================================================================
*/

void  TestMessage::run_001b ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_int.send (20);
   root._msg_int.send (31);

   document.commit ();

   flip_TEST (fired_cnt == 2);
   flip_TEST (value == 51);
}



/*
==============================================================================
Name : run_001c
==============================================================================
*/

void  TestMessage::run_001c ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_int.send (20);
   root._msg_int.send (31);
   root._msg_int.send (32);

   document.commit ();

   flip_TEST (fired_cnt == 3);
   flip_TEST (value == 83);
}



/*
==============================================================================
Name : run_001d
==============================================================================
*/

void  TestMessage::run_001d ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << int32_t (35);

   Transaction tx;
   tx.push_message_push (root._msg_int.ref (), 0, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
   flip_TEST (value == 35);
}



/*
==============================================================================
Name : run_001e
==============================================================================
*/

void  TestMessage::run_001e ()
{
   size_t fired_cnt = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      // COV_NF_START
      root._msg_int.get ([&](bool /*forward_flag*/, int /*val*/){
         flip_TEST_FAILED;
      });
      // COV_NF_END
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << int32_t (35);

   Transaction tx;
   tx.push_message_push (root._msg_int.ref (), 0, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 0);
}



/*
==============================================================================
Name : run_001f
==============================================================================
*/

void  TestMessage::run_001f ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << int32_t (35);

   Transaction tx;
   tx.push_message_push (root._msg_int.ref (), 0, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
   flip_TEST (value == 35);
}



/*
==============================================================================
Name : run_001g
==============================================================================
*/

void  TestMessage::run_001g ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << int32_t (35);

   Transaction tx;
   tx.push_message_push (root._msg_int.ref (), 0, data);

   bool ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   ok_flag = document.execute_forward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 2);
   flip_TEST (value == 70);
}



/*
==============================================================================
Name : run_001h
==============================================================================
*/

void  TestMessage::run_001h ()
{
   size_t fired_cnt = 0;
   int value = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_int.changed ()) return;

      root._msg_int.get ([&](bool forward_flag, int val){
         flip_TEST (!forward_flag);
         fired_cnt += 1;
         value += val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data;
   StreamBinOut sbo (data);
   sbo << int32_t (35);

   Transaction tx;
   tx.push_message_push (root._msg_int.ref (), 0, data);

   bool ok_flag = document.execute_backward (tx);
   flip_TEST (ok_flag);

   document.commit ();

   flip_TEST (fired_cnt == 1);
   flip_TEST (value == 35);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestMessage::run_002 ()
{
   bool fired_flag = false;
   double value_double = 0.0;
   int value_int = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_double_int.changed ()) return;

      root._msg_double_int.get ([&](bool forward_flag, double val_dbl, int val_int){
         flip_TEST (forward_flag);
         fired_flag = true;
         value_double = val_dbl;
         value_int = val_int;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_double_int.send (2.5, 35);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value_double == 2.5);
   flip_TEST (value_int == 35);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestMessage::run_003 ()
{
   bool fired_flag = false;
   float value_float = 0.f;
   double value_double = 0.0;
   int value_int = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_float_double_int.changed ()) return;

      root._msg_float_double_int.get ([&](bool forward_flag, float val_flt, double val_dbl, int val_int){
         flip_TEST (forward_flag);
         fired_flag = true;
         value_float = val_flt;
         value_double = val_dbl;
         value_int = val_int;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   root._msg_float_double_int.send (1.7f, 3.5, 37);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value_float == 1.7f);
   flip_TEST (value_double == 3.5);
   flip_TEST (value_int == 37);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestMessage::run_004 ()
{
   bool fired_flag = false;
   Info value;
   value._val_1 = 0;
   value._val_2 = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_info.changed ()) return;

      root._msg_info.get ([&](bool forward_flag, Info val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Info info;
   info._val_1 = 35;
   info._val_2 = 77;
   root._msg_info.send (info);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (info._val_1 == 35);
   flip_TEST (info._val_2 == 77);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestMessage::run_005 ()
{
   bool fired_flag = false;
   Info value;
   value._val_1 = 0;
   value._val_2 = 0;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_info.changed ()) return;

      root._msg_info.get ([&](bool forward_flag, const Info & val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   Info info;
   info._val_1 = 35;
   info._val_2 = 77;
   root._msg_info.send (info);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (info._val_1 == 35);
   flip_TEST (info._val_2 == 77);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestMessage::run_006 ()
{
   bool fired_flag = false;
   std::vector <Info> value;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_vector_info.changed ()) return;

      root._msg_vector_info.get ([&](bool forward_flag, const std::vector <Info> & val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <Info> info_arr;
   info_arr.emplace_back (35, 77);
   info_arr.emplace_back (1564, 878);

   root._msg_vector_info.send (info_arr);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value == info_arr);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestMessage::run_007 ()
{
   bool fired_flag = false;
   std::list <Info> value;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_list_info.changed ()) return;

      root._msg_list_info.get ([&](bool forward_flag, const std::list <Info> & val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::list <Info> info_arr;
   info_arr.emplace_back (35, 77);
   info_arr.emplace_back (1564, 878);

   root._msg_list_info.send (info_arr);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value == info_arr);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestMessage::run_008 ()
{
   bool fired_flag = false;
   std::map <double, Info> value;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_map_double_info.changed ()) return;

      root._msg_map_double_info.get ([&](bool forward_flag, const std::map <double, Info> & val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::map <double, Info> info_map;
   info_map [1.2] = Info (35, 77);
   info_map [2.7] = Info (1564, 878);

   root._msg_map_double_info.send (info_map);

   document.commit ();

   flip_TEST (fired_flag);
   flip_TEST (value == info_map);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestMessage::run_009 ()
{
   bool fired_flag = false;
   std::vector <uint8_t> value;

   DocumentObserverLambda <Root> observer ([&](Root & root){
      if (!root.changed ()) return;
      if (!root._msg_data.changed ()) return;

      root._msg_data.get ([&](bool forward_flag, const std::vector <uint8_t> & val){
         flip_TEST (forward_flag);
         fired_flag = true;
         value = val;
      });
   });

   Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

   BackEndIR backend1 = document.write ();

   Root & root = document.root <Root> ();

   std::vector <uint8_t> data ({0xff, 0x01, 0x00, 0x80, 0x79});

   root._msg_data.send (data);

   document.commit ();

   BackEndIR backend2 = document.write ();

   flip_TEST (fired_flag);
   flip_TEST (value == data);
   flip_TEST (backend1.equal (backend2));
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestMessage::run_010 ()
{
   Message <> msg;
   msg.send ();

   Transaction tx;
   msg.make (tx);

   Transaction tx2;
   tx2.push_message_push (Ref::null, ExecFlags::OP_IN_UNDO, std::vector <uint8_t> ());

   flip_TEST (tx.equal (tx2));
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestMessage::run_011 ()
{
   Message <> msg;
   msg.send ();

   Message <> msg2 = msg;

   Transaction tx;
   msg2.make (tx);

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestMessage::run_012 ()
{
   Message <> msg;
   msg.send ();

   Message <> msg2;
   msg2 = msg;

   Transaction tx;
   msg2.make (tx);

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestMessage::run_013 ()
{
   Message <> msg;
   msg.send ();

   msg.revert ();

   Transaction tx;
   msg.make (tx);

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestMessage::run_014 ()
{
   Message <int64_t> msg;
   msg.send (1234567890123LL);

   msg.revert ();

   Transaction tx;
   msg.make (tx);

   flip_TEST (tx.empty ());
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestMessage::run_015 ()
{
   Message <int64_t> msg;
   msg.send (1234567890123LL);

   flip_TEST (msg.impl_is_reset ());

   msg.impl_reset ();

   flip_TEST (msg.impl_is_reset ());
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

