/*****************************************************************************

      TestHistory.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"



namespace flip
{



class TestHistory
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
      Int         _int;
      Float       _float;
   };

   class Root
   :  public Object
   {
   public:
      A           _a;
   };

   class Model2 : public DataModel <Model2> {};

   class Root2
   :  public Object
   {
   public:
   };

                  TestHistory () = default;
   virtual        ~TestHistory () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   template <class HistoryStoreImpl, class... Args>
   void           run_000 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_001 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_002 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_003 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_004 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_005 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_006 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_007 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_008 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_009 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_010 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_011 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_012 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_013 (Args &&... args);

   template <class HistoryStoreImpl, class... Args>
   void           run_016 (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_016b (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_016c (Args &&... args);
   template <class HistoryStoreImpl, class... Args>
   void           run_016d (Args &&... args);

   void           run_014 (const char * path_0);
   void           run_014b ();
   void           run_015 (const char * path_0);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestHistory (const TestHistory & rhs) = delete;
   TestHistory &  operator = (const TestHistory & rhs) = delete;
                  TestHistory (TestHistory && rhs) = delete;
   TestHistory &  operator = (TestHistory && rhs) = delete;
   bool           operator == (const TestHistory & rhs) const = delete;
   bool           operator != (const TestHistory & rhs) const = delete;



}; // class TestHistory



}  // namespace flip



#include  "TestHistory.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

