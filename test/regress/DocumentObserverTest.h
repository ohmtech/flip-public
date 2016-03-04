/*****************************************************************************

      DocumentObserverTest.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/DataConsumerMemory.h"
#include "flip/detail/ConsumerTextOut.h"
#include "flip/detail/DocumentObserverBase.h"

#include <vector>

#include <cstdint>



namespace flip
{



class Float;
class Int;
class ObjectRefBase;
class CollectionBase;
class Type;

class DocumentObserverTest
:  public DocumentObserverBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DocumentObserverTest ();
   virtual        ~DocumentObserverTest () = default;

   void           enable_debug_output ();
   void           enable_test_output ();
   void           test (const std::string & str);

   // DocumentObserverBase
   virtual void   notify_document_changed (Object & object) override;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   struct LessType
   {
   public:
      bool        operator () (const Type * lhs, const Type * rhs) const;
   };

   void           document_changed (Type & object);
   void           document_changed (Int & object);
   void           document_changed (Float & object);
   void           document_changed (ObjectRefBase & object);
   void           document_changed (CollectionBase & object);
   void           document_changed (Object & object);

   Ref            make_ref (Type * type_ptr);
   void           output_lf ();

   bool           _output_flag = false;
   bool           _output_test_flag = true;
   std::string    _test;

   std::vector <uint8_t>
                  _data;
   DataConsumerMemory
                  _data_consumer;
   ConsumerTextOut
                  _out;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DocumentObserverTest (const DocumentObserverTest & rhs) = delete;
   DocumentObserverTest &
                  operator = (const DocumentObserverTest & rhs) = delete;
                  DocumentObserverTest (DocumentObserverTest && rhs) = delete;
   DocumentObserverTest &
                  operator = (DocumentObserverTest && rhs) = delete;
   bool           operator == (const DocumentObserverTest & rhs) const = delete;
   bool           operator != (const DocumentObserverTest & rhs) const = delete;



}; // class DocumentObserverTest



}  // namespace flip



//#include  "flip/DocumentObserverTest.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

