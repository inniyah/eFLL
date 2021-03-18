#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..'))

from eFLL import *

from time import time
from random import seed, random

seed(time())

fuzzy = Fuzzy()

# FuzzyInput: distance
distance = FuzzyInput(1)
near = FuzzySet(0, 20, 20, 40)
distance.addFuzzySet(near)
safe = FuzzySet(30, 50, 50, 70)
distance.addFuzzySet(safe)
distant = FuzzySet(60, 80, 100, 100)
distance.addFuzzySet(distant)
fuzzy.addFuzzyInput(distance)

# FuzzyInput: speed
inputSpeed = FuzzyInput(2)
stopedInput = FuzzySet(0, 0, 0, 0)
inputSpeed.addFuzzySet(stopedInput)
slowInput = FuzzySet(1, 10, 10, 20)
inputSpeed.addFuzzySet(slowInput)
normalInput = FuzzySet(15, 30, 30, 50)
inputSpeed.addFuzzySet(normalInput)
quickInput = FuzzySet(45, 60, 70, 70)
inputSpeed.addFuzzySet(quickInput)
fuzzy.addFuzzyInput(inputSpeed)

# FuzzyInput: temperature
temperature = FuzzyInput(3)
cold = FuzzySet(-30, -30, -20, -10)
temperature.addFuzzySet(cold)
good = FuzzySet(-15, 0, 0, 15)
temperature.addFuzzySet(good)
hot = FuzzySet(10, 20, 30, 30)
temperature.addFuzzySet(hot)
fuzzy.addFuzzyInput(temperature)

# FuzzyOutput
risk = FuzzyOutput(1)
minimum = FuzzySet(0, 20, 20, 40)
risk.addFuzzySet(minimum)
average = FuzzySet(30, 50, 50, 70)
risk.addFuzzySet(average)
maximum = FuzzySet(60, 80, 80, 100)
risk.addFuzzySet(maximum)
fuzzy.addFuzzyOutput(risk)

# FuzzyOutput
speedOutput = FuzzyOutput(2)
stopedOutput = FuzzySet(0, 0, 0, 0)
speedOutput.addFuzzySet(stopedOutput)
slowOutput = FuzzySet(1, 10, 10, 20)
speedOutput.addFuzzySet(slowOutput)
normalOutput = FuzzySet(15, 30, 30, 50)
speedOutput.addFuzzySet(normalOutput)
quickOutput = FuzzySet(45, 60, 70, 70)
speedOutput.addFuzzySet(quickOutput)
fuzzy.addFuzzyOutput(speedOutput)

# FuzzyRule
distanceCloseAndSpeedQuick = FuzzyRuleAntecedent()
distanceCloseAndSpeedQuick.joinWithAND(near, quickInput)
temperatureCold = FuzzyRuleAntecedent()
temperatureCold.joinSingle(cold)
ifDistanceCloseAndSpeedQuickOrTemperatureCold = FuzzyRuleAntecedent()
ifDistanceCloseAndSpeedQuickOrTemperatureCold.joinWithOR(distanceCloseAndSpeedQuick, temperatureCold)

thenRisMaximumAndSpeedSlow = FuzzyRuleConsequent()
thenRisMaximumAndSpeedSlow.addOutput(maximum)
thenRisMaximumAndSpeedSlow.addOutput(slowOutput)

fuzzyRule1 = FuzzyRule(1, ifDistanceCloseAndSpeedQuickOrTemperatureCold, thenRisMaximumAndSpeedSlow)
fuzzy.addFuzzyRule(fuzzyRule1)

# FuzzyRule
distanceSafeAndSpeedNormal = FuzzyRuleAntecedent()
distanceSafeAndSpeedNormal.joinWithAND(safe, normalInput)
ifDistanceSafeAndSpeedNormalOrTemperatureGood = FuzzyRuleAntecedent()
ifDistanceSafeAndSpeedNormalOrTemperatureGood.joinWithOR(distanceSafeAndSpeedNormal, good)

thenRiskAverageAndSpeedNormal = FuzzyRuleConsequent()
thenRiskAverageAndSpeedNormal.addOutput(average)
thenRiskAverageAndSpeedNormal.addOutput(normalOutput)

fuzzyRule2 = FuzzyRule(2, ifDistanceSafeAndSpeedNormalOrTemperatureGood, thenRiskAverageAndSpeedNormal)
fuzzy.addFuzzyRule(fuzzyRule2)

# FuzzyRule
distanceDistantAndSpeedSlow = FuzzyRuleAntecedent()
distanceDistantAndSpeedSlow.joinWithAND(distant, slowInput)
ifDistanceDistantAndSpeedSlowOrTemperatureHot = FuzzyRuleAntecedent()
ifDistanceDistantAndSpeedSlowOrTemperatureHot.joinWithOR(distanceDistantAndSpeedSlow, hot)

thenRiskMinimumSpeedQuick = FuzzyRuleConsequent()
thenRiskMinimumSpeedQuick.addOutput(minimum)
thenRiskMinimumSpeedQuick.addOutput(quickOutput)

fuzzyRule3 = FuzzyRule(3, ifDistanceDistantAndSpeedSlowOrTemperatureHot, thenRiskMinimumSpeedQuick)
fuzzy.addFuzzyRule(fuzzyRule3)

# get random entrances
input1 = random() * 100.0
input2 = random() * 70.0
input3 = random() * 60.0 - 30.0

print(f"\n\n\nEntrance: \n\t\t\tDistance: {input1}, Speed: {input2}, and Temperature: {input3}")

fuzzy.setInput(1, input1)
fuzzy.setInput(2, input2)
fuzzy.setInput(3, input3)

fuzzy.fuzzify()

print(f"Input: \n\tDistance: Near. {near.getPertinence()}, Safe.{safe.getPertinence()}, Distant. {distant.getPertinence()}")
print(f"\tSpeed: Stoped. {stopedInput.getPertinence()},  Slow. {slowInput.getPertinence()},  Normal. {normalInput.getPertinence()},  Quick. {quickInput.getPertinence()}")
print(f"\tTemperature: Cold.{cold.getPertinence()}, Good. {good.getPertinence()}, Hot. {hot.getPertinence()}")

print(f"Roles: \n\tRole01. {fuzzyRule1.isFired()}, Role02. {fuzzyRule2.isFired()}, Role03. {fuzzyRule3.isFired()}")

output1 = fuzzy.defuzzify(1)
output2 = fuzzy.defuzzify(2)

print(f"Output: \n\tRisk: Minimum. {minimum.getPertinence()}, Average.{average.getPertinence()}, Maximum. {maximum.getPertinence()}")
print(f"\tSpeed: Stoped. {stopedOutput.getPertinence()},  Slow. {slowOutput.getPertinence()},  Normal. {normalOutput.getPertinence()},  Quick. {quickOutput.getPertinence()}")

print(f"Result: \n\t\t\tRisk: {output1}, and Speed: {output2}")
