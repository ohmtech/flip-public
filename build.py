#!/usr/bin/env python
#
#     build.py
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

import argparse
import fileinput
import logging
import os
import platform
import subprocess
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_FLIP = os.path.abspath (os.path.dirname (__file__))
PATH_FLIP_PROJECTS = os.path.join (PATH_FLIP, 'projects')



"""
==============================================================================
Name : parse_args
==============================================================================
"""

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

   arg_parser.add_argument(
      '-c', '--configuration',
      default = 'Release',
      choices = ['Debug', 'Release'],
      help = 'The build configuration to use. Defaults to Release'
   )

   if platform.system () == 'Windows':
      arg_parser.add_argument(
         '-p', '--platform',
         default = 'Win32',
         choices = ['Win32', 'x64'],
         help = 'The build platform to use. Defaults to Win32'
      )

   arg_parser.add_argument (
      '-q', '--quiet',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.ERROR,
      help = 'Provides less output.'
   )

   arg_parser.add_argument (
      '-v', '--verbose',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.DEBUG,
      help = 'Provides more output.'
   )

   arg_parser.add_argument (
      '-n', '--ninja',
      action = 'store_true',
      help = 'Builds using Ninja.'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : build_ninja
==============================================================================
"""

def build_ninja (args):
   cmd = 'ninja -C %s ' % os.path.join (PATH_FLIP_PROJECTS, 'out', args.configuration)

   if (platform.system () == 'Darwin'):
      cmd += '&& install_name_tool -change '
      cmd += '/usr/local/lib/libflip_dll_cpp_entity_strict_type.dylib '
      cmd += '@loader_path/libflip_dll_cpp_entity_strict_type.dylib '
      cmd += '%s ' % os.path.join (PATH_FLIP_PROJECTS, 'out', args.configuration, 'regress_flip_dll')

   return subprocess.check_call (cmd, shell = True)



"""
==============================================================================
Name : build_osx
==============================================================================
"""

def build_osx (args):
   conf_dir = os.path.join (PATH_FLIP_PROJECTS, 'build', args.configuration)

   if not os.path.exists (conf_dir):
      os.makedirs (conf_dir)

   cmd = '/Applications/Xcode.app/Contents/Developer/usr/bin/xcodebuild '
   cmd += '-project %s ' % os.path.join (PATH_FLIP_PROJECTS, 'flip.xcodeproj')
   cmd += '-configuration %s ' % args.configuration
   cmd += '-alltargets '
   cmd += '-parallelizeTargets '
   cmd += 'SYMROOT=%s ' % os.path.join (PATH_FLIP_PROJECTS, 'build')

   return subprocess.check_call (cmd, shell = True)



"""
==============================================================================
Name : build_win
==============================================================================
"""

def build_win (args):
   msbuild_path = os.getenv ('PROGRAMFILES(X86)') + '/MSBuild/12.0/Bin/MSBuild.exe'

   if not os.path.exists (msbuild_path):
      msbuild_path = os.getenv ('PROGRAMFILES(X86)') + '/MSBuild/14.0/Bin/MSBuild.exe'

   if args.target:
         msbuild_cmd = [
         msbuild_path,
         os.path.join (PATH_FLIP_PROJECTS, 'flip.sln'),
         '/property:Configuration=%s' % args.configuration,
         '/property:Platform=%s' % args.platform,
         '/target:%s' % args.target,
         '/verbosity:minimal',
         '/maxcpucount',
      ]

   else:
      msbuild_cmd = [
         msbuild_path,
         os.path.join (PATH_FLIP_PROJECTS, 'flip.sln'),
         '/property:Configuration=%s' % args.configuration,
         '/property:Platform=%s' % args.platform,
         '/verbosity:minimal',
         '/maxcpucount',
      ]

   return subprocess.check_call (msbuild_cmd)


"""
==============================================================================
Name : build
==============================================================================
"""

def build (args):
   if args.ninja:
      return build_ninja (args)

   elif platform.system () == 'Darwin':
      return build_osx (args)

   elif platform.system () == 'Windows':
      return build_win (args)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (build (parse_args ()))
   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Build command exited with %d' % error.returncode
      sys.exit(1)
