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
    def calculatePertinence(self, float crispValue):
        return deref(self.thisptr).calculatePertinence(crispValue)
    def setPertinence(self, float pertinence):
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
    def addPoint(self, float point, float pertinence):
        return deref(self.thisptr).addPoint(point, pertinence)
    def checkPoint(self, float point, float pertinence):
        return deref(self.thisptr).checkPoint(point, pertinence)
    def build(self):
        return deref(self.thisptr).build()
    def calculate(self):
        return deref(self.thisptr).calculate()
    def empty(self):
        return deref(self.thisptr).empty()
    def countPoints(self):
        return deref(self.thisptr).countPoints()

cdef class cFuzzyRuleAntecedent:
    cdef Fuzzy.FuzzyRuleAntecedent * thisptr
    def __cinit__(self):
        self.thisptr = new Fuzzy.FuzzyRuleAntecedent()
    def __dealloc__(self):
        if(self.thisptr):
            del self.thisptr
            self.thisptr = NULL
    def joinSingle(self, cFuzzySet fuzzySet):
        return deref(self.thisptr).joinSingle(fuzzySet.thisptr)
    def joinWithAND(self, cFuzzySet fuzzySet1, cFuzzySet fuzzySet2):
        return deref(self.thisptr).joinWithAND(fuzzySet1.thisptr, fuzzySet2.thisptr)
    def joinWithOR(self, cFuzzySet fuzzySet1, cFuzzySet fuzzySet2):
        return deref(self.thisptr).joinWithOR(fuzzySet1.thisptr, fuzzySet2.thisptr)
    def joinWithAND(self, cFuzzySet fuzzySet, cFuzzyRuleAntecedent fuzzyRuleAntecedent):
        return deref(self.thisptr).joinWithAND(fuzzySet.thisptr, fuzzyRuleAntecedent.thisptr)
    def joinWithAND(self, cFuzzyRuleAntecedent fuzzyRuleAntecedent, cFuzzySet fuzzySet):
        return deref(self.thisptr).joinWithAND(fuzzyRuleAntecedent.thisptr, fuzzySet.thisptr)
    def joinWithOR(self, cFuzzySet fuzzySet, cFuzzyRuleAntecedent fuzzyRuleAntecedent):
        return deref(self.thisptr).joinWithOR(fuzzySet.thisptr, fuzzyRuleAntecedent.thisptr)
    def joinWithOR(self, cFuzzyRuleAntecedent fuzzyRuleAntecedent, cFuzzySet fuzzySet):
        return deref(self.thisptr).joinWithOR(fuzzyRuleAntecedent.thisptr, fuzzySet.thisptr)
    def joinWithAND(self, cFuzzyRuleAntecedent fuzzyRuleAntecedent1, cFuzzyRuleAntecedent fuzzyRuleAntecedent2):
        return deref(self.thisptr).joinWithAND(fuzzyRuleAntecedent1.thisptr, fuzzyRuleAntecedent2.thisptr)
    def joinWithOR(self, cFuzzyRuleAntecedent fuzzyRuleAntecedent1, cFuzzyRuleAntecedent fuzzyRuleAntecedent2):
        return deref(self.thisptr).joinWithOR(fuzzyRuleAntecedent1.thisptr, fuzzyRuleAntecedent2.thisptr)

cdef class cFuzzyRuleConsequent:
    cdef Fuzzy.FuzzyRuleConsequent * thisptr
    def __cinit__(self):
        self.thisptr = new Fuzzy.FuzzyRuleConsequent()
    def __dealloc__(self):
        if(self.thisptr):
            del self.thisptr
            self.thisptr = NULL
    def addOutput(self, cFuzzySet fuzzySet):
        return deref(self.thisptr).addOutput(fuzzySet.thisptr)
    def evaluate(self, float power):
        return deref(self.thisptr).evaluate(power)

cdef class cFuzzyRule:
    cdef Fuzzy.FuzzyRule * thisptr
    def __cinit__(self):
        self.thisptr = new Fuzzy.FuzzyRule()
    def __cinit__(self, int index, cFuzzyRuleAntecedent fuzzyRuleAntecedent, cFuzzyRuleConsequent fuzzyRuleConsequent):
        self.thisptr = new Fuzzy.FuzzyRule(index, fuzzyRuleAntecedent.thisptr, fuzzyRuleConsequent.thisptr)
    def __dealloc__(self):
        if(self.thisptr):
            del self.thisptr
            self.thisptr = NULL
    def getIndex(self):
        return deref(self.thisptr).getIndex()
    def evaluateExpression(self):
        return deref(self.thisptr).evaluateExpression()
    def isFired(self):
        return deref(self.thisptr).isFired()
