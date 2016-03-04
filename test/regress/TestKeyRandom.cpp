/*****************************************************************************

      TestKeyRandom.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestKeyRandom.h"

#include "flip/detail/KeyRandom.h"
#include "TestDef.h"

#include <utility>
#include <set>

#include <climits>
#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestKeyRandom::run ()
{
   KeyRandom a;
   flip_TEST (a.get ().size () == KeyRandom::SIZE);

   KeyRandom b = a;
   flip_TEST (b == a);
   flip_TEST (! (b != a));

   KeyRandom c;
   b = c;
   flip_TEST (b == c);
   flip_TEST (! (b != c));

   KeyRandom d = std::move (b);
   flip_TEST (d == c);  // not b
   flip_TEST (! (d != c)); // not b

   std::set <KeyRandom> key_set;

   for (size_t i = 0 ; i < 1000 ; ++i)
   {
      key_set.insert (KeyRandom ());
   }

   flip_TEST (key_set.size () == 1000);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

