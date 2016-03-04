/*****************************************************************************

      TestMold.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Float.h"
#include "flip/Enum.h"
#include "flip/Int.h"
#include "flip/Message.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class Mold;

class TestMold
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model
   :  public DataModel <Model>
   {
   };

   class Note
   :  public Object
   {
   public:
      Float       position;
      Float       duration;
   };

   using Notes = Collection <Note>;

   class Clip
   :  public Object
   {
   public:
      enum class Content
      {
                  Audio, Midi,
      };

                  Clip () = default;   // COV_NF_LINE
                  Clip (int color_) : color (color_) {}

      Int         color;
      Bool        active;
      String      name;
      Blob        chunk;
      Notes       notes;
      Message <>  transport;
      Enum <Content>
                  content;
   };

   typedef Collection <Clip> Clips;

   class ClipFrame
   :  public Object
   {
   public:
                  ClipFrame () = default; // COV_NF_LINE
                  ClipFrame (Clip & clip, double position_, double duration_, const std::vector <uint8_t> & data_) : clip_ref (&clip), position (position_), duration (duration_), data (data_) {}

      Clip &      use () {return *clip_ref;}

      ObjectRef <Clip>
                  clip_ref;
      Float       position;
      Float       duration;
      Blob        data;
   };

   using ClipFrames = Collection <ClipFrame>;

   class Event
   :  public Object
   {
   public:
                  Event () = delete;
                  Event (double position_, int64_t value_) : position (position_), value (value_) {}
                  Event (Default &) {}

      Float       position;
      Int         value;
   };

   class Abstract
   :  public Object
   {
   public:
      virtual void
                  foo () = 0;
   };

   class Song
   :  public Object
   {
   public:
      Clips       clips;
      ClipFrames  clip_frames;
   };

                  TestMold () = default;
   virtual        ~TestMold () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_000b ();
   void           run_000c ();
   void           run_000d_concept ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestMold (const TestMold & rhs) = delete;
   TestMold &
                  operator = (const TestMold & rhs) = delete;
                  TestMold (TestMold && rhs) = delete;
   TestMold &
                  operator = (TestMold && rhs) = delete;
   bool           operator == (const TestMold & rhs) const = delete;
   bool           operator != (const TestMold & rhs) const = delete;



}; // class TestMold



}  // namespace flip



//#include  "flip/TestMold.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

