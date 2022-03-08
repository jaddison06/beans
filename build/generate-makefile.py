import os
import os.path as path
from platform import system

def makefile_item(name: str, dependencies: list[str], commands: list[str]) -> str:
    out = f'{name}:'
    for dep in dependencies: out += f' {dep}'
    for cmd in commands: out += f'\n	{cmd}'
    out += '\n\n'
    return out

def all_with_extension(*exts: str) -> list[str]:
    for ext in exts:
        if not ext.startswith('.'): ext = f'.{ext}'

    out: list[str] = []

    for (dirpath, _, filenames) in os.walk('.'):
        for file in filenames:
            for ext in exts:
                if path.splitext(file)[1] == ext:
                    out.append(f'{dirpath}/{file}')
                    break

    return out

COMPILER = 'g++'
EXECUTABLE = 'beans'
PYTHON = 'python'
CLOC = 'C:/Users/jjadd/Downloads/cloc-1.92.exe'

def fs_util(*commands: str) -> str:
    return f'{PYTHON} build/fs_util.py {" ".join(commands)}'

# name -> list of occurrences -> list of arguments
annotation_list_t = dict[str, list[list[str]]]

def parse_annotations(fname: str) -> annotation_list_t:
    out: annotation_list_t = {}
    with open(fname, 'rt') as fh:
        lines = fh.readlines()
    
    for line in lines:
        if line.startswith('//~'):
            _, name, *args = line.strip().split(' ')
            if not name in out:
                out[name] = []
            out[name].append(args)
    
    return out

def main():
    c_cpp_files = all_with_extension('.c', '.cpp')
    headers = all_with_extension('.h', '.hpp')

    makefile = ''

    objects: list[str] = []
    libs: list[str] = []

    for file in c_cpp_files:
        dirname = 'build/objects/' + path.dirname(file)
        obj_name = 'build/objects/' + path.splitext(file)[0] + '.o'
        header_name = path.splitext(file)[0] + '.hpp'
        dependencies = [file]
        if header_name in headers: dependencies.append(header_name)

        annotations = parse_annotations(file)

        if 'link' in annotations:
            for line in annotations['link']:
                for lib in line:
                    if lib not in libs:
                        libs.append(lib)

        makefile += makefile_item(obj_name, dependencies, [fs_util('mkdir', dirname), f'{COMPILER} -c {file} -o {obj_name}'])
        objects.append(obj_name)
    
    
    libs_str = ' '.join(map(lambda lib: f'-l{lib}', libs))
    
    makefile = makefile_item(
        'all',
        objects,
        [f'{COMPILER} {" ".join(objects)} {libs_str} -o {EXECUTABLE}']
    ) + makefile_item(
        'run',
        ['all'],
        [f'./{EXECUTABLE}']
    ) + makefile_item(
        'makefile',
        [],
        [f'{PYTHON} build/generate-makefile.py']
    ) + makefile_item(
        'clean',
        [],
        [
            fs_util('rmdir', 'build/objects'),
            fs_util('rmfile', EXECUTABLE + '.exe' if system() == 'Windows' else '')
        ]
    ) + makefile_item(
        'cloc',
        [],
        [
            f'{CLOC} . --exclude-list=.cloc_exclude_list.txt'
        ]
    ) + makefile

    if system() == 'Windows':
        # fnames not case-sensitive so makefile target needs to be phony
        makefile = '.PHONY: makefile\n\n' + makefile

    with open('Makefile', 'wt') as fh: fh.write(makefile)
    
if __name__ == '__main__': main()
