from sys import argv
import os.path as path
import os
from shutil import rmtree, copytree

def main():
    match argv[1]:
        case 'rmfile':
            if path.exists(argv[2]):
                os.remove(argv[2])
        case 'rmdir':
            if path.exists(argv[2]):
                rmtree(argv[2])
        case 'mkdir':
            if not path.exists(argv[2]):
                os.makedirs(argv[2])
        case 'copydir':
            if path.exists(argv[3]): rmtree(argv[3])
            copytree(argv[2], argv[3])

if __name__ == '__main__': main()