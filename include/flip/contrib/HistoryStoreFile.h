/*****************************************************************************

      HistoryStoreFile.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/config.h"
#include "flip/Transaction.h"

#include <memory>
#include <string>

#include <cstdint>



namespace flip
{



class SqlDatabase;

class flip_API HistoryStoreFile
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class flip_API iterator;

   class flip_API TransactionProxy
   {
   public:
                  TransactionProxy (iterator & parent);
      virtual     ~TransactionProxy () {}

      TransactionProxy &
                  operator = (Transaction tx);

      uint64_t    user () const;
      uint64_t    actor () const;
      uint64_t    nbr () const;

      std::string label () const;
      std::string metadata (const std::string & key) const;

                  operator Transaction ();

   private:
                  TransactionProxy () = delete;
                  TransactionProxy (const TransactionProxy & rhs) = delete;
      TransactionProxy &
                  operator = (const TransactionProxy & rhs) = delete;

      iterator &  _parent;
   };

   class flip_API iterator
   {
   public:
                  iterator ();
                  iterator (const iterator & rhs);
      virtual     ~iterator () = default;

      iterator &  operator = (const iterator & rhs);

      iterator &  operator ++ ();
      iterator &  operator -- ();

      bool        operator == (const iterator & rhs) const;
      bool        operator != (const iterator & rhs) const;

      TransactionProxy &
                  operator * ();
      TransactionProxy *
                  operator -> ();

   private:
      friend class HistoryStoreFile;
      friend class TransactionProxy;

      HistoryStoreFile *
                  _parent_ptr = nullptr;
      int64_t     _id = 0LL;
      TransactionProxy
                  _proxy;
   };

                  HistoryStoreFile (const std::string & version, const char * path_0);
   virtual        ~HistoryStoreFile ();

   std::string    version ();

   void           set_max_size (size_t size);

   iterator       begin ();
   iterator       end ();
   iterator       last_undo ();
   iterator       first_redo ();
   void           set_first_redo (iterator it);

   void           clear ();
   void           erase (iterator it);
   void           push (Transaction tx);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   int64_t        get_next (int64_t row_id);
   int64_t        get_prev (int64_t row_id);
   std::string    get_metadata (int64_t row_id, const std::string & key);
   Transaction    get_transaction (int64_t row_id);
   void           set_transaction (int64_t row_id, Transaction tx);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           create ();

   size_t         _max_size = SIZE_MAX;
   size_t         _cur_size = 0;
   std::unique_ptr <SqlDatabase>
                  _db_uptr;

   iterator       _it_redo;

   std::string    _document_version;
   std::string    _version;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  HistoryStoreFile () = delete;
                  HistoryStoreFile (const HistoryStoreFile & rhs) = delete;
   HistoryStoreFile &
                  operator = (const HistoryStoreFile & rhs) = delete;
                  HistoryStoreFile (HistoryStoreFile && rhs) = delete;
   HistoryStoreFile &
                  operator = (HistoryStoreFile && rhs) = delete;
   bool           operator == (const HistoryStoreFile & rhs) const = delete;
   bool           operator != (const HistoryStoreFile & rhs) const = delete;



}; // class HistoryStoreFile



}  // namespace flip



//#include  "flip/HistoryStoreFile.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

