/*****************************************************************************

      DocumentObserverTest.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocumentObserverTest.h"

#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/detail/CollectionBase.h"
#include "flip/detail/ClassBase.h"
#include "flip/detail/ObjectRefBase.h"
#include "flip/detail/TypeId.h"

#include <set>

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DocumentObserverTest::DocumentObserverTest ()
:  _data_consumer (_data)
,  _out (_data_consumer)
{
}



/*
==============================================================================
Name : enable_debug_output
==============================================================================
*/

void  DocumentObserverTest::enable_debug_output ()
{
   _output_flag = true;
   _output_test_flag = false;
}



/*
==============================================================================
Name : enable_test_output
==============================================================================
*/

void  DocumentObserverTest::enable_test_output ()
{
   _output_flag = true;
   _output_test_flag = true;
}



/*
==============================================================================
Name : test
==============================================================================
*/

void  DocumentObserverTest::test (const std::string & str)
{
   _test = str;
}



/*
==============================================================================
Name : notify_document_changed
==============================================================================
*/

void  DocumentObserverTest::notify_document_changed (Object & object)
{
   Type & type = object;

   document_changed (type);

   std::string output (_data.begin (), _data.end ());

   if (_output_flag)
   {
      printf ("\n%s\n\n", output.c_str ());
   }

   if (!_test.empty ())
   {
      assert (_test == output);
   }

   _test.clear ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : LessType::operator ()
==============================================================================
*/

bool  DocumentObserverTest::LessType::operator () (const Type * lhs, const Type * rhs) const
{
   return lhs->ref () < rhs->ref ();
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (Type & object)
{
   const auto & class_base = object.get_class ();

   _out.print ("%@ %@", class_base.name (), object.ref ());
   output_lf ();

   ConsumerTextOut::Indent auto_indent (_out, 2);

   // base

   _out.print ("added: %@:%@", object._added_before_flag, object._added_flag);
   output_lf ();
   _out.print ("modcnt: %@", object._total_modification_cnt);
   output_lf ();

   // value

   switch (object.get_class ().type_id ())
   {
   case TypeId::INT:
      document_changed (dynamic_cast <Int &> (object));
      break;

   case TypeId::FLOAT:
      document_changed (dynamic_cast <Float &> (object));
      break;

   case TypeId::OBJECT_REF:
      document_changed (dynamic_cast <ObjectRefBase &> (object));
      break;

   case TypeId::COLLECTION:
      document_changed (dynamic_cast <CollectionBase &> (object));
      break;

   default:
      document_changed (dynamic_cast <Object &> (object));
      break;
   }
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (Int & object)
{
   _out.print ("value:  %@:%@", object.before (), int64_t (object));
   output_lf ();
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (Float & object)
{
   _out.print ("value:  %@:%@", object.before (), double (object));
   output_lf ();
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (ObjectRefBase & object)
{
   _out.print ("value:  %@:%@", object.get_before (), object.get ());
   output_lf ();
}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (CollectionBase & object)
{
   std::map <KeyRandom, Type *> elem_map = object.impl_raw_data ();

   // sort by ref

   std::set <Type *, LessType> elem_set;

   for (auto & elem : elem_map)
   {
      auto sub_type_ptr = elem.second;

      elem_set.insert (sub_type_ptr);
   }

   // recurse

   uint64_t nbr = 0;

   for (auto & elem : elem_set)
   {
      auto & sub_type = *elem;

      _out.print ("%@:", nbr);
      output_lf ();

      ConsumerTextOut::Indent auto_indent (_out, 2);

      document_changed (sub_type);

      ++nbr;
   }

}



/*
==============================================================================
Name : document_changed
==============================================================================
*/

void  DocumentObserverTest::document_changed (Object & object)
{
   _out.print (
      "parent: %@:%@",
      make_ref (object.parent ().before_ptr <Type> ()),
      make_ref (object._parent_ptr)
   );
   output_lf ();

   for (const auto & member : object.get_class ().members ())
   {
      Type & sub_type = member._representative.from (object);

      _out.print ("%@:", member._name_0);
      output_lf ();

      ConsumerTextOut::Indent auto_indent (_out, 2);

      document_changed (sub_type);
   }
}



/*
==============================================================================
Name : make_ref
==============================================================================
*/

Ref   DocumentObserverTest::make_ref (Type * type_ptr)
{
   if (type_ptr == nullptr) return Ref::null;   // done

   return type_ptr->ref ();
}



/*
==============================================================================
Name : output_lf
==============================================================================
*/

void  DocumentObserverTest::output_lf ()
{
   if (_output_test_flag)
   {
      _out.print ("\\n");
   }
   else
   {
      _out.print ("\n");
   }
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

