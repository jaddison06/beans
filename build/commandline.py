import xml.etree.ElementTree as ET
from io import StringIO
from dataclasses import dataclass

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
    key: str | None # defaults to None

    attrs: list[Attr] # defaults to empty

def parseGrammar(grammarFile: str) -> list[Noun]: ...


def codegen(grammar: list[Noun]) -> str:
    buf = StringIO()



    return buf.getvalue()

GRAMMAR_FILE = 'test_data/grammar.bcmdl'
OUTPUT = 'core/commandline/generated.hpp'

def main():
    grammar = parseGrammar(GRAMMAR_FILE)
    header = codegen(grammar)

    with open(OUTPUT, 'wt') as fh:
        fh.write(header)

if __name__ == '__main__': main()