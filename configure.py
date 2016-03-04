#!/usr/bin/env python
#
#     configure.py
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

import argparse
import fileinput
import gyp
import logging
import os
import platform
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_FLIP = os.path.dirname (__file__)
PATH_FLIP_PROJECTS = os.path.join (PATH_FLIP, 'projects')



"""
==============================================================================
Name : parse_args
==============================================================================
"""

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

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
      help = 'Generates Ninja build files.'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : process
==============================================================================
"""

def process (args):
   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % PATH_FLIP_PROJECTS
   ]

   if args.ninja:
      gyp_args += ['--format', 'ninja']
      os.environ.update({'CC': 'clang', 'CXX': 'clang++'})

   return gyp.main (gyp_args + ['flip.gyp'])



"""
==============================================================================
Name : post_process_xcode
==============================================================================
"""

def post_process_xcode (args):
   file = os.path.join (PATH_FLIP_PROJECTS, 'flip.xcodeproj', 'project.pbxproj')

   for line in fileinput.input (file, inplace = 1):
      print line,

      if 'BuildIndependentTargetsInParallel' in line:
         print '\t\t\t\tLastUpgradeCheck = 1000;'


"""
==============================================================================
Name : post_process
==============================================================================
"""

def post_process (args):
   if platform.system () == 'Darwin':
      if not args.ninja:
         post_process_xcode (args)



"""
==============================================================================
Name : configure
==============================================================================
"""

def configure (args):
   process (args)
   post_process (args)



##############################################################################

if __name__ == '__main__':
   sys.exit (configure (parse_args ()))
