/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYOUTPUT_H_69CC4EE6_86FD_11EB_BBA9_9F51BE0723A1
#define FUZZYOUTPUT_H_69CC4EE6_86FD_11EB_BBA9_9F51BE0723A1

#include "FuzzyCommon.h"
#include "FuzzyIO.h"
#include "FuzzyComposition.h"

namespace eFLL {

class FuzzyOutput : public FuzzyIO {
public:
  using SharedPointer = std::shared_ptr<FuzzyOutput>;
  using WeakPointer = std::weak_ptr<FuzzyOutput>;

  // CONTRUCTORS
  FuzzyOutput();
  FuzzyOutput(int index);
  // DESTRUCTOR
  ~FuzzyOutput();
  // PUBLIC METHODS
  bool truncate();
  float getCrispOutput();
  bool order();
  FuzzyComposition::SharedPointer getFuzzyComposition();

private:
  // PRIVATE VARIABLES
  FuzzyComposition::SharedPointer fuzzyComposition;

  // PRIVATE METHODS
  bool swap(fuzzySetArray *fuzzySetA, fuzzySetArray *fuzzySetB);
  bool rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *point, float *pertinence);
};

} // namespace eFLL

#endif // FUZZYOUTPUT_H_69CC4EE6_86FD_11EB_BBA9_9F51BE0723A1
