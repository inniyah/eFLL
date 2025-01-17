/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * Fuzzy.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZY_H_69CC4F40_86FD_11EB_BBAA_57E5E1373EE0
#define FUZZY_H_69CC4F40_86FD_11EB_BBAA_57E5E1373EE0

#include "FuzzyCommon.h"
#include "FuzzyInput.h"
#include "FuzzyOutput.h"
#include "FuzzyRule.h"

namespace eFLL {

// Array struct for FuzzyInput objects
struct fuzzyInputArray {
  FuzzyInput::SharedPointer fuzzyInput;
  fuzzyInputArray *next = NULL;
};

// Array struct for FuzzyOutput objects
struct fuzzyOutputArray {
  FuzzyOutput::SharedPointer fuzzyOutput;
  fuzzyOutputArray *next = NULL;
};

// Array struct for FuzzyRule objects
struct fuzzyRuleArray {
  FuzzyRule::SharedPointer fuzzyRule;
  fuzzyRuleArray *next = NULL;
};

// Main class of this library
class Fuzzy {
public:
  using SharedPointer = std::shared_ptr<Fuzzy>;
  using WeakPointer = std::weak_ptr<Fuzzy>;

  // CONTRUCTORS
  Fuzzy();

  // DESTRUCTOR
  ~Fuzzy();

  // PUBLIC METHODS
  FuzzyInput::SharedPointer &addFuzzyInput(FuzzyInput::SharedPointer &fuzzyInput);
  FuzzyOutput::SharedPointer &addFuzzyOutput(FuzzyOutput::SharedPointer &fuzzyOutput);
  FuzzyRule::SharedPointer &addFuzzyRule(FuzzyRule::SharedPointer &fuzzyRule);
  bool setInput(int fuzzyInputIndex, float crispValue);
  bool fuzzify();
  bool isFiredRule(int fuzzyRuleIndex);
  float defuzzify(int fuzzyOutputIndex);

private:
  // PRIVATE VARIABLES
  // pointers to manage the array of FuzzyInput
  fuzzyInputArray *fuzzyInputs;
  // pointers to manage the array of FuzzyOutput
  fuzzyOutputArray *fuzzyOutputs;
  // pointers to manage the array of FuzzyRule
  fuzzyRuleArray *fuzzyRules;

  // PRIVATE METHODS
  void cleanFuzzyInputs(fuzzyInputArray *aux);
  void cleanFuzzyOutputs(fuzzyOutputArray *aux);
  void cleanFuzzyRules(fuzzyRuleArray *aux);
};

} // namespace eFLL

#endif // FUZZY_H_69CC4F40_86FD_11EB_BBAA_57E5E1373EE0
