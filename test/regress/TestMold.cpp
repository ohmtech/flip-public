/*****************************************************************************

      TestMold.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestMold.h"

#include "flip/Class.h"
#include "flip/Document.h"
#include "flip/Mold.h"
#include "TestDef.h"

#include <iostream>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestMold::run ()
{
   Model::version ("test.mold");

   Model::declare <Note> ()
      .name ("Note")
      .member <Float, &Note::position> ("position")
      .member <Float, &Note::duration> ("duration");

   Model::declare <Clip::Content> ()
      .name ("Clip.Content")
      .enumerator <Clip::Content::Audio> ("Audio")
      .enumerator <Clip::Content::Midi> ("Midi");

   Model::declare <Clip> ()
      .name ("Clip")
      .member <Int, &Clip::color> ("color")
      .member <Bool, &Clip::active> ("active")
      .member <String, &Clip::name> ("name")
      .member <Blob, &Clip::chunk> ("chunk")
      .member <Notes, &Clip::notes> ("notes")
      .member <Message <>, &Clip::transport> ("transport")
      .member <Enum <Clip::Content>, &Clip::content> ("content");

   Model::declare <ClipFrame> ()
      .name ("ClipFrame")
      .member <ObjectRef <Clip>, &ClipFrame::clip_ref> ("clip_ref")
      .member <Float, &ClipFrame::position> ("position")
      .member <Float, &ClipFrame::duration> ("duration")
      .member <Blob, &ClipFrame::data> ("data");

   Model::declare <Event> ()
      .name ("Event")
      .member <Float, &Event::position> ("position")
      .member <Int, &Event::value> ("value");

   Model::declare <Song> ()
      .name ("Song")
      .member <Clips, &Song::clips> ("clips")
      .member <ClipFrames, &Song::clip_frames> ("clip_frames");

   Model2::version ("test.mold2");

   run_000 ();
   run_000b ();
   run_000c ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestMold::run_000 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif
   clip.content = Clip::Content::Midi;

   Mold mold (Model::use ());
   mold.make (clip);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
   flip_TEST (clip2.content == Clip::Content::Midi);
}



/*
==============================================================================
Name : run_000b
==============================================================================
*/

void  TestMold::run_000b ()
{
   Clip clip;
   clip.color = 1LL;
   Note & note = *clip.notes.emplace ();
   note.position = 2.5;
   note.duration = 3.5;

   Mold mold (Model::use ());
   mold.make (clip);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.notes.begin ()->position == 2.5);
   flip_TEST (clip2.notes.begin ()->duration == 3.5);
}



/*
==============================================================================
Name : run_000c
==============================================================================
*/

void  TestMold::run_000c ()
{
   Event event (1.0, 2LL);

   Mold mold (Model::use ());
   mold.make (event);

   flip_TEST (mold.has <Event> ());

   Event event2 = mold.cast <Event> ();
   flip_TEST (!mold.has <ClipFrame> ());

   flip_TEST (event2.position == 1.0);
   flip_TEST (event2.value == 2LL);
}



/*
==============================================================================
Name : run_000d_concept
Note :
   Does not compile on purpose
==============================================================================
*/

void  TestMold::run_000d_concept ()
{
   /*Abstract * abstract_ptr = nullptr;

   Mold mold (Model::use ());
   mold.make (*abstract_ptr);
   Abstract abstract2 = mold.cast <Abstract> ();*/
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestMold::run_001 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song.clips.emplace (3);
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif
   clip.content = Clip::Content::Midi;

   Mold mold (Model::use ());
   mold.make (clip);

   clip.color = 0LL;
   clip.active = false;
   clip.name = "";
   clip.chunk = std::vector <uint8_t> ();
   clip.content = Clip::Content::Audio;

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 3LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
   flip_TEST (clip2.content == Clip::Content::Midi);

   flip_TEST (mold.has <Clip> ());

   clip = mold.cast <Clip> ();
   flip_TEST (clip.color == 3LL);
   flip_TEST (clip.active == true);
   flip_TEST (clip.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip.chunk == std::vector <uint8_t> ({0x23}));
#endif
   flip_TEST (clip.content == Clip::Content::Midi);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestMold::run_002 ()
{
   Document document (Model::use (), 123456789ULL, 'flip', 'mold');

   Song & song = document.root <Song> ();

   Clip & clip = *song.clips.emplace (3);
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   ClipFrame & clip_frame = *song.clip_frames.emplace (
      clip, 0.5, 2.5, std::vector <uint8_t> ({0x00, 0xf0, 0xea})
   );
#endif

   Mold mold (Model::use ());
   mold.make (clip);
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   mold.make (clip_frame);
#endif

   clip.color = 0LL;

   flip_TEST (mold.has <Clip> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 3LL);

   flip_TEST (mold.has <Clip> ());

   clip = mold.cast <Clip> ();
   flip_TEST (clip.color == 3LL);

#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (mold.has <ClipFrame> ());

   ClipFrame clip_frame2 = mold.cast <ClipFrame> ();
   flip_TEST (clip_frame2.clip_ref == &clip);
   flip_TEST (clip_frame2.position == 0.5);
   flip_TEST (clip_frame2.duration == 2.5);
   flip_TEST (clip_frame2.data == std::vector <uint8_t> ({0x00, 0xf0, 0xea}));

   ClipFrame & clip_frame3 = *song.clip_frames.emplace (mold);
   flip_TEST (clip_frame3.clip_ref == &clip);
   flip_TEST (clip_frame3.position == 0.5);
   flip_TEST (clip_frame3.duration == 2.5);
   flip_TEST (clip_frame3.data == std::vector <uint8_t> ({0x00, 0xf0, 0xea}));
#endif
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestMold::run_003 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif

   auto mold = Mold {Model::use ()};
   mold.make (clip);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestMold::run_004 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif

   auto other_mold = Mold {Model::use ()};
   other_mold.make (clip);

   Mold mold (Model::use ());
   mold = std::move (other_mold);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestMold::run_005 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif

   auto other_mold = Mold {Model::use ()};

   Mold mold (std::move (other_mold));
   mold.make (clip);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestMold::run_006 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   clip.chunk = std::vector <uint8_t> ({0x23});
#endif

   const Clip & const_clip = clip;

   auto mold = Mold {Model::use ()};
   mold.make (const_clip);

   flip_TEST (mold.has <Clip> ());
   flip_TEST (!mold.has <ClipFrame> ());

   Clip clip2 = mold.cast <Clip> ();
   flip_TEST (clip2.color == 1LL);
   flip_TEST (clip2.active == true);
   flip_TEST (clip2.name == "test");
#if (flip_COMPILER != flip_COMPILER_MSVC) // initializer list support
   flip_TEST (clip2.chunk == std::vector <uint8_t> ({0x23}));
#endif
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestMold::run_007 ()
{
   Clip clip;
   clip.color = 1LL;
   clip.active = true;
   clip.name = "test";

   std::vector <uint8_t> data;

   {
      StreamBinOut sbo (data);
      Mold mold (Model::use (), sbo);
      mold.make (clip);
      mold.cure ();
   }

   {
      StreamBinIn sbi (data);
      Mold mold (Model::use (), sbi);
   }

   {
      StreamBinIn sbi (data);
      flip_CHECK_THROW (Mold mold (Model2::use (), sbi));
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

