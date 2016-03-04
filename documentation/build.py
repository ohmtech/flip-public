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
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

OTDGEN = '/usr/local/bin/otdgen'
PATH_FLIP_DOCUMENTATION = os.path.dirname (__file__)
PATH_FLIP_DOC_ROOT = os.path.join (PATH_FLIP_DOCUMENTATION, 'src', 'library.otd')
PATH_FLIP_GITHUB = os.path.join (PATH_FLIP_DOCUMENTATION, 'markdown')
PATH_FLIP_HTML = os.path.join (PATH_FLIP_DOCUMENTATION, 'html')
PATH_FLIP_DOCSET = os.path.join (PATH_FLIP_DOCUMENTATION, 'docset')



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

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : process
==============================================================================
"""

def process ():
   print 'Generating github.'
   os.system (
      '%s --format=github --output=%s %s' % (OTDGEN, PATH_FLIP_GITHUB, PATH_FLIP_DOC_ROOT)
   )
   print 'Generating html.'
   os.system (
      '%s --format=html --output=%s %s' % (OTDGEN, PATH_FLIP_HTML, PATH_FLIP_DOC_ROOT)
   )
   print 'Generating docset.'
   os.system (
      '%s --format=docset --output=%s %s' % (OTDGEN, PATH_FLIP_DOCSET, PATH_FLIP_DOC_ROOT)
   )



"""
==============================================================================
Name : build
==============================================================================
"""

def build (args):
   process ()



##############################################################################

if __name__ == '__main__':
   sys.exit (build (parse_args ()))
