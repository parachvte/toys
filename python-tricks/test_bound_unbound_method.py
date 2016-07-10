# -*- coding: UTF-8 -*-
"""
Understanding the doc in python reference:

When a user-defined method object is created by retrieving another method object from a class or instance, the behaviour is the same as for a function object, except that the __func__ attribute of the new instance is not the original method object but its __func__ attribute.
"""

from __future__ import print_function

import sys

class Foo():

    def foo(self):
        pass


def main():

    foo = Foo()

    print(Foo.foo)
    print(Foo.__dict__["foo"])
    print(foo.foo)

    Foo.bar = Foo.foo

    print(Foo.bar)
    print(Foo.__dict__["bar"])
    print(foo.bar)
                

if __name__ == "__main__":
    sys.exit(main())

