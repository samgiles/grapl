import os
import platform
import sys
import re
import json

try:
    import multiprocessing.synchronize
    gyp_parallel_support = True
except ImportError:
    gyp_parallel_support = False

def find_source_files(directory, regex):
    matches = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in filter(regex.match, filenames):
            matches.append(os.path.join(root, filename))
    return matches


def find_cxx_source_files(directory):
    return find_source_files(directory, re.compile('.*\.c((c?)|(pp)?)?$'))

def host_arch():
    machine = platform.machine()
    if machine == 'i386':   return 'ia32'
    if machine == 'x86_64': return 'x64'
    if machine.startswith('arm'): return 'arm'
    if machine.startswith('mips'): return 'mips'

    return machine

def add_additional_gyp_args(args):
    if not any(a.startswith('-Dhost_arch=') for a in args):
        args.append('-Dhost_arch=%s' % host_arch())

    if not any(a.startswith('-Dtarget_arch=') for a in args):
        args.append('-Dtarget_arch=%s' % host_arch())

    # Some platforms (OpenBSD for example) don't have multiprocessing.synchronize
    # so gyp must be run with --no-parallel
    if not gyp_parallel_support:
        args.append('--no-parallel')
    return args


class gyp_file:
    def __init__(self, path):
        self._path = path
        self._handle = None
        self._gyp = {}

    def __enter__(self):
        self._handle = open(self._path, 'r+')
        self._gyp = eval(self._handle.read())
        return self

    def __exit__(self, type, value, traceback):
        output = json.dumps(self._gyp, sort_keys=True, indent=2)
        self._handle.seek(0)
        self._handle.write(output)
        self._handle.close()

    def get_target(self, name):
        all_targets = self._gyp['targets']

        targets = filter(lambda tgt: tgt['target_name'] is name, all_targets)

        if len(targets) > 1:
            print("More than one target named %s" % name)
            return Nil
        elif len(targets) < 1:
            return None
        else:
            return targets[0]

    def update_target(self, new_target):
        return self.replace_target(new_target['target_name'], new_target)

    def replace_target(self, name, new_target):
        all_targets = self._gyp['targets']
        index = 0
        while index < len(all_targets):
            target = all_targets[index]
            if target['target_name'] is name:
                target[index] = new_target
                return True
        return False

    def update_or_add_target(self, new_target):
        if not self.update_target(new_target):
            self.add_target(new_target)

    def add_target(self, new_target):
        self._gyp['targets'].append(new_target)
