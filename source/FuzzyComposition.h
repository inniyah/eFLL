/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyComposition.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYCOMPOSITION_H_69CC4C70_86FD_11EB_BBA3_836BA6AD27E7
#define FUZZYCOMPOSITION_H_69CC4C70_86FD_11EB_BBA3_836BA6AD27E7

#include "FuzzyCommon.h"

namespace eFLL {

// CONSTANTS
#define EPS 1.0E-3

// Array struct for points objects
struct pointsArray {
  pointsArray *previous = NULL;
  float point = 0.0;
  float pertinence = 0.0;
  pointsArray *next = NULL;
};

class FuzzyComposition {
public:
  using SharedPointer = std::shared_ptr<FuzzyComposition>;
  using WeakPointer = std::weak_ptr<FuzzyComposition>;

  // CONTRUCTORS
  FuzzyComposition();
  // DESTRUCTOR
  ~FuzzyComposition();
  // PUBLIC METHODS
  bool addPoint(float point, float pertinence);
  bool checkPoint(float point, float pertinence);
  bool build();
  float calculate();
  bool empty();
  int countPoints();

private:
  // PRIVATE VARIABLES
  pointsArray *points;

  // PRIVATE METHODS
  void cleanPoints(pointsArray *aux);
  bool rebuild(pointsArray *aSegmentBegin, pointsArray *aSegmentEnd, pointsArray *bSegmentBegin, pointsArray *bSegmentEnd);
  bool rmvPoint(pointsArray *point);
};

} // namespace eFLL

#endif // FUZZYCOMPOSITION_H_69CC4C70_86FD_11EB_BBA3_836BA6AD27E7
