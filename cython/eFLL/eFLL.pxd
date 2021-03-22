# cython: profile=False
# distutils: language = c++
# cython: embedsignature = True
# cython: language_level = 3

from libcpp cimport bool
from libcpp.memory cimport shared_ptr, weak_ptr

cdef extern from "FuzzySet.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzySet "eFLL::FuzzySet":
    _FuzzySet() except +
    _FuzzySet(float a, float b, float c, float d) except +
    ctypedef shared_ptr[_FuzzySet] SharedPointer
    ctypedef weak_ptr[_FuzzySet] WeakPointer
    float getPointA()
    float getPointB()
    float getPointC()
    float getPointD()
    bool calculatePertinence(float crispValue)
    void setPertinence(float pertinence)
    float getPertinence()
    void reset()

cdef extern from "FuzzyComposition.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyComposition "eFLL::FuzzyComposition":
    _FuzzyComposition() except +
    ctypedef shared_ptr[_FuzzyComposition] SharedPointer
    ctypedef weak_ptr[_FuzzyComposition] WeakPointer
    bool addPoint(float point, float pertinence)
    bool checkPoint(float point, float pertinence)
    bool build()
    float calculate()
    bool empty()
    int countPoints()

cdef extern from "FuzzyRuleAntecedent.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyRuleAntecedent "eFLL::FuzzyRuleAntecedent":
    _FuzzyRuleAntecedent() except +
    ctypedef shared_ptr[_FuzzyRuleAntecedent] SharedPointer
    ctypedef weak_ptr[_FuzzyRuleAntecedent] WeakPointer
    bool joinSingle(_FuzzySet.SharedPointer &fuzzySet)
    bool joinWithAND(_FuzzySet.SharedPointer &fuzzySet1, _FuzzySet.SharedPointer &fuzzySet2)
    bool joinWithAND(_FuzzySet.SharedPointer &fuzzySet, _FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent)
    bool joinWithAND(_FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, _FuzzySet.SharedPointer &fuzzySet)
    bool joinWithAND(_FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent1, _FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent2)
    bool joinWithOR(_FuzzySet.SharedPointer &fuzzySet1, _FuzzySet.SharedPointer &fuzzySet2)
    bool joinWithOR(_FuzzySet.SharedPointer &fuzzySet, _FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent)
    bool joinWithOR(_FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, _FuzzySet.SharedPointer &fuzzySet)
    bool joinWithOR(_FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent1, _FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent2)
    float evaluate()

cdef extern from "FuzzyRuleConsequent.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyRuleConsequent "eFLL::FuzzyRuleConsequent":
    _FuzzyRuleConsequent() except +
    ctypedef shared_ptr[_FuzzyRuleConsequent] SharedPointer
    ctypedef weak_ptr[_FuzzyRuleConsequent] WeakPointer
    bool addOutput(_FuzzySet.SharedPointer &fuzzySet)
    bool evaluate(float power)

cdef extern from "FuzzyRule.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyRule "eFLL::FuzzyRule":
    _FuzzyRule() except +
    _FuzzyRule(int index, _FuzzyRuleAntecedent.SharedPointer &fuzzyRuleAntecedent, _FuzzyRuleConsequent.SharedPointer &fuzzyRuleConsequent) except +
    ctypedef shared_ptr[_FuzzyRule] SharedPointer
    ctypedef weak_ptr[_FuzzyRule] WeakPointer
    int getIndex()
    bool evaluateExpression()
    bool isFired()

cdef extern from "FuzzyIO.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyIO "eFLL::FuzzyIO":
    _FuzzyIO() except +
    ctypedef shared_ptr[_FuzzyIO] SharedPointer
    ctypedef weak_ptr[_FuzzyIO] WeakPointer
    int getIndex()
    void setCrispInput(float crispInput)
    float getCrispInput()
    _FuzzySet.SharedPointer &addFuzzySet(_FuzzySet.SharedPointer &fuzzySet)
    void resetFuzzySets()

cdef extern from "FuzzyInput.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyInput "eFLL::FuzzyInput" (_FuzzyIO):
    _FuzzyInput() except +
    _FuzzyInput(int index) except +
    ctypedef shared_ptr[_FuzzyInput] SharedPointer
    ctypedef weak_ptr[_FuzzyInput] WeakPointer
    bool calculateFuzzySetPertinences()

cdef extern from "FuzzyOutput.h" namespace "eFLL" nogil:
  cdef cppclass _FuzzyOutput "eFLL::FuzzyOutput" (_FuzzyIO):
    _FuzzyOutput() except +
    _FuzzyOutput(int index) except +
    ctypedef shared_ptr[_FuzzyOutput] SharedPointer
    ctypedef weak_ptr[_FuzzyOutput] WeakPointer
    bool truncate()
    float getCrispOutput()
    bool order()
    _FuzzyComposition.SharedPointer getFuzzyComposition()

cdef extern from "Fuzzy.h" namespace "eFLL" nogil:
  cdef cppclass _Fuzzy "eFLL::Fuzzy":
    _Fuzzy() except +
    ctypedef shared_ptr[_Fuzzy] SharedPointer
    ctypedef weak_ptr[_Fuzzy] WeakPointer
    bool addFuzzyInput(_FuzzyInput.SharedPointer &fuzzyInput)
    bool addFuzzyOutput(_FuzzyOutput.SharedPointer &fuzzyOutput)
    bool addFuzzyRule(_FuzzyRule.SharedPointer &fuzzyRule)
    bool setInput(int fuzzyInputIndex, float crispValue)
    bool fuzzify()
    bool isFiredRule(int fuzzyRuleIndex)
    float defuzzify(int fuzzyOutputIndex)
