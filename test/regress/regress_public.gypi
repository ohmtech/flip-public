##############################################################################
#
#     regress_public.gypi
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets': [

      {
         'target_name': 'regress',
         'type': 'executable',

         'xcode_settings': {
            'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
            'OTHER_CFLAGS': [
               '-fvisibility=default',
            ],
         },

         'defines': [
            'flip_FATAL_MODE=flip_FATAL_MODE_THROW',
            'flip_SPECS_CHECK_FLAG',
            'flip_TEST_REGRESS_FLAG',
         ],

         'include_dirs': [
            '../../include',
         ],

         'includes' : [
            'src.gypi',
         ],

         'msvs_settings': {
            'VCLinkerTool': {
               'AdditionalDependencies': [
                  '../../lib/windows/Visual Studio 2013/Win32/flip.lib',
                  '../../lib/windows/Visual Studio 2013/x64/flip.lib',
               ],
            },
         },

         'conditions': [
            ['OS=="mac"', {
               'link_settings': {
                  'libraries': [
                     '../../lib/macos/libflip.a',
                  ],
               },
            }],
         ],
      },
   ]
}
