/*****************************************************************************

      fnc.hpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (flip_fnc_CURRENT_CODEHEADER)
   #error Recursive inclusion of fnc code header.
#endif
#define  flip_fnc_CURRENT_CODEHEADER

#if ! defined (flip_fnc_CODEHEADER_INCLUDED)
#define  flip_fnc_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/Type.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : modify
Description :
   Set and notify modification :
   - if the new value is different from before, we have one more modification
   - if the new value is the same as before, we have one modification less
==============================================================================
*/

template <class T>
void  modify (Type & obj, T & before, T & current, T value)
{
   assert (current != value);

   if (before == current)
   {
      obj.impl_incr_modification_cnt (1);
   }
   else if (before == value)
   {
      obj.impl_incr_modification_cnt (-1);
   }

   current = value;
}



/*
==============================================================================
Name : modify_move
Description :
   Set and notify modification :
   - if the new value is different from before, we have one more modification
   - if the new value is the same as before, we have one modification less
==============================================================================
*/

template <class T>
void  modify_move (Type & obj, T & before, T & current, T && value)
{
   assert (current != value);

   if (before == current)
   {
      obj.impl_incr_modification_cnt (1);
   }
   else if (before == value)
   {
      obj.impl_incr_modification_cnt (-1);
   }

   current = std::move (value);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



#endif   // flip_fnc_CODEHEADER_INCLUDED

#undef flip_fnc_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

