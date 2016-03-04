/*****************************************************************************

      TestDataModelClone.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestDataModelClone.h"

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

void  TestDataModelClone::run ()
{
   Model::version ("test.document");

   Model::declare <Clip::Content> ()
      .name ("Content")
      .enumerator <Clip::Content::Audio> ("Audio")
      .enumerator <Clip::Content::Midi> ("Midi");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Float, &Clip::position> ("position")
      .member <Float, &Clip::duration> ("duration")
      .member <Int, &Clip::color_id> ("color_id")
      .member <Enum <Clip::Content>, &Clip::content> ("content");

   Model::declare <ClipAudio> ()
      .name ("ClipAudio")
      .inherit <Clip> ()
      .member <String, &ClipAudio::sample_path> ("sample_path");

   Model::declare <Track> ()
      .name ("Track")
      .member <Collection <Clip>, &Track::clip_coll> ("clip_coll");

   Model::declare <Song> ()
      .name ("Song")
      .member <Array <Track>, &Song::track_arr> ("track_arr");


   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDataModelClone::run_001 ()
{
   ModelClip::clone_from <Model> ();
   ModelClip::set_root <Clip> ();

   flip_TEST (ModelClip::has <Clip::Content> ());
   flip_TEST (ModelClip::use ().has_enum ("Content"));
   flip_TEST (ModelClip::has <Clip> ());
   flip_TEST (ModelClip::use ().has_class ("Clip"));
   flip_TEST (Class <Clip>::use ().type_id (ModelClip::use ()) == TypeId::OBJECT);
   flip_TEST (ModelClip::has <ClipAudio> ());
   flip_TEST (ModelClip::use ().has_class ("ClipAudio"));
   flip_TEST (Class <ClipAudio>::use ().type_id (ModelClip::use ()) == TypeId::OBJECT + 1);
   flip_TEST (ModelClip::has <Track> ());
   flip_TEST (ModelClip::use ().has_class ("Track"));
   flip_TEST (Class <Track>::use ().type_id (ModelClip::use ()) == TypeId::OBJECT + 3);
   flip_TEST (ModelClip::has <Song> ());
   flip_TEST (ModelClip::use ().has_class ("Song"));
   flip_TEST (Class <Song>::use ().type_id (ModelClip::use ()) == TypeId::OBJECT + 2);
   flip_TEST (&ModelClip::use ().get_root_class () == &Class <Clip>::use ());

   Document document (ModelClip::use (), 123456789UL, 'appl', 'gui ');

   Clip & clip = document.root <Clip> ();
   clip.position = 2.3;
   clip.duration = 3.3;
   clip.color_id = 5LL;

   document.commit ();
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDataModelClone::run_002 ()
{
   ModelClipAudio::clone_from <Model> ();
   ModelClipAudio::set_root <ClipAudio> ();

   flip_TEST (ModelClipAudio::has <Clip::Content> ());
   flip_TEST (ModelClipAudio::use ().has_enum ("Content"));
   flip_TEST (ModelClipAudio::has <Clip> ());
   flip_TEST (ModelClipAudio::use ().has_class ("Clip"));
   flip_TEST (ModelClipAudio::has <ClipAudio> ());
   flip_TEST (ModelClipAudio::use ().has_class ("ClipAudio"));
   flip_TEST (ModelClipAudio::has <Track> ());
   flip_TEST (ModelClipAudio::use ().has_class ("Track"));
   flip_TEST (ModelClipAudio::has <Song> ());
   flip_TEST (ModelClipAudio::use ().has_class ("Song"));
   flip_TEST (&ModelClipAudio::use ().get_root_class () == &Class <ClipAudio>::use ());

   Document document (ModelClipAudio::use (), 123456789UL, 'appl', 'gui ');

   ClipAudio & clip = document.root <ClipAudio> ();
   clip.position = 2.3;
   clip.duration = 3.3;
   clip.color_id = 5LL;
   clip.sample_path = "/path/to/sample";

   document.commit ();
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestDataModelClone::run_003 ()
{
   ModelTrack::clone_from <Model> ();
   ModelTrack::set_root <Track> ();

   flip_TEST (ModelTrack::has <Clip::Content> ());
   flip_TEST (ModelTrack::use ().has_enum ("Content"));
   flip_TEST (ModelTrack::has <Clip> ());
   flip_TEST (ModelTrack::use ().has_class ("Clip"));
   flip_TEST (ModelTrack::has <ClipAudio> ());
   flip_TEST (ModelTrack::use ().has_class ("ClipAudio"));
   flip_TEST (ModelTrack::has <Track> ());
   flip_TEST (ModelTrack::use ().has_class ("Track"));
   flip_TEST (ModelTrack::has <Song> ());
   flip_TEST (ModelTrack::use ().has_class ("Song"));
   flip_TEST (&ModelTrack::use ().get_root_class () == &Class <Track>::use ());

   Document document (ModelTrack::use (), 123456789UL, 'appl', 'gui ');

   Track & track = document.root <Track> ();
   ClipAudio & clip = dynamic_cast <ClipAudio &> (*track.clip_coll.emplace <ClipAudio> ());
   clip.position = 2.3;
   clip.duration = 3.3;
   clip.color_id = 5LL;
   clip.sample_path = "/path/to/sample";

   document.commit ();
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestDataModelClone::run_004 ()
{
   ModelSong::clone_from <Model> ();
   ModelSong::set_root <Song> ();

   flip_TEST (ModelSong::has <Clip::Content> ());
   flip_TEST (ModelSong::use ().has_enum ("Content"));
   flip_TEST (ModelSong::has <Clip> ());
   flip_TEST (ModelSong::use ().has_class ("Clip"));
   flip_TEST (ModelSong::has <ClipAudio> ());
   flip_TEST (ModelSong::use ().has_class ("ClipAudio"));
   flip_TEST (ModelSong::has <Track> ());
   flip_TEST (ModelSong::use ().has_class ("Track"));
   flip_TEST (ModelSong::has <Song> ());
   flip_TEST (ModelSong::use ().has_class ("Song"));
   flip_TEST (&ModelSong::use ().get_root_class () == &Class <Song>::use ());

   Document document (ModelSong::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();
   Track & track = *song.track_arr.emplace (song.track_arr.end ());
   ClipAudio & clip = dynamic_cast <ClipAudio &> (*track.clip_coll.emplace <ClipAudio> ());
   clip.position = 2.3;
   clip.duration = 3.3;
   clip.color_id = 5LL;
   clip.sample_path = "/path/to/sample";

   document.commit ();
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestDataModelClone::run_005 ()
{
   ModelFixture::clone_from <Model> ();
   ModelFixture::declare <TestFixture> ()
      .name ("TestFixture")
      .member <Song, &TestFixture::song> ("song");

   flip_TEST (ModelFixture::has <Clip::Content> ());
   flip_TEST (ModelFixture::use ().has_enum ("Content"));
   flip_TEST (ModelFixture::has <Clip> ());
   flip_TEST (ModelFixture::use ().has_class ("Clip"));
   flip_TEST (Class <Clip>::use ().type_id (ModelFixture::use ()) == TypeId::OBJECT);
   flip_TEST (ModelFixture::has <ClipAudio> ());
   flip_TEST (ModelFixture::use ().has_class ("ClipAudio"));
   flip_TEST (Class <ClipAudio>::use ().type_id (ModelFixture::use ()) == TypeId::OBJECT + 1);
   flip_TEST (ModelFixture::has <Track> ());
   flip_TEST (ModelFixture::use ().has_class ("Track"));
   flip_TEST (Class <Track>::use ().type_id (ModelFixture::use ()) == TypeId::OBJECT + 4);
   flip_TEST (ModelFixture::has <Song> ());
   flip_TEST (ModelFixture::use ().has_class ("Song"));
   flip_TEST (Class <Song>::use ().type_id (ModelFixture::use ()) == TypeId::OBJECT + 2);
   flip_TEST (ModelFixture::has <TestFixture> ());
   flip_TEST (ModelFixture::use ().has_class ("TestFixture"));
   flip_TEST (Class <TestFixture>::use ().type_id (ModelFixture::use ()) == TypeId::OBJECT + 3);
   flip_TEST (&ModelFixture::use ().get_root_class () == &Class <TestFixture>::use ());

   Document document (ModelFixture::use (), 123456789UL, 'appl', 'gui ');

   TestFixture & fixture = document.root <TestFixture> ();
   Song & song = fixture.song;
   Track & track = *song.track_arr.emplace (song.track_arr.end ());
   ClipAudio & clip = dynamic_cast <ClipAudio &> (*track.clip_coll.emplace <ClipAudio> ());
   clip.position = 2.3;
   clip.duration = 3.3;
   clip.color_id = 5LL;
   clip.sample_path = "/path/to/sample";

   document.commit ();
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

