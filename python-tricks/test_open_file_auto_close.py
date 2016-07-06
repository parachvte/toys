# -*- coding: UTF-8 -*-

from __future__ import print_function
import __builtin__
import os
import sys
import time


oldfile = __builtin__.file
oldopen = __builtin__.open

openfiles = set()


class newfile(oldfile):
    def __init__(self, *args):
        self.x = args[0]
        print("### OPENING %s ###" % str(self.x))
        oldfile.__init__(self, *args)
        openfiles.add(self)

    def close(self):
        print("### CLOSING %s ###" % str(self.x))
        oldfile.close(self)
        openfiles.remove(self)


def newopen(*args):
    return newfile(*args)


__builtin__.file = newfile
__builtin__.open = newopen

def printOpenFiles():
    print("### %d OPEN FILES: [%s]" % (len(openfiles), ", ".join(f.x if not f.closed else "FUCK CLOSED" for f in openfiles)))


def test_1():
    with open("input.txt") as f:
        f.read()
    printOpenFiles()


def test_2():
    a = open("input.txt").read()  # will not be closed automatically
    printOpenFiles()


def main():
    test_1()
    printOpenFiles()
    
    test_2()
    printOpenFiles()
        
if __name__ == "__main__":
    sys.exit(main())


