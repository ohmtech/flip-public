/*****************************************************************************

      TestSignal.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Collection.h"
#include "flip/DataModel.h"
#include "flip/Int.h"
#include "flip/Float.h"
#include "flip/Object.h"
#include "flip/Signal.h"



namespace flip
{



class TestSignal
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestSignal () = default;
   virtual        ~TestSignal () = default;

   void           run ();

   class Model : public DataModel <Model> {};

   class A
   :  public Object
   {
   public:
      enum
      {
                  TEST_void,
                  TEST_int,
                  TEST_double_int,
                  TEST_float_double_int,
                  TEST_Info,
                  TEST_cr_Info,
                  TEST_vector_Info,
                  TEST_list_Info,
                  TEST_map_double_Info,
      };

                  A () : _signal_void (TEST_void, *this), _signal_int (TEST_int, *this), _signal_double_int (TEST_double_int, *this), _signal_float_double_int (TEST_float_double_int, *this), _signal_info (TEST_Info, *this), _signal_cr_info (TEST_cr_Info, *this), _signal_vector_info (TEST_vector_Info, *this), _signal_list_info (TEST_list_Info, *this), _signal_map_double_info (TEST_map_double_Info, *this) {}
                  A (const A & other) : Object (other), _signal_void (TEST_void, *this), _signal_int (TEST_int, *this), _signal_double_int (TEST_double_int, *this), _signal_float_double_int (TEST_float_double_int, *this), _signal_info (TEST_Info, *this), _signal_cr_info (TEST_cr_Info, *this), _signal_vector_info (TEST_vector_Info, *this), _signal_list_info (TEST_list_Info, *this), _signal_map_double_info (TEST_map_double_Info, *this) {}

      class Info
      {
      public:
         uint64_t _val_1;
         uint32_t _val_2;
      };

      Signal <>   _signal_void;
      Signal <int>
                  _signal_int;
      Signal <double, int>
                  _signal_double_int;
      Signal <float, double, int>
                  _signal_float_double_int;
      Signal <Info>
                  _signal_info;
      Signal <Info>
                  _signal_cr_info;
      Signal <std::vector <Info>>
                  _signal_vector_info;
      Signal <std::list <Info>>
                  _signal_list_info;
      Signal <std::map <double, Info>>
                  _signal_map_double_info;

      Int         _int;
   };

   class Root
   :  public Object
   {
   public:
      A           _a;
      Collection <A>
                  _coll_a;
   };

   class AView // COV_NF_LINE
   {
   public:
                  AView (A & a);
      virtual     ~AView () = default;

      void        signal_int (int val);

      SignalConnection
                  _cnx;

      bool        _signaled_flag = false;

   private:
                  AView () = delete;
                  AView (const AView & rhs) = delete;
   };



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum SignalType
   {
                  TEST,
   };

   void           run_pre ();
   void           run_000 ();
   void           run_000b ();
   void           run_000c ();
   void           run_000d ();
   void           run_000e ();
   void           recv_000 ();
   bool           _recv_000_flag;

   void           run_001 ();
   void           run_001b ();
   void           run_001c ();
   void           recv_001 (int val);
   bool           _recv_001_flag;

   void           run_002 ();
   void           recv_002 (double x, int y);
   bool           _recv_002_flag;

   void           run_003 ();
   void           recv_003 (float z, double x, int y);
   void           run_003b ();
   bool           _recv_003_flag;

   void           run_004 ();
   bool           _recv_004_flag;

   void           run_005 ();
   bool           _recv_005_flag;

   void           run_006 ();
   bool           _recv_006_flag;

   void           run_007 ();
   bool           _recv_007_flag;

   void           run_008 ();
   bool           _recv_008_flag;

   void           run_009 ();
   void           run_010 ();
   void           run_011 ();




/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestSignal (const TestSignal & rhs) = delete;
   TestSignal &   operator = (const TestSignal & rhs) = delete;
                  TestSignal (TestSignal && rhs) = delete;
   TestSignal &   operator = (TestSignal && rhs) = delete;
   bool           operator == (const TestSignal & rhs) const = delete;
   bool           operator != (const TestSignal & rhs) const = delete;



}; // class TestSignal



}  // namespace flip



//#include  "flip/TestSignal.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

