/*****************************************************************************

      TestUseCaseCopyPaste.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUseCaseCopyPaste.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/Mold.h"
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

void  TestUseCaseCopyPaste::run ()
{
   Model::version ("test.usecase");

   Model::declare <Note> ()
      .name ("Note")
      .member <Float, &Note::_position> ("position")
      .member <Float, &Note::_duration> ("duration");

   Model::declare <NoteMidi> ()
      .name ("NoteMidi")
      .inherit <Note> ()
      .member <Int, &NoteMidi::_velocity> ("velocity");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Int, &Clip::_color> ("color")
      .member <Notes, &Clip::_notes> ("notes");

   Model::declare <ClipFrame> ()
      .name ("ClipFrame")
      .member <ObjectRef <Clip>, &ClipFrame::_clip_ref> ("clip_ref")
      .member <Float, &ClipFrame::_position> ("position")
      .member <Float, &ClipFrame::_duration> ("duration");

   Model::declare <Track> ()
      .name ("Track")
      .member <ClipFrames, &Track::_clip_frames> ("clip_frames");

   Model::declare <Song> ()
      .name ("Song")
      .member <Clips, &Song::_clips> ("clips")
      .member <Tracks, &Song::_tracks> ("tracks");



   run_001 ();
   run_002 ();
   run_003 ();
}



/*
==============================================================================
Name : copy
==============================================================================
*/

std::vector <uint8_t>   TestUseCaseCopyPaste::copy (std::vector <uint8_t> & data, ClipFrame & clip_frame)
{
   StreamBinOut sbo (data);

   Track & track = clip_frame.ancestor <Track> ();

   // remember original track ref
   sbo << track.ref ();

   Mold mold (Model::use (), sbo);
   mold.make (clip_frame);
   mold.make (*clip_frame._clip_ref);
   mold.make (clip_frame.ancestor <Track> (), true);  // only direct members
   mold.cure ();

   return data;
}



/*
==============================================================================
Name : paste
==============================================================================
*/

void  TestUseCaseCopyPaste::paste (Song & song, const std::vector <uint8_t> & data, double position_offset, bool deep_copy_flag)
{
   StreamBinIn sbi (data);

   while (!sbi.is_eos ())
   {
      Ref track_ref;
      sbi >> track_ref;

      Track * track_ptr = song.document ().object_ptr <Track> (track_ref);
      if (track_ptr == nullptr) return;   // abort

      Track & track = *track_ptr;

      Mold mold (Model::use (), sbi);

      ClipFrame & clip_frame = *track._clip_frames.emplace (mold);
      clip_frame._position += position_offset;

      if (deep_copy_flag)
      {
         Clip & clip = *song._clips.emplace (mold);
         clip_frame._clip_ref = &clip;
      }
   }

   song.document ().commit ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
Description :
   Copy, and "linked" paste.
==============================================================================
*/

void  TestUseCaseCopyPaste::run_001 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song._clips.emplace (1);
   clip._notes.emplace <NoteMidi> (0.0, 1.0, 2);
   clip._notes.emplace <NoteMidi> (1.0, 1.0, 16);

   Track & track = *song._tracks.emplace ();
   ClipFrame & clip_frame = *track._clip_frames.emplace (clip, 0.0, 4.0);

   std::vector <uint8_t> data;
   copy (data, clip_frame);

   paste (song, data, 4.0, false);

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 1);
   flip_TEST (song._clips.begin ()->_notes.count_if ([](Note &){return true;}) == 2);
   flip_TEST (song._tracks.count_if ([](Track &){return true;}) == 1);
   flip_TEST (song._tracks.begin ()->_clip_frames.count_if ([](ClipFrame &){return true;}) == 2);
}



/*
==============================================================================
Name : run_002
Description :
   Copy, and "deep copy" paste.
==============================================================================
*/

void  TestUseCaseCopyPaste::run_002 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song._clips.emplace (1);
   clip._notes.emplace <NoteMidi> (0.0, 1.0, 2);
   clip._notes.emplace <NoteMidi> (1.0, 1.0, 16);

   Track & track = *song._tracks.emplace ();
   ClipFrame & clip_frame = *track._clip_frames.emplace (clip, 0.0, 4.0);

   std::vector <uint8_t> data;
   copy (data, clip_frame);

   paste (song, data, 4.0, true);

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 2);
   flip_TEST (song._clips.begin ()->_notes.count_if ([](Note &){return true;}) == 2);
   flip_TEST (song._tracks.count_if ([](Track &){return true;}) == 1);
   flip_TEST (song._tracks.begin ()->_clip_frames.count_if ([](ClipFrame &){return true;}) == 2);
}



/*
==============================================================================
Name : run_003
Description :
   Copy multiple.
==============================================================================
*/

void  TestUseCaseCopyPaste::run_003 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song._clips.emplace (1);
   clip._notes.emplace <NoteMidi> (0.0, 1.0, 2);
   clip._notes.emplace <NoteMidi> (1.0, 1.0, 16);

   Track & track = *song._tracks.emplace ();
   ClipFrame & clip_frame1 = *track._clip_frames.emplace (clip, 0.0, 4.0);
   ClipFrame & clip_frame2 = *track._clip_frames.emplace (clip, 4.0, 8.0);

   std::vector <uint8_t> data;
   copy (data, clip_frame1);
   copy (data, clip_frame2);

   paste (song, data, 8.0, true);

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 3);
   flip_TEST (song._clips.begin ()->_notes.count_if ([](Note &){return true;}) == 2);
   flip_TEST (song._tracks.count_if ([](Track &){return true;}) == 1);
   flip_TEST (song._tracks.begin ()->_clip_frames.count_if ([](ClipFrame &){return true;}) == 4);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

