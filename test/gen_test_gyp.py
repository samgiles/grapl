#!/usr/bin/env python

import os
import platform
import sys
import fnmatch
import re


root_dir = os.path.join(os.path.dirname(__file__), '..')
grapl_root = os.path.normpath(root_dir)
output_dir = os.path.join(os.path.abspath(grapl_root), 'out')

this_script_dir = os.path.dirname(__file__)
test_root = os.path.normpath(this_script_dir)


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


test_gypfile = os.path.join(test_root, 'tests.gyp')

def generate_gyp(directory):
    with gyputil.gyp_file(test_gypfile, as_new=True, top_comment="!!!!!! Do not edit this file manually, it is automatically generated by gen_test_gyp.py") as g:
        tests = gyputil.find_files(directory, re.compile('^.*Test\.c(pp|c)$'))

        g._gyp['includes'] = [ 'test_common.gypi' ]

        for test in tests:
            print "Adding target for %s\n" % test
            target = {
                    'target_name': os.path.splitext(os.path.basename(test))[0],
                    'sources': [ os.path.join(*(test.split(os.path.sep)[1:])) ],
                    'type': 'executable',
                    "dependencies": [
                        "libgrapl",
                        "external/glfw-3.1.2/glfw.gyp:glfw"
                        ],
                    "include_dirs": [
                        "../test",
                        "../lib",
                        "../external/glfw-3.1.2/include"
                        ],
                    "includes": [
                        "../common.gypi"
                        ]
                    }
            g.add_target(target)
print test_root
generate_gyp(os.path.join(test_root, 'src'))
