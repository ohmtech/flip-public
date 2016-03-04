/*****************************************************************************

      RandomDevice.hpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (flip_RandomDevice_CURRENT_CODEHEADER)
   #error Recursive inclusion of RandomDevice code header.
#endif
#define  flip_RandomDevice_CURRENT_CODEHEADER

#if ! defined (flip_RandomDevice_CODEHEADER_INCLUDED)
#define  flip_RandomDevice_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"

#include <cstring>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : get
==============================================================================
*/

template <std::size_t SIZE>
void  RandomDevice::get (std::array <uint8_t, SIZE> & array)
{
   static_assert ((SIZE / 4) * 4 == SIZE, "");

   for (size_t i = 0 ; i < SIZE / 4 ; ++i)
   {
      uint32_t r = _engine ();

      std::memcpy (&array [i * 4], &r, 4);
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



#endif   // flip_RandomDevice_CODEHEADER_INCLUDED

#undef flip_RandomDevice_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

