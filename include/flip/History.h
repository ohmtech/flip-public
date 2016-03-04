/*****************************************************************************

      History.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Transaction.h"

#include <list>



namespace flip
{



class DocumentBase;

template <class HistoryStoreImpl>
class History
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using iterator = typename HistoryStoreImpl::iterator;

   template <class... Args>
                  History (DocumentBase & document, Args &&... args);
   virtual        ~History () = default;

   HistoryStoreImpl &
                  store ();

   std::string    version ();

   iterator       begin ();
   iterator       end ();
   iterator       last_undo ();
   iterator       first_redo ();

   void           clear ();
   iterator       erase (iterator it);

   void           add_undo_step (Transaction tx);

   bool           execute_undo ();
   bool           execute_redo ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   DocumentBase & _document;
   HistoryStoreImpl
                  _store;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  History () = delete;
                  History (const History & rhs) = delete;
   History &      operator = (const History & rhs) = delete;
                  History (History && rhs) = delete;
   History &      operator = (History && rhs) = delete;
   bool           operator == (const History & rhs) const = delete;
   bool           operator != (const History & rhs) const = delete;



}; // class History



}  // namespace flip



#include  "flip/History.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

