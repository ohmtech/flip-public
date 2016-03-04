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

   arg_parser.add_argument(
      '-t', '--target',
      help = 'The build target to use'
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
      help = 'Generates Ninja build files.'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : run_ninja
==============================================================================
"""

def run_ninja (args):
   return subprocess.check_call (
      [os.path.join (PATH_FLIP_PROJECTS, 'out', args.configuration, args.target)],
      cwd = os.path.join (PATH_FLIP_PROJECTS, 'out', args.configuration)
   )



"""
==============================================================================
Name : run_osx
==============================================================================
"""

def run_osx (args):
   run_path = os.path.join (PATH_FLIP_PROJECTS, 'build', args.configuration, args.target)

   run_cmd = [
      run_path,
   ]

   os.chdir (os.path.join (PATH_FLIP_PROJECTS, 'build', args.configuration))
   return subprocess.check_call (run_cmd)



"""
==============================================================================
Name : run_win
==============================================================================
"""

def run_win (args):
   run_path = os.path.join (PATH_FLIP_PROJECTS, args.configuration, args.target)

   run_cmd = [
      run_path,
   ]

   os.chdir (os.path.join (PATH_FLIP_PROJECTS, args.configuration))
   return subprocess.check_call (run_cmd)



"""
==============================================================================
Name : run
==============================================================================
"""

def run (args):
   if args.ninja:
      return run_ninja (args)

   elif platform.system () == 'Darwin':
      return run_osx (args)

   elif platform.system () == 'Windows':
      return run_win (args)



##############################################################################

if __name__ == '__main__':
   logging.basicConfig (format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (run (parse_args ()))
   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Run command exited with %d' % error.returncode
      sys.exit(1)
