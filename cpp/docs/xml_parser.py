#!/usr/bin/env python

import os
import xml.etree.ElementTree as ET


def access(roots, *args):
    if not type(roots) is list:
        return access([roots], *args)
    if not args:
        return roots
    new_roots = []
    for root in roots:
        for child in root:
            if child.tag == args[0]:
                new_roots += [child]
    return access(new_roots, *args[1:])


class Document:
    def __init__(self, fname, para, items):
        self.fname = fname
        self.para = para
        self.items = items


def parse_class(class_name, filename_to_docs):
    path = 'xml/%s' % class_name
    root = ET.parse(path).getroot()
    mems = access(root, 'compounddef', 'sectiondef', 'memberdef')
    publics = [c for c in mems if c.attrib['prot'] == 'public']
    if all([c.text != 'main' for c in access(publics, 'name')]):
        for fnode in publics:
            fname = access(fnode, 'definition')
            argsstring = access(fnode, 'argsstring')
            para = access(fnode, 'detaileddescription')
            pitem = access(para, 'para', 'parameterlist', 'parameteritem')
            location = access(fnode, 'location')[0].attrib['file']
            basename = location.split('/')[-1]
            items = []
            for p in pitem:
                pname = access(p, 'parameternamelist', 'parametername')[0].text
                pdesc = access(p, 'parameterdescription', 'para')[0].text
                items += ["`%s` : %s" % (pname, pdesc)]
            doc = Document(fname[0].text, argsstring[0].text, items)
            if basename in filename_to_docs:
                filename_to_docs[basename] += [doc]
            else:
                filename_to_docs[basename] = [doc]


filename_to_docs = {}


for fname in os.listdir('xml'):
    parse_class(fname, filename_to_docs)

for filename, items in filename_to_docs.items():
    print(filename)
    for doc in items:
        print(doc.fname + (doc.para if doc.para else ""))
        print(doc.items)
