/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyIO.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYIO_H_69CC4E3C_86FD_11EB_BBA7_7BFC87568D80
#define FUZZYIO_H_69CC4E3C_86FD_11EB_BBA7_7BFC87568D80

#include "FuzzyCommon.h"
#include "FuzzySet.h"

namespace eFLL {

// Array struct for FuzzySet objects
struct fuzzySetArray
{
  FuzzySet::SharedPointer fuzzySet;
  fuzzySetArray *next;
};

class FuzzyIO
{
public:
  using SharedPointer = std::shared_ptr<FuzzyIO>;
  using WeakPointer = std::weak_ptr<FuzzyIO>;

  // CONTRUCTORS
  FuzzyIO();
  FuzzyIO(int index);
  // DESTRUCTOR
  ~FuzzyIO();
  // PUBLIC METHODS
  int getIndex();
  void setCrispInput(float crispInput);
  float getCrispInput();
  bool addFuzzySet(FuzzySet::SharedPointer &fuzzySet);
  void resetFuzzySets();

protected:
  // PROTECTED VARIABLES
  int index;
  float crispInput;
  fuzzySetArray *fuzzySets;

  // PROTECTED METHODS
  void cleanFuzzySets(fuzzySetArray *aux);
};

} // namespace eFLL

#endif // FUZZYIO_H_69CC4E3C_86FD_11EB_BBA7_7BFC87568D80
