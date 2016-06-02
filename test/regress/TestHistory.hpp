/*****************************************************************************

      TestHistory.hpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (flip_TestHistory_CURRENT_CODEHEADER)
   #error Recursive inclusion of TestHistory code header.
#endif
#define  flip_TestHistory_CURRENT_CODEHEADER

#if ! defined (flip_TestHistory_CODEHEADER_INCLUDED)
#define  flip_TestHistory_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Document.h"
#include "flip/History.h"
#include "flip/detail/def.h"
#include "TestDef.h"



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_000 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   flip_TEST (document.data_model ().version () == history.version ());

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_001 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_002 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   root._a._int = 5LL;
   root._a._float = 4.7;

   auto tx2 = document.commit ();
   history.add_undo_step (tx2);

   history.execute_undo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 5LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 4.7);

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 5LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 4.7);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 0.0);

   history.execute_redo ();
   flip_TEST (root._a._int == 5LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 4.7);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_003 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   root._a._int = 5LL;
   root._a._float = 4.7;

   auto tx2 = document.commit ();
   history.add_undo_step (tx2);

   history.execute_undo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 5LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 4.7);

   document.commit ();

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 5LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 4.7);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_004 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();

   root._a._int = 5LL;
   root._a._float = 4.7;

   auto tx2 = document.commit ();
   history.add_undo_step (tx2);

   flip_TEST (history.first_redo () == history.end ());

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 5LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 4.7);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 5LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 4.7);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();

   flip_TEST (history.first_redo () == history.end ());
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_005 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   document.set_label ("to 2LL, 3.5");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.last_undo ()->label () == "to 2LL, 3.5");

   flip_TEST (history.first_redo () == history.end ());

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();

   flip_TEST (history.last_undo () == history.end ());

   flip_TEST (history.first_redo ()->label () == "to 2LL, 3.5");

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();
}



/*
==============================================================================
Name : run_005b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_005b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   document.set_label ("to 2LL, 3.5");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.clast_undo ()->label () == "to 2LL, 3.5");

   flip_TEST (history.cfirst_redo () == history.cend ());

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 2LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 3.5);

   document.commit ();

   flip_TEST (history.clast_undo () == history.cend ());

   flip_TEST (history.cfirst_redo ()->label () == "to 2LL, 3.5");

   history.execute_redo ();
   flip_TEST (root._a._int == 2LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 3.5);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_006 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   root._a._int = 0LL;
   root._a._float = 0.0;

   document.commit ();

   root._a._int = 4LL;
   root._a._float = 7.1;

   tx = document.commit ();
   *history.last_undo () = tx;

   history.execute_undo ();
   flip_TEST (root._a._int == 0LL);
   flip_TEST (root._a._int.before () == 4LL);
   flip_TEST (root._a._float == 0.0);
   flip_TEST (root._a._float.before () == 7.1);

   document.commit ();

   history.execute_redo ();
   flip_TEST (root._a._int == 4LL);
   flip_TEST (root._a._int.before () == 0LL);
   flip_TEST (root._a._float == 7.1);
   flip_TEST (root._a._float.before () == 0.0);

   document.commit ();
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_007 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 3.5;

   auto tx = document.commit ();
   flip_TEST (history.last_undo () == history.end ());
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_008 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   int i = 0;
   for (auto && tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "2LL");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 1);
         break;

      case 1:
         flip_TEST (tx2.label () == "3.5");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 2);
         break;

      case 2:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_008b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_008b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   int i = 0;
   for (const auto & tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "2LL");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 1);
         break;

      case 1:
         flip_TEST (tx2.label () == "3.5");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 2);
         break;

      case 2:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_009 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   history.store ().set_max_size (2);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   int i = 0;
   for (auto && tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "3.5");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 2);
         break;

      case 1:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_009b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_009b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   history.store ().set_max_size (2);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   int i = 0;
   for (const auto & tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "3.5");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 2);
         break;

      case 1:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_010 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   auto it = history.begin ();
   ++it;
   history.erase (it);

   //

   int i = 0;
   for (auto && tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "2LL");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 1);
         break;

      case 1:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_010b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_010b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   auto it = history.begin ();
   ++it;
   history.erase (it);

   //

   int i = 0;
   for (const auto & tx2 : history)
   {
      switch (i)
      {
      case 0:
         flip_TEST (tx2.label () == "2LL");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 1);
         break;

      case 1:
         flip_TEST (tx2.label () == "4.7");
         flip_TEST (tx2.user () == document.user ());
         flip_TEST (tx2.actor () == document.actor ());
         flip_TEST (tx2.nbr () == 3);
         break;
      }

      ++i;
   }
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_011 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   history.erase (history.begin ());
   history.erase (history.begin ());
   history.erase (history.begin ());

   //

   flip_TEST (history.begin () == history.end ());
}



/*
==============================================================================
Name : run_011b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_011b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   history.erase (history.begin ());
   history.erase (history.begin ());
   history.erase (history.begin ());

   //

   flip_TEST (history.cbegin () == history.cend ());
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_012 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   history.erase (history.last_undo ());
   history.erase (history.last_undo ());
   history.erase (history.last_undo ());

   //

   flip_TEST (history.begin () == history.end ());
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_013 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   history.execute_undo ();
   history.execute_undo ();

   // redo points to 3.5

   auto it = history.begin ();
   ++it; // 3.5

   history.erase (it);

   flip_TEST (history.first_redo ()->label () == "4.7");
   flip_TEST (history.last_undo ()->label () == "2LL");

   history.erase (history.begin ());

   flip_TEST (history.first_redo ()->label () == "4.7");
   flip_TEST (history.last_undo () == history.end ());

   history.erase (history.begin ());

   flip_TEST (history.first_redo () == history.end ());
   flip_TEST (history.last_undo () == history.end ());
}



/*
==============================================================================
Name : run_013b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_013b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;

   document.set_label ("2LL");

   auto tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 3.5;

   document.set_label ("3.5");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   root._a._float = 4.7;

   document.set_label ("4.7");

   tx = document.commit ();
   history.add_undo_step (tx);

   //

   history.execute_undo ();
   history.execute_undo ();

   // redo points to 3.5

   auto it = history.begin ();
   ++it; // 3.5

   history.erase (it);

   flip_TEST (history.cfirst_redo ()->label () == "4.7");
   flip_TEST (history.clast_undo ()->label () == "2LL");

   history.erase (history.begin ());

   flip_TEST (history.cfirst_redo ()->label () == "4.7");
   flip_TEST (history.clast_undo () == history.cend ());

   history.erase (history.begin ());

   flip_TEST (history.cfirst_redo () == history.cend ());
   flip_TEST (history.clast_undo () == history.cend ());
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_016 (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.first_redo () == history.end ());
   flip_TEST (history.last_undo () == history.end ());
}



/*
==============================================================================
Name : run_016b
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_016b (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int.disable_in_undo ();
   root._a._int = 2LL;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.first_redo () == history.end ());
   flip_TEST (history.last_undo () == history.end ());
}



/*
==============================================================================
Name : run_016c
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_016c (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int.disable_in_undo ();
   root._a._int = 2LL;
   root._a._float = 2.5;

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.first_redo () == history.end ());
   flip_TEST (history.last_undo () != history.end ());
}



/*
==============================================================================
Name : run_016d
==============================================================================
*/

template <class HistoryStoreImpl, class... Args>
void  TestHistory::run_016d (Args &&... args)
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   History <HistoryStoreImpl> history (document, args...);

   Root & root = document.root <Root> ();

   root._a._int = 2LL;
   root._a._float = 2.5;

   root._a._float.disable_in_undo ();

   auto tx = document.commit ();
   history.add_undo_step (tx);

   flip_TEST (history.first_redo () == history.end ());
   flip_TEST (history.last_undo () != history.end ());
}



}  // namespace flip



#endif   // flip_TestHistory_CODEHEADER_INCLUDED

#undef flip_TestHistory_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

