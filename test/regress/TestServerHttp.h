/*****************************************************************************

      TestServerHttp.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Blob.h"
#include "flip/Bool.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Enum.h"
#include "flip/Float.h"
#include "flip/Int.h"
#include "flip/Message.h"
#include "flip/Object.h"
#include "flip/ObjectRef.h"
#include "flip/String.h"
#include "flip/contrib/Socket.h"

#include <cstdint>



namespace flip
{



class TestServerHttp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
      Int         _int;
   };

   enum class B
   {
                  x0, x1,
   };

   class Root
   :  public Object
   {
   public:
      Bool        _bool;
      Int         _int;
      Float       _float;
      Enum <B>    _enum;
      ObjectRef <A>
                  _object_ref;
      Blob        _blob;
      String      _string;
      Collection <A>
                  _coll;
      Array <A>   _array;
      Message <>  _message;
      A           _a;
   };

                  TestServerHttp () = default;
   virtual        ~TestServerHttp () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Socket::Id     connect_loopback ();

   void           run_000 ();
   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();
   void           run_006 ();
   void           run_007 ();
   void           run_008 ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();
   void           run_015 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestServerHttp (const TestServerHttp & rhs) = delete;
   TestServerHttp &
                  operator = (const TestServerHttp & rhs) = delete;
                  TestServerHttp (TestServerHttp && rhs) = delete;
   TestServerHttp &
                  operator = (TestServerHttp && rhs) = delete;
   bool           operator == (const TestServerHttp & rhs) const = delete;
   bool           operator != (const TestServerHttp & rhs) const = delete;



}; // class TestServerHttp



}  // namespace flip



//#include  "flip/TestServerHttp.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

