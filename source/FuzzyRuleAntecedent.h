/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleAntecedent.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYRULEANTECEDENT_H_69CC4CF2_86FD_11EB_BBA4_8BF967D306BD
#define FUZZYRULEANTECEDENT_H_69CC4CF2_86FD_11EB_BBA4_8BF967D306BD

#include "FuzzyCommon.h"
#include "FuzzySet.h"

namespace eFLL {

// CONSTANTS
// possible logic operators
#define OP_AND 1
#define OP_OR 2
// possible join associations modes
#define MODE_FS 1
#define MODE_FS_FS 2
#define MODE_FS_FRA 3
#define MODE_FRA_FRA 4

class FuzzyRuleAntecedent
{
public:
  using SharedPointer = std::shared_ptr<FuzzyRuleAntecedent>;
  using WeakPointer = std::weak_ptr<FuzzyRuleAntecedent>;

  // CONTRUCTORS
  FuzzyRuleAntecedent();
  // PUBLIC METHODS
  bool joinSingle(FuzzySet::SharedPointer &fuzzySet);
  bool joinWithAND(FuzzySet::SharedPointer &fuzzySet1, FuzzySet::SharedPointer &fuzzySet2);
  bool joinWithOR(FuzzySet::SharedPointer &fuzzySet1, FuzzySet::SharedPointer &fuzzySet2);
  bool joinWithAND(FuzzySet::SharedPointer &fuzzySet, FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent);
  bool joinWithAND(FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent, FuzzySet::SharedPointer &fuzzySet);
  bool joinWithOR(FuzzySet::SharedPointer &fuzzySet, FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent);
  bool joinWithOR(FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent, FuzzySet::SharedPointer &fuzzySet);
  bool joinWithAND(FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent1, FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent2);
  bool joinWithOR(FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent1, FuzzyRuleAntecedent::SharedPointer &fuzzyRuleAntecedent2);
  float evaluate();

private:
  // PRIVATE VARIABLES
  int op;
  int mode;
  FuzzySet::SharedPointer fuzzySet1;
  FuzzySet::SharedPointer fuzzySet2;
  FuzzyRuleAntecedent::SharedPointer fuzzyRuleAntecedent1;
  FuzzyRuleAntecedent::SharedPointer fuzzyRuleAntecedent2;
};

} // namespace eFLL

#endif // FUZZYRULEANTECEDENT_H_69CC4CF2_86FD_11EB_BBA4_8BF967D306BD
