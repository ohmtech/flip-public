/*****************************************************************************

      TestEntity.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestEntity.h"

#include "flip/config.h"
#include "flip/Entity.h"
#include "TestDef.h"

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

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

void  TestEntity::run ()
{
#if 0
   std::cout << "entity size: " << sizeof (Entity) << std::endl;
#endif

#if (flip_ENTITY_USE != flip_ENTITY_USE_PEDANTIC)
   run_000 ();
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
#endif
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

int   TestEntity::_class_a_cnt = 0;
int   TestEntity::_class_b_cnt = 0;

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestEntity::run_000 ()
{
   flip_TEST (_class_a_cnt == 0);

   {
      Entity::Bundle bundle (new A, Entity::delete_func <A>, Entity::copy_ctor_func <A>);
   }

   flip_TEST (_class_a_cnt == 0);

   {
      Entity::Bundle bundle (new A, Entity::delete_func <A>, Entity::copy_ctor_func <A>);
      Entity::Bundle bundle2 (bundle);
   }

   flip_TEST (_class_a_cnt == 0);

   {
      Entity::Bundle bundle (new A, Entity::delete_func <A>, Entity::copy_ctor_func <A>);
      Entity::Bundle bundle2 (new A, Entity::delete_func <A>, Entity::copy_ctor_func <A>);
      bundle2 = bundle;
   }

   flip_TEST (_class_a_cnt == 0);

   {
      Entity::Bundle bundle (new A, Entity::delete_func <A>, Entity::copy_ctor_func <A>);
      Entity::Bundle bundle2 (std::move (bundle));
   }

   flip_TEST (_class_a_cnt == 0);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestEntity::run_001 ()
{
   flip_TEST (_class_a_cnt == 0);

   Entity entity;
   A & a = entity.emplace <A> ();

   flip_TEST (_class_a_cnt == 1);

   flip_CHECK_THROW (entity.emplace <A> ());
   flip_CHECK_THROW (entity.use <B> ()._val = 10);
   flip_CHECK_THROW (entity.erase <B> ());

   A & a2 = entity.use <A> ();
   flip_TEST (&a == &a2);
   flip_TEST (_class_a_cnt == 1);

   A * a3_ptr = entity.get <A> ();
   flip_TEST (&a == a3_ptr);
   flip_TEST (_class_a_cnt == 1);

   entity.erase <A> ();

   flip_TEST (_class_a_cnt == 0);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestEntity::run_002 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   B & b = entity.emplace <B> (1);
   flip_TEST (b._val == 1);

   flip_TEST (_class_b_cnt == 1);

   B & b2 = entity.use <B> ();
   flip_TEST (&b == &b2);
   flip_TEST (_class_b_cnt == 1);

   B * b3_ptr = entity.get <B> ();
   flip_TEST (&b == b3_ptr);
   flip_TEST (_class_b_cnt == 1);

   entity.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestEntity::run_003 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   B & b = entity.emplace <B> (1);
   flip_TEST (b._val == 1);

   flip_TEST (_class_b_cnt == 1);

   Entity entity2 = entity;

   flip_TEST (_class_b_cnt == 2);

   entity.erase <B> ();

   flip_TEST (_class_b_cnt == 1);

   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestEntity::run_004 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   B & b = entity.emplace <B> (1);
   flip_TEST (b._val == 1);

   flip_TEST (_class_b_cnt == 1);

   Entity entity2 = entity;

   flip_TEST (_class_b_cnt == 2);

   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 1);

   entity.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestEntity::run_005 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   B & b = entity.emplace <B> (1);
   flip_TEST (b._val == 1);

   flip_TEST (_class_b_cnt == 1);

   Entity entity2 = entity;
   flip_TEST (_class_b_cnt == 2);
   flip_TEST (entity2.use <B> ()._val == 1);

   entity2.use <B> ()._val = 2;
   flip_TEST (entity2.use <B> ()._val == 2);
   flip_TEST (entity.use <B> ()._val == 1);

   entity.erase <B> ();

   flip_TEST (_class_b_cnt == 1);
   flip_TEST (entity2.use <B> ()._val == 2);

   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestEntity::run_006 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   B & b = entity.emplace <B> (1);
   flip_TEST (b._val == 1);

   flip_TEST (_class_b_cnt == 1);

   Entity entity2 (std::move (entity));
   flip_TEST (_class_b_cnt == 1);
   flip_TEST (entity2.use <B> ()._val == 1);

   flip_CHECK_THROW (entity.use <B> ()._val = 10);

   entity2.use <B> ()._val = 2;
   flip_TEST (entity2.use <B> ()._val == 2);

   flip_CHECK_THROW (entity.erase <B> ());

   flip_TEST (_class_b_cnt == 1);
   flip_TEST (entity2.use <B> ()._val == 2);

   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestEntity::run_007 ()
{
   Entity entity;
   C & c = entity.emplace <C> ();
   flip_TEST (c._list.empty ());
   c._list.push_back (10);

   Entity entity2 = entity;
   flip_TEST (entity2.use <C> ()._list.size () == 1);
   flip_TEST (entity2.use <C> ()._list.front () == 10);

   entity2.use <C> ()._list.front () = 2;
   flip_TEST (entity2.use <C> ()._list.front () == 2);
   flip_TEST (entity.use <C> ()._list.front () == 10);

   entity.erase <C> ();

   flip_TEST (entity2.use <C> ()._list.front () == 2);

   entity2.erase <C> ();
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestEntity::run_008 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;

   entity.emplace <B> (20);

   C & c = entity.emplace <C> ();
   flip_TEST (c._list.empty ());
   c._list.push_back (10);

   Entity entity2 = entity;
   flip_TEST (entity2.use <B> ()._val == 20);
   flip_TEST (entity2.use <C> ()._list.size () == 1);
   flip_TEST (entity2.use <C> ()._list.front () == 10);

   entity2.use <B> ()._val = 5;
   entity2.use <C> ()._list.front () = 2;
   flip_TEST (entity2.use <B> ()._val == 5);
   flip_TEST (entity2.use <C> ()._list.front () == 2);
   flip_TEST (entity.use <B> ()._val == 20);
   flip_TEST (entity.use <C> ()._list.front () == 10);

   entity.erase <B> ();
   entity.use <C> ()._list.front () = 7;
   entity.erase <C> ();

   flip_TEST (entity2.use <B> ()._val == 5);
   flip_TEST (entity2.use <C> ()._list.front () == 2);

   entity2.erase <C> ();
   entity2.use <B> ()._val = 17;
   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_009
Description :
   std::shared_ptr version, for classes that cannot support copy constructor
   while using Object copy constructor (for example inserting in a container)
==============================================================================
*/

void  TestEntity::run_009 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;
   auto & b_sptr = entity.emplace <std::shared_ptr <B>> (new B (1));
   flip_TEST (b_sptr->_val == 1);

   flip_TEST (_class_b_cnt == 1);

   flip_CHECK_THROW (entity.erase <B> ());

   Entity entity2 = entity;

   flip_TEST (_class_b_cnt == 1);

   entity2.erase <std::shared_ptr <B>> ();

   flip_TEST (_class_b_cnt == 1);

   entity.erase <std::shared_ptr <B>> ();

   flip_TEST (_class_b_cnt == 0);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestEntity::run_010 ()
{
   flip_TEST (_class_a_cnt == 0);

   Entity entity;
   entity.emplace <A> ();

   flip_TEST (_class_a_cnt == 1);

#if (flip_ENTITY_USE == flip_ENTITY_USE_STRICT)
   flip_CHECK_THROW (entity.impl_clear ());

   flip_TEST (_class_a_cnt == 1);

   entity.erase <A> ();

#elif (flip_ENTITY_USE == flip_ENTITY_USE_RELAXED)
   entity.impl_clear ();

#endif

   flip_TEST (_class_a_cnt == 0);
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestEntity::run_011 ()
{
   Entity entity;
   entity.emplace <D> ();
   entity.erase <D> ();
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestEntity::run_012 ()
{
   flip_TEST (_class_b_cnt == 0);

   Entity entity;

   entity.emplace <B> (20);

   C & c = entity.emplace <C> ();
   flip_TEST (c._list.empty ());
   c._list.push_back (10);

   Entity entity2;
   entity2 = std::move (entity);
   flip_TEST (entity2.use <B> ()._val == 20);
   flip_TEST (entity2.use <C> ()._list.size () == 1);
   flip_TEST (entity2.use <C> ()._list.front () == 10);

   entity2.erase <C> ();
   entity2.use <B> ()._val = 17;
   entity2.erase <B> ();

   flip_TEST (_class_b_cnt == 0);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

