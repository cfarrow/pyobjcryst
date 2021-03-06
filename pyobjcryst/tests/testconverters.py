#!/usr/bin/env python
"""Test the converters.

This verifies results from tests built into the _registerconverters module.
"""

import unittest
from pyobjcryst._pyobjcryst import getTestVector, getTestMatrix
import numpy

class TestConverters(unittest.TestCase):

    def testVector(self):
        tv = numpy.array(range(3), dtype=float)
        v = getTestVector()
        self.assertTrue( numpy.array_equal(tv, v) )
        return

    def testMatrix(self):
        tm = numpy.array(range(6), dtype=float).reshape(3,2)
        m = getTestMatrix()
        self.assertTrue( numpy.array_equal(tm, m) )
        return


if __name__ == "__main__":
    unittest.main()
