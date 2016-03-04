/*****************************************************************************

      TestUseCaseShared.h
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



class TestUseCaseShared
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (int color) : _color (color) {}

      Int         _color;
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

   class Song
   :  public Object
   {
   public:
      Clips       _clips;
      ClipFrames  _clip_frames;
   };

                  TestUseCaseShared () = default;
   virtual        ~TestUseCaseShared () = default;

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
                  TestUseCaseShared (const TestUseCaseShared & rhs) = delete;
   TestUseCaseShared &  operator = (const TestUseCaseShared & rhs) = delete;
                  TestUseCaseShared (TestUseCaseShared && rhs) = delete;
   TestUseCaseShared &  operator = (TestUseCaseShared && rhs) = delete;
   bool           operator == (const TestUseCaseShared & rhs) const = delete;
   bool           operator != (const TestUseCaseShared & rhs) const = delete;



}; // class TestUseCaseShared



}  // namespace flip



//#include  "flip/TestUseCaseShared.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

