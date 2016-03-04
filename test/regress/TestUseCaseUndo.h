/*****************************************************************************

      TestUseCaseUndo.h
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



class TestUseCaseUndo
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (double position, double duration) : _position (position), _duration (duration) {}

      Float       _position;
      Float       _duration;
   };

   typedef Collection <Clip> Clips;

   class Track
   :  public Object
   {
   public:

      Clips       _clips;
   };

   typedef Collection <Track> Tracks;

   class SelectionElem
   :  public Object
   {
   public:
                  SelectionElem () = default;   // COV_NF_LINE
                  SelectionElem (Object & object) : _object_ref (&object) {}

      template <class T>
      T &         use () {return dynamic_cast <T &> (*_object_ref);}

      ObjectRef <Object>
                  _object_ref;
   };

   typedef Collection <SelectionElem> Selection;

   class Song
   :  public Object
   {
   public:
      Selection   _selection;
      Tracks      _tracks;
   };

   Transaction    move (Song & song, Clip & clip, double position);
   void           undo (Song & song, Transaction tx, const std::set <Ref> & ref_set);
   void           redo (Song & song, Transaction tx, const std::set <Ref> & ref_set);
   void           select (Song & song, const std::set <Ref> & ref_set);

                  TestUseCaseUndo () = default;
   virtual        ~TestUseCaseUndo () = default;

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
   void           run_006 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestUseCaseUndo (const TestUseCaseUndo & rhs) = delete;
   TestUseCaseUndo & operator = (const TestUseCaseUndo & rhs) = delete;
                  TestUseCaseUndo (TestUseCaseUndo && rhs) = delete;
   TestUseCaseUndo & operator = (TestUseCaseUndo && rhs) = delete;
   bool           operator == (const TestUseCaseUndo & rhs) const = delete;
   bool           operator != (const TestUseCaseUndo & rhs) const = delete;



}; // class TestUseCaseUndo



}  // namespace flip



//#include  "flip/TestUseCaseUndo.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

