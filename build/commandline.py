from typing import Callable, NoReturn
import xml.etree.ElementTree as ET
from io import StringIO
from dataclasses import dataclass
import os.path as path

GRAMMAR_FILE = 'test_data/grammar.bcmdl'
HEADER = 'core/commandline/generated.hpp'
IMPL = 'core/commandline/generated.cpp'
NOUN_HEADER_PATH = 'core/commandline/nouns/'

@dataclass
class Attr:
    name: str
    type_: str
    get: bool       # defaults to True
    set_: bool      # defaults to True
    key: str | None # defaults to None

@dataclass
class Param:
    name: str
    type_: str
    optional: bool # defaults to False

@dataclass
class Function:
    name: str

    params: list[Param] # defaults to empty

@dataclass
class Noun:
    name: str
    key: str | None           # defaults to None

    dynamicAttrs: list[str]   # defaults to empty
    attrs: list[Attr]         # defaults to empty
    functions: list[Function] # defaults to empty

def boolParam(param: str) -> bool: return param.lower() in ['y', 'yes', 't', 'true']

def parseGrammar(grammarFile: str) -> list[Noun]:
    out: list[Noun] = []

    root = ET.parse(grammarFile).getroot()

    for noun in root:
        if noun.tag != 'noun': continue
        nounName = noun.attrib['name']
        nounKey = noun.attrib.get('key', None)
        dynamicAttrs: list[str] = []
        attrs: list[Attr] = []
        functions: list[Function] = []
        for member in noun:
            if member.tag == 'dynamicattrs':
                dynamicAttrs.append(member.attrib['name'])
            elif member.tag == 'attr':
                attrName = member.attrib['name']
                type_ = member.attrib['type']
                get = boolParam(member.attrib.get('get', 'true'))
                set_ = boolParam(member.attrib.get('set', 'true'))
                attrKey = member.attrib.get('key', None)
                attrs.append(Attr(attrName, type_, get, set_, attrKey))
            elif member.tag == 'function':
                memberName = member.attrib['name']
                params: list[Param] = []
                for param in member:
                    paramName = param.attrib['name']
                    type_ = param.attrib['type']
                    optional = boolParam(param.attrib.get('optional', 'false'))
                    params.append(Param(paramName, type_, optional))
                functions.append(Function(memberName, params))
        out.append(Noun(nounName, nounKey, dynamicAttrs, attrs, functions))
    
    return out

def error(msg: str) -> NoReturn:
    print(f'\u001b[31m{msg}\u001b[0m')
    exit(-1)

# kinda yucky but it's a utility so who cares
_buf = StringIO()
_indent = 0

def indent():
    global _indent
    _indent += 1

def unindent():
    global _indent
    _indent -= 1

def write(text: str, end: str = '\n'):
    _buf.write(('    ' * _indent) + text + end)

def buildstring(func: Callable[[list[Noun]], None]) -> Callable[[list[Noun]], str]:
    def inner(grammar: list[Noun]):
        global _buf, _indent
        _buf = StringIO()
        _indent = 0
        func(grammar)
        return _buf.getvalue()
    return inner

@buildstring
def header(grammar: list[Noun]):
    write('#pragma once\n\n#include <functional>\n#include<string>\n')

    for noun in grammar:
        if not path.exists(f'{NOUN_HEADER_PATH}{noun.name}.hpp'):
            error(f'No header found for noun {noun.name}!')
        write(f'#include "{NOUN_HEADER_PATH}{noun.name}.hpp"')

    write('\nnamespace beans::commandline {')
    indent()

    write('enum class Noun {')
    indent()
    
    for noun in grammar:
        write(f'{noun.name}', '\n' if noun == grammar[-1] else ',\n')

    unindent()
    write('};\n')


    write('using NounLookup = std::function< void*(Noun, uint32_t) >;\n')

    # we're in the commandline namespace so i reckon we can go with short names
    write('''struct Config {
        NounLookup lookup;
    };\n''')

    write('void Init(Config config);\n')

    write('// If the user uses a shortcut, turn the sequence of keys into a valid one.')
    write('std::string Complete(std::string keys);')
    write('// Execute a command')
    write('void Execute(std::string keys);')

    unindent()
    write('}')

@buildstring
def impl(grammar: list[Noun]):
    write(f'#include "{HEADER}"\n')

    write('namespace beans::commandline {')
    indent()

    write('static Config config;')
    write('void commandline::Init(Config config_) {')
    write('    config = config_;')
    write('}\n')

    write('std::string commandline::Complete(std::string keys) {}')
    write('void commandline::Execute(std::string keys) {}')

    unindent()
    write('}')


def main():
    grammar = parseGrammar(GRAMMAR_FILE)

    with open(HEADER, 'wt') as fh:
        fh.write(header(grammar))
    with open(IMPL, 'wt') as fh:
        fh.write(impl(grammar))

if __name__ == '__main__': main()