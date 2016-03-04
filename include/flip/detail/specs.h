/*****************************************************************************

      specs.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace flip
{



class ArrayBase;
class CollectionBase;
class Object;
class Type;

void              specs_check_recursive (Type & obj);
void              specs_check_recursive (ArrayBase & obj);
void              specs_check_recursive (CollectionBase & obj);
void              specs_check_recursive (Object & obj);

void              specs_check_object_state (ArrayBase & obj);
void              specs_check_object_state (CollectionBase & obj);

void              specs_check_object_state_added_recursive (Type & obj);
void              specs_check_object_state_added_recursive (Object & obj);
void              specs_check_object_state_added_recursive (ArrayBase & obj);
void              specs_check_object_state_added_recursive (CollectionBase & obj);
void              specs_check_object_state_removed_recursive (Type & obj);
void              specs_check_object_state_removed_recursive (Object & obj);
void              specs_check_object_state_removed_recursive (ArrayBase & obj);
void              specs_check_object_state_removed_recursive (CollectionBase & obj);



}  // namespace flip



//#include  "flip/specs.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

