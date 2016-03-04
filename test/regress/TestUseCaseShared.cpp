/*****************************************************************************

      TestUseCaseShared.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUseCaseShared.h"

#include "flip/Class.h"
#include "flip/Document.h"
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

void  TestUseCaseShared::run ()
{
   Model::version ("test.usecase");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Int, &Clip::_color> ("color");

   Model::declare <ClipFrame> ()
      .name ("ClipFrame")
      .member <ObjectRef <Clip>, &ClipFrame::_clip_ref> ("clip_ref")
      .member <Float, &ClipFrame::_position> ("position")
      .member <Float, &ClipFrame::_duration> ("duration");

   Model::declare <Song> ()
      .name ("Song")
      .member <Clips, &Song::_clips> ("clips")
      .member <ClipFrames, &Song::_clip_frames> ("clip_frames");



   run_001 ();
   run_002 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestUseCaseShared::run_001 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();

   song._clips.disable_in_undo ();

   song._clips.emplace (1);

   Transaction tx = document.commit ();

   // undo

   bool undo_mode_flag = true;
   document.execute_backward (tx, undo_mode_flag);
   document.commit ();

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 1);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestUseCaseShared::run_002 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();

   song._clips.disable_in_undo ();

   Clip & clip = *song._clips.emplace (1);
   song._clip_frames.emplace (clip, 0.0, 1.0);
   song._clip_frames.emplace (clip, 2.0, 3.0);

   Transaction tx = document.commit ();

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 1);
   flip_TEST (song._clip_frames.count_if ([](ClipFrame &){return true;}) == 2);

   // undo

   bool undo_mode_flag = true;
   document.execute_backward (tx, undo_mode_flag);
   document.commit ();

   flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 1);
   flip_TEST (song._clip_frames.count_if ([](ClipFrame &){return true;}) == 0);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

