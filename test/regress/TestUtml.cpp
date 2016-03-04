/*****************************************************************************

      TestUtml.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

#include "TestUtml.h"

#include "flip/DataConsumerMemory.h"
#include "flip/DataProviderMemory.h"
#include "flip/Document.h"
#include "flip/contrib/Utml.h"
#include "TestDef.h"

#include <cassert>



namespace flip
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestUtml::run ()
{
   Model::version ("test.document");

   Model::declare <A> ()
      .name ("MyClass")
      .member <Bool, &A::_bool> ("bool")
      .member <Int, &A::_int> ("int")
      .member <Float, &A::_float> ("float")
      .member <ObjectRef <A>, &A::_ref_a> ("ref_a")
      .member <Blob, &A::_blob> ("blob");

   Model::declare <B> ()
      .name ("flip.Test")
      .inherit <A> ()
      .member <Bool, &B::_bool2> ("bool2")
      .member <Int, &B::_int2> ("int2")
      .member <Float, &B::_float2> ("float2")
      .member <Blob, &B::_blob2> ("blob2")
      .member <A, &B::_a2> ("a2")
      .member <Message <>, &B::_message2> ("message2")
      .member <Collection <A>, &B::_coll> ("coll")
      .member <Variant <A>, &B::_variant> ("variant");

   Model::declare <C> ()
      .name ("flip.C")
      .member <B, &C::_b> ("b");

   Model::declare <Root> ()
      .name ("flip.Root")
      .member <Bool, &Root::_bool> ("bool")
      .member <Int, &Root::_int> ("int")
      .member <Float, &Root::_float> ("float")
      .member <ObjectRef <A>, &Root::_ref_a> ("ref_a")
      .member <Blob, &Root::_blob> ("blob")
      .member <String, &Root::_string> ("string")
      .member <A, &Root::_a> ("a")
      .member <Collection <A>, &Root::_coll_a> ("coll_a")
      .member <Collection <B>, &Root::_coll_b> ("coll_b")
      .member <Array <A>, &Root::_array_a> ("array_a")
      .member <Collection <C>, &Root::_coll_c> ("coll_c")
      .member <Message <>, &Root::_message> ("message");



   run_000 ();
   run_001 ();
   run_002 ();
   run_002b ();
   run_002c ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_005b ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
   run_013 ();
   run_014 ();
   run_015 ();
   run_015b ();
   run_016 ();
   run_017 ();
   run_018 ();
   run_019 ();
   run_020 ();
   run_021 ();
   run_022 ();
   run_023 ();
   run_024 ();
   run_025 ();
   run_026 ();
   run_027 ();
   run_028 ();
   run_029 ();
   run_030 ();
   run_031 ();
   run_032 ();
   run_033 ();
   run_034 ();
   run_035 ();
}






/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
==============================================================================
*/

void  TestUtml::run_000 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');

   Root & root = document.root <Root> ();

   std::vector <uint8_t> blob_data;
   blob_data.resize (41);

   for (size_t i = 0 ; i < blob_data.size () ; ++i)
   {
      blob_data [i] = uint8_t (i + 54);
   }

   root._bool = true;
   root._int = 3;
   root._float = 2.5;
   root._ref_a = &root._a;
   root._blob = std::vector <uint8_t> {0xff, 0x12};
   root._string = "This is a test";
   root._a._float = 4.25;
   root._a._ref_a = &root._a;
   root._a._blob = blob_data;
   A & a = *root._coll_a.emplace ();
   a._ref_a = &a;
   A & a2 = *root._coll_a.emplace ();
   a2._ref_a = &a2;
   A & a3 = *root._array_a.emplace (root._array_a.end ());
   a3._ref_a = &a3;
   A & a4 = *root._array_a.emplace (root._array_a.end ());
   a4._ref_a = &a4;
   C & c = *root._coll_c.emplace ();
   A & a5 = *root._array_a.emplace (root._array_a.end ());
   a5._ref_a = &c._b._a2;
   B & b = dynamic_cast <B &> (*root._coll_a.emplace <B> ());
   b._ref_a = &b;
   b._variant.reset <A> ();

   std::vector <uint8_t> data;
   DataConsumerMemory consumer (data);
   Utml::write (consumer, document.write ());

   std::string text (data.begin (), data.end ());

   text = transform_whitespaces (text);

   //printf ("%s", text.c_str ());

   flip_TEST (contains (text, "flip.Root root1 { bool = true int = 3 float = 2.5 ref_a = root1.a blob = 0xff12 string = \"This is a test\" a = { float = 4.25 ref_a = root1.a blob = decode_b64 (Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV4=) } coll_a = {"));
   flip_TEST (contains (text, "MyClass my_class1"));
   flip_TEST (contains (text, "MyClass my_class2"));
   flip_TEST (contains (text, "MyClass my_class3"));
   flip_TEST (contains (text, "flip.Test test1 { ref_a = test1 a2 = { } variant = {"));
   flip_TEST (contains (text, "array_a = { MyClass my_class4 { ref_a = my_class4 } MyClass my_class5 { ref_a = my_class5 } MyClass my_class6 { ref_a = c1.b.a2 } } coll_c = { flip.C c1 { b = { a2 = { } } } } }"));
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestUtml::run_001 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root {}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestUtml::run_002 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root {bool = true}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_002b
==============================================================================
*/

void  TestUtml::run_002b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root {bool = true int = 2 float = 4}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 2LL);
   flip_TEST (root._float == 4.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_002c
==============================================================================
*/

void  TestUtml::run_002c ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root {bool=true a={float=3.25} int=2 float=4}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == true);
   flip_TEST (root._int == 2LL);
   flip_TEST (root._float == 4.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 3.25);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestUtml::run_003 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root { int=7 }";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 7LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestUtml::run_004 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{float=7.5}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 7.5);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestUtml::run_005 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{blob=0xff12}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.size () == 2);
   flip_TEST (root._blob.value ()[0] == 0xff);
   flip_TEST (root._blob.value ()[1] == 0x12);
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_005b
==============================================================================
*/

void  TestUtml::run_005b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{blob=decode_b64(am95IQ==)}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.size () == 4);
   flip_TEST (root._blob.value ()[0] == 'j');
   flip_TEST (root._blob.value ()[1] == 'o');
   flip_TEST (root._blob.value ()[2] == 'y');
   flip_TEST (root._blob.value ()[3] == '!');
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestUtml::run_006 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{string=\"this is a test\"}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string == "this is a test");
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestUtml::run_007 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{bool=false a={float=4.25}}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 4.25);
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestUtml::run_008 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{coll_a={MyClass{bool=true}}}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
   flip_TEST (std::distance (root._coll_a.begin (), root._coll_a.end ()) == 1);
   flip_TEST (root._coll_a.begin ()->_bool == true);
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestUtml::run_009 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{array_a={MyClass{bool=true}}}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
   flip_TEST (std::distance (root._array_a.begin (), root._array_a.end ()) == 1);
   flip_TEST (root._array_a.begin ()->_bool == true);
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestUtml::run_010 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{array_a={MyClass test{ref_a=test}}}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == nullptr);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
   flip_TEST (std::distance (root._array_a.begin (), root._array_a.end ()) == 1);
   flip_TEST (root._array_a.begin ()->_ref_a == &*root._array_a.begin ());
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestUtml::run_011 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{ref_a=root.a}";
   read (document, text);

   Root & root = document.root <Root> ();

   flip_TEST (root._bool == false);
   flip_TEST (root._int == 0LL);
   flip_TEST (root._float == 0.0);
   flip_TEST (root._ref_a == &root._a);
   flip_TEST (root._blob.empty ());
   flip_TEST (root._string.empty ());
   flip_TEST (root._a._float == 0.0);
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestUtml::run_012 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{";

   test_parsing_error (document, text, 1, 14);
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestUtml::run_013 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{{";

   test_parsing_error (document, text, 1, 15);
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestUtml::run_014 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{something = 15}";

   test_parsing_error (document, text, 1, 15);
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestUtml::run_015 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{coll_a = {root {}}}";

   test_parsing_error (document, text, 1, 25);
}



/*
==============================================================================
Name : run_015b
==============================================================================
*/

void  TestUtml::run_015b ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{array_a = {root {}}}";

   test_parsing_error (document, text, 1, 26);
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestUtml::run_016 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "Blabla root{}";

   test_parsing_error (document, text, 1, 0);
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestUtml::run_017 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "MyClass root{}";

   test_parsing_error (document, text, 1, 0);
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestUtml::run_018 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{message=bla}";

   test_parsing_error (document, text, 1, 15);
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestUtml::run_019 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{bool=fals}";

   test_parsing_error (document, text, 1, 20);
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestUtml::run_020 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{string=\"bla\\hbla\"}";

   test_parsing_error (document, text, 1, 23);
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestUtml::run_021 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{blob=0x123z}";

   test_parsing_error (document, text, 1, 22);
}



/*
==============================================================================
Name : run_022
==============================================================================
*/

void  TestUtml::run_022 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{blob=decode_b64(am95IQ.)}";

   test_parsing_error (document, text, 1, 31);
}



/*
==============================================================================
Name : run_023
==============================================================================
*/

void  TestUtml::run_023 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{blob=decode_b64(am95IQ==}";

   test_parsing_error (document, text, 1, 31);
}



/*
==============================================================================
Name : run_024
==============================================================================
*/

void  TestUtml::run_024 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root{ref_a=ident}";

   test_parsing_error (document, text, 1, 21);
}



/*
==============================================================================
Name : run_025
==============================================================================
*/

void  TestUtml::run_025 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{ref_a=root.bla}";

   test_parsing_error (document, text, 1, 29);
}




/*
==============================================================================
Name : run_026
==============================================================================
*/

void  TestUtml::run_026 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root";

   test_parsing_error (document, text, 1, 0);
}



/*
==============================================================================
Name : run_027
==============================================================================
*/

void  TestUtml::run_027 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root";

   test_parsing_error (document, text, 1, 10);
}



/*
==============================================================================
Name : run_028
==============================================================================
*/

void  TestUtml::run_028 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root\nroot";

   test_parsing_error (document, text, 2, 0);
}



/*
==============================================================================
Name : run_029
==============================================================================
*/

void  TestUtml::run_029 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root\nroot\n{bla=true}";

   test_parsing_error (document, text, 3, 1);
}



/*
==============================================================================
Name : run_030
==============================================================================
*/

void  TestUtml::run_030 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{string=\"bla";

   test_parsing_error (document, text, 1, 23);
}



/*
==============================================================================
Name : run_031
==============================================================================
*/

void  TestUtml::run_031 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{string={bla";

   test_parsing_error (document, text, 1, 22);
}



/*
==============================================================================
Name : run_032
==============================================================================
*/

void  TestUtml::run_032 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root{blob=0";

   test_parsing_error (document, text, 1, 20);
}



/*
==============================================================================
Name : run_033
==============================================================================
*/

void  TestUtml::run_033 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = " ";

   test_parsing_error (document, text, 1, 0);
}



/*
==============================================================================
Name : run_034
==============================================================================
*/

void  TestUtml::run_034 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "";

   test_parsing_error (document, text, 1, 0);
}



/*
==============================================================================
Name : run_035
==============================================================================
*/

void  TestUtml::run_035 ()
{
   Document document (Model::use (), 123456789UL, 'appl', 'gui ');
   std::string text = "flip.Root root=";

   test_parsing_error (document, text, 1, 14);
}



/*
==============================================================================
Name : transform_whitespaces
==============================================================================
*/

std::string TestUtml::transform_whitespaces (const std::string & str)
{
   std::string ret;

   bool ws_flag = false;

   for (char c : str)
   {
      bool sub_ws_flag = false;
      sub_ws_flag |= c == ' ';
      sub_ws_flag |= c == '\t';
      sub_ws_flag |= c == '\r';
      sub_ws_flag |= c == '\n';

      if (sub_ws_flag)
      {
         if (!ws_flag) ret += ' ';
      }
      else
      {
         ret += c;
      }

      ws_flag = sub_ws_flag;
   }

   return ret;
}



/*
==============================================================================
Name : contains
==============================================================================
*/

bool  TestUtml::contains (const std::string & text, const std::string & pattern)
{
   return text.find (pattern) != std::string::npos;
}



/*
==============================================================================
Name : read
==============================================================================
*/

void  TestUtml::read (DocumentBase & document, const std::string & text)
{
   std::vector <uint8_t> data (text.begin (), text.end ());
   DataProviderMemory provider (data);

   BackEndIR backend = Utml::read (provider, document.data_model ());

   document.read (backend);
}



/*
==============================================================================
Name : test_parsing_error
==============================================================================
*/

void  TestUtml::test_parsing_error (DocumentBase & document, const std::string & text, size_t line, size_t column)
{
   bool throw_flag = false;

   try
   {
      read (document, text);
   }
   catch (const Utml::Error & e)
   {
      //e.trace ();
      flip_TEST (e.line == line);
      flip_TEST (e.column == column);
      throw_flag = true;
   }

   flip_TEST (throw_flag);
}



}  // namespace flip



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

