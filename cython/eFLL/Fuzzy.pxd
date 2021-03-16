# cython: profile=False
# distutils: language = c++
# cython: embedsignature = True
# cython: language_level = 3

cdef extern from "FuzzySet.h" namespace "eFLL" nogil:
  cdef cppclass FuzzySet:
    FuzzySet() except +
    FuzzySet(float a, float b, float c, float d) except +

cdef extern from "FuzzyComposition.h" namespace "eFLL" nogil:
  cdef cppclass pointsArray:
    pointsArray * previous
    float point
    float pertinence
    pointsArray * next
  cdef cppclass FuzzyComposition:
    FuzzyComposition() except +

cdef extern from "FuzzyRuleAntecedent.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRuleAntecedent:
    FuzzyRuleAntecedent() except +

cdef extern from "FuzzyRuleConsequent.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetOutputArray:
    FuzzySet * fuzzySet
    fuzzySetOutputArray * next
  cdef cppclass FuzzyRuleConsequent:
    FuzzyRuleConsequent() except +

cdef extern from "FuzzyRule.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyRule:
    FuzzyRule() except +

cdef extern from "FuzzyIO.h" namespace "eFLL" nogil:
  cdef cppclass fuzzySetArray:
    FuzzySet * fuzzySet
    fuzzySetArray * next
  cdef cppclass FuzzyIO:
    FuzzyIO() except +

cdef extern from "FuzzyInput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyInput:
    FuzzyInput() except +

cdef extern from "FuzzyOutput.h" namespace "eFLL" nogil:
  cdef cppclass FuzzyOutput:
    FuzzyOutput() except +

cdef extern from "Fuzzy.h" namespace "eFLL" nogil:
  cdef cppclass fuzzyInputArray:
    FuzzyInput *fuzzyInput
    fuzzyInputArray *next
  cdef cppclass fuzzyOutputArray:
    FuzzyOutput *fuzzyOutput
    fuzzyOutputArray *next
  cdef cppclass fuzzyRuleArray:
    FuzzyRule *fuzzyRule
    fuzzyRuleArray *next
  cdef cppclass Fuzzy:
    Fuzzy() except +
