#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from eFLL import *

from time import time
from random import seed, random

fuzzy = Fuzzy()

# FuzzyInput: distance
distance = FuzzyInput(1)
small = FuzzySet(0, 20, 20, 40)
distance.addFuzzySet(small)
safe = FuzzySet(30, 50, 50, 70)
distance.addFuzzySet(safe)
big = FuzzySet(60, 80, 80, 80)
distance.addFuzzySet(big)
fuzzy.addFuzzyInput(distance)

# FuzzyOutput: speed
speed = FuzzyOutput(1)
slow = FuzzySet(0, 10, 10, 20)
speed.addFuzzySet(slow)
average = FuzzySet(10, 20, 30, 40)
speed.addFuzzySet(average)
fast = FuzzySet(30, 40, 40, 50)
speed.addFuzzySet(fast)
fuzzy.addFuzzyOutput(speed)


# FuzzyRule: IF distance = small THEN speed = slow
ifDistanceSmall = FuzzyRuleAntecedent()
ifDistanceSmall.joinSingle(small)
thenSpeedSlow = FuzzyRuleConsequent()
thenSpeedSlow.addOutput(slow)
fuzzyRule01 = FuzzyRule(1, ifDistanceSmall, thenSpeedSlow)
fuzzy.addFuzzyRule(fuzzyRule01)

# FuzzyRule: IF distance = safe THEN speed = average
ifDistanceSafe = FuzzyRuleAntecedent()
ifDistanceSafe.joinSingle(safe)
thenSpeedAverage = FuzzyRuleConsequent()
thenSpeedAverage.addOutput(average)
fuzzyRule02 = FuzzyRule(2, ifDistanceSafe, thenSpeedAverage)
fuzzy.addFuzzyRule(fuzzyRule02)

# FuzzyRule: IF distance = big THEN speed = high
ifDistanceBig = FuzzyRuleAntecedent()
ifDistanceBig.joinSingle(big)
thenSpeedFast = FuzzyRuleConsequent()
thenSpeedFast.addOutput(fast)
fuzzyRule03 = FuzzyRule(3, ifDistanceBig, thenSpeedFast)
fuzzy.addFuzzyRule(fuzzyRule03)

seed(time())
input = random() * 100.0
print(f"Distance (input): {input}")
fuzzy.setInput(1, input)
fuzzy.fuzzify()
output = fuzzy.defuzzify(1)
print(f"Speed (output): {output}")
