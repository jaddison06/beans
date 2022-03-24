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



def codegen(grammar: list[Noun]) -> str:
    buf = StringIO()

    print(grammar)

    return buf.getvalue()

GRAMMAR_FILE = 'test_data/grammar.bcmdl'
OUTPUT = 'core/commandline/generated.hpp'

def main():
    grammar = parseGrammar(GRAMMAR_FILE)
    header = codegen(grammar)

    with open(OUTPUT, 'wt') as fh:
        fh.write(header)

if __name__ == '__main__': main()