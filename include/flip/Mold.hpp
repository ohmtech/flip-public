/*****************************************************************************

      Mold.hpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (flip_Mold_CURRENT_CODEHEADER)
   #error Recursive inclusion of Mold code header.
#endif
#define  flip_Mold_CURRENT_CODEHEADER

#if ! defined (flip_Mold_CODEHEADER_INCLUDED)
#define  flip_Mold_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Class.h"
#include "flip/detail/def.h"
#include "flip/detail/StreamBinIn.h"
#include "flip/detail/StreamBinOut.h"



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : make
Description :
   Make mold from 'type'. If 'type' type id is already present in the mold,
   then the old one is overwritten.

   This version is used when the mold is make from an object out of a
   document.
==============================================================================
*/

template <class T>
void  Mold::make (T & obj, bool skip_container_flag)
{
   const ClassBase & class_base = Class <T>::use ();

   // bind class for members introspection
   obj.impl_set_class (class_base);

   auto type_id = class_base.type_id (_model);

   auto & data = _map [type_id];
   data.clear ();

   StreamBinOut sbo (data);

   make (obj, sbo, skip_container_flag);
}



/*
==============================================================================
Name : make
Description :
   Make mold from 'type'. If 'type' type id is already present in the mold,
   then the old one is overwritten.

   This version can only be used for an object of a document.
==============================================================================
*/

template <class T>
void  Mold::make (const T & obj, bool skip_container_flag)
{
   // to use this version of 'make', 'obj' must have its flip class bound
   // to allow for automatic flip introspection
   auto type_id = obj.get_class ().type_id (_model);

   auto & data = _map [type_id];
   data.clear ();

   StreamBinOut sbo (data);

   make (obj, sbo, skip_container_flag);
}



/*
==============================================================================
Name : cast
Description :
   flip default ctor version.
==============================================================================
*/

template <class T>
typename std::enable_if <
   std::is_constructible <T, Default &>::value, T
>::type  Mold::cast () const
{
   Default default_;
   T obj (default_);

   cast <T> (obj);

   return obj;
}



/*
==============================================================================
Name : cast
Description :
   c++ default ctor version.
==============================================================================
*/

template <class T>
typename std::enable_if <
   !std::is_constructible <T, Default &>::value, T
>::type  Mold::cast () const
{
   T obj;

   cast <T> (obj);

   return obj;
}



/*
==============================================================================
Name : cast
==============================================================================
*/

template <class T>
void  Mold::cast (T & obj) const
{
   const ClassBase & class_base = Class <T>::use ();

   auto type_id = class_base.type_id (_model);

   auto it = _map.find (type_id);
   if (it == _map.end ()) flip_FATAL;

   obj.impl_set_class (class_base);

   const auto & data = it->second;

   StreamBinIn sbi (data);

   cast (obj, sbi);

   if (!sbi.is_eos ()) flip_FATAL;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace flip



#endif   // flip_Mold_CODEHEADER_INCLUDED

#undef flip_Mold_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

