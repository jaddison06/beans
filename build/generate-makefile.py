import os
import os.path as path
from platform import system

def makefile_item(name: str, dependencies: list[str], commands: list[str]) -> str:
    out = f'{name}:'
    for dep in dependencies: out += f' {dep}'
    for cmd in commands: out += f'\n	{cmd}'
    out += '\n\n'
    return out

def all_with_extension(ext: str) -> list[str]:
    if not ext.startswith('.'): ext = f'.{ext}'

    out: list[str] = []

    for (dirpath, _, filenames) in os.walk('.'):
        for file in filenames:
            if path.splitext(file)[1] == ext: out.append(f'{dirpath}/{file}')

    return out

COMPILER = 'g++'
EXECUTABLE = 'beans'
PYTHON = 'python'

def fs_util(*commands: str) -> str:
    return f'{PYTHON} build/fs_util.py {" ".join(commands)}'

def main():
    # todo: header dependencies are unhappy - probs windows paths

    cpp_files = all_with_extension('.cpp')
    headers = all_with_extension('.hpp')

    makefile = ''

    objects: list[str] = []

    for file in cpp_files:
        dirname = 'build/objects/' + path.dirname(file)
        obj_name = 'build/objects/' + path.splitext(file)[0] + '.o'
        header_name = path.splitext(file)[0] + '.h'
        dependencies = [file]
        if header_name in headers: dependencies.append(header_name)
        makefile += makefile_item(obj_name, dependencies, [fs_util('mkdir', dirname), f'{COMPILER} -c {file} -o {obj_name}'])
        objects.append(obj_name)
    
    makefile = makefile_item(
        'all',
        objects,
        [f'{COMPILER} {" ".join(objects)} -o {EXECUTABLE}']
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
    ) + makefile

    if system() == 'Windows':
        # fnames not case-sensitive so makefile target needs to be phony
        makefile = '.PHONY: makefile\n\n' + makefile

    with open('Makefile', 'wt') as fh: fh.write(makefile)
    
if __name__ == '__main__': main()
