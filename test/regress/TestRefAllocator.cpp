/*****************************************************************************

      TestRefAllocator.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestRefAllocator.h"

#include "TestDef.h"

#include "flip/Int.h"
#include "flip/detail/RefAllocator.h"

#include <utility>
#include <vector>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestRefAllocator::run ()
{
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestRefAllocator::run_000 ()
{
   RefAllocator allocator (123456789, 987654321);

   Ref ref = allocator.allocate (1);

   flip_TEST (ref == Ref::make (123456789, 987654321, 1));
   flip_TEST (allocator.get_next () == Ref::make (123456789, 987654321, 2));

   ref = allocator.allocate (3);

   flip_TEST (ref == Ref::make (123456789, 987654321, 2));
   flip_TEST (allocator.get_next () == Ref::make (123456789, 987654321, 5));

   ref = allocator.allocate (1);

   flip_TEST (ref == Ref::make (123456789, 987654321, 5));
   flip_TEST (allocator.get_next () == Ref::make (123456789, 987654321, 6));
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestRefAllocator::run_001 ()
{
   RefAllocator allocator (123456789, 987654321);

   flip_TEST (allocator.can_allocate (Ref::make (123456789, 987654321, 1), 1));

   Int type;
   allocator.bind (type, Ref::make (123456789, 987654321, 1));

   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 1), 1));
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestRefAllocator::run_002 ()
{
   RefAllocator allocator (123456789, 987654321);

   flip_TEST (allocator.can_allocate (Ref::make (123456789, 987654321, 1), 2));

   Int type;
   allocator.bind (type, Ref::make (123456789, 987654321, 1));
   allocator.bind (type, Ref::make (123456789, 987654321, 2));

   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 1), 1));
   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 1), 2));
   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 2), 1));
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestRefAllocator::run_003 ()
{
   RefAllocator allocator (123456789, 987654321);

   flip_TEST (allocator.can_allocate (Ref::make (123456789, 987654321, 1), 3));

   Int type;
   allocator.bind (type, Ref::make (123456789, 987654321, 2));
   allocator.bind (type, Ref::make (123456789, 987654321, 3));

   flip_TEST (allocator.can_allocate (Ref::make (123456789, 987654321, 1), 1));
   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 1), 2));
   flip_TEST (!allocator.can_allocate (Ref::make (123456789, 987654321, 1), 3));
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

