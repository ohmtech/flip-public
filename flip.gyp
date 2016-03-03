##############################################################################
#
#     flip.gyp
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults' : {

      'xcode_settings': {
         'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
         'USE_HEADERMAP': 'NO',
      },
   },

   'includes': [
      'test/test.gypi',
   ]
}