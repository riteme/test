import os
import ycm_core

flags = ['-Werror',
         '-Wall',
         '-Wno-c++98-compat',
         '-std=c++1z',
         '-x',
         'c++',
         '-DUSE_CLANG_COMPLETER',
         '-I/usr/include',
         '-I/usr/include/*',
         '-I/usr/include/python2.7',
         '-I/usr/include/c++/v1',
         '-I/usr/include/c++/*',
         '-I/usr/include/x86_64-linux-gnu',
         '-I/usr/bin/../lib/gcc/x86_64-linux-gnu/4.9/include',
         '-I.', '-Iinclude', '-Iincludes'
         ]


def FlagsForFile(filename):
    return {
        'flags': flags,
        'do_cache': True
    }
