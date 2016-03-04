/*****************************************************************************

      TestMessage.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/Message.h"
#include "flip/DataModel.h"
#include "flip/Object.h"

#include <vector>
#include <list>
#include <map>

#include <cstdint>



namespace flip
{



class TestMessage
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class Model : public DataModel <Model> {};

   class Info
   {
   public:
                  Info () = default;
                  Info (uint64_t val_1, uint32_t val_2) : _val_1 (val_1), _val_2 (val_2) {}

      bool        operator == (const Info & rhs) const {return _val_1 == rhs._val_1 && _val_2 == rhs._val_2;}

      void        write (StreamBinOut & sbo) const;
      void        read (StreamBinIn & sbi);

      uint64_t    _val_1;
      uint32_t    _val_2;
   };

   class Root
   :  public Object
   {
   public:
      Message <>  _msg_void;
      Message <int32_t>
                  _msg_int;
      Message <double, int32_t>
                  _msg_double_int;
      Message <float, double, int32_t>
                  _msg_float_double_int;
      Message <Info>
                  _msg_info;
      Message <Info>
                  _msg_cr_info;
      Message <std::vector <Info>>
                  _msg_vector_info;
      Message <std::list <Info>>
                  _msg_list_info;
      Message <std::map <double, Info>>
                  _msg_map_double_info;
      Message <std::vector <uint8_t>>
                  _msg_data;
   };

                  TestMessage () = default;
   virtual        ~TestMessage () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_000b ();
   void           run_000c ();
   void           run_000d ();
   void           run_000e ();
   void           run_000f ();
   void           run_000g ();
   void           run_000h ();
   void           run_001 ();
   void           run_001b ();
   void           run_001c ();
   void           run_001d ();
   void           run_001e ();
   void           run_001f ();
   void           run_001g ();
   void           run_001h ();
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
                  TestMessage (const TestMessage & rhs) = delete;
   TestMessage &  operator = (const TestMessage & rhs) = delete;
                  TestMessage (TestMessage && rhs) = delete;
   TestMessage &  operator = (TestMessage && rhs) = delete;
   bool           operator == (const TestMessage & rhs) const = delete;
   bool           operator != (const TestMessage & rhs) const = delete;



}; // class TestMessage



}  // namespace flip



//#include  "flip/TestMessage.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

