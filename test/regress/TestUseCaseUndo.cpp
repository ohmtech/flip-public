/*****************************************************************************

      TestUseCaseUndo.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUseCaseUndo.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/History.h"
#include "flip/HistoryStoreMemory.h"
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

void  TestUseCaseUndo::run ()
{
   Model::version ("test.usecase");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Float, &Clip::_position> ("position")
      .member <Float, &Clip::_duration> ("duration");

   Model::declare <Track> ()
      .name ("Track")
      .member <Clips, &Track::_clips> ("clips");

   Model::declare <SelectionElem> ()
      .name ("SelectionElem")
      .member <ObjectRef <Object>, &SelectionElem::_object_ref> ("object_ref");

   Model::declare <Song> ()
      .name ("Song")
      .member <Selection, &Song::_selection> ("selection")
      .member <Tracks, &Song::_tracks> ("tracks");



   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
}



/*
==============================================================================
Name : move
Description :
   Move the current selection of song so that 'clip' is at 'position'
==============================================================================
*/

Transaction TestUseCaseUndo::move (Song & song, Clip & clip, double position)
{
   double position_delta = position - clip._position;

   for (auto & elem : song._selection)
   {
      elem.use <Clip> ()._position += position_delta;
   }

   return song.document ().commit ();
}  // COV_NF_LINE



/*
==============================================================================
Name : undo
Description :
   Complete the transaction just before execution.
==============================================================================
*/

void  TestUseCaseUndo::undo (Song & song, Transaction tx, const std::set <Ref> & ref_set)
{
   song.document ().execute_correct_backward (tx);

   select (song, ref_set);

   song.document ().commit ();
}



/*
==============================================================================
Name : redo
Description :
   Complete the transaction just before execution.
==============================================================================
*/

void  TestUseCaseUndo::redo (Song & song, Transaction tx, const std::set <Ref> & ref_set)
{
   song.document ().execute_correct_forward (tx);

   select (song, ref_set);

   song.document ().commit ();
}



/*
==============================================================================
Name : select
==============================================================================
*/

void  TestUseCaseUndo::select (Song & song, const std::set <Ref> & ref_set)
{
   for (const auto & ref : ref_set)
   {
      // insert if not in selection

      auto it = song._selection.find_if ([&ref](SelectionElem & elem) {
         return elem.template use <Object> ().ref () == ref;
      });

      if (it == song._selection.end ())
      {
         song._selection.emplace (song.document ().object <Object> (ref));
      }
   }

   auto it = song._selection.begin ();
   auto it_end = song._selection.end ();

   for (; it != it_end ;)
   {
      auto it_next = it;
      ++it_next;

      auto & elem = *it;

      // erase if not in 'ref_set'

      if (ref_set.find (elem.use <Object> ().ref ()) == ref_set.end ())
      {
         song._selection.erase (it);
      }

      it = it_next;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestUseCaseUndo::run_001 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();

   // memorize selection

   std::set <Ref> ref_set;

   for (auto & elem : song._selection)
   {
      ref_set.insert (elem.use <Object> ().ref ());
   }

   Transaction tx = move (song, clip1, 3.0);

   // undo

   undo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 1.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 5.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);


   // redo

   redo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 3.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 7.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestUseCaseUndo::run_002 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();

   // memorize selection

   std::set <Ref> ref_set;

   for (auto & elem : song._selection)
   {
      ref_set.insert (elem.use <Object> ().ref ());
   }

   Transaction tx = move (song, clip1, 3.0);

   song._selection.clear ();
   document.commit ();

   // undo

   undo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 1.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 5.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);


   song._selection.clear ();
   document.commit ();

   // redo

   redo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 3.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 7.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestUseCaseUndo::run_003 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   Clip & clip3 = *track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();

   // memorize selection

   std::set <Ref> ref_set;

   for (auto & elem : song._selection)
   {
      ref_set.insert (elem.use <Object> ().ref ());
   }

   Transaction tx = move (song, clip1, 3.0);

   song._selection.clear ();
   song._selection.emplace (clip3);
   document.commit ();

   // undo

   undo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 1.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 5.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);


   song._selection.clear ();
   song._selection.emplace (clip3);
   document.commit ();

   // redo

   redo (song, tx, ref_set);

   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 3.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
   }) == 1);
   flip_TEST (track._clips.count_if ([](Clip & sub_clip){
      return (sub_clip._position == 7.0) && (sub_clip._duration == 1.0);
   }) == 1);
   flip_TEST (song._selection.count_if ([](SelectionElem &){return true;}) == 2);
   flip_TEST (song._selection.count_if ([&clip1](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip1.ref ();
   }) == 1);
   flip_TEST (song._selection.count_if ([&clip2](SelectionElem & elem){
      return elem.template use <Object> ().ref () == clip2.ref ();
   }) == 1);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestUseCaseUndo::run_004 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();
   document.push ();

   History <HistoryStoreMemory> history (document);

   clip1._position = 2.0;

   document.commit ();
   auto tx = document.squash ();
   history.add_undo_step (tx);

   bool ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.0);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 2.0);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestUseCaseUndo::run_005 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();
   document.push ();

   History <HistoryStoreMemory> history (document);

   clip1._position = 2.0;

   document.commit ();
   auto tx = document.squash ();
   history.add_undo_step (tx);

   clip1._position = 3.5;

   document.commit ();
   tx = document.squash ();
   *history.last_undo () = tx;

   bool ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.0);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 3.5);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestUseCaseUndo::run_006 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 1.0);
   Clip & clip3 = *track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();
   document.push ();

   History <HistoryStoreMemory> history (document);

   //

   clip1._position = 2.0;

   document.commit ();
   auto tx = document.squash ();
   history.add_undo_step (tx);

   //

   clip1._position = 3.5;

   document.commit ();
   tx = document.squash ();
   *history.last_undo () = tx;
   document.push ();

   //

   clip1._position = 4.7;
   clip1._duration = 2.5;
   clip2._position = 4.2;

   document.commit ();
   tx = document.squash ();
   history.add_undo_step (tx);

   //

   clip2._position = 4.2;
   document.commit ();

   clip1._position = 1.2;
   document.commit ();

   clip3._position = 3.4;
   document.commit ();

   tx = document.squash ();
   *history.last_undo () = tx;

   //

   bool ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 3.5);
   flip_TEST (clip1._duration == 1.0);
   flip_TEST (clip2._position == 5.0);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 2.5);
   flip_TEST (clip3._duration == 2.0);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.2);
   flip_TEST (clip1._duration == 2.5);
   flip_TEST (clip2._position == 4.2);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 3.4);
   flip_TEST (clip3._duration == 2.0);

   ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.0);
   flip_TEST (clip1._duration == 1.0);
   flip_TEST (clip2._position == 5.0);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 2.5);
   flip_TEST (clip3._duration == 2.0);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 3.5);
   flip_TEST (clip1._duration == 1.0);
   flip_TEST (clip2._position == 5.0);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 2.5);
   flip_TEST (clip3._duration == 2.0);

   ok_flag = history.execute_undo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.0);
   flip_TEST (clip1._duration == 1.0);
   flip_TEST (clip2._position == 5.0);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 2.5);
   flip_TEST (clip3._duration == 2.0);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   ok_flag = history.execute_redo ();
   flip_TEST (ok_flag);

   flip_TEST (clip1._position == 1.2);
   flip_TEST (clip1._duration == 2.5);
   flip_TEST (clip2._position == 4.2);
   flip_TEST (clip2._duration == 1.0);
   flip_TEST (clip3._position == 3.4);
   flip_TEST (clip3._duration == 2.0);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

