/*****************************************************************************

      TestHistory.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestHistory.h"

#include "flip/Class.h"
#include "flip/HistoryStoreMemory.h"
#include "flip/contrib/HistoryStoreFile.h"
#include "flip/detail/def.h"
#include "TestDef.h"

#if (flip_PLATFORM == flip_PLATFORM_IOS)
   // this file is required to be compiled as a Objective-C++ source file
   #import <Foundation/Foundation.h>
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

void  TestHistory::run ()
{
   Model::version ("test.history");

   Model::declare <A> ()
      .name ("A")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float");

   Model::declare <Root> ()
      .name ("Root")
      .member <A, &Root::_a> ("a");

   Model2::version ("test.history2");

   Model2::declare <Root2> ()
      .name ("Root");

   run_000 <HistoryStoreMemory> ();
   run_001 <HistoryStoreMemory> ();
   run_002 <HistoryStoreMemory> ();
   run_003 <HistoryStoreMemory> ();
   run_004 <HistoryStoreMemory> ();
   run_005 <HistoryStoreMemory> ();
   run_005b <HistoryStoreMemory> ();
   run_006 <HistoryStoreMemory> ();
   run_007 <HistoryStoreMemory> ();
   run_008 <HistoryStoreMemory> ();
   run_008b <HistoryStoreMemory> ();
   run_009 <HistoryStoreMemory> ();
   run_009b <HistoryStoreMemory> ();
   run_010 <HistoryStoreMemory> ();
   run_010b <HistoryStoreMemory> ();
   run_011 <HistoryStoreMemory> ();
   run_011b <HistoryStoreMemory> ();
   run_012 <HistoryStoreMemory> ();
   run_013 <HistoryStoreMemory> ();
   run_013b <HistoryStoreMemory> ();
   run_016 <HistoryStoreMemory> ();
   run_016b <HistoryStoreMemory> ();
   run_016c <HistoryStoreMemory> ();
   run_016d <HistoryStoreMemory> ();

   // special path to tell sqlite to operate in memory
   const char * path_0 = ":memory:";

   // path to test persistence

#if (flip_PLATFORM == flip_PLATFORM_IOS)
   const char * path2_0
      = [[NSTemporaryDirectory() stringByAppendingPathComponent:@"undo.sqlite"] UTF8String];
#else
   const char * path2_0 = "undo.sqlite";
#endif

   run_000 <HistoryStoreFile> (path_0);
   run_001 <HistoryStoreFile> (path_0);
   run_002 <HistoryStoreFile> (path_0);
   run_003 <HistoryStoreFile> (path_0);
   run_004 <HistoryStoreFile> (path_0);
   run_005 <HistoryStoreFile> (path_0);
   run_005b <HistoryStoreFile> (path_0);
   run_006 <HistoryStoreFile> (path_0);
   run_007 <HistoryStoreFile> (path_0);
   run_008 <HistoryStoreFile> (path_0);
   run_008b <HistoryStoreFile> (path_0);
   run_009 <HistoryStoreFile> (path_0);
   run_009b <HistoryStoreFile> (path_0);
   run_010 <HistoryStoreFile> (path_0);
   run_010b <HistoryStoreFile> (path_0);
   run_011 <HistoryStoreFile> (path_0);
   run_011b <HistoryStoreFile> (path_0);
   run_012 <HistoryStoreFile> (path_0);
   run_013 <HistoryStoreFile> (path_0);
   run_013b <HistoryStoreFile> (path_0);

   run_016 <HistoryStoreFile> (path_0);
   run_016b <HistoryStoreFile> (path_0);
   run_016c <HistoryStoreFile> (path_0);
   run_016d <HistoryStoreFile> (path_0);

   run_014 (path2_0);
   run_014b ();
   run_015 (path2_0);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestHistory::run_014 (const char * path_0)
{
   remove (path_0);

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');
      History <HistoryStoreFile> history (document, path_0);

      Root & root = document.root <Root> ();

      root._a._int = 2LL;
      root._a._float = 3.5;

      auto tx = document.commit ();
      history.add_undo_step (tx);
   }

   {
      Document document (Model2::use (), 123456789UL, 'appl', 'gui ');
      History <HistoryStoreFile> history (document, path_0);

      flip_TEST (document.data_model ().version () != history.version ());

      history.clear ();

      flip_TEST (document.data_model ().version () == history.version ());
   }
}



/*
==============================================================================
Name : run_014b
==============================================================================
*/

void  TestHistory::run_014b ()
{
   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');
      History <HistoryStoreMemory> history (document);

      Root & root = document.root <Root> ();

      root._a._int = 2LL;
      root._a._float = 3.5;

      auto tx = document.commit ();
      history.add_undo_step (tx);

      history.clear ();

      flip_TEST (history.begin () == history.end ());
      flip_TEST (history.last_undo () == history.end ());
      flip_TEST (history.first_redo () == history.end ());
   }
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestHistory::run_015 (const char * path_0)
{
   remove (path_0);

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   {
      History <HistoryStoreFile> history (document, path_0);

      Root & root = document.root <Root> ();

      root._a._int = 2LL;
      root._a._float = 3.5;

      auto tx = document.commit ();
      history.add_undo_step (tx);
   }

   {
      History <HistoryStoreFile> history (document, path_0);

      Root & root = document.root <Root> ();

      bool ok_flag = history.execute_undo ();
      flip_TEST (ok_flag);

      flip_TEST (root._a._int == 0LL);
      flip_TEST (root._a._float== 0.0);
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

