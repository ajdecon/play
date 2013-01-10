import unittest
import numpy

# Fortran module dsum.so, compiled with f2py -c dsum.pyf dsum.f
from dsum import dsum

class TestDsum(unittest.TestCase):

    def testAddAllIntegers(self):
        in_tuple = (1,2,3,4,5)
        self.failUnless(dsum(in_tuple)==15.0)

    def testAddTwoIntegers(self):
        in_tuple = (1,2,3,4,5)
        self.failUnless(dsum(in_tuple,2)==3.0)

    def testAddAllFloats(self):
        in_tuple = (1.5,2.5,3.5,4.5,5.5)
        self.failUnless(dsum(in_tuple)==17.5)

    def testAddThreeFloats(self):
        in_tuple = (1.5,2.5,3.5,4.5,5.5)
        self.failUnless(dsum(in_tuple,3)==7.5)

    def testAddNumpyArray(self):
        in_array = numpy.array([1,2,3,4,5])
        self.failUnless(dsum(in_array)==15.0)

    def testAddPartialNumpyArray(self):
        in_array = numpy.array([1,2,3,4,5])
        self.failUnless(dsum(in_array,2)==3.0)

def main():
    unittest.main()

if __name__ == '__main__':
    main()
