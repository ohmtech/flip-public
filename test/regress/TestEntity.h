/*****************************************************************************

      TestEntity.h
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <list>



namespace flip
{



class TestEntity
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestEntity () = default;
   virtual        ~TestEntity () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

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

   static int     _class_a_cnt;
   static int     _class_b_cnt;

   class A
   {
   public:
                  A () {++_class_a_cnt;}
                  A (const A &) {++_class_a_cnt;}
                  A (A &&) {}
      virtual     ~A () {--_class_a_cnt;}
   };

   class B
   {
   public:
                  B (int val) : _val (val) {++_class_b_cnt;}
                  B (const B & rhs) : _val (rhs._val) {++_class_b_cnt;}
                  B (B && rhs) : _val (rhs._val) {rhs._val = 0;}
      virtual     ~B () {--_class_b_cnt;}
      int         _val;
   };

   class C
   {
   public:
                  C () = default;
                  C (const C & rhs) = default;
                  C (C && rhs) : _list (std::move (rhs._list)) {}
      virtual     ~C () = default;

      std::list <int>
                  _list;
   };

   class D
   {
   public:
                  D () = default;

   private: // MSVC 2013u4 does not implement 'delete' so we need to hide copy ctor
                  D (const D & rhs) = delete;
   };



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestEntity (const TestEntity & rhs) = delete;
   TestEntity &   operator = (const TestEntity & rhs) = delete;
                  TestEntity (TestEntity && rhs) = delete;
   TestEntity &   operator = (TestEntity && rhs) = delete;
   bool           operator == (const TestEntity & rhs) const = delete;
   bool           operator != (const TestEntity & rhs) const = delete;



}; // class TestEntity



}  // namespace flip



//#include  "flip/TestEntity.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

