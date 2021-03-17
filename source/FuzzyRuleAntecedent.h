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
  bool joinSingle(FuzzySet *fuzzySet);
  bool joinWithAND(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2);
  bool joinWithOR(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2);
  bool joinWithAND(FuzzySet *fuzzySet, FuzzyRuleAntecedent *fuzzyRuleAntecedent);
  bool joinWithAND(FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet);
  bool joinWithOR(FuzzySet *fuzzySet, FuzzyRuleAntecedent *fuzzyRuleAntecedent);
  bool joinWithOR(FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet);
  bool joinWithAND(FuzzyRuleAntecedent *fuzzyRuleAntecedent1, FuzzyRuleAntecedent *fuzzyRuleAntecedent2);
  bool joinWithOR(FuzzyRuleAntecedent *fuzzyRuleAntecedent1, FuzzyRuleAntecedent *fuzzyRuleAntecedent2);
  float evaluate();

private:
  // PRIVATE VARIABLES
  int op;
  int mode;
  FuzzySet *fuzzySet1;
  FuzzySet *fuzzySet2;
  FuzzyRuleAntecedent *fuzzyRuleAntecedent1;
  FuzzyRuleAntecedent *fuzzyRuleAntecedent2;
};

} // namespace eFLL

#endif // FUZZYRULEANTECEDENT_H_69CC4CF2_86FD_11EB_BBA4_8BF967D306BD
