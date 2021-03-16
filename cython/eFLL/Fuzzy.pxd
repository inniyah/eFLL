# cython: profile=False
# distutils: language = c++
# cython: embedsignature = True
# cython: language_level = 3

from libcpp cimport bool

cdef extern from "FuzzySet.h" namespace "eFLL" nogil:
  cdef cppclass FuzzySet:
    FuzzySet() except +
    FuzzySet(float a, float b, float c, float d) except +
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
    bool addPoint(float point, float pertinence)
    bool checkPoint(float point, float pertinence)
    bool build()
    float calculate()
    bool empty()
    int countPoints()

cdef extern from "FuzzyRuleAntecedent.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRuleAntecedent:
    FuzzyRuleAntecedent() except +
    bool joinSingle(FuzzySet * fuzzySet)
    bool joinWithAND(FuzzySet * fuzzySet1, FuzzySet * fuzzySet2)
    bool joinWithOR(FuzzySet * fuzzySet1, FuzzySet * fuzzySet2)
    bool joinWithAND(FuzzySet * fuzzySet, FuzzyRuleAntecedent * fuzzyRuleAntecedent)
    bool joinWithAND(FuzzyRuleAntecedent * fuzzyRuleAntecedent, FuzzySet * fuzzySet)
    bool joinWithOR(FuzzySet * fuzzySet, FuzzyRuleAntecedent * fuzzyRuleAntecedent)
    bool joinWithOR(FuzzyRuleAntecedent * fuzzyRuleAntecedent, FuzzySet * fuzzySet)
    bool joinWithAND(FuzzyRuleAntecedent * fuzzyRuleAntecedent1, FuzzyRuleAntecedent * fuzzyRuleAntecedent2)
    bool joinWithOR(FuzzyRuleAntecedent * fuzzyRuleAntecedent1, FuzzyRuleAntecedent * fuzzyRuleAntecedent2)
    float evaluate()

cdef extern from "FuzzyRuleConsequent.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetOutputArray:
    FuzzySet * fuzzySet
    fuzzySetOutputArray * next
  cdef cppclass FuzzyRuleConsequent:
    FuzzyRuleConsequent() except +
    bool addOutput(FuzzySet * fuzzySet)
    bool evaluate(float power)

cdef extern from "FuzzyRule.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRule:
    FuzzyRule() except +
    FuzzyRule(int index, FuzzyRuleAntecedent * fuzzyRuleAntecedent, FuzzyRuleConsequent * fuzzyRuleConsequent) except +
    int getIndex()
    bool evaluateExpression()
    bool isFired()

cdef extern from "FuzzyIO.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetArray:
    FuzzySet * fuzzySet
    fuzzySetArray * next
  cdef cppclass FuzzyIO:
    FuzzyIO() except +
    int getIndex()
    void setCrispInput(float crispInput)
    float getCrispInput()
    bool addFuzzySet(FuzzySet * fuzzySet)
    void resetFuzzySets()

cdef extern from "FuzzyInput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyInput(FuzzyIO):
    FuzzyInput() except +
    FuzzyInput(int index) except +
    bool calculateFuzzySetPertinences()

cdef extern from "FuzzyOutput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyOutput(FuzzyIO):
    FuzzyOutput() except +
    FuzzyOutput(int index) except +
    bool truncate()
    float getCrispOutput()
    bool order()
    FuzzyComposition * getFuzzyComposition()

cdef extern from "Fuzzy.h" namespace "eFLL" nogil:
  cdef cppclass fuzzyInputArray:
    FuzzyInput * fuzzyInput
    fuzzyInputArray * next
  cdef cppclass fuzzyOutputArray:
    FuzzyOutput * fuzzyOutput
    fuzzyOutputArray * next
  cdef cppclass fuzzyRuleArray:
    FuzzyRule * fuzzyRule
    fuzzyRuleArray * next
  cdef cppclass Fuzzy:
    Fuzzy() except +
    bool addFuzzyInput(FuzzyInput * fuzzyInput)
    bool addFuzzyOutput(FuzzyOutput * fuzzyOutput)
    bool addFuzzyRule(FuzzyRule * fuzzyRule)
    bool setInput(int fuzzyInputIndex, float crispValue)
    bool fuzzify()
    bool isFiredRule(int fuzzyRuleIndex)
    float defuzzify(int fuzzyOutputIndex)
