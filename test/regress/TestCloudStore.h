/*****************************************************************************

      TestCloudStore.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Array.h"
#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/DocumentObserver.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/detail/TransportBase.h"

#include <condition_variable>
#include <mutex>
#include <thread>



namespace flip
{



class ApiDropboxServerEmulation;

class TestCloudStore
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestCloudStore () = default;
   virtual        ~TestCloudStore () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   class Model : public DataModel <Model> {};

   class Clip
   :  public Object
   {
   public:
                  Clip () = default;   // COV_NF_LINE
                  Clip (double position, double duration) : _position (position), _duration (duration) {}

      Float       _position;
      Float       _duration;
   };

   typedef Collection <Clip> Clips;

   class Track
   :  public Object
   {
   public:

      Clips       _clips;
   };

   typedef Array <Track> Tracks;

   class Song
   :  public Object
   {
   public:
      Tracks      _tracks;
   };



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   class Listener
   :  public TransportListener
   {
   };

   class AutoApiDropboxServer
   {
   public:
                  AutoApiDropboxServer (int error_period = 0, int longpoll_timeout = 10);
                  ~AutoApiDropboxServer ();

   private:
      void        init ();

      const int   _error_period;
      const int   _longpoll_timeout;

      mutable bool
                  _loop_flag = true;
      mutable bool
                  _ready_flag = false;
      std::mutex  _mutex;
      std::condition_variable
                  _cond;
      std::thread _thread;
      std::unique_ptr <ApiDropboxServerEmulation>
                  _server_uptr;

      std::string _base_api;
      std::string _base_api_notify;
      std::string _base_api_content;
   };

   void           run_f001 ();
   void           run_f002 ();
   void           run_f003 ();
   void           run_f004 ();

   void           run_s001 ();
   void           run_s002 ();
   void           run_s003 ();
   void           run_s004 ();
   void           run_s005 ();
   void           run_s006 ();
   void           run_s007 ();
   void           run_s008 ();
   void           run_s009 ();

   void           run_r001 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestCloudStore (const TestCloudStore & rhs) = delete;
   TestCloudStore &
                  operator = (const TestCloudStore & rhs) = delete;
                  TestCloudStore (TestCloudStore && rhs) = delete;
   TestCloudStore &
                  operator = (TestCloudStore && rhs) = delete;
   bool           operator == (const TestCloudStore & rhs) const = delete;
   bool           operator != (const TestCloudStore & rhs) const = delete;



}; // class TestCloudStore



}  // namespace flip



//#include  "flip/TestCloudStore.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

