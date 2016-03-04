/*****************************************************************************

      TestVector.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/Vector.h"

#include <cstdint>



namespace flip
{



class StreamBinIn;
class StreamBinOut;

class TestVector
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   struct Elem
   {
      double      a;
      double      b;

      bool        operator == (const Elem & rhs) const;

      void        write (StreamBinOut & sbo) const;
      void        read (StreamBinIn & sbi);
   };

   class Elem2
   {
   public:
                  Elem2 () = default;
                  Elem2 (const Elem2 & rhs) = default;
                  Elem2 (bool a_, double b_, char c_, float d_);

      Elem2 &     operator = (const Elem2 & rhs) = default;

      bool        operator == (const Elem2 & rhs) const;

      void        write (StreamBinOut & sbo) const;
      void        read (StreamBinIn & sbi);

      bool        a;
      double      b;
      char        c;
      float       d;
   };

   class Root
   :  public Object
   {
   public:
      Vector <double>
                  _vector_double;
      Vector <Elem>
                  _vector_elem;
      Vector <Elem2>
                  _vector_elem2;
   };

                  TestVector () = default;
   virtual        ~TestVector () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_000b ();
   void           run_000c ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();
   void           run_007 ();
   void           run_007b ();
   void           run_008 ();
   void           run_008b ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();
   void           run_015 ();
   void           run_016 ();
   void           run_017 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestVector (const TestVector & rhs) = delete;
   TestVector &   operator = (const TestVector & rhs) = delete;
                  TestVector (TestVector && rhs) = delete;
   TestVector &   operator = (TestVector && rhs) = delete;
   bool           operator == (const TestVector & rhs) const = delete;
   bool           operator != (const TestVector & rhs) const = delete;



}; // class TestVector



}  // namespace flip



//#include  "flip/TestVector.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

