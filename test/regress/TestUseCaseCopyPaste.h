/*****************************************************************************

      TestUseCaseCopyPaste.h
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



namespace flip
{



class TestUseCaseCopyPaste
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

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (int color) : _color (color) {}

      Int         _color;
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

                  TestUseCaseCopyPaste () = default;
   virtual        ~TestUseCaseCopyPaste () = default;

   void           run ();

   std::vector <uint8_t>
                  copy (std::vector <uint8_t> & data, ClipFrame & clip_frame);
   void           paste (Song & song, const std::vector <uint8_t> & data, double position_offset, bool deep_copy_flag);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_001 ();
   void           run_002 ();
   void           run_003 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestUseCaseCopyPaste (const TestUseCaseCopyPaste & rhs) = delete;
   TestUseCaseCopyPaste &  operator = (const TestUseCaseCopyPaste & rhs) = delete;
                  TestUseCaseCopyPaste (TestUseCaseCopyPaste && rhs) = delete;
   TestUseCaseCopyPaste &  operator = (TestUseCaseCopyPaste && rhs) = delete;
   bool           operator == (const TestUseCaseCopyPaste & rhs) const = delete;
   bool           operator != (const TestUseCaseCopyPaste & rhs) const = delete;



}; // class TestUseCaseCopyPaste



}  // namespace flip



//#include  "flip/TestUseCaseCopyPaste.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

