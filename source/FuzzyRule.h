/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRule.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYRULE_H_69CC4DC4_86FD_11EB_BBA6_57F3151559AD
#define FUZZYRULE_H_69CC4DC4_86FD_11EB_BBA6_57F3151559AD

#include "FuzzyCommon.h"
#include "FuzzyRuleAntecedent.h"
#include "FuzzyRuleConsequent.h"

namespace eFLL {

class FuzzyRule
{
public:
  using SharedPointer = std::shared_ptr<FuzzyRule>;
  using WeakPointer = std::weak_ptr<FuzzyRule>;

  // CONTRUCTORS
  FuzzyRule();
  FuzzyRule(int index, FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzyRuleConsequent *fuzzyRuleConsequent);
  // PUBLIC METHODS
  int getIndex();
  bool evaluateExpression();
  bool isFired();

private:
  // PRIVATE VARIABLES
  int index;
  bool fired;
  FuzzyRuleAntecedent *fuzzyRuleAntecedent;
  FuzzyRuleConsequent *fuzzyRuleConsequent;
};

} // namespace eFLL

#endif // FUZZYRULE_H_69CC4DC4_86FD_11EB_BBA6_57F3151559AD
