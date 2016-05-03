/*****************************************************************************

      TestUseCaseSignal.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/ObjectRef.h"
#include "flip/Signal.h"



namespace flip
{



class TestUseCaseSignal
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Note
   :  public Object
   {
   public:
      enum
      {
                  PLAY,
      };

                  Note () : Note (0.0, 0.0) {}  // COV_NF_LINE
                  Note (double position, double duration) : signal_play (PLAY, *this), _position (position), _duration (duration) {}
                  Note (const Note & rhs) : Note (rhs._position, rhs._duration) {}  // COV_NF_LINE

      Signal <double /* velocity */>
                  signal_play;

      Float       _position;
      Float       _duration;
   };

   class NoteView // COV_NF_LINE
   {
   public:
                  NoteView (Note & note);
      virtual     ~NoteView ();

      void        play (double velocity);

      SignalConnection
                  _cnx;
      bool        _fired_flag = false;

   private:
                  NoteView () = delete;
                  NoteView (const NoteView & rhs) = delete;
   };

   class NoteView2   // COV_NF_LINE
   {
   public:
                  NoteView2 (Note & note);
      virtual     ~NoteView2 ();

      void        play (double velocity);

      SignalConnection
                  _cnx;
      bool        _fired_flag = false;

   private:
                  NoteView2 () = delete;
                  NoteView2 (const NoteView2 & rhs) = delete;
   };

   typedef Collection <Note> Notes;

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE

      Notes       _notes;
   };

   typedef Collection <Clip> Clips;

   class ClipFrame
   :  public Object
   {
   public:
                  ClipFrame () = default; // COV_NF_LINE
                  ClipFrame (Clip & clip, double position, double duration) : _clip_ref (&clip), _position (position), _duration (duration) {}

      Clip &      use () {return *_clip_ref;}

      ObjectRef <Clip>
                  _clip_ref;
      Float       _position;
      Float       _duration;
   };

   typedef Collection <ClipFrame> ClipFrames;

   class Track
   :  public Object
   {
   public:

      enum
      {
                  OPEN_GUI,
      };
                  Track () : signal_open_gui (OPEN_GUI, *this) {}
                  Track (const Track & other) : Object (other), signal_open_gui (OPEN_GUI, *this), _clip_frames (other._clip_frames) {}   // COV_NF_LINE

      Signal <>   signal_open_gui;

      ClipFrames  _clip_frames;
   };

   typedef Collection <Track> Tracks;

   class Song
   :  public Object
   {
   public:
      Clips       _clips;
      Tracks      _tracks;
   };

                  TestUseCaseSignal () = default;
   virtual        ~TestUseCaseSignal () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_001 ();
   void           run_002 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestUseCaseSignal (const TestUseCaseSignal & rhs) = delete;
   TestUseCaseSignal &
                  operator = (const TestUseCaseSignal & rhs) = delete;
                  TestUseCaseSignal (TestUseCaseSignal && rhs) = delete;
   TestUseCaseSignal &
                  operator = (TestUseCaseSignal && rhs) = delete;
   bool           operator == (const TestUseCaseSignal & rhs) const = delete;
   bool           operator != (const TestUseCaseSignal & rhs) const = delete;



}; // class TestUseCaseSignal



}  // namespace flip



//#include  "flip/TestUseCaseSignal.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

