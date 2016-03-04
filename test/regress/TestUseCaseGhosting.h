/*****************************************************************************

      TestUseCaseGhosting.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/ObjectRef.h"



namespace flip
{



class TestUseCaseGhosting
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   typedef std::pair <double, double> Range;

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (double position, double duration) : _position (position), _duration (duration) {}

      Range       get_range () const {return Range (_position, _position + _duration);}

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

      Transaction _last_tx;
   };

   bool           move (Song & song, Clip & clip, double position);
   void           move_end (Song & song);

   void           cut (Song & song, Clip & clip_sel);
   bool           cut (Song & song, Clip & clip_sel, Clip & clip);

   Range          get_move_range (Song & song);
   double         limit (Range range, double val);
   Range          intersect (Range lhs, const Range & rhs);

                  TestUseCaseGhosting () = default;
   virtual        ~TestUseCaseGhosting () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_move ();
   void           run_move2 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestUseCaseGhosting (const TestUseCaseGhosting & rhs) = delete;
   TestUseCaseGhosting &
                  operator = (const TestUseCaseGhosting & rhs) = delete;
                  TestUseCaseGhosting (TestUseCaseGhosting && rhs) = delete;
   TestUseCaseGhosting &
                  operator = (TestUseCaseGhosting && rhs) = delete;
   bool           operator == (const TestUseCaseGhosting & rhs) const = delete;
   bool           operator != (const TestUseCaseGhosting & rhs) const = delete;



}; // class TestUseCaseGhosting



}  // namespace flip



//#include  "flip/TestUseCaseGhosting.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

