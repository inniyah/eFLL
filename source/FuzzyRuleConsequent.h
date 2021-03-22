/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleConsequent.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYRULECONSEQUENT_H_69CC4D56_86FD_11EB_BBA5_3FB42709DFAC
#define FUZZYRULECONSEQUENT_H_69CC4D56_86FD_11EB_BBA5_3FB42709DFAC

#include "FuzzyCommon.h"
#include "FuzzySet.h"

namespace eFLL {

// Array struct for fuzzySet (for Output) objects
struct fuzzySetOutputArray {
  FuzzySet::SharedPointer fuzzySet;
  fuzzySetOutputArray *next = NULL;
};

class FuzzyRuleConsequent {
public:
  using SharedPointer = std::shared_ptr<FuzzyRuleConsequent>;
  using WeakPointer = std::weak_ptr<FuzzyRuleConsequent>;

  // CONTRUCTORS
  FuzzyRuleConsequent();
  // DESTRUCTOR
  ~FuzzyRuleConsequent();
  // PUBLIC METHODS
  bool addOutput(FuzzySet::SharedPointer &fuzzySet);
  bool evaluate(float power);

private:
  // PRIVATE VARIABLES
  fuzzySetOutputArray *fuzzySetOutputs;

  // PRIVATE METHODS
  void cleanFuzzySets(fuzzySetOutputArray *aux);
};

} // namespace eFLL

#endif // FUZZYRULECONSEQUENT_H_69CC4D56_86FD_11EB_BBA5_3FB42709DFAC
