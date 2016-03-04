/*****************************************************************************

      TestDataModelClone.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Float.h"
#include "flip/Enum.h"
#include "flip/Int.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestDataModelClone
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};
   class ModelClip : public DataModel <ModelClip> {};
   class ModelClipAudio : public DataModel <ModelClipAudio> {};
   class ModelTrack : public DataModel <ModelTrack> {};
   class ModelSong : public DataModel <ModelSong> {};

   class Clip
   :  public Object
   {
   public:
      enum class Content
      {
                  Audio, Midi,
      };

      Float       position;
      Float       duration;
      Int         color_id;
      Enum <Content>
                  content;
   };

   class ClipAudio
   :  public Clip
   {
   public:
      String      sample_path;
   };

   class Track
   :  public Object
   {
   public:
      Collection <Clip>
                  clip_coll;
   };

   class Song
   :  public Object
   {
   public:
      Array <Track>
                  track_arr;
   };

   class ModelFixture : public DataModel <ModelFixture> {};

   class TestFixture
   :  public Object
   {
   public:
      Song        song;
   };

                  TestDataModelClone () = default;
   virtual        ~TestDataModelClone () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestDataModelClone (const TestDataModelClone & rhs) = delete;
   TestDataModelClone &
                  operator = (const TestDataModelClone & rhs) = delete;
                  TestDataModelClone (TestDataModelClone && rhs) = delete;
   TestDataModelClone &
                  operator = (TestDataModelClone && rhs) = delete;
   bool           operator == (const TestDataModelClone & rhs) const = delete;
   bool           operator != (const TestDataModelClone & rhs) const = delete;



}; // class TestDataModelClone



}  // namespace flip



//#include  "flip/TestDataModelClone.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

