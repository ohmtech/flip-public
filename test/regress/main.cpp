/*****************************************************************************

      main.cpp
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "flip/detail/def.h"
flip_DISABLE_WARNINGS_TEST

//#include  "DebugServerHttp.h"

#include "TestAbstractClass.h"
#include "TestApiDropboxServer.h"
#include "TestArray.h"
#include "TestBackEndBinary.h"
#include "TestBackEndIRDiff.h"
#include "TestBackEndMl.h"
#include "TestBackEndMlCodec.h"
#include "TestCarrierPortDirect.h"
#include "TestClass.h"
/*#include "TestCloudStore.h"*/
#include "TestCodec.h"
#include "TestCollection.h"
#include "TestConsumerTextOut.h"
#include "TestDataConsumerProvider.h"
#include "TestDataModel.h"
#include "TestDataModelClone.h"
#include "TestDntDirect.h"
#include "TestDocument.h"
#include "TestDocumentIO.h"
#include "TestEntity.h"
#include "TestEnum.h"
#include "TestHistory.h"
#include "TestHttpRequestParser.h"
#include "TestHub.h"
#include "TestHubLocal.h"
#include "TestInt.h"
#include "TestKeyFloat.h"
#include "TestKeyRandom.h"
#include "TestLockFreeQueue.h"
#include "TestMessage.h"
#include "TestMold.h"
#include "TestMulticastService.h"
#include "TestNonDefaultCtor.h"
#include "TestObserver.h"
#include "TestOptional.h"
#include "TestRef.h"
#include "TestRefAllocator.h"
#include "TestRepresentative.h"
#include "TestServer.h"
#include "TestServerHttp.h"
#include "TestSignal.h"
#include "TestStreamBin.h"
#include "TestTransaction.h"
#include "TestTransactionStack.h"
#include "TestTransportBase.h"
#include "TestTransportSocket.h"
#include "TestUseCaseCopyPaste.h"
#include "TestUseCaseGhosting.h"
#include "TestUseCaseShared.h"
#include "TestUseCaseSignal.h"
#include "TestUseCaseUndo.h"
#include "TestUtml.h"
#include "TestValidator.h"
#include "TestVariant.h"
#include "TestVector.h"

#include <iostream>



#if defined (_MSC_VER)
   __pragma (warning (disable: 4505))
#endif



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void  playground ();
void  run_test ();
void  run_perf ();



/*
==============================================================================
Name : playground
==============================================================================
*/

void  playground ()
{
   using namespace flip;
}



/*
==============================================================================
Name : run_test
==============================================================================
*/

void  run_test ()
{
#if 1
   using namespace flip;

   std::cout << "Running Regression Tests..." << std::endl;

   std::cout << "   Running TestRef..." << std::endl;

   {
      TestRef test;
      test.run ();
   }

   std::cout << "   Running TestEntity..." << std::endl;

   {
      TestEntity test;
      test.run ();
   }

   std::cout << "   Running TestSignal..." << std::endl;

   {
      TestSignal test;
      test.run ();
   }

   std::cout << "   Running TestRepresentative..." << std::endl;

   {
      TestRepresentative test;
      test.run ();
   }

   std::cout << "   Running TestKeyRandom..." << std::endl;

   {
      TestKeyRandom test;
      test.run ();
   }

   std::cout << "   Running TestKeyFloat..." << std::endl;

   {
      TestKeyFloat test;
      test.run ();
   }

   std::cout << "   Running TestStreamBin..." << std::endl;

   {
      TestStreamBin test;
      test.run ();
   }

   std::cout << "   Running TestDataConsumerProvider..." << std::endl;

   {
      TestDataConsumerProvider test;
      test.run ();
   }

   std::cout << "   Running TestConsumerTextOut..." << std::endl;

   {
      TestConsumerTextOut test;
      test.run ();
   }

   std::cout << "   Running TestLockFreeQueue..." << std::endl;

   {
      TestLockFreeQueue test;
      test.run ();
   }

   std::cout << "   Running TestClass..." << std::endl;

   {
      TestClass test;
      test.run ();
   }

   std::cout << "   Running TestDataModel..." << std::endl;

   {
      TestDataModel test;
      test.run ();
   }

   std::cout << "   Running TestRefAllocator..." << std::endl;

   {
      TestRefAllocator test;
      test.run ();
   }

   std::cout << "   Running TestInt..." << std::endl;

   {
      TestInt test;
      test.run ();
   }

   std::cout << "   Running TestArray..." << std::endl;

   {
      TestArray test;
      test.run ();
   }

   std::cout << "   Running TestCollection..." << std::endl;

   {
      TestCollection test;
      test.run ();
   }

   std::cout << "   Running TestEnum..." << std::endl;

   {
      TestEnum test;
      test.run ();
   }

   std::cout << "   Running TestMessage..." << std::endl;

   {
      TestMessage test;
      test.run ();
   }

   std::cout << "   Running TestVariant..." << std::endl;

   {
      TestVariant test;
      test.run ();
   }

   std::cout << "   Running TestOptional..." << std::endl;

   {
      TestOptional test;
      test.run ();
   }

   std::cout << "   Running TestVector..." << std::endl;

   {
      TestVector test;
      test.run ();
   }

   std::cout << "   Running TestAbstractClass..." << std::endl;

   {
      TestAbstractClass test;
      test.run ();
   }

   std::cout << "   Running TestDataModelClone..." << std::endl;

   {
      TestDataModelClone test;
      test.run ();
   }

   std::cout << "   Running TestDocumentIO..." << std::endl;

   {
      TestDocumentIO test;
      test.run ();
   }

   std::cout << "   Running TestTransaction..." << std::endl;

   {
      TestTransaction test;
      test.run ();
   }

   std::cout << "   Running TestMold..." << std::endl;

   {
      TestMold test;
      test.run ();
   }

   std::cout << "   Running TestBackEndIRDiff..." << std::endl;

   {
      TestBackEndIRDiff test;
      test.run ();
   }

   std::cout << "   Running TestBackEndBinary..." << std::endl;

   {
      TestBackEndBinary test;
      test.run ();
   }

   std::cout << "   Running TestBackEndMlCodec..." << std::endl;

   {
      TestBackEndMlCodec test;
      test.run ();
   }

   std::cout << "   Running TestBackEndMl..." << std::endl;

   {
      TestBackEndMl test;
      test.run ();
   }

   std::cout << "   Running TestDocument..." << std::endl;

   {
      TestDocument test;
      test.run ();
   }

   std::cout << "   Running TestTransactionStack..." << std::endl;

   {
      TestTransactionStack test;
      test.run ();
   }

   std::cout << "   Running TestNonDefaultCtor..." << std::endl;

   {
      TestNonDefaultCtor test;
      test.run ();
   }

   std::cout << "   Running TestHub..." << std::endl;

   {
      TestHub test;
      test.run ();
   }

   std::cout << "   Running TestObserver..." << std::endl;

   {
      TestObserver test;
      test.run ();
   }

   std::cout << "   Running TestValidator..." << std::endl;

   {
      TestValidator test;
      test.run ();
   }

   std::cout << "   Running TestHistory..." << std::endl;

   {
      TestHistory test;
      test.run ();
   }

   std::cout << "   Running TestUseCaseGhosting..." << std::endl;

   {
      TestUseCaseGhosting test;
      test.run ();
   }

   std::cout << "   Running TestUseCaseShared..." << std::endl;

   {
      TestUseCaseShared test;
      test.run ();
   }

   std::cout << "   Running TestUseCaseUndo..." << std::endl;

   {
      TestUseCaseUndo test;
      test.run ();
   }

   std::cout << "   Running TestUseCaseCopyPaste..." << std::endl;

   {
      TestUseCaseCopyPaste test;
      test.run ();
   }

   std::cout << "   Running TestUseCaseSignal..." << std::endl;

   {
      TestUseCaseSignal test;
      test.run ();
   }

   std::cout << "   Running TestCodec..." << std::endl;

   {
      TestCodec test;
      test.run ();
   }

   std::cout << "   Running TestCarrierPortDirect..." << std::endl;

   {
      TestCarrierPortDirect test;
      test.run ();
   }

   std::cout << "   Running TestServer..." << std::endl;

   {
      TestServer test;
      test.run ();
   }

   std::cout << "   Running TestDntDirect..." << std::endl;

   {
      TestDntDirect test;
      test.run ();
   }

   std::cout << "   Running TestTransportBase..." << std::endl;

   {
      TestTransportBase test;
      test.run ();
   }

   std::cout << "   Running TestHubLocal..." << std::endl;

   {
      TestHubLocal test;
      test.run ();
   }

   std::cout << "   Running TestHttpRequestParser..." << std::endl;

   {
      TestHttpRequestParser test;
      test.run ();
   }

   std::cout << "   Running TestUtml..." << std::endl;

   {
      TestUtml test;
      test.run ();
   }

   std::cout << "   Running TestTransportSocket..." << std::endl;

   {
      TestTransportSocket test;
      test.run ();
   }


   std::cout << "   Running TestMulticastService..." << std::endl;

   {
      TestMulticastService test;
      test.run ();
   }

   std::cout << "   Running TestServerHttp..." << std::endl;

   {
      TestServerHttp test;
      test.run ();
   }

#if defined (flip_ENABLE_CLOUD_STORE)
   std::cout << "   Running TestApiDropboxServer..." << std::endl;

   {
      TestApiDropboxServer test;
      test.run ();
   }
#endif

#if defined (flip_ENABLE_CLOUD_STORE)
   /*std::cout << "   Running TestCloudStore..." << std::endl;

   {
      TestCloudStore test;
      test.run ();
   }*/
#endif

   std::cout << "OK" << std::endl;
#endif
}



/*
==============================================================================
Name : main
==============================================================================
*/

int   main (int /* argc */, const char * /* argv */[])
{
   playground ();

   using namespace flip;

#if 0
   DebugServerHttp debug;
   debug.run ();
#endif

   run_test ();

   return 0;
}
