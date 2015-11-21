#!/usr/bin/env python

import os
import platform
import sys
import fnmatch
import re

# Preamble: to try and reduce friction set up include of the scripts.  This
# means we don't have to worry about the python path
this_script_dir = os.path.dirname(__file__)
grapl_root = os.path.normpath(this_script_dir)
output_dir = os.path.join(os.path.abspath(grapl_root), 'out')

sys.path.insert(0, os.path.join(grapl_root, 'build', 'gyp', 'pylib'))
sys.path.insert(0, os.path.join(grapl_root, 'build', 'pylib'))

try:
    import gyputil
except ImportError:
    print('Could not use gyputil :(')
    sys.exit(1)

try:
    import gyp
except ImportError:
    print('You need to install gyp in build/gyp first.  See the README.')
    sys.exit(1)


def run_gyp(args):
    retval = gyp.main(args)
    if retval != 0:
        print 'Error running gyp'
        sys.exit(retval)

def update_sources(grapl_gyp):
    with gyputil.gyp_file(grapl_gyp) as g:
        grapl_target = g.get_target('libgrapl')
        grapl_target['sources'] = gyputil.find_cxx_source_files('lib')

if __name__ == '__main__':
    args = sys.argv[1:]

    # GYP bug.
    # On msvs it will crash if it gets an absolute path.
    # On Mac/make it will crash if it doesn't get an absolute path.
    if sys.platform == 'win32':
        grapl_gyp = os.path.join(grapl_root, 'grapl.gyp')
        # we force vs 2010 over 2008 which would otherwise be the default for gyp
        if not os.environ.get('GYP_MSVS_VERSION'):
            os.environ['GYP_MSVS_VERSION'] = '2010'
    else:
        grapl_gyp = os.path.join(os.path.abspath(grapl_root), 'grapl.gyp')

    update_sources(grapl_gyp)

    args = gyputil.add_additional_gyp_args(args)

    args.append('--depth=' + grapl_root)
    args.append(grapl_gyp)

    if sys.platform != 'win32':
        if '-f' not in args:
            args.extend('-f make'.split())
        if 'eclipse' not in args and 'ninja' not in args:
            args.extend(['-Goutput_dir=' + output_dir])
            args.extend(['--generator-output', output_dir])

    gyp_args = list(args)
    print gyp_args
    run_gyp(gyp_args)
