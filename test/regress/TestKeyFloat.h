/*****************************************************************************

      TestKeyFloat.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/KeyFloat.h"



namespace flip
{



class TestKeyFloat
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestKeyFloat () = default;
   virtual        ~TestKeyFloat () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_pre_01 ();
   uint8_t        mask_pre (uint8_t l, uint8_t r);
   void           run_pre_02 ();
   KeyFloat       test_pre (std::vector <uint8_t> data, size_t nbr_bits);

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_002 (const KeyFloat & left, const KeyFloat & right, size_t depth);
   void           run_003 ();
   void           run_004 ();

   KeyFloat       generate (std::vector <uint8_t> data);
   KeyFloat       test (const KeyFloat & left, const KeyFloat & right);
   void           test (const KeyFloat & left, const KeyFloat & right, int nbr);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestKeyFloat (const TestKeyFloat & rhs) = delete;
   TestKeyFloat & operator = (const TestKeyFloat & rhs) = delete;
                  TestKeyFloat (TestKeyFloat && rhs) = delete;
   TestKeyFloat & operator = (TestKeyFloat && rhs) = delete;
   bool           operator == (const TestKeyFloat & rhs) const = delete;
   bool           operator != (const TestKeyFloat & rhs) const = delete;



}; // class TestKeyFloat



}  // namespace flip



//#include  "flip/TestKeyFloat.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

