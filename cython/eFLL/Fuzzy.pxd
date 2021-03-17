# cython: profile=False
# distutils: language = c++
# cython: embedsignature = True
# cython: language_level = 3

from libcpp cimport bool
from libcpp.memory cimport shared_ptr, weak_ptr

cdef extern from "FuzzySet.h" namespace "eFLL" nogil:
  cdef cppclass FuzzySet:
    FuzzySet() except +
    FuzzySet(float a, float b, float c, float d) except +
    ctypedef shared_ptr[FuzzySet] SharedPointer
    ctypedef weak_ptr[FuzzySet] WeakPointer
    float getPointA()
    float getPointB()
    float getPointC()
    float getPointD()
    bool calculatePertinence(float crispValue)
    void setPertinence(float pertinence)
    float getPertinence()
    void reset()

cdef extern from "FuzzyComposition.h" namespace "eFLL" nogil:
  cdef cppclass pointsArray:
    pointsArray * previous
    float point
    float pertinence
    pointsArray * next
  cdef cppclass FuzzyComposition:
    FuzzyComposition() except +
    ctypedef shared_ptr[FuzzyComposition] SharedPointer
    ctypedef weak_ptr[FuzzyComposition] WeakPointer
    bool addPoint(float point, float pertinence)
    bool checkPoint(float point, float pertinence)
    bool build()
    float calculate()
    bool empty()
    int countPoints()

cdef extern from "FuzzyRuleAntecedent.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRuleAntecedent:
    FuzzyRuleAntecedent() except +
    ctypedef shared_ptr[FuzzyRuleAntecedent] SharedPointer
    ctypedef weak_ptr[FuzzyRuleAntecedent] WeakPointer
    bool joinSingle(FuzzySet.SharedPointer &fuzzySet)
    bool joinWithAND(FuzzySet.SharedPointer &fuzzySet1, FuzzySet.SharedPointer &fuzzySet2)
    bool joinWithOR(FuzzySet.SharedPointer &fuzzySet1, FuzzySet.SharedPointer &fuzzySet2)
    bool joinWithAND(FuzzySet.SharedPointer &fuzzySet, FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent)
    bool joinWithAND(FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, FuzzySet.SharedPointer &fuzzySet)
    bool joinWithOR(FuzzySet.SharedPointer &fuzzySet, FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent)
    bool joinWithOR(FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, FuzzySet.SharedPointer &fuzzySet)
    bool joinWithAND(FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent1, FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent2)
    bool joinWithOR(FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent1, FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent2)
    float evaluate()

cdef extern from "FuzzyRuleConsequent.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetOutputArray:
    FuzzySet.SharedPointer fuzzySet
    fuzzySetOutputArray * next
  cdef cppclass FuzzyRuleConsequent:
    FuzzyRuleConsequent() except +
    ctypedef shared_ptr[FuzzyRuleConsequent] SharedPointer
    ctypedef weak_ptr[FuzzyRuleConsequent] WeakPointer
    bool addOutput(FuzzySet.SharedPointer &fuzzySet)
    bool evaluate(float power)

cdef extern from "FuzzyRule.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRule:
    FuzzyRule() except +
    ctypedef shared_ptr[FuzzyRule] SharedPointer
    ctypedef weak_ptr[FuzzyRule] WeakPointer
    FuzzyRule(int index, FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, FuzzyRuleConsequent.SharedPointer &fuzzyRuleConsequent) except +
    int getIndex()
    bool evaluateExpression()
    bool isFired()

cdef extern from "FuzzyIO.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetArray:
    FuzzySet.SharedPointer fuzzySet
    fuzzySetArray * next
  cdef cppclass FuzzyIO:
    FuzzyIO() except +
    ctypedef shared_ptr[FuzzyIO] SharedPointer
    ctypedef weak_ptr[FuzzyIO] WeakPointer
    int getIndex()
    void setCrispInput(float crispInput)
    float getCrispInput()
    bool addFuzzySet(FuzzySet.SharedPointer &fuzzySet)
    void resetFuzzySets()

cdef extern from "FuzzyInput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyInput(FuzzyIO):
    FuzzyInput() except +
    FuzzyInput(int index) except +
    ctypedef shared_ptr[FuzzyInput] SharedPointer
    ctypedef weak_ptr[FuzzyInput] WeakPointer
    bool calculateFuzzySetPertinences()

cdef extern from "FuzzyOutput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyOutput(FuzzyIO):
    FuzzyOutput() except +
    FuzzyOutput(int index) except +
    ctypedef shared_ptr[FuzzyOutput] SharedPointer
    ctypedef weak_ptr[FuzzyOutput] WeakPointer
    bool truncate()
    float getCrispOutput()
    bool order()
    FuzzyComposition.SharedPointer getFuzzyComposition()

cdef extern from "Fuzzy.h" namespace "eFLL" nogil:
  cdef cppclass fuzzyInputArray:
    FuzzyInput.SharedPointer fuzzyInput
    fuzzyInputArray * next
  cdef cppclass fuzzyOutputArray:
    FuzzyOutput.SharedPointer fuzzyOutput
    fuzzyOutputArray * next
  cdef cppclass fuzzyRuleArray:
    FuzzyRule.SharedPointer fuzzyRule
    fuzzyRuleArray * next
  cdef cppclass Fuzzy:
    Fuzzy() except +
    ctypedef shared_ptr[Fuzzy] SharedPointer
    ctypedef weak_ptr[Fuzzy] WeakPointer
    bool addFuzzyInput(FuzzyInput.SharedPointer &fuzzyInput)
    bool addFuzzyOutput(FuzzyOutput.SharedPointer &fuzzyOutput)
    bool addFuzzyRule(FuzzyRule.SharedPointer &fuzzyRule)
    bool setInput(int fuzzyInputIndex, float crispValue)
    bool fuzzify()
    bool isFiredRule(int fuzzyRuleIndex)
    float defuzzify(int fuzzyOutputIndex)
