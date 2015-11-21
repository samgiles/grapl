import os
import platform
import sys
import re
import ast
import pprint

try:
    import multiprocessing.synchronize
    gyp_parallel_support = True
except ImportError:
    gyp_parallel_support = False

def find_files(directory, regex):
    matches = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in filter(regex.match, filenames):
            matches.append(os.path.join(root, filename))
    return matches

def find_cxx_source_files(directory):
    return find_files(directory, re.compile('.*\.c((c?)|(pp)?)?$'))

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
    def __init__(self, path, as_new=False, top_comment=None):
        self._path = path
        self._handle = None
        self._gyp = {}
        self._as_new = as_new
        self._top_comment = top_comment

    def __enter__(self):
        self._handle = open(self._path, 'r+' if not self._as_new else 'w+')
        if not self._as_new:
            try:
                self._gyp = ast.literal_eval(self._handle.read())
            except SyntaxError as e:
                self._handle.close()
                raise e

        return self

    def __exit__(self, type, value, traceback):
        self._handle.seek(0)
        self._handle.truncate()
        if self._top_comment is not None:
            self._handle.write("# %s\n" % self._top_comment)
        self._handle.write(pformat(self._gyp))

        self._handle.close()

    def get_target(self, name):
        all_targets = self._gyp['targets']
        targets = filter(lambda tgt: tgt['target_name'] == name, all_targets)

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
        if 'targets' not in self._gyp:
            return False

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
        if 'targets' not in self._gyp:
            self._gyp['targets'] = []

        self._gyp['targets'].append(new_target)


def pformat(obj, indent=2):
    formatted = _pformat(obj, indent=indent)
    return formatted.rstrip(',\n')

def _pformat(obj, indent=2, current_indent_level=0, maybe_newline_first=False):
    builder = ""
    def add_nl(builder):
        return "\n" if not builder.endswith("\n") else ""

    if isinstance(obj, list):
        if maybe_newline_first:
            builder += add_nl(builder)
            current_indent_level -= indent
            builder += " " * current_indent_level

        current_indent_level += indent
        builder += "[\n"
        for val in obj:
            builder += " " * current_indent_level
            builder += _pformat(val, indent=indent, current_indent_level=current_indent_level)
            builder += add_nl(builder)
        current_indent_level -= indent
        builder += " " * current_indent_level
        builder += "],\n"
        return builder
    elif isinstance(obj, dict):
        if maybe_newline_first:
            builder += add_nl(builder)
            current_indent_level -= indent
            builder += " " * current_indent_level
        builder += "{\n"
        current_indent_level += indent
        for (k,v) in obj.iteritems():
            builder += " " * current_indent_level
            builder += pprint.pformat(k) + ": "
            builder += _pformat(v, indent=indent,
                    current_indent_level=current_indent_level+indent,
                    maybe_newline_first=True)
            builder += add_nl(builder)
        current_indent_level -= indent
        builder += " " * current_indent_level
        builder += "},\n"
        return builder
    else:
        builder += pprint.pformat(obj, indent=0) + ","
        return builder
