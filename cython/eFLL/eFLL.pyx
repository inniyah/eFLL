from eFLL.eFLL cimport *

from libcpp cimport bool
from libcpp.memory cimport shared_ptr, weak_ptr
from cython.operator cimport dereference as deref

cdef class FuzzySet:
    cdef shared_ptr[_FuzzySet] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzySet](new _FuzzySet())
    def __cinit__(self, float a, float b, float c, float d):
        self.thisptr = shared_ptr[_FuzzySet](new _FuzzySet(a, b, c, d))
    def __dealloc__(self):
        self.thisptr.reset()
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

cdef class FuzzyComposition:
    cdef shared_ptr[_FuzzyComposition] thisptr
    def __cinit__(self):
        pass
    def __dealloc__(self):
        self.thisptr.reset()
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

cdef class FuzzyRuleAntecedent:
    cdef shared_ptr[_FuzzyRuleAntecedent] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzyRuleAntecedent](new _FuzzyRuleAntecedent())
    def __dealloc__(self):
        self.thisptr.reset()
    def joinSingle(self, FuzzySet fuzzySet):
        return deref(self.thisptr).joinSingle(fuzzySet.thisptr)
    def joinWithAND(self, item1, item2):
        if isinstance(item1, FuzzySet) and isinstance(item2, FuzzySet):
            return deref(self.thisptr).joinWithAND((<FuzzySet>item1).thisptr, (<FuzzySet>item2).thisptr)
        elif isinstance(item1, FuzzySet) and isinstance(item2, FuzzyRuleAntecedent):
            return deref(self.thisptr).joinWithAND((<FuzzySet>item1).thisptr, (<FuzzyRuleAntecedent>item2).thisptr)
        elif isinstance(item1, FuzzyRuleAntecedent) and isinstance(item2, FuzzySet):
            return deref(self.thisptr).joinWithAND((<FuzzyRuleAntecedent>item1).thisptr, (<FuzzySet>item2).thisptr)
        elif isinstance(item1, FuzzyRuleAntecedent) and isinstance(item2, FuzzyRuleAntecedent):
            return deref(self.thisptr).joinWithAND((<FuzzyRuleAntecedent>item1).thisptr, (<FuzzyRuleAntecedent>item2).thisptr)
        else:
            raise ValueError("Arguments are neither of type FuzzySet nor FuzzyRuleAntecedent")
    def joinWithOR(self, item1, item2):
        if isinstance(item1, FuzzySet) and isinstance(item2, FuzzySet):
            return deref(self.thisptr).joinWithOR((<FuzzySet>item1).thisptr, (<FuzzySet>item2).thisptr)
        elif isinstance(item1, FuzzySet) and isinstance(item2, FuzzyRuleAntecedent):
            return deref(self.thisptr).joinWithOR((<FuzzySet>item1).thisptr, (<FuzzyRuleAntecedent>item2).thisptr)
        elif isinstance(item1, FuzzyRuleAntecedent) and isinstance(item2, FuzzySet):
            return deref(self.thisptr).joinWithOR((<FuzzyRuleAntecedent>item1).thisptr, (<FuzzySet>item2).thisptr)
        elif isinstance(item1, FuzzyRuleAntecedent) and isinstance(item2, FuzzyRuleAntecedent):
            return deref(self.thisptr).joinWithOR((<FuzzyRuleAntecedent>item1).thisptr, (<FuzzyRuleAntecedent>item2).thisptr)
        else:
            raise ValueError("Arguments are neither of type FuzzySet nor FuzzyRuleAntecedent")

cdef class FuzzyRuleConsequent:
    cdef shared_ptr[_FuzzyRuleConsequent] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzyRuleConsequent](new _FuzzyRuleConsequent())
    def __dealloc__(self):
        self.thisptr.reset()
    def addOutput(self, FuzzySet fuzzySet):
        return deref(self.thisptr).addOutput(fuzzySet.thisptr)
    def evaluate(self, float power):
        return deref(self.thisptr).evaluate(power)

cdef class FuzzyRule:
    cdef shared_ptr[_FuzzyRule] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzyRule](new _FuzzyRule())
    def __cinit__(self, int index, FuzzyRuleAntecedent fuzzyRuleAntecedent, FuzzyRuleConsequent fuzzyRuleConsequent):
        self.thisptr = shared_ptr[_FuzzyRule](new _FuzzyRule(index, fuzzyRuleAntecedent.thisptr, fuzzyRuleConsequent.thisptr))
    def __dealloc__(self):
        self.thisptr.reset()
    def getIndex(self):
        return deref(self.thisptr).getIndex()
    def evaluateExpression(self):
        return deref(self.thisptr).evaluateExpression()
    def isFired(self):
        return deref(self.thisptr).isFired()

cdef class FuzzyInput():
    cdef shared_ptr[_FuzzyInput] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzyInput](new _FuzzyInput())
    def __cinit__(self, int index):
        self.thisptr = shared_ptr[_FuzzyInput](new _FuzzyInput(index))
    def __dealloc__(self):
        self.thisptr.reset()
    def calculateFuzzySetPertinences(self):
        return deref(self.thisptr).calculateFuzzySetPertinences()
    def getIndex(self):
        return deref(self.thisptr).getIndex()
    def setCrispInput(self, float crispInput):
        deref(self.thisptr).setCrispInput(crispInput)
    def getCrispInput(self):
        return deref(self.thisptr).getCrispInput()
    def addFuzzySet(self, FuzzySet fuzzySet):
        deref(self.thisptr).addFuzzySet(fuzzySet.thisptr)
        return fuzzySet
    def resetFuzzySets(self):
        deref(self.thisptr).resetFuzzySets()

cdef class FuzzyOutput():
    cdef shared_ptr[_FuzzyOutput] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_FuzzyOutput](new _FuzzyOutput())
    def __cinit__(self, int index):
        self.thisptr = shared_ptr[_FuzzyOutput](new _FuzzyOutput(index))
    def __dealloc__(self):
        self.thisptr.reset()
    def truncate(self):
        return deref(self.thisptr).truncate()
    def getCrispOutput(self):
        return deref(self.thisptr).getCrispOutput()
    def order(self):
        return deref(self.thisptr).order()
    def getFuzzyComposition(self):
        fuzzyComposition = FuzzyComposition()
        fuzzyComposition.thisptr = deref(self.thisptr).getFuzzyComposition()
        return fuzzyComposition
    def getIndex(self):
        return deref(self.thisptr).getIndex()
    def setCrispInput(self, float crispInput):
        deref(self.thisptr).setCrispInput(crispInput)
    def getCrispInput(self):
        return deref(self.thisptr).getCrispInput()
    def addFuzzySet(self, FuzzySet fuzzySet):
        deref(self.thisptr).addFuzzySet(fuzzySet.thisptr)
        return fuzzySet
    def resetFuzzySets(self):
        deref(self.thisptr).resetFuzzySets()

cdef class Fuzzy:
    cdef shared_ptr[_Fuzzy] thisptr
    def __cinit__(self):
        self.thisptr = shared_ptr[_Fuzzy](new _Fuzzy())
    def __dealloc__(self):
        self.thisptr.reset()
    def addFuzzyInput(self, FuzzyInput fuzzyInput):
        deref(self.thisptr).addFuzzyInput(fuzzyInput.thisptr)
        return fuzzyInput
    def addFuzzyOutput(self, FuzzyOutput fuzzyOutput):
        deref(self.thisptr).addFuzzyOutput(fuzzyOutput.thisptr)
        return fuzzyOutput
    def addFuzzyRule(self, FuzzyRule fuzzyRule):
        deref(self.thisptr).addFuzzyRule(fuzzyRule.thisptr)
        return fuzzyRule
    def setInput(self, int fuzzyInputIndex, float crispValue):
        return deref(self.thisptr).setInput(fuzzyInputIndex, crispValue)
    def fuzzify(self):
        return deref(self.thisptr).fuzzify()
    def isFiredRule(self, int fuzzyRuleIndex):
        return deref(self.thisptr).isFiredRule(fuzzyRuleIndex)
    def defuzzify(self, int fuzzyOutputIndex):
        return deref(self.thisptr).defuzzify(fuzzyOutputIndex)
