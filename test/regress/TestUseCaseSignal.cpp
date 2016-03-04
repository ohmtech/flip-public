/*****************************************************************************

      TestUseCaseSignal.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUseCaseSignal.h"

#include "flip/config.h"
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

void  TestUseCaseSignal::run ()
{
   Model::version ("test.usecase");

   Model::declare <Note> ()
      .name ("Note")
      .member <Float, &Note::_position> ("position")
      .member <Float, &Note::_duration> ("duration");

   Model::declare <Clip> ()
      .name ("Clip")
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
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : NoteView::ctor
==============================================================================
*/

TestUseCaseSignal::NoteView::NoteView (Note & note)
:  _cnx (note.signal_play.connect (*this, &NoteView::play))
{
}



/*
==============================================================================
Name : NoteView::dtor
==============================================================================
*/

TestUseCaseSignal::NoteView::~NoteView ()
{
}



/*
==============================================================================
Name : NoteView::play
==============================================================================
*/

void  TestUseCaseSignal::NoteView::play (double velocity)
{
   flip_TEST (!_fired_flag);
   flip_TEST (velocity == 0.5);

   _fired_flag = true;
}



/*
==============================================================================
Name : NoteView2::ctor
==============================================================================
*/

TestUseCaseSignal::NoteView2::NoteView2 (Note & note)
:  _cnx (note.signal_play.connect (*this, &NoteView2::play))
{
}



/*
==============================================================================
Name : NoteView2::dtor
==============================================================================
*/

TestUseCaseSignal::NoteView2::~NoteView2 ()
{
}



/*
==============================================================================
Name : NoteView2::play
==============================================================================
*/

void  TestUseCaseSignal::NoteView2::play (double velocity)
{
   flip_TEST (!_fired_flag);
   flip_TEST (velocity == 0.5);

   _fired_flag = true;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestUseCaseSignal::run_001 ()
{
#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE) \
   && (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song._clips.emplace ();
   Note & note1 = *clip._notes.emplace <Note> (0.0, 1.0);
   clip._notes.emplace <Note> (1.0, 1.0);

   Track & track = *song._tracks.emplace ();
   track._clip_frames.emplace (clip, 0.0, 4.0);

   NoteView & note_view = note1.entity ().emplace <NoteView> (note1);

   note1.signal_play (0.5);

   document.commit ();
   document.pull ();
   flip_TEST (note_view._fired_flag);

   // !!! warning !!! this is essential, because the signal
   // is deleted before the entity (and therefore NoteView which
   // reference the signal in this example)
   // this is detected in entity strict mode
   note1.entity ().erase <NoteView> ();

   bool fired_flag = false;
   SignalConnection cnx = track.signal_open_gui.connect ([&fired_flag](){fired_flag = true;});

   track.signal_open_gui ();

   document.pull ();
   flip_TEST (fired_flag);
#endif
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestUseCaseSignal::run_002 ()
{
#if (flip_ENTITY_LOCATION != flip_ENTITY_LOCATION_NONE) \
   && (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song._clips.emplace ();
   Note & note1 = *clip._notes.emplace <Note> (0.0, 1.0);
   clip._notes.emplace <Note> (1.0, 1.0);

   Track & track = *song._tracks.emplace ();
   track._clip_frames.emplace (clip, 0.0, 4.0);

   NoteView & note_view1 = note1.entity ().emplace <NoteView> (note1);
   NoteView2 & note_view2 = note1.entity ().emplace <NoteView2> (note1);

   document.commit ();

   note1.signal_play (0.5);

   document.pull ();
   flip_TEST (note_view1._fired_flag);
   flip_TEST (note_view2._fired_flag);

   note1.entity ().erase <NoteView> ();
   note1.entity ().erase <NoteView2> ();
#endif
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

