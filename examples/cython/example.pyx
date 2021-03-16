cimport eFLL.Fuzzy as Fuzzy

from cython.operator cimport dereference as deref

cdef class cFuzzySet:
    cdef Fuzzy.FuzzySet * thisptr
    def __cinit__(self):
        self.thisptr = new Fuzzy.FuzzySet()
    def __dealloc__(self):
        if(self.thisptr):
            del self.thisptr
            self.thisptr = NULL
    def getPointA(self):
        return deref(self.thisptr).getPointA()
    def getPointB(self):
        return deref(self.thisptr).getPointB()
    def getPointC(self):
        return deref(self.thisptr).getPointC()
    def getPointD(self):
        return deref(self.thisptr).getPointD()
    def getPoints(self):
        return (
            deref(self.thisptr).getPointA(),
            deref(self.thisptr).getPointB(),
            deref(self.thisptr).getPointC(),
            deref(self.thisptr).getPointD()
        )
    def calculatePertinence(self, crispValue):
        return deref(self.thisptr).calculatePertinence(crispValue)
    def setPertinence(self, pertinence):
        deref(self.thisptr).setPertinence(pertinence)
    def getPertinence(self):
        return deref(self.thisptr).getPertinence()
    def reset(self):
        deref(self.thisptr).reset()

cdef class cFuzzyComposition:
    cdef Fuzzy.FuzzyComposition * thisptr
    def __cinit__(self):
        self.thisptr = new Fuzzy.FuzzyComposition()
    def __dealloc__(self):
        if(self.thisptr):
            del self.thisptr
            self.thisptr = NULL
    def addPoint(self, point, pertinence):
        return deref(self.thisptr).addPoint(point, pertinence)
    def checkPoint(self, point, pertinence):
        return deref(self.thisptr).checkPoint(point, pertinence)
    def build(self):
        return deref(self.thisptr).build()
    def calculate(self):
        return deref(self.thisptr).calculate()
    def empty(self):
        return deref(self.thisptr).empty()
    def countPoints(self):
        return deref(self.thisptr).countPoints()
