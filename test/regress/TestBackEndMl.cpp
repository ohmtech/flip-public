/*****************************************************************************

      TestBackEndMl.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestBackEndMl.h"

#include "flip/BackEndMl.h"
#include "flip/BackEndIR.h"
#include "flip/Class.h"
#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "flip/detail/def.h"
#include "TestDef.h"

#include <limits>

#include <cmath>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestBackEndMl::run ()
{
   Model::version ("appl.rev.1");

   Model::declare <Note> ()
      .name ("appl.Note")
      .member <Float, &Note::_position> ("position")
      .member <Float, &Note::_duration> ("duration");

   Model::declare <NoteMidi> ()
      .name ("appl.NoteMidi")
      .inherit <Note> ()
      .member <Int, &NoteMidi::_velocity> ("velocity");

   Model::declare <Color> ()
      .name ("appl.Color")
      .member <Int, &Color::_id> ("id");

   Model::declare <Clip> ()
      .name ("appl.Clip")
      .member <Color, &Clip::_color> ("color")
      .member <String, &Clip::_name> ("name")
      .member <Bool, &Clip::_active> ("active")
      .member <Notes, &Clip::_notes> ("notes");

   Model::declare <ClipFrame> ()
      .name ("appl.ClipFrame")
      .member <ObjectRef <Clip>, &ClipFrame::_clip_ref> ("clip_ref")
      .member <Float, &ClipFrame::_position> ("position")
      .member <Float, &ClipFrame::_duration> ("duration")
      .member <Blob, &ClipFrame::_sample_key> ("sample_key")
      .member <Blob, &ClipFrame::_chunk> ("chunk");

   Model::declare <Track> ()
      .name ("appl.Track")
      .member <ClipFrames, &Track::_clip_frames> ("clip_frames");

   Model::declare <Song> ()
      .name ("appl.Song")
      .member <Clips, &Song::_clips> ("clips")
      .member <Tracks, &Song::_tracks> ("tracks")
      .member <Message <>, &Song::_transport> ("transport");



   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestBackEndMl::run_000 ()
{
   std::vector <uint8_t> data;

   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Song & song = document.root <Song> ();

   Clip & clip1 = *song._clips.emplace (1, "clip1");
   clip1._notes.emplace <NoteMidi> (std::numeric_limits <double>::infinity (), 1.0, 80);
   clip1._notes.emplace <NoteMidi> (- std::numeric_limits <double>::infinity (), 1.0, 68);
   clip1._notes.emplace <NoteMidi> (2.0, 1.0, 78);
   clip1._notes.emplace <NoteMidi> (3.5, 1.0, 53);

   Clip & clip2 = *song._clips.emplace (1, "clip2");
   clip2._notes.emplace <Note> (0.0, 1.0);
   clip2._notes.emplace <Note> (1.0, 1.0);
   clip2._notes.emplace <Note> (2.0, 1.0);
   clip2._notes.emplace <Note> (3.5, 1.0);
   clip2._active = false;

   Track & track1 = *song._tracks.emplace (song._tracks.end ());
   track1._clip_frames.emplace (clip1, 0.0, 4.0);
   track1._clip_frames.emplace (clip1, 4.0, 4.0);
   track1._clip_frames.emplace (clip2, 8.0, 4.0);

   Track & track2 = *song._tracks.emplace (song._tracks.end ());
   ClipFrame & clip_frame1 = *track2._clip_frames.emplace (clip2, 3.5, 3.5);
   clip_frame1._sample_key = std::vector <uint8_t> ({0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef});

   std::vector <uint8_t> chunk;
   for (size_t i = 0 ; i < 500 ; ++i) chunk.push_back (uint8_t (i));
   clip_frame1._chunk = chunk;

   track2._clip_frames.emplace (clip2, 7.0, 4.0);

   DataConsumerMemory consumer (data);

   BackEndIR backend = document.write ();
   backend.write <BackEndMl> (consumer);

#if 0
   std::string str (data.begin (), data.end ());

   printf ("%s\n", str.c_str ());
#endif
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestBackEndMl::run_001 ()
{
   std::vector <uint8_t> data;

   std::string str;

   {
      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      Song & song = document.root <Song> ();

      Clip & clip1 = *song._clips.emplace (1, "clip1");
      clip1._notes.emplace <NoteMidi> (0.0, 1.0, 80);
      clip1._notes.emplace <NoteMidi> (1.0, 1.0, 68);
      clip1._notes.emplace <NoteMidi> (2.0, 1.0, 78);
      clip1._notes.emplace <NoteMidi> (3.5, 1.0, 53);

      Clip & clip2 = *song._clips.emplace (1, "clip2");
      clip2._notes.emplace <Note> (1.0, 1.0);
      clip2._notes.emplace <Note> (- 1.0, 1.0);
      clip2._notes.emplace <Note> (2.0, 1.0);
      clip2._notes.emplace <Note> (3.5, 1.0);
      clip2._active = false;

      Track & track1 = *song._tracks.emplace (song._tracks.end ());
      track1._clip_frames.emplace (clip1, 0.0, 4.0);
      track1._clip_frames.emplace (clip1, 4.0, 4.0);
      track1._clip_frames.emplace (clip2, 8.0, 4.0);

      Track & track2 = *song._tracks.emplace (song._tracks.end ());
      ClipFrame & clip_frame1 = *track2._clip_frames.emplace (clip2, 3.5, 3.5);
      clip_frame1._sample_key = std::vector <uint8_t> ({0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef});

      std::vector <uint8_t> chunk;
      for (size_t i = 0 ; i < 500 ; ++i) chunk.push_back (uint8_t (i));
      clip_frame1._chunk = chunk;

      track2._clip_frames.emplace (clip2, 7.0, 4.0);

      DataConsumerMemory consumer (data);

      BackEndIR backend = document.write ();
      backend.write <BackEndMl> (consumer);

      str = std::string (data.begin (), data.end ());

#if 0
      printf ("%s\n", str.c_str ());
#endif
   }

   {
      DataProviderMemory provider (data);

      BackEndIR backend;
      backend.register_backend <BackEndMl> ();

      bool ok_flag = backend.read (provider);
      flip_TEST (ok_flag);

      Document document (Model::use (), 123456789UL, 'appl', 'gui ');

      document.read (backend);
      document.commit ();

      Song & song = document.root <Song> ();

      flip_TEST (song._clips.count_if ([](Clip &){return true;}) == 2);
      flip_TEST (song._tracks.count_if ([](Track &){return true;}) == 2);

      {
         data.clear ();

         DataConsumerMemory consumer (data);

         BackEndIR backend2 = document.write ();
         backend2.write <BackEndMl> (consumer);

         std::string str2 = std::string (data.begin (), data.end ());

#if 0
         printf ("%s\n", str2.c_str ());
#endif

         assert_compare (str, str2);
      }
   }
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestBackEndMl::run_002 ()
{
   std::vector <uint8_t> data;
   data.push_back ('!');
   data.push_back ('x');
   data.push_back ('l');
   data.push_back ('i');
   data.push_back ('p');
   data.push_back ('.');
   data.push_back ('M');
   data.push_back ('l');   // instead of L

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestBackEndMl::run_003 ()
{
   std::vector <uint8_t> data;
   data.push_back ('!');
   data.push_back ('x');
   data.push_back ('l');
   data.push_back ('i');
   data.push_back ('p');
   data.push_back ('.');
   data.push_back ('M');
   data.push_back ('L');

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestBackEndMl::run_004 ()
{
   std::vector <uint8_t> data;
   data.push_back ('!');
   data.push_back ('x');
   data.push_back ('l');
   data.push_back ('i');
   data.push_back ('p');
   data.push_back ('.');
   data.push_back ('M');
   data.push_back ('L');
   data.push_back ('\0');

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestBackEndMl::run_005 ()
{
   std::string str;

   str += "!flip.ML appl.rev.1\n";
   str += "appl.Song 0|fliproot|1 {\n";
   str += "flip.Bool active = false\n";
   str += "}\n";
   str += "!EOF";

   std::vector <uint8_t> data (str.begin (), str.end ());

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestBackEndMl::run_006 ()
{
   std::string str;

   str += "!flip.ML appl.rev.1\n";
   str += "appl.Song 0|fliproot|1 {\n";
   str += "flip.Bool active = test\n";
   str += "}\n";
   str += "!EOF";

   std::vector <uint8_t> data (str.begin (), str.end ());

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestBackEndMl::run_007 ()
{
   std::string str;

   str += "!flip.ML appl.rev.1\n";
   str += "appl.Song 0|fliproot|1 {\n";
   str += "flip.Blob chunk = Hexadecimal ()\n";
   str += "}\n";
   str += "!EOF";

   std::vector <uint8_t> data (str.begin (), str.end ());

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (ok_flag);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestBackEndMl::run_008 ()
{
   std::string str;

   str += "!flip.ML appl.rev.1\n";
   str += "appl.Song 0|fliproot|1 {\n";
   str += "flip.Blob chunk = Test ()\n";
   str += "}\n";
   str += "!EOF";

   std::vector <uint8_t> data (str.begin (), str.end ());

   DataProviderMemory provider (data);

   BackEndIR backend;
   backend.register_backend <BackEndMl> ();

   bool ok_flag = backend.read (provider);
   flip_TEST (!ok_flag);
}



/*
==============================================================================
Name : assert_compare
==============================================================================
*/

void  TestBackEndMl::assert_compare (const std::string & lhs, const std::string & rhs)
{
   if (lhs == rhs) return; // ok

   // COV_NF_START
   size_t i = 0;

   for (; (i < lhs.size ()) && (i < rhs.size ()) ; ++i)
   {
      if (lhs [i] != rhs [i]) break;
   }

   size_t left = i;
   if (left < 10) left = 10;
   left -= 10;

   size_t right = i + 10;
   if (right > rhs.size ()) right = rhs.size ();
   if (right > lhs.size ()) right = lhs.size ();

   std::string sub = lhs.substr (left, right - left);

   printf ("%s\n", sub.c_str ());
   flip_TEST_FAILED;
   // COV_NF_END
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

