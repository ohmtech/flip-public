##############################################################################
#
#     win.gypi
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults': {
      'configurations': {

         ##### Debug
         'Debug': {
            'msvs_configuration_platform': 'Win32',
            'defines': [
               '_SCL_SECURE_NO_WARNINGS',
            ],
            'msvs_settings': {
               'VCCLCompilerTool': {
                  'Optimization': 0, # Disabled (/Od)
                  'RuntimeLibrary': 3, # Multi-threaded Debug DLL (/MDd)
               },
            },
         },

         ##### Release
         'Release': {
            'msvs_configuration_platform': 'Win32',
            'msvs_settings': {
               'VCCLCompilerTool': {
                  'Optimization': 2, # Maximize Speed (/O2)
                  'RuntimeLibrary': 2, # Multi-threaded DLL (/MD)
               },
            },
         },
      },

      'conditions': [
         ['OS=="win"', {
            'configurations': {
               ##### Debug_x64
               'Debug_x64': {
                  'msvs_configuration_platform': 'x64',
                  'defines': [
                     '_SCL_SECURE_NO_WARNINGS',
                  ],
                  'msvs_settings': {
                     'VCCLCompilerTool': {
                        'Optimization': 0, # Disabled (/Od)
                        'RuntimeLibrary': 3, # Multi-threaded Debug DLL (/MDd)
                     },
                  },
               },

               ##### Release_x64
               'Release_x64': {
                  'msvs_configuration_platform': 'x64',
                  'msvs_settings': {
                     'VCCLCompilerTool': {
                        'Optimization': 2, # Maximize Speed (/O2)
                        'RuntimeLibrary': 2, # Multi-threaded DLL (/MD)
                     },
                  },
               },
            },
         }],
      ],

      'msvs_settings': {
         'VCCLCompilerTool': {
            'ExceptionHandling': '1', # Yes (/EHsc)
            'WarningLevel': '4',
            'WarnAsError': 'true',
            'AdditionalOptions': ['/Wall'],
            'MultiProcessorCompilation': 'true',
         },

         'VCLinkerTool': {
            'GenerateDebugInformation': 'true',
            'target_conditions': [
               ['_type=="executable"', {
                  'SubSystem': 1,  # /SUBSYSTEM:CONSOLE
               }],
            ],
            'AdditionalDependencies': [
               'ws2_32.lib',
            ],
         },
      },

      # documented in Flip Configuration Guide, MSVC Warnings Notes
      'msvs_disabled_warnings': [
         # C4251: https://msdn.microsoft.com/en-us/library/esew7y1w.aspx
         4251,

         # C4265: https://msdn.microsoft.com/en-us/library/wzxffy8c.aspx
         4265,

         # C4350: https://msdn.microsoft.com/en-us/library/0eestyah.aspx
         4350,

         # C4355: https://msdn.microsoft.com/en-us/library/3c594ae3.aspx
         4355,

         # C4365: https://msdn.microsoft.com/en-us/library/ms173683.aspx
         4365,

         # C4435: https://msdn.microsoft.com/en-us/library/jj155806.aspx
         4435,

         # C4514: https://msdn.microsoft.com/en-us/library/cw9x3tcf.aspx
         4514,

         # C4702: https://msdn.microsoft.com/en-us/library/c26da40e.aspx
         4702,

         # C4571: https://msdn.microsoft.com/en-us/library/55s8esw4.aspx
         4571,

         # C4640: https://msdn.microsoft.com/en-us/library/4f5c8560.aspx
         4640,

         # C4710: https://msdn.microsoft.com/en-us/library/yd3056cz.aspx
         4710,

         # C4711: https://msdn.microsoft.com/en-us/library/k402bt7y.aspx
         4711,

         # C4820: https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
         4820,
      ],
   },
}
