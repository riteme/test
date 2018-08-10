#!/usr/bin/python
# vim: set fileencoding=utf-8
import clang.cindex
import asciitree # must be version 0.2
import sys

def node_children(node):
    return [c for c in node.get_children() if c.location.file and c.location.file.name == sys.argv[1]]

def print_node(node):
    text = node.spelling or node.displayname
    kind = str(node.kind)[str(node.kind).index('.')+1:]
    return '[{}:{}]-[{}:{}] {} {}'.format(
        node.extent.start.line, node.extent.start.column,
        node.extent.end.line, node.extent.end.column,
        kind, text,
    )

if len(sys.argv) != 2:
    print("Usage: dump_ast.py [header file name]")
    sys.exit()

clang.cindex.Config.set_library_file('/usr/lib/llvm-6.0/lib/libclang-6.0.so.1')
index = clang.cindex.Index.create()
translation_unit = index.parse(
    sys.argv[1],
    ['-fsyntax-only', '-x', 'c++', '-std=c++11', '-D__CODE_GENERATOR__'],
    options=clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
)

print(asciitree.draw_tree(translation_unit.cursor, node_children, print_node))
