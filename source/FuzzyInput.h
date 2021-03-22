/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyInput.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */

#pragma once

#ifndef FUZZYINPUT_H_69CC4E96_86FD_11EB_BBA8_CB96D905530C
#define FUZZYINPUT_H_69CC4E96_86FD_11EB_BBA8_CB96D905530C

#include "FuzzyCommon.h"
#include "FuzzyIO.h"

namespace eFLL {

class FuzzyInput : public FuzzyIO {
public:
  using SharedPointer = std::shared_ptr<FuzzyInput>;
  using WeakPointer = std::weak_ptr<FuzzyInput>;

  // CONTRUCTORS
  FuzzyInput();
  FuzzyInput(int index);
  // DESTRUCTOR
  ~FuzzyInput();
  // PUBLIC METHODS
  bool calculateFuzzySetPertinences();
};

} // namespace eFLL

#endif // FUZZYINPUT_H_69CC4E96_86FD_11EB_BBA8_CB96D905530C
