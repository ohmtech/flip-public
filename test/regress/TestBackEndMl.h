/*****************************************************************************

      TestBackEndMl.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Message.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestBackEndMl
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Note
   :  public Object
   {
   public:
                  Note () = default;   // COV_NF_LINE
                  Note (double position, double duration) : _position (position), _duration (duration) {}

      Float       _position;
      Float       _duration;
   };

   class NoteMidi
   :  public Note
   {
   public:
                  NoteMidi () = default;  // COV_NF_LINE
                  NoteMidi (double position, double duration, int velocity) : Note (position, duration), _velocity (velocity) {}

      Int         _velocity;
   };

   typedef Collection <Note> Notes;

   class Color
   :  public Object
   {
   public:
                  Color () = default;  // COV_NF_LINE
                  Color (int color_id) : _id (color_id) {}

      Int         _id;
   };

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (int color_id, const std::string & name) : _color (color_id), _name (name), _active (true) {}

      Color       _color;
      String      _name;
      Bool        _active;
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
      Blob        _sample_key;
      Blob        _chunk;
   };

   typedef Collection <ClipFrame> ClipFrames;

   class Track
   :  public Object
   {
   public:
      ClipFrames  _clip_frames;
   };

   typedef Array <Track> Tracks;

   class Song
   :  public Object
   {
   public:
      Clips       _clips;
      Tracks      _tracks;
      Message <>  _transport;
   };

                  TestBackEndMl () = default;
   virtual        ~TestBackEndMl () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();
   void           run_007 ();
   void           run_008 ();

   void           assert_compare (const std::string & lhs, const std::string & rhs);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestBackEndMl (const TestBackEndMl & rhs) = delete;
   TestBackEndMl &
                  operator = (const TestBackEndMl & rhs) = delete;
                  TestBackEndMl (TestBackEndMl && rhs) = delete;
   TestBackEndMl &
                  operator = (TestBackEndMl && rhs) = delete;
   bool           operator == (const TestBackEndMl & rhs) const = delete;
   bool           operator != (const TestBackEndMl & rhs) const = delete;



}; // class TestBackEndMl



}  // namespace flip



//#include  "flip/TestBackEndMl.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

