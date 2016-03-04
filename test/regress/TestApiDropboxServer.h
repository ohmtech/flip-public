/*****************************************************************************

      TestApiDropboxServer.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/contrib/cloud_store/ApiDropbox.h"

#include <string>



namespace flip
{



class ApiDropboxServerEmulation;

class TestApiDropboxServer
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestApiDropboxServer () = default;
   virtual        ~TestApiDropboxServer () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   class AutoBaseApiSwap
   {
   public:
                  AutoBaseApiSwap ();
                  ~AutoBaseApiSwap ();
   private:
      std::string _base_api;
      std::string _base_api_notify;
      std::string _base_api_content;
   };

   void           run_001 ();
   void           run_002 ();
   void           run_003 ();

   long           call_delta (ApiDropbox::ReplyDelta & reply, ApiDropboxServerEmulation & server, std::string & cursor);
   long           call_files_put (ApiDropboxServerEmulation & server, std::string path, std::string content);
   long           call_files (std::string & reply, ApiDropboxServerEmulation & server, std::string path);
   long           call_fileops_delete (ApiDropboxServerEmulation & server, std::string path);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestApiDropboxServer (const TestApiDropboxServer & rhs) = delete;
   TestApiDropboxServer &
                  operator = (const TestApiDropboxServer & rhs) = delete;
                  TestApiDropboxServer (TestApiDropboxServer && rhs) = delete;
   TestApiDropboxServer &
                  operator = (TestApiDropboxServer && rhs) = delete;
   bool           operator == (const TestApiDropboxServer & rhs) const = delete;
   bool           operator != (const TestApiDropboxServer & rhs) const = delete;



}; // class TestApiDropboxServer



}  // namespace flip



//#include  "flip/TestApiDropboxServer.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

