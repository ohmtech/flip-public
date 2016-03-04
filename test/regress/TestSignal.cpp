/*****************************************************************************

      TestSignal.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestSignal.h"

#include "flip/config.h"
#include "flip/CarrierDirect.h"
#include "flip/Document.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/detail/def.h"
#include "flip/detail/SignalData.h"
#include "TestDef.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestSignal::run ()
{
   Model::version ("test.signal");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int");

   Model::declare <Root> ()
      .name ("Root")
      .member <A, &Root::_a> ("a")
      .member <Collection <A>, &Root::_coll_a> ("coll_a");

   run_pre ();
   run_000 ();
   run_000b ();
   run_000c ();
   run_000d ();
   run_000e ();
   run_001 ();
   run_001b ();
   run_001c ();
   run_002 ();
   run_003 ();
   run_003b ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
}



/*
==============================================================================
Name : AView::ctor
==============================================================================
*/

TestSignal::AView::AView (A & a)
:  _cnx (a._signal_int.connect (*this, &AView::signal_int))
{
}



/*
==============================================================================
Name : AView::signal_int
==============================================================================
*/

void  TestSignal::AView::signal_int (int val)
{
   flip_TEST (val == 123);
   _signaled_flag = true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_pre
==============================================================================
*/

void  TestSignal::run_pre ()
{
   {
      std::vector <uint8_t> data;

      SignalData signal_data;
      StreamBinOut sbo (data);
      sbo << signal_data;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data.type_id == signal_data2.type_id);
      flip_TEST (signal_data.ref == signal_data2.ref);
      flip_TEST (signal_data.type == signal_data2.type);
      flip_TEST (signal_data.data == signal_data2.data);
   }

   {
      std::vector <uint8_t> data;

      std::vector <uint8_t> sdata {0x01, 0x23, 0xff, 0x3d};
      Ref ref = Ref::make (123456789ULL, 987654ULL, 789123ULL);
      SignalData signal_data (1234UL, ref, 456789UL, sdata);
      StreamBinOut sbo (data);
      sbo << signal_data;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data.type_id == signal_data2.type_id);
      flip_TEST (signal_data.ref == signal_data2.ref);
      flip_TEST (signal_data.type == signal_data2.type);
      flip_TEST (signal_data.data == signal_data2.data);
   }

   {
      std::vector <uint8_t> data;

      std::vector <uint8_t> sdata {0x01, 0x23, 0xff, 0x3d};
      Ref ref = Ref::make (123456789ULL, 987654ULL, 789123ULL);
      SignalData signal_data (1234UL, ref, 456789UL, sdata);

      SignalData signal_data3 = signal_data;

      StreamBinOut sbo (data);
      sbo << signal_data3;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data.type_id == signal_data2.type_id);
      flip_TEST (signal_data.ref == signal_data2.ref);
      flip_TEST (signal_data.type == signal_data2.type);
      flip_TEST (signal_data.data == signal_data2.data);
   }

   {
      std::vector <uint8_t> data;

      std::vector <uint8_t> sdata {0x01, 0x23, 0xff, 0x3d};
      Ref ref = Ref::make (123456789ULL, 987654ULL, 789123ULL);
      SignalData signal_data (1234UL, ref, 456789UL, sdata);

      SignalData signal_data3 = std::move (signal_data);

      StreamBinOut sbo (data);
      sbo << signal_data3;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data3.type_id == signal_data2.type_id);
      flip_TEST (signal_data3.ref == signal_data2.ref);
      flip_TEST (signal_data3.type == signal_data2.type);
      flip_TEST (signal_data3.data == signal_data2.data);
   }

   {
      std::vector <uint8_t> data;

      std::vector <uint8_t> sdata {0x01, 0x23, 0xff, 0x3d};
      Ref ref = Ref::make (123456789ULL, 987654ULL, 789123ULL);
      SignalData signal_data (1234UL, ref, 456789UL, sdata);

      SignalData signal_data3;
      signal_data3 = signal_data;

      StreamBinOut sbo (data);
      sbo << signal_data3;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data.type_id == signal_data2.type_id);
      flip_TEST (signal_data.ref == signal_data2.ref);
      flip_TEST (signal_data.type == signal_data2.type);
      flip_TEST (signal_data.data == signal_data2.data);
   }

   {
      std::vector <uint8_t> data;

      std::vector <uint8_t> sdata {0x01, 0x23, 0xff, 0x3d};
      Ref ref = Ref::make (123456789ULL, 987654ULL, 789123ULL);
      SignalData signal_data (1234UL, ref, 456789UL, sdata);

      SignalData signal_data3;
      signal_data3 = std::move (signal_data);

      StreamBinOut sbo (data);
      sbo << signal_data3;

      SignalData signal_data2;
      StreamBinIn sbi (data);
      sbi >> signal_data2;

      flip_TEST (signal_data3.type_id == signal_data2.type_id);
      flip_TEST (signal_data3.ref == signal_data2.ref);
      flip_TEST (signal_data3.type == signal_data2.type);
      flip_TEST (signal_data3.data == signal_data2.data);
   }
}



/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestSignal::run_000 ()
{
   _recv_000_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_void.connect (*this, &TestSignal::recv_000);

   root._a._signal_void ();

   document.pull ();

   flip_TEST (_recv_000_flag);

   _recv_000_flag = false;
}



/*
==============================================================================
Name : run_000b
==============================================================================
*/

void  TestSignal::run_000b ()
{
   _recv_000_flag = false;

   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_void.connect (*this, &TestSignal::recv_000);

   root._a._signal_void ();

   document.pull ();

   flip_TEST (_recv_000_flag);

   _recv_000_flag = false;
}



/*
==============================================================================
Name : run_000c
==============================================================================
*/

void  TestSignal::run_000c ()
{
   _recv_000_flag = false;

   PortDirect port;
   PortDirect port2;
   Hub hub (Model::use (), 123456789ULL, port, port2);

   Document document1 (Model::use (), 123456789ULL, 'flip', 'sig ');
   CarrierDirect carrier (document1, port);
   document1.pull ();

   Document document2 (Model::use (), 123456789ULL, 'flip', 'sig2');
   CarrierDirect carrier2 (document2, port2);
   document2.pull ();

   Root & root1 = document1.root <Root> ();
   Root & root2 = document2.root <Root> ();

   SignalConnection cnx = root2._a._signal_void.connect (*this, &TestSignal::recv_000);

   root1._a._signal_void ();

   document2.pull ();

   flip_TEST (_recv_000_flag);

   _recv_000_flag = false;
}



/*
==============================================================================
Name : run_000d
==============================================================================
*/

void  TestSignal::run_000d ()
{
   _recv_000_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   root._coll_a.insert (root._a);

   document.commit ();

   SignalConnection cnx = root._a._signal_void.connect (*this, &TestSignal::recv_000);

   root._a._signal_void ();

   document.pull ();

   flip_TEST (_recv_000_flag);

   _recv_000_flag = false;
}



/*
==============================================================================
Name : run_000e
==============================================================================
*/

void  TestSignal::run_000e ()
{
   _recv_000_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx;
   cnx = root._a._signal_void.connect (*this, &TestSignal::recv_000);

   root._a._signal_void ();

   document.pull ();

   flip_TEST (_recv_000_flag);

   _recv_000_flag = false;
}



/*
==============================================================================
Name : recv_000
==============================================================================
*/

void  TestSignal::recv_000 ()
{
   _recv_000_flag = true;
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestSignal::run_001 ()
{
   _recv_001_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_int.connect (*this, &TestSignal::recv_001);

   root._a._signal_int (123);

   document.pull ();

   flip_TEST (_recv_001_flag);

   _recv_001_flag = false;
}



/*
==============================================================================
Name : run_001b
==============================================================================
*/

void  TestSignal::run_001b ()
{
#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE) \
   && (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   root._a.entity ().emplace <AView> (root._a);

   root._a._signal_int (123);

   document.pull ();

   flip_TEST (root._a.entity ().use <AView> ()._signaled_flag);

   root._a.entity ().erase <AView> ();
#endif
}



/*
==============================================================================
Name : run_001c
==============================================================================
*/

void  TestSignal::run_001c ()
{
#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE) \
   && (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);
   document.pull ();

   Root & root = document.root <Root> ();

   root._a.entity ().emplace <AView> (root._a);

   root._a._signal_int (123);

   document.pull ();

   flip_TEST (root._a.entity ().use <AView> ()._signaled_flag);

   root._a.entity ().erase <AView> ();
#endif
}



/*
==============================================================================
Name : recv_001
==============================================================================
*/

void  TestSignal::recv_001 (int val)
{
   flip_TEST (val == 123);
   _recv_001_flag = true;
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestSignal::run_002 ()
{
   _recv_002_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_double_int.connect (*this, &TestSignal::recv_002);

   root._a._signal_double_int (0.25, 234);

   document.pull ();

   flip_TEST (_recv_002_flag);

   _recv_002_flag = false;
}



/*
==============================================================================
Name : recv_002
==============================================================================
*/

void  TestSignal::recv_002 (double x, int y)
{
   flip_TEST (x == 0.25);
   flip_TEST (y == 234);
   _recv_002_flag = true;
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestSignal::run_003 ()
{
   _recv_003_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_float_double_int.connect (*this, &TestSignal::recv_003);

   root._a._signal_float_double_int (1.25f, 0.33, 456);

   document.pull ();

   flip_TEST (_recv_003_flag);

   _recv_003_flag = false;
}



/*
==============================================================================
Name : recv_003
==============================================================================
*/

void  TestSignal::recv_003 (float z, double x, int y)
{
   flip_TEST (z == 1.25f);
   flip_TEST (x == 0.33);
   flip_TEST (y == 456);
   _recv_003_flag = true;
}



/*
==============================================================================
Name : run_003b
==============================================================================
*/

void  TestSignal::run_003b ()
{
   _recv_003_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_float_double_int.connect ([this](float z, double x, int y) {
      flip_TEST (z == 1.25f);
      flip_TEST (x == 0.33);
      flip_TEST (y == 456);
      _recv_003_flag = true;
   });

   root._a._signal_float_double_int (1.25f, 0.33, 456);

   document.pull ();

   flip_TEST (_recv_003_flag);

   _recv_003_flag = false;
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestSignal::run_004 ()
{
   _recv_004_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_info.connect ([this](A::Info info) {
      flip_TEST (info._val_1 == 789456123789456123ULL);
      flip_TEST (info._val_2 == 1234);
      _recv_004_flag = true;
   });

   A::Info info;
   info._val_1 = 789456123789456123ULL;
   info._val_2 = 1234;
   root._a._signal_info (info);

   document.pull ();

   flip_TEST (_recv_004_flag);

   _recv_004_flag = false;
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestSignal::run_005 ()
{
   _recv_005_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_cr_info.connect ([this](const A::Info & info) {
      flip_TEST (info._val_1 == 789456123789456123ULL);
      flip_TEST (info._val_2 == 1234);
      _recv_005_flag = true;
   });

   A::Info info;
   info._val_1 = 789456123789456123ULL;
   info._val_2 = 1234;
   root._a._signal_cr_info (info);

   document.pull ();

   flip_TEST (_recv_005_flag);

   _recv_005_flag = false;
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestSignal::run_006 ()
{
   _recv_006_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_vector_info.connect ([this](const std::vector <A::Info> & info_arr) {
      flip_TEST (info_arr.size () == 2);
      flip_TEST (info_arr [0]._val_1 == 789456123789456123ULL);
      flip_TEST (info_arr [0]._val_2 == 1234);
      flip_TEST (info_arr [1]._val_1 == 123456789ULL);
      flip_TEST (info_arr [1]._val_2 == 4567);
      _recv_006_flag = true;
   });

   std::vector <A::Info> info_arr (2);
   info_arr [0]._val_1 = 789456123789456123ULL;
   info_arr [0]._val_2 = 1234;
   info_arr [1]._val_1 = 123456789ULL;
   info_arr [1]._val_2 = 4567;

   root._a._signal_vector_info (info_arr);

   document.pull ();

   flip_TEST (_recv_006_flag);

   _recv_006_flag = false;
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestSignal::run_007 ()
{
   _recv_007_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_list_info.connect ([this](const std::list <A::Info> & info_arr) {
      flip_TEST (info_arr.size () == 2);
      auto it = info_arr.begin ();
      flip_TEST (it->_val_1 == 789456123789456123ULL);
      flip_TEST (it->_val_2 == 1234);
      ++it;
      flip_TEST (it->_val_1 == 123456789ULL);
      flip_TEST (it->_val_2 == 4567);
      _recv_007_flag = true;
   });

   std::list <A::Info> info_arr;
   info_arr.push_back ({789456123789456123ULL, 1234});
   info_arr.push_back ({123456789ULL, 4567});
   flip_TEST (info_arr.size () == 2);

   root._a._signal_list_info (info_arr);

   document.pull ();

   flip_TEST (_recv_007_flag);

   _recv_007_flag = false;
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestSignal::run_008 ()
{
   _recv_008_flag = false;

   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx = root._a._signal_map_double_info.connect ([this](const std::map <double, A::Info> & info_map) {
      flip_TEST (info_map.size () == 2);
      auto it = info_map.begin ();
      flip_TEST (it->first == 0.0);
      flip_TEST (it->second._val_1 == 789456123789456123ULL);
      flip_TEST (it->second._val_2 == 1234);
      ++it;
      flip_TEST (it->first == 2.5);
      flip_TEST (it->second._val_1 == 123456789ULL);
      flip_TEST (it->second._val_2 == 4567);
      _recv_008_flag = true;
   });

   std::map <double, A::Info> info_map;
   info_map [0.0] = {789456123789456123ULL, 1234};
   info_map [2.5] = {123456789ULL, 4567};

   root._a._signal_map_double_info (info_map);

   document.pull ();

   flip_TEST (_recv_008_flag);

   _recv_008_flag = false;
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestSignal::run_009 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx;

   int val = 0;

   cnx = root._a._signal_void.connect ([&val](){
      val = 1;
   });

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 1);

   val = 0;

   cnx = root._a._signal_void.connect ([&val](){
      val = 2;
   });

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 2);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestSignal::run_010 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx;
   SignalConnection cnx2;

   int val = 0;

   auto lambda = [&val](){
      val += 1;
   };

   cnx = root._a._signal_void.connect (lambda);
   cnx2 = root._a._signal_void.connect (lambda);

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 2);

   cnx2.disconnect ();

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 3);

   cnx.disconnect ();

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 3);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestSignal::run_011 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'sig ');

   Root & root = document.root <Root> ();

   SignalConnection cnx;

   int val = 0;

   cnx = root._a._signal_void.connect ([&val](){
      val += 3;   // COV_NF_LINE
   });            // COV_NF_LINE

   cnx = root._a._signal_void.connect ([&val](){
      val += 7;
   });

   root._a._signal_void ();

   document.pull ();

   flip_TEST (val == 7);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

