/*****************************************************************************

      TestUseCaseGhosting.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUseCaseGhosting.h"

#include "flip/CarrierDirect.h"
#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/Hub.h"
#include "flip/PortDirect.h"
#include "flip/detail/def.h"
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

void  TestUseCaseGhosting::run ()
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



   run_move ();
   run_move2 ();
}



/*
==============================================================================
Name : move
Description :
   Move the current selection of song so that 'clip' is at 'position'
==============================================================================
*/

bool  TestUseCaseGhosting::move (Song & song, Clip & clip, double position)
{
   // apply 'song._last_tx' so that we go back at the same start
   // position
   bool ok_flag = song.document ().execute_backward (song._last_tx);

   // detect conflict and end gesture if needed
   if (!ok_flag) return false;

   // commit will propagate to audio engine
   // but since audio engine will pull after this call, it will see only
   // the concatenation of the 2 commits (and seeing only the clip move
   // ie. not going back to their start position)
   song.document ().commit ();

   // 'clip' is at start position. calculate the delta position requested
   double position_delta = position - clip._position;

   // limit by the valid range of delta for the current selection
   position_delta = limit (get_move_range (song), position_delta);

   // move all the selection by this amount
   for (auto & elem : song._selection)
   {
      elem.use <Clip> ()._position += position_delta;
   }

   // shrink or split clips which range collide with selection
   for (auto & elem : song._selection)
   {
      cut (song, elem.use <Clip> ());
   }

   // apply the changes : this the tx from start position
   // to new position : store it for next move
   song._last_tx = song.document ().commit ();

   // don't push until end of move

   return true;
}



/*
==============================================================================
Name : move_end
Description :
   End move gesture
==============================================================================
*/

void  TestUseCaseGhosting::move_end (Song & song)
{
   song.document ().push ();

   // clear last tx

   song._last_tx.clear ();
}



/*
==============================================================================
Name : cut
Description :
   Shrink or split every clip on the same track of 'clip_sel' which range
   collide with 'clip_sel'
Note :
   Since the clips of the selection are moved by the same amount, they
   cannot collide if they didn't collide.
==============================================================================
*/

void  TestUseCaseGhosting::cut (Song & song, Clip & clip_sel)
{
   Track & track = clip_sel.ancestor <Track> ();

   auto it = track._clips.begin ();
   auto it_end = track._clips.end ();

   for (; it != it_end ;)
   {
      auto it_next = it;
      ++it_next;

      Clip & clip = *it;

      bool add_flag = false;

      if (&clip != &clip_sel)
      {
         add_flag = cut (song, clip_sel, clip);
      }

      it = add_flag ? track._clips.begin () : it_next;
   }
}



/*
==============================================================================
Name : cut
Description :
   Shrink or split 'clip' if it collides with 'clip_sel'
   Returns 'true' iff a clip was added to the track.
==============================================================================
*/

bool  TestUseCaseGhosting::cut (Song & /* song */, Clip & clip_sel, Clip & clip)
{
   Range clip_sel_range = clip_sel.get_range ();
   Range clip_range = clip.get_range ();
   Range clip_inter = intersect (clip_sel_range, clip_range);

   if (clip_inter.first >= clip_inter.second) return false; // no intersection

   Track & track = clip.ancestor <Track> ();
   auto it = track._clips.find_if ([&clip](Clip & sub_clip){return &clip == &sub_clip;});

   if (clip_inter.first == clip_range.first)
   {
      // clip_sel on the left or overlap

      if (clip_inter.second == clip_range.second)
      {
         // overlap

         track._clips.erase (it);
      }
      else
      {
         // shrink left

         double right = clip._position + clip._duration;
         clip._position = clip_sel_range.second;
         clip._duration = right - clip._position;
      }
   }
   else
   {
      if (clip_inter.second == clip_sel_range.second)
      {
         // split

         double left1 = clip_range.first;
         double right1 = clip_sel_range.first;

         double left2 = clip_sel_range.second;
         double right2 = clip_range.second;

         // shrink 1

         clip._position = left1;
         clip._duration = right1 - left1;

         // add 2

         track._clips.emplace (left2, right2 - left2);

         return true;   // add
      }
      else
      {
         // shrink right
         double right = clip_sel_range.first;
         clip._duration = right - clip._position;
      }
   }

   return false;  // removed or resized
}



/*
==============================================================================
Name : get_move_range
Description :
   Returns the range of acceptable position delta for the whole selection.
   An acceptable position is a position or 0 position.
==============================================================================
*/

TestUseCaseGhosting::Range TestUseCaseGhosting::get_move_range (Song & song)
{
   Range range (
      - std::numeric_limits <double>::infinity (),
      std::numeric_limits <double>::infinity ()
   );

   for (auto & elem : song._selection)
   {
      auto position = elem.use <Clip> ()._position;
      auto min_delta = - position;
      auto max_delta = std::numeric_limits <double>::infinity ();

      range.first = std::max (range.first, min_delta);
      range.second = std::min (range.second, max_delta);
   }

   return range;
}  // COV_NF_LINE



/*
==============================================================================
Name : limit
==============================================================================
*/

double   TestUseCaseGhosting::limit (Range range, double val)
{
   val = std::max (range.first, val);
   val = std::min (range.second, val);

   return val;
}



/*
==============================================================================
Name : intersect
==============================================================================
*/

TestUseCaseGhosting::Range TestUseCaseGhosting::intersect (Range lhs, const Range & rhs)
{
   lhs.first = std::max (lhs.first, rhs.first);
   lhs.second = std::min (lhs.second, rhs.second);

   return lhs;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_move
==============================================================================
*/

void  TestUseCaseGhosting::run_move ()
{
   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   document.pull ();

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip1 = *track._clips.emplace (1.0, 1.0);
   Clip & clip2 = *track._clips.emplace (5.0, 2.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip1);
   song._selection.emplace (clip2);

   document.commit ();
   document.push ();

   for (auto pos : {1.25, 1.75, 2.0, 2.5, 3.0, 4.0, 1.0, 0.0, -1.0})
   {
      bool ok_flag = move (song, clip1, pos);
      flip_TEST (ok_flag);

      if (pos == -1.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 0.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 1.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 4.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 0.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 0.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 1.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 4.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 1.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 1.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 5.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 1.25)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 1.25) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 5.25) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 1.75)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 1.75) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.75) && (sub_clip._duration == 1.75);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 5.75) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 2.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 3.0) && (sub_clip._duration == 1.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 6.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 2.5)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 3.5) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 6.5) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 3.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 3.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 0.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 4.0) && (sub_clip._duration == 0.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 7.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 4.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 4.0) && (sub_clip._duration == 1.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 1.5);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 8.0) && (sub_clip._duration == 2.0);
         }) == 1);
      }

      document.pull ();
   }

   move_end (song);
}



/*
==============================================================================
Name : run_move2
==============================================================================
*/

void  TestUseCaseGhosting::run_move2 ()
{
   PortDirect port;
   Hub hub (Model::use (), 123456789ULL, port);

   Document document (Model::use (), 123456789ULL, 'appl', 'gui ');
   CarrierDirect carrier (document, port);

   document.pull ();

   Song & song = document.root <Song> ();
   Track & track = *song._tracks.emplace ();
   Clip & clip = *track._clips.emplace (5.0, 2.0);
   track._clips.emplace (2.5, 2.0);
   song._selection.emplace (clip);

   document.commit ();
   document.push ();

   for (auto pos : {0.0, 2.5})
   {
      bool ok_flag = move (song, clip, pos);
      flip_TEST (ok_flag);

      if (pos == 0.0)
      {
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 0.0) && (sub_clip._duration == 2.0);
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
         }) == 1);
      }
      else if (pos == 2.5)
      {
         flip_TEST (track._clips.count_if ([](Clip &){
            return true;
         }) == 1);
         flip_TEST (track._clips.count_if ([](Clip & sub_clip){
            return (sub_clip._position == 2.5) && (sub_clip._duration == 2.0);
         }) == 1);
      }
   }

   move_end (song);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

