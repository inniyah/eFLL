#include "gtest/gtest.h"

#include "../source/Fuzzy.h"

using namespace eFLL;

// ##### Tests of FuzzySet

TEST(FuzzySet, getPoints)
{
    auto fuzzySet = std::make_shared<FuzzySet>(0, 10, 20, 30);
    ASSERT_EQ(0, fuzzySet->getPointA());
    ASSERT_EQ(10, fuzzySet->getPointB());
    ASSERT_EQ(20, fuzzySet->getPointC());
    ASSERT_EQ(30, fuzzySet->getPointD());
}

TEST(FuzzySet, calculateAndGetPertinence)
{
    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);

    fuzzySet1->calculatePertinence(-5);
    ASSERT_FLOAT_EQ(0.0, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(5);
    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(10);
    ASSERT_FLOAT_EQ(1.0, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(15);
    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(25);
    ASSERT_FLOAT_EQ(0.0, fuzzySet1->getPertinence());

    auto fuzzySet2 = std::make_shared<FuzzySet>(0, 0, 20, 30);

    fuzzySet2->calculatePertinence(-5);
    ASSERT_FLOAT_EQ(1.0, fuzzySet2->getPertinence());

    auto fuzzySet3 = std::make_shared<FuzzySet>(0, 10, 20, 20);

    fuzzySet3->calculatePertinence(25);
    ASSERT_FLOAT_EQ(1.0, fuzzySet3->getPertinence());
}

// ##### Tests of FuzzyInput (It tests FuzzyIO too)

TEST(FuzzyInput, addFuzzySet)
{
    auto fuzzyInput = std::make_shared<FuzzyInput>(1);
    auto fuzzySet = std::make_shared<FuzzySet>(0, 10, 10, 20);
    ASSERT_TRUE(fuzzyInput->addFuzzySet(fuzzySet));
}

TEST(FuzzyInput, setCrispInputAndGetCrispInput)
{
    auto fuzzyInput = std::make_shared<FuzzyInput>(1);
    fuzzyInput->setCrispInput(10.190);
    ASSERT_FLOAT_EQ(10.190, fuzzyInput->getCrispInput());
}

TEST(FuzzyInput, calculateFuzzySetPertinences)
{
    auto fuzzyInput = std::make_shared<FuzzyInput>(1);

    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);

    fuzzyInput->addFuzzySet(fuzzySet1);

    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);

    fuzzyInput->addFuzzySet(fuzzySet2);

    fuzzyInput->setCrispInput(5);

    ASSERT_TRUE(fuzzyInput->calculateFuzzySetPertinences());

    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    ASSERT_FLOAT_EQ(0.0, fuzzySet2->getPertinence());
}

// ##### Tests of FuzzyComposition

TEST(FuzzyComposition, addPointAndCheckPoint)
{
    auto fuzzyComposition = std::make_shared<FuzzyComposition>();

    ASSERT_TRUE(fuzzyComposition->addPoint(1, 0.1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(1, 0.1));

    ASSERT_TRUE(fuzzyComposition->addPoint(5, 0.5));
    ASSERT_TRUE(fuzzyComposition->checkPoint(5, 0.5));

    ASSERT_TRUE(fuzzyComposition->addPoint(9, 0.9));
    ASSERT_TRUE(fuzzyComposition->checkPoint(9, 0.9));

    ASSERT_FALSE(fuzzyComposition->checkPoint(5, 0.1));
}

TEST(FuzzyComposition, build)
{
    auto fuzzyComposition = std::make_shared<FuzzyComposition>();

    fuzzyComposition->addPoint(0, 0);
    fuzzyComposition->addPoint(10, 1);
    fuzzyComposition->addPoint(20, 0);

    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);

    ASSERT_TRUE(fuzzyComposition->build());

    ASSERT_TRUE(fuzzyComposition->checkPoint(0, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(10, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(15, 0.5));
    ASSERT_FALSE(fuzzyComposition->checkPoint(10, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(20, 1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(30, 0));
}

TEST(FuzzyComposition, calculateAndEmptyAndCountPoints)
{
    auto fuzzyComposition = std::make_shared<FuzzyComposition>();

    fuzzyComposition->addPoint(25, 1);
    fuzzyComposition->addPoint(25, 1);
    fuzzyComposition->build();
    ASSERT_EQ(2, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(25, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);
    fuzzyComposition->build();
    ASSERT_EQ(3, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(20, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(30, 1);
    fuzzyComposition->addPoint(50, 1);
    fuzzyComposition->addPoint(60, 0);
    fuzzyComposition->build();
    ASSERT_EQ(4, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(40, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(0, 0);
    fuzzyComposition->addPoint(10, 1);
    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);
    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(30, 1);
    fuzzyComposition->addPoint(40, 0);
    fuzzyComposition->build();
    ASSERT_EQ(7, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(20, fuzzyComposition->calculate());
}

// ##### Test of FuzzyOutput (It tests FuzzyIO too)

TEST(FuzzyOutput, getIndex)
{
    auto fuzzyOutput = std::make_shared<FuzzyOutput>(1);
    ASSERT_EQ(1, fuzzyOutput->getIndex());
}

TEST(FuzzyOutput, setCrispInputAndGetCrispInput)
{
    auto fuzzyOutput = std::make_shared<FuzzyOutput>(1);
    fuzzyOutput->setCrispInput(10.190);
    ASSERT_FLOAT_EQ(10.190, fuzzyOutput->getCrispInput());
}

TEST(FuzzyOutput, addFuzzySetAndResetFuzzySets)
{
    auto fuzzyOutput = std::make_shared<FuzzyOutput>(1);

    auto fuzzySetTest = std::make_shared<FuzzySet>(0, 10, 10, 20);

    ASSERT_TRUE(fuzzyOutput->addFuzzySet(fuzzySetTest));

    fuzzySetTest->setPertinence(0.242);
    ASSERT_FLOAT_EQ(0.242, fuzzySetTest->getPertinence());

    fuzzyOutput->resetFuzzySets();

    ASSERT_FLOAT_EQ(0.0, fuzzySetTest->getPertinence());
}

TEST(FuzzyOutput, truncateAndGetCrispOutputAndGetFuzzyComposition)
{
    auto fuzzyOutput = std::make_shared<FuzzyOutput>(1);

    ASSERT_EQ(1, fuzzyOutput->getIndex());

    auto fuzzySetTest1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySetTest1->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest1);

    auto fuzzySetTest2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzySetTest2->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest2);

    auto fuzzySetTest3 = std::make_shared<FuzzySet>(20, 30, 30, 40);
    fuzzySetTest3->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest3);

    ASSERT_TRUE(fuzzyOutput->truncate());

    auto fuzzyComposition = fuzzyOutput->getFuzzyComposition();

    ASSERT_NE(nullptr, fuzzyComposition);

    ASSERT_EQ(7, fuzzyComposition->countPoints());

    ASSERT_TRUE(fuzzyComposition->checkPoint(0, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(10, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));

    ASSERT_TRUE(fuzzyComposition->checkPoint(15, 0.5));

    ASSERT_FALSE(fuzzyComposition->checkPoint(10, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(20, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(30, 0));

    ASSERT_TRUE(fuzzyComposition->checkPoint(25, 0.5));

    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(30, 1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(40, 0));

    ASSERT_FLOAT_EQ(20.0, fuzzyOutput->getCrispOutput());
}

// ##### Tests for FuzzyRuleAntecedent

TEST(FuzzyRuleAntecedent, joinSingleAndEvaluate)
{
    auto fuzzyRuleAntecedent = std::make_shared<FuzzyRuleAntecedent>();

    auto fuzzySet = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet->setPertinence(0.25);

    ASSERT_TRUE(fuzzyRuleAntecedent->joinSingle(fuzzySet));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent->evaluate());
}

TEST(FuzzyRuleAntecedent, joinTwoFuzzySetAndEvaluate)
{
    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);

    auto fuzzyRuleAntecedent1 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent1->joinWithAND(fuzzySet1, fuzzySet2));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent1->evaluate());

    auto fuzzyRuleAntecedent2 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent2->joinWithOR(fuzzySet1, fuzzySet2));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent2->evaluate());
}

TEST(FuzzyRuleAntecedent, joinOneFuzzySetAndOneFuzzyAntecedentAndEvaluate)
{
    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);

    auto fuzzyRuleAntecedent1 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet2);

    auto fuzzyRuleAntecedent2 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent2->joinWithAND(fuzzySet1, fuzzyRuleAntecedent1));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent2->evaluate());

    auto fuzzyRuleAntecedent3 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzySet1));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent3->evaluate());

    auto fuzzyRuleAntecedent4 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent4->joinWithOR(fuzzySet1, fuzzyRuleAntecedent1));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent4->evaluate());

    auto fuzzyRuleAntecedent5 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent5->joinWithOR(fuzzyRuleAntecedent1, fuzzySet1));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent5->evaluate());
}

TEST(FuzzyRuleAntecedent, joinTwoFuzzyAntecedentAndEvaluate)
{
    auto fuzzyRuleAntecedent1 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet1);

    auto fuzzyRuleAntecedent2 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);
    auto fuzzySet3 = std::make_shared<FuzzySet>(30, 40, 40, 50);
    fuzzySet3->setPertinence(0.5);
    fuzzyRuleAntecedent2->joinWithOR(fuzzySet2, fuzzySet3);

    auto fuzzyRuleAntecedent3 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent3->evaluate());

    auto fuzzyRuleAntecedent4 = std::make_shared<FuzzyRuleAntecedent>();
    ASSERT_TRUE(fuzzyRuleAntecedent4->joinWithOR(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent4->evaluate());
}

// ##### Tests for FuzzyRuleConsequent

TEST(FuzzyRuleConsequent, addOutputAndEvaluate)
{
    auto fuzzyRuleConsequent = std::make_shared<FuzzyRuleConsequent>();

    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);

    ASSERT_TRUE(fuzzyRuleConsequent->addOutput(fuzzySet1));

    fuzzyRuleConsequent->addOutput(fuzzySet2);

    ASSERT_TRUE(fuzzyRuleConsequent->evaluate(0.5));

    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());
    ASSERT_FLOAT_EQ(0.5, fuzzySet2->getPertinence());
}

// ##### Tests for FuzzyRule

TEST(FuzzyRule, getIndexAndEvaluateExpressionAndIsFired)
{
    auto fuzzyRuleAntecedent1 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet->setPertinence(0.75);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet);

    auto fuzzyRuleAntecedent2 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet2 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet2->setPertinence(0.25);
    fuzzyRuleAntecedent2->joinSingle(fuzzySet2);

    auto fuzzyRuleAntecedent3 = std::make_shared<FuzzyRuleAntecedent>();
    fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

    auto fuzzyRuleConsequent = std::make_shared<FuzzyRuleConsequent>();
    auto fuzzySet3 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzyRuleConsequent->addOutput(fuzzySet3);

    auto fuzzyRule = std::make_shared<FuzzyRule>(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);

    ASSERT_EQ(1, fuzzyRule->getIndex());
    ASSERT_FALSE(fuzzyRule->isFired());

    ASSERT_TRUE(fuzzyRule->evaluateExpression());

    ASSERT_TRUE(fuzzyRule->isFired());
}

// ##### Tests for Fuzzy

TEST(Fuzzy, addFuzzyInput)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    auto fuzzyInput = std::make_shared<FuzzyInput>(1);

    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzyInput->addFuzzySet(fuzzySet1);
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzyInput->addFuzzySet(fuzzySet2);
    auto fuzzySet3 = std::make_shared<FuzzySet>(20, 30, 30, 40);
    fuzzyInput->addFuzzySet(fuzzySet3);

    ASSERT_TRUE(fuzzy->addFuzzyInput(fuzzyInput));
}

TEST(Fuzzy, addFuzzyOutput)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    auto fuzzyOutput = std::make_shared<FuzzyOutput>(1);

    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzyOutput->addFuzzySet(fuzzySet1);
    auto fuzzySet2 = std::make_shared<FuzzySet>(10, 20, 20, 30);
    fuzzyOutput->addFuzzySet(fuzzySet2);
    auto fuzzySet3 = std::make_shared<FuzzySet>(20, 30, 30, 40);
    fuzzyOutput->addFuzzySet(fuzzySet3);

    ASSERT_TRUE(fuzzy->addFuzzyOutput(fuzzyOutput));
}

TEST(Fuzzy, addFuzzyRule)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    auto fuzzyRuleAntecedent1 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet1 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet1);

    auto fuzzyRuleAntecedent2 = std::make_shared<FuzzyRuleAntecedent>();
    auto fuzzySet2 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzySet2->setPertinence(0.75);
    fuzzyRuleAntecedent2->joinSingle(fuzzySet2);

    auto fuzzyRuleAntecedent3 = std::make_shared<FuzzyRuleAntecedent>();
    fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

    auto fuzzyRuleConsequent = std::make_shared<FuzzyRuleConsequent>();
    auto fuzzySet3 = std::make_shared<FuzzySet>(0, 10, 10, 20);
    fuzzyRuleConsequent->addOutput(fuzzySet3);

    auto fuzzyRule = std::make_shared<FuzzyRule>(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);

    ASSERT_TRUE(fuzzy->addFuzzyRule(fuzzyRule));
}

TEST(Fuzzy, setInputAndFuzzifyAndIsFiredRuleAndDefuzzify)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    // FuzzyInput
    auto temperature = std::make_shared<FuzzyInput>(1);

    auto low = std::make_shared<FuzzySet>(0, 10, 10, 20);
    temperature->addFuzzySet(low);
    auto mean = std::make_shared<FuzzySet>(10, 20, 30, 40);
    temperature->addFuzzySet(mean);
    auto high = std::make_shared<FuzzySet>(30, 40, 40, 50);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyOutput
    auto climate = std::make_shared<FuzzyOutput>(1);

    auto cold = std::make_shared<FuzzySet>(0, 10, 10, 20);
    climate->addFuzzySet(cold);
    auto good = std::make_shared<FuzzySet>(10, 20, 30, 40);
    climate->addFuzzySet(good);
    auto hot = std::make_shared<FuzzySet>(30, 40, 40, 50);
    climate->addFuzzySet(hot);

    fuzzy->addFuzzyOutput(climate);

    // Building FuzzyRule
    auto ifTemperatureLow = std::make_shared<FuzzyRuleAntecedent>();
    ifTemperatureLow->joinSingle(low);
    auto thenClimateCold = std::make_shared<FuzzyRuleConsequent>();
    thenClimateCold->addOutput(cold);

    auto fuzzyRule1 = std::make_shared<FuzzyRule>(1, ifTemperatureLow, thenClimateCold);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    auto ifTemperatureMean = std::make_shared<FuzzyRuleAntecedent>();
    ifTemperatureMean->joinSingle(mean);
    auto thenClimateGood = std::make_shared<FuzzyRuleConsequent>();
    thenClimateGood->addOutput(good);

    auto fuzzyRule2 = std::make_shared<FuzzyRule>(2, ifTemperatureMean, thenClimateGood);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    auto ifTemperatureHigh = std::make_shared<FuzzyRuleAntecedent>();
    ifTemperatureHigh->joinSingle(high);
    auto thenClimateHot = std::make_shared<FuzzyRuleConsequent>();
    thenClimateHot->addOutput(cold);

    auto fuzzyRule3 = std::make_shared<FuzzyRule>(3, ifTemperatureHigh, thenClimateHot);
    fuzzy->addFuzzyRule(fuzzyRule3);

    ASSERT_TRUE(fuzzy->setInput(1, 15));

    ASSERT_TRUE(fuzzy->fuzzify());

    ASSERT_TRUE(fuzzy->isFiredRule(1));
    ASSERT_TRUE(fuzzy->isFiredRule(2));
    ASSERT_FALSE(fuzzy->isFiredRule(3));

    ASSERT_FLOAT_EQ(19.729731, fuzzy->defuzzify(1));
}

// ##### Tests from explanation Fuzzy System

// From: https://www.massey.ac.nz/~nhreyes/MASSEY/159741/Lectures/Lec2012-3-159741-FuzzyLogic-v.2.pdf
TEST(Fuzzy, testFromLectureSystemsOne)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    // FuzzyInput
    auto size = std::make_shared<FuzzyInput>(1);

    auto smallSize = std::make_shared<FuzzySet>(-5, -5, 0, 10);
    size->addFuzzySet(smallSize);
    auto largeSize = std::make_shared<FuzzySet>(0, 10, 15, 15);
    size->addFuzzySet(largeSize);

    fuzzy->addFuzzyInput(size);

    // FuzzyInput
    auto weight = std::make_shared<FuzzyInput>(2);

    auto smallWeight = std::make_shared<FuzzySet>(-50, -50, 0, 100);
    weight->addFuzzySet(smallWeight);
    auto largeWeight = std::make_shared<FuzzySet>(0, 100, 150, 150);
    weight->addFuzzySet(largeWeight);

    fuzzy->addFuzzyInput(weight);

    // FuzzyOutput
    auto quality = std::make_shared<FuzzyOutput>(1);

    auto bad = std::make_shared<FuzzySet>(-0.25, -0.25, 0, 0.5);
    quality->addFuzzySet(bad);
    auto medium = std::make_shared<FuzzySet>(0, 0.5, 0.5, 1.0);
    quality->addFuzzySet(medium);
    auto good = std::make_shared<FuzzySet>(0.5, 1.0, 1.25, 1.25);
    quality->addFuzzySet(good);

    fuzzy->addFuzzyOutput(quality);

    // Building FuzzyRule
    auto ifSizeSmallAndWeightSmall = std::make_shared<FuzzyRuleAntecedent>();
    ifSizeSmallAndWeightSmall->joinWithAND(smallSize, smallWeight);
    auto thenQualityBad = std::make_shared<FuzzyRuleConsequent>();
    thenQualityBad->addOutput(bad);
    auto fuzzyRule1 = std::make_shared<FuzzyRule>(1, ifSizeSmallAndWeightSmall, thenQualityBad);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    auto ifSizeSmallAndWeightLarge = std::make_shared<FuzzyRuleAntecedent>();
    ifSizeSmallAndWeightLarge->joinWithAND(smallSize, largeWeight);
    auto thenQualityMedium1 = std::make_shared<FuzzyRuleConsequent>();
    thenQualityMedium1->addOutput(medium);
    auto fuzzyRule2 = std::make_shared<FuzzyRule>(2, ifSizeSmallAndWeightLarge, thenQualityMedium1);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    auto ifSizeLargeAndWeightSmall = std::make_shared<FuzzyRuleAntecedent>();
    ifSizeLargeAndWeightSmall->joinWithAND(largeSize, smallWeight);
    auto thenQualityMedium2 = std::make_shared<FuzzyRuleConsequent>();
    thenQualityMedium2->addOutput(medium);
    auto fuzzyRule3 = std::make_shared<FuzzyRule>(3, ifSizeLargeAndWeightSmall, thenQualityMedium2);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule
    auto ifSizeLargeAndWeightLarge = std::make_shared<FuzzyRuleAntecedent>();
    ifSizeLargeAndWeightLarge->joinWithAND(largeSize, largeWeight);
    auto thenQualityGood = std::make_shared<FuzzyRuleConsequent>();
    thenQualityGood->addOutput(good);
    auto fuzzyRule4 = std::make_shared<FuzzyRule>(4, ifSizeLargeAndWeightLarge, thenQualityGood);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // run it
    fuzzy->setInput(1, 2);
    fuzzy->setInput(2, 25);
    fuzzy->fuzzify();

    ASSERT_FLOAT_EQ(0.75, ifSizeSmallAndWeightSmall->evaluate());
    ASSERT_FLOAT_EQ(0.25, ifSizeSmallAndWeightLarge->evaluate());
    ASSERT_FLOAT_EQ(0.2, ifSizeLargeAndWeightSmall->evaluate());
    ASSERT_FLOAT_EQ(0.2, ifSizeLargeAndWeightLarge->evaluate());

    ASSERT_FLOAT_EQ(0.3698, fuzzy->defuzzify(1));
}

// From: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.486.1238&rep=rep1&type=pdf
TEST(Fuzzy, testFromLectureSystemsTwo)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    // FuzzyInput
    auto temperature = std::make_shared<FuzzyInput>(1);

    auto veryLow = std::make_shared<FuzzySet>(-5, -5, 0, 15);
    temperature->addFuzzySet(veryLow);
    auto low = std::make_shared<FuzzySet>(10, 20, 20, 30);
    temperature->addFuzzySet(low);
    auto high = std::make_shared<FuzzySet>(25, 30, 30, 35);
    temperature->addFuzzySet(high);
    auto veryHigh = std::make_shared<FuzzySet>(30, 45, 50, 50);
    temperature->addFuzzySet(veryHigh);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    auto humidity = std::make_shared<FuzzyInput>(2);

    auto dry = std::make_shared<FuzzySet>(-5, -5, 0, 30);
    humidity->addFuzzySet(dry);
    auto comfortable = std::make_shared<FuzzySet>(20, 35, 35, 50);
    humidity->addFuzzySet(comfortable);
    auto humid = std::make_shared<FuzzySet>(40, 55, 55, 70);
    humidity->addFuzzySet(humid);
    auto sticky = std::make_shared<FuzzySet>(60, 100, 105, 105);
    humidity->addFuzzySet(sticky);

    fuzzy->addFuzzyInput(humidity);

    // FuzzyOutput
    auto speed = std::make_shared<FuzzyOutput>(1);

    auto off = std::make_shared<FuzzySet>(0, 0, 0, 0);
    speed->addFuzzySet(off);
    auto lowHumidity = std::make_shared<FuzzySet>(30, 45, 45, 60);
    speed->addFuzzySet(lowHumidity);
    auto medium = std::make_shared<FuzzySet>(50, 65, 65, 80);
    speed->addFuzzySet(medium);
    auto fast = std::make_shared<FuzzySet>(70, 90, 95, 95);
    speed->addFuzzySet(fast);

    fuzzy->addFuzzyOutput(speed);

    // Building FuzzyRule
    auto ifVeryLowAndDry = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryLowAndDry->joinWithAND(veryLow, dry);
    auto thenOff1 = std::make_shared<FuzzyRuleConsequent>();
    thenOff1->addOutput(off);
    auto fuzzyRule1 = std::make_shared<FuzzyRule>(1, ifVeryLowAndDry, thenOff1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    auto ifVeryLowAndComfortable = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryLowAndComfortable->joinWithAND(veryLow, comfortable);
    auto thenOff2 = std::make_shared<FuzzyRuleConsequent>();
    thenOff2->addOutput(off);
    auto fuzzyRule2 = std::make_shared<FuzzyRule>(2, ifVeryLowAndComfortable, thenOff2);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    auto ifVeryLowAndHumid = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryLowAndHumid->joinWithAND(veryLow, humid);
    auto thenOff3 = std::make_shared<FuzzyRuleConsequent>();
    thenOff3->addOutput(off);
    auto fuzzyRule3 = std::make_shared<FuzzyRule>(3, ifVeryLowAndHumid, thenOff3);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule
    auto ifVeryLowAndSticky = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryLowAndSticky->joinWithAND(veryLow, sticky);
    auto thenLow1 = std::make_shared<FuzzyRuleConsequent>();
    thenLow1->addOutput(lowHumidity);
    auto fuzzyRule4 = std::make_shared<FuzzyRule>(4, ifVeryLowAndSticky, thenLow1);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // Building FuzzyRule
    auto ifLowAndDry = std::make_shared<FuzzyRuleAntecedent>();
    ifLowAndDry->joinWithAND(low, dry);
    auto thenOff4 = std::make_shared<FuzzyRuleConsequent>();
    thenOff4->addOutput(off);
    auto fuzzyRule5 = std::make_shared<FuzzyRule>(5, ifLowAndDry, thenOff4);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // Building FuzzyRule
    auto ifLowAndComfortable = std::make_shared<FuzzyRuleAntecedent>();
    ifLowAndComfortable->joinWithAND(low, comfortable);
    auto thenOff5 = std::make_shared<FuzzyRuleConsequent>();
    thenOff5->addOutput(off);
    auto fuzzyRule6 = std::make_shared<FuzzyRule>(6, ifLowAndComfortable, thenOff5);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // Building FuzzyRule
    auto ifLowAndHumid = std::make_shared<FuzzyRuleAntecedent>();
    ifLowAndHumid->joinWithAND(low, humid);
    auto thenLow2 = std::make_shared<FuzzyRuleConsequent>();
    thenLow2->addOutput(lowHumidity);
    auto fuzzyRule7 = std::make_shared<FuzzyRule>(7, ifLowAndHumid, thenLow2);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // Building FuzzyRule
    auto ifLowAndSticky = std::make_shared<FuzzyRuleAntecedent>();
    ifLowAndSticky->joinWithAND(low, sticky);
    auto thenMedium1 = std::make_shared<FuzzyRuleConsequent>();
    thenMedium1->addOutput(medium);
    auto fuzzyRule8 = std::make_shared<FuzzyRule>(8, ifLowAndSticky, thenMedium1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // Building FuzzyRule
    auto ifHighAndDry = std::make_shared<FuzzyRuleAntecedent>();
    ifHighAndDry->joinWithAND(high, dry);
    auto thenLow3 = std::make_shared<FuzzyRuleConsequent>();
    thenLow3->addOutput(lowHumidity);
    auto fuzzyRule9 = std::make_shared<FuzzyRule>(9, ifHighAndDry, thenLow3);
    fuzzy->addFuzzyRule(fuzzyRule9);

    // Building FuzzyRule
    auto ifHighAndComfortable = std::make_shared<FuzzyRuleAntecedent>();
    ifHighAndComfortable->joinWithAND(high, comfortable);
    auto thenMedium2 = std::make_shared<FuzzyRuleConsequent>();
    thenMedium2->addOutput(medium);
    auto fuzzyRule10 = std::make_shared<FuzzyRule>(10, ifHighAndComfortable, thenMedium2);
    fuzzy->addFuzzyRule(fuzzyRule10);

    // Building FuzzyRule
    auto ifHighAndHumid = std::make_shared<FuzzyRuleAntecedent>();
    ifHighAndHumid->joinWithAND(high, humid);
    auto thenFast1 = std::make_shared<FuzzyRuleConsequent>();
    thenFast1->addOutput(fast);
    auto fuzzyRule11 = std::make_shared<FuzzyRule>(11, ifHighAndHumid, thenFast1);
    fuzzy->addFuzzyRule(fuzzyRule11);

    // Building FuzzyRule
    auto ifHighAndSticky = std::make_shared<FuzzyRuleAntecedent>();
    ifHighAndSticky->joinWithAND(high, sticky);
    auto thenFast2 = std::make_shared<FuzzyRuleConsequent>();
    thenFast2->addOutput(fast);
    auto fuzzyRule12 = std::make_shared<FuzzyRule>(12, ifHighAndSticky, thenFast2);
    fuzzy->addFuzzyRule(fuzzyRule12);

    // Building FuzzyRule
    auto ifVeryHighAndDry = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryHighAndDry->joinWithAND(veryHigh, dry);
    auto thenMedium3 = std::make_shared<FuzzyRuleConsequent>();
    thenMedium3->addOutput(medium);
    auto fuzzyRule13 = std::make_shared<FuzzyRule>(13, ifVeryHighAndDry, thenMedium3);
    fuzzy->addFuzzyRule(fuzzyRule13);

    // Building FuzzyRule
    auto ifVeryHighAndComfortable = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryHighAndComfortable->joinWithAND(veryHigh, comfortable);
    auto thenFast3 = std::make_shared<FuzzyRuleConsequent>();
    thenFast3->addOutput(fast);
    auto fuzzyRule14 = std::make_shared<FuzzyRule>(14, ifVeryHighAndComfortable, thenFast3);
    fuzzy->addFuzzyRule(fuzzyRule14);

    // Building FuzzyRule
    auto ifVeryHighAndHumid = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryHighAndHumid->joinWithAND(veryHigh, humid);
    auto thenFast4 = std::make_shared<FuzzyRuleConsequent>();
    thenFast4->addOutput(fast);
    auto fuzzyRule15 = std::make_shared<FuzzyRule>(15, ifVeryHighAndHumid, thenFast4);
    fuzzy->addFuzzyRule(fuzzyRule15);

    // Building FuzzyRule
    auto ifVeryHighAndSticky = std::make_shared<FuzzyRuleAntecedent>();
    ifVeryHighAndSticky->joinWithAND(veryHigh, sticky);
    auto thenFast5 = std::make_shared<FuzzyRuleConsequent>();
    thenFast5->addOutput(fast);
    auto fuzzyRule16 = std::make_shared<FuzzyRule>(16, ifVeryHighAndSticky, thenFast5);
    fuzzy->addFuzzyRule(fuzzyRule16);

    // run it
    fuzzy->setInput(1, 2);
    fuzzy->setInput(2, 25);
    fuzzy->fuzzify();

    ASSERT_FLOAT_EQ(0.3698, fuzzy->defuzzify(1));
}

// ##### Tests from real systems, received from eFLL users

// From miss Casco (Paraguay)
TEST(Fuzzy, testFromLibraryUsersSystemsCasco)
{
    auto fuzzy = std::make_shared<Fuzzy>();

    // FuzzyInput
    auto humedad = std::make_shared<FuzzyInput>(1);

    auto seco = std::make_shared<FuzzySet>(0, 0, 0, 42.5);
    humedad->addFuzzySet(seco);
    auto humedo = std::make_shared<FuzzySet>(37.5, 60, 60, 82.5);
    humedad->addFuzzySet(humedo);
    auto encharcado = std::make_shared<FuzzySet>(77.5, 100, 100, 100);
    humedad->addFuzzySet(encharcado);

    fuzzy->addFuzzyInput(humedad);

    // FuzzyInput
    auto temperatura = std::make_shared<FuzzyInput>(2);

    auto frio = std::make_shared<FuzzySet>(-5, -5, -5, 12.5);
    temperatura->addFuzzySet(frio);
    auto templado = std::make_shared<FuzzySet>(7.5, 17.5, 17.5, 27.5);
    temperatura->addFuzzySet(templado);
    auto calor = std::make_shared<FuzzySet>(22.5, 45, 45, 45);
    temperatura->addFuzzySet(calor);

    fuzzy->addFuzzyInput(temperatura);

    // FuzzyOutput
    auto tiempo = std::make_shared<FuzzyOutput>(1);

    auto nada = std::make_shared<FuzzySet>(0, 0, 0, 0);
    tiempo->addFuzzySet(nada);
    auto muyPoco = std::make_shared<FuzzySet>(0, 0, 0, 5.5);
    tiempo->addFuzzySet(muyPoco);
    auto poco = std::make_shared<FuzzySet>(4.5, 7.5, 7.5, 10.5);
    tiempo->addFuzzySet(poco);
    auto medio = std::make_shared<FuzzySet>(9.5, 12.5, 12.5, 15.5);
    tiempo->addFuzzySet(medio);
    auto bastante = std::make_shared<FuzzySet>(14.5, 17.5, 17.5, 20.5);
    tiempo->addFuzzySet(bastante);
    auto mucho = std::make_shared<FuzzySet>(19.5, 22.5, 22.5, 25.5);
    tiempo->addFuzzySet(mucho);
    auto muchisimo = std::make_shared<FuzzySet>(24.5, 30, 30, 30);
    tiempo->addFuzzySet(muchisimo);

    fuzzy->addFuzzyOutput(tiempo);

    // ############## Rule 1
    auto humedadSecoandTemperaturaFrio = std::make_shared<FuzzyRuleAntecedent>();
    humedadSecoandTemperaturaFrio->joinWithAND(seco, frio);
    auto thenMedio_1 = std::make_shared<FuzzyRuleConsequent>();
    thenMedio_1->addOutput(medio);

    auto fuzzyRule1 = std::make_shared<FuzzyRule>(1, humedadSecoandTemperaturaFrio, thenMedio_1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // ############## Rule 2
    auto humedadHumedoandTemperaturaFrio = std::make_shared<FuzzyRuleAntecedent>();
    humedadHumedoandTemperaturaFrio->joinWithAND(humedo, frio);
    auto thenMuyPoco_1 = std::make_shared<FuzzyRuleConsequent>();
    thenMuyPoco_1->addOutput(muyPoco);

    auto fuzzyRule2 = std::make_shared<FuzzyRule>(2, humedadHumedoandTemperaturaFrio, thenMuyPoco_1);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // ############## Rule 3
    auto humedadEncharcadoandTemperaturaFrio = std::make_shared<FuzzyRuleAntecedent>();
    humedadEncharcadoandTemperaturaFrio->joinWithAND(encharcado, frio);
    auto thenNada_1 = std::make_shared<FuzzyRuleConsequent>();
    thenNada_1->addOutput(nada);

    auto fuzzyRule3 = std::make_shared<FuzzyRule>(3, humedadEncharcadoandTemperaturaFrio, thenNada_1);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // ############## Rule 4
    auto humedadSecoandTemperaturaTemplado = std::make_shared<FuzzyRuleAntecedent>();
    humedadSecoandTemperaturaTemplado->joinWithAND(seco, templado);
    auto thenBastante = std::make_shared<FuzzyRuleConsequent>();
    thenBastante->addOutput(bastante);

    auto fuzzyRule4 = std::make_shared<FuzzyRule>(4, humedadSecoandTemperaturaTemplado, thenBastante);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // ############## Rule 5
    auto humedadHumedoandTemperaturaTemplado = std::make_shared<FuzzyRuleAntecedent>();
    humedadHumedoandTemperaturaTemplado->joinWithAND(humedo, templado);
    auto thenMedio_2 = std::make_shared<FuzzyRuleConsequent>();
    thenMedio_2->addOutput(medio);

    auto fuzzyRule5 = std::make_shared<FuzzyRule>(5, humedadHumedoandTemperaturaTemplado, thenMedio_2);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // ############## Rule 6
    auto humedadEncharcadoandTemperaturaTemplado = std::make_shared<FuzzyRuleAntecedent>();
    humedadEncharcadoandTemperaturaTemplado->joinWithAND(encharcado, templado);
    auto thenMuyPoco_2 = std::make_shared<FuzzyRuleConsequent>();
    thenMuyPoco_2->addOutput(muyPoco);

    auto fuzzyRule6 = std::make_shared<FuzzyRule>(6, humedadEncharcadoandTemperaturaTemplado, thenMuyPoco_2);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // ############## Rule 7
    auto humedadSecoandTemperaturaCalor = std::make_shared<FuzzyRuleAntecedent>();
    humedadSecoandTemperaturaCalor->joinWithAND(seco, calor);
    auto thenMucho = std::make_shared<FuzzyRuleConsequent>();
    thenMucho->addOutput(mucho);

    auto fuzzyRule7 = std::make_shared<FuzzyRule>(7, humedadSecoandTemperaturaCalor, thenMucho);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // ############## Rule 8
    auto humedadHumedoandTemperaturaCalor = std::make_shared<FuzzyRuleAntecedent>();
    humedadHumedoandTemperaturaCalor->joinWithAND(humedo, calor);
    auto thenMuchisimo = std::make_shared<FuzzyRuleConsequent>();
    thenMuchisimo->addOutput(muchisimo);

    auto fuzzyRule8 = std::make_shared<FuzzyRule>(8, humedadHumedoandTemperaturaCalor, thenBastante);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // ############## Rule 9
    auto humedadEncharcadoandTemperaturaCalor = std::make_shared<FuzzyRuleAntecedent>();
    humedadEncharcadoandTemperaturaCalor->joinWithAND(encharcado, calor);
    auto thenNada_2 = std::make_shared<FuzzyRuleConsequent>();
    thenNada_2->addOutput(nada);

    auto fuzzyRule9 = std::make_shared<FuzzyRule>(9, humedadEncharcadoandTemperaturaCalor, thenNada_2);
    fuzzy->addFuzzyRule(fuzzyRule9);

    // TEST 01
    fuzzy->setInput(1, 78.4);
    fuzzy->setInput(2, 42.5);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(17.3, fuzzy->defuzzify(1));

    // TEST 02
    fuzzy->setInput(1, 81.2);
    fuzzy->setInput(2, 26.1);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(8.28, fuzzy->defuzzify(1));

    // TEST 03
    fuzzy->setInput(1, 81.2);
    fuzzy->setInput(2, 33.9);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(15.3, fuzzy->defuzzify(1));
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify09)
{
    // Instantiating an object of library
    auto fuzzy = std::make_shared<Fuzzy>();

    FuzzyInput::SharedPointer shift;
    FuzzyInput::SharedPointer distance;

    FuzzyOutput::SharedPointer steeringangle;
    FuzzyOutput::SharedPointer runningspeed;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_4AndDistanceD_0;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_4AndRunningspeedSpeed_2;
    FuzzyRule::SharedPointer fuzzyRule1;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_4AndDistanceD_1;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_4AndRunningspeedSpeed_1;
    FuzzyRule::SharedPointer fuzzyRule2;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_4AndDistanceD_2;
    FuzzyRule::SharedPointer fuzzyRule3;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_4AndDistanceD_3;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_4AndRunningspeedSpeed_0;
    FuzzyRule::SharedPointer fuzzyRule4;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_4AndDistanceD_4;
    FuzzyRule::SharedPointer fuzzyRule5;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_3AndDistanceD_0;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_3AndRunningspeedSpeed_3;
    FuzzyRule::SharedPointer fuzzyRule6;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_3AndDistanceD_1;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_3AndRunningspeedSpeed_2;
    FuzzyRule::SharedPointer fuzzyRule7;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_3AndDistanceD_2;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_3AndRunningspeedSpeed_1;
    FuzzyRule::SharedPointer fuzzyRule8;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_3AndDistanceD_3;
    FuzzyRule::SharedPointer fuzzyRule9;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_3AndDistanceD_4;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_3AndRunningspeedSpeed_0;
    FuzzyRule::SharedPointer fuzzyRule10;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_2;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_2AndRunningspeedSpeed_4;
    FuzzyRule::SharedPointer fuzzyRule11;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_1AndDistanceD_0;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_1AndRunningspeedSpeed_3;
    FuzzyRule::SharedPointer fuzzyRule12;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_1AndDistanceD_1;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_1AndRunningspeedSpeed_2;
    FuzzyRule::SharedPointer fuzzyRule13;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_1AndDistanceD_2;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_1AndRunningspeedSpeed_1;
    FuzzyRule::SharedPointer fuzzyRule14;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_1AndDistanceD_3;
    FuzzyRule::SharedPointer fuzzyRule15;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_1AndDistanceD_4;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_1AndRunningspeedSpeed_0;
    FuzzyRule::SharedPointer fuzzyRule16;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_0AndDistanceD_0;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_0AndRunningspeedSpeed_2;
    FuzzyRule::SharedPointer fuzzyRule17;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_0AndDistanceD_1;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_0AndRunningspeedSpeed_1;
    FuzzyRule::SharedPointer fuzzyRule18;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_0AndDistanceD_2;
    FuzzyRule::SharedPointer fuzzyRule19;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_0AndDistanceD_3;
    FuzzyRuleConsequent::SharedPointer thenSteeringangleAng_0AndRunningspeedSpeed_0;
    FuzzyRule::SharedPointer fuzzyRule20;

    FuzzyRuleAntecedent::SharedPointer ifShiftS_0AndDistanceD_4;
    FuzzyRule::SharedPointer fuzzyRule21;

    // Fuzzy set
    auto s_0 = std::make_shared<FuzzySet>(9, 21, 21, 33);      //veri left
    auto s_1 = std::make_shared<FuzzySet>(24, 31.5, 31.5, 39); //medium left
    auto s_2 = std::make_shared<FuzzySet>(35, 39, 39, 43);     //zero
    auto s_3 = std::make_shared<FuzzySet>(39, 46.5, 46.5, 54); //medium right
    auto s_4 = std::make_shared<FuzzySet>(45, 57, 57, 69);     //very right

    auto d_0 = std::make_shared<FuzzySet>(0, 5, 5, 10);    //farthest
    auto d_1 = std::make_shared<FuzzySet>(5, 10, 10, 15);  //far
    auto d_2 = std::make_shared<FuzzySet>(10, 15, 15, 20); //middle
    auto d_3 = std::make_shared<FuzzySet>(15, 25, 25, 35); //near
    auto d_4 = std::make_shared<FuzzySet>(25, 42, 42, 59); //nearest

    auto ang_0 = std::make_shared<FuzzySet>(60, 70, 70, 80);     //leftmost
    auto ang_1 = std::make_shared<FuzzySet>(69, 79, 79, 89);     //left
    auto ang_2 = std::make_shared<FuzzySet>(88, 90, 90, 92);     //middle
    auto ang_3 = std::make_shared<FuzzySet>(91, 101, 101, 111);  //right
    auto ang_4 = std::make_shared<FuzzySet>(100, 110, 110, 120); // rightmost

    auto speed_0 = std::make_shared<FuzzySet>(50, 75, 75, 100);    //very slow
    auto speed_1 = std::make_shared<FuzzySet>(75, 110, 110, 145);  //slow
    auto speed_2 = std::make_shared<FuzzySet>(120, 150, 150, 180); //middle
    auto speed_3 = std::make_shared<FuzzySet>(155, 190, 190, 225); //fast
    auto speed_4 = std::make_shared<FuzzySet>(200, 225, 225, 250); //veryfast

    // Fuzzy input
    shift = std::make_shared<FuzzyInput>(1);
    shift->addFuzzySet(s_0);
    shift->addFuzzySet(s_1);
    shift->addFuzzySet(s_2);
    shift->addFuzzySet(s_3);
    shift->addFuzzySet(s_4);
    fuzzy->addFuzzyInput(shift);

    distance = std::make_shared<FuzzyInput>(2);
    distance->addFuzzySet(d_0);
    distance->addFuzzySet(d_1);
    distance->addFuzzySet(d_2);
    distance->addFuzzySet(d_3);
    distance->addFuzzySet(d_4);
    fuzzy->addFuzzyInput(distance);

    // Fuzzy output
    steeringangle = std::make_shared<FuzzyOutput>(1);
    steeringangle->addFuzzySet(ang_0);
    steeringangle->addFuzzySet(ang_1);
    steeringangle->addFuzzySet(ang_2);
    steeringangle->addFuzzySet(ang_3);
    steeringangle->addFuzzySet(ang_4);
    fuzzy->addFuzzyOutput(steeringangle);

    runningspeed = std::make_shared<FuzzyOutput>(2);
    runningspeed->addFuzzySet(speed_0);
    runningspeed->addFuzzySet(speed_1);
    runningspeed->addFuzzySet(speed_2);
    runningspeed->addFuzzySet(speed_3);
    fuzzy->addFuzzyOutput(runningspeed);

    // Fuzzy rule
    ifShiftS_4AndDistanceD_0 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_4AndDistanceD_0->joinWithAND(s_4, d_0);
    thenSteeringangleAng_4AndRunningspeedSpeed_2 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(ang_4);
    thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule1 = std::make_shared<FuzzyRule>(1, ifShiftS_4AndDistanceD_0, thenSteeringangleAng_4AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule1);

    ifShiftS_4AndDistanceD_1 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_4AndDistanceD_1->joinWithAND(s_4, d_1);
    thenSteeringangleAng_4AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(ang_4);
    thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule2 = std::make_shared<FuzzyRule>(2, ifShiftS_4AndDistanceD_1, thenSteeringangleAng_4AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule2);

    ifShiftS_4AndDistanceD_2 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_4AndDistanceD_2->joinWithAND(s_4, d_2);
    // FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(ang_4);
    // thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule3 = std::make_shared<FuzzyRule>(3, ifShiftS_4AndDistanceD_2, thenSteeringangleAng_4AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule3);

    ifShiftS_4AndDistanceD_3 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_4AndDistanceD_3->joinWithAND(s_4, d_3);
    thenSteeringangleAng_4AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
    thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule4 = std::make_shared<FuzzyRule>(4, ifShiftS_4AndDistanceD_3, thenSteeringangleAng_4AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule4);

    ifShiftS_4AndDistanceD_4 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_4AndDistanceD_4->joinWithAND(s_4, d_4);
    // FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
    // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule5 = std::make_shared<FuzzyRule>(5, ifShiftS_4AndDistanceD_4, thenSteeringangleAng_4AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule5);

    ifShiftS_3AndDistanceD_0 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_3AndDistanceD_0->joinWithAND(s_3, d_0);
    thenSteeringangleAng_3AndRunningspeedSpeed_3 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(speed_3);
    fuzzyRule6 = std::make_shared<FuzzyRule>(6, ifShiftS_3AndDistanceD_0, thenSteeringangleAng_3AndRunningspeedSpeed_3);
    fuzzy->addFuzzyRule(fuzzyRule6);

    ifShiftS_3AndDistanceD_1 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_3AndDistanceD_1->joinWithAND(s_3, d_1);
    thenSteeringangleAng_3AndRunningspeedSpeed_2 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule7 = std::make_shared<FuzzyRule>(7, ifShiftS_3AndDistanceD_1, thenSteeringangleAng_3AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule7);

    ifShiftS_3AndDistanceD_2 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_3AndDistanceD_2->joinWithAND(s_3, d_2);
    thenSteeringangleAng_3AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule8 = std::make_shared<FuzzyRule>(8, ifShiftS_3AndDistanceD_2, thenSteeringangleAng_3AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    ifShiftS_3AndDistanceD_3 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_3AndDistanceD_3->joinWithAND(s_3, d_3);
    // FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
    // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule9 = std::make_shared<FuzzyRule>(9, ifShiftS_3AndDistanceD_3, thenSteeringangleAng_3AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule9);

    ifShiftS_3AndDistanceD_4 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_3AndDistanceD_4->joinWithAND(s_3, d_4);
    thenSteeringangleAng_3AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_3AndRunningspeedSpeed_0->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule10 = std::make_shared<FuzzyRule>(10, ifShiftS_3AndDistanceD_4, thenSteeringangleAng_3AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule10);

    ifShiftS_2 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_2->joinSingle(s_2);
    thenSteeringangleAng_2AndRunningspeedSpeed_4 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_2AndRunningspeedSpeed_4->addOutput(ang_2);
    thenSteeringangleAng_2AndRunningspeedSpeed_4->addOutput(speed_4);
    fuzzyRule11 = std::make_shared<FuzzyRule>(11, ifShiftS_2, thenSteeringangleAng_2AndRunningspeedSpeed_4);
    fuzzy->addFuzzyRule(fuzzyRule11);

    ifShiftS_1AndDistanceD_0 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_1AndDistanceD_0->joinWithAND(s_1, d_0);
    thenSteeringangleAng_1AndRunningspeedSpeed_3 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(speed_3);
    fuzzyRule12 = std::make_shared<FuzzyRule>(12, ifShiftS_1AndDistanceD_0, thenSteeringangleAng_1AndRunningspeedSpeed_3);
    fuzzy->addFuzzyRule(fuzzyRule12);

    ifShiftS_1AndDistanceD_1 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_1AndDistanceD_1->joinWithAND(s_1, d_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_2 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule13 = std::make_shared<FuzzyRule>(13, ifShiftS_1AndDistanceD_1, thenSteeringangleAng_1AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule13);

    ifShiftS_1AndDistanceD_2 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_1AndDistanceD_2->joinWithAND(s_1, d_2);
    thenSteeringangleAng_1AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule14 = std::make_shared<FuzzyRule>(14, ifShiftS_1AndDistanceD_2, thenSteeringangleAng_1AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule14);

    ifShiftS_1AndDistanceD_3 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_1AndDistanceD_3->joinWithAND(s_1, d_3);
    // FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
    // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule15 = std::make_shared<FuzzyRule>(15, ifShiftS_1AndDistanceD_3, thenSteeringangleAng_1AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule15);

    ifShiftS_1AndDistanceD_4 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_1AndDistanceD_4->joinWithAND(s_1, d_4);
    thenSteeringangleAng_1AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule16 = std::make_shared<FuzzyRule>(16, ifShiftS_1AndDistanceD_4, thenSteeringangleAng_1AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule16);

    ifShiftS_0AndDistanceD_0 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_0AndDistanceD_0->joinWithAND(s_0, d_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_2 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule17 = std::make_shared<FuzzyRule>(17, ifShiftS_0AndDistanceD_0, thenSteeringangleAng_0AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule17);

    ifShiftS_0AndDistanceD_1 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_0AndDistanceD_1->joinWithAND(s_0, d_1);
    thenSteeringangleAng_0AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule18 = std::make_shared<FuzzyRule>(18, ifShiftS_0AndDistanceD_1, thenSteeringangleAng_0AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule18);

    ifShiftS_0AndDistanceD_2 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_0AndDistanceD_2->joinWithAND(s_0, d_2);
    // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_1 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
    // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule19 = std::make_shared<FuzzyRule>(19, ifShiftS_0AndDistanceD_2, thenSteeringangleAng_0AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule19);

    ifShiftS_0AndDistanceD_3 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_0AndDistanceD_3->joinWithAND(s_0, d_3);
    thenSteeringangleAng_0AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule20 = std::make_shared<FuzzyRule>(20, ifShiftS_0AndDistanceD_3, thenSteeringangleAng_0AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule20);

    ifShiftS_0AndDistanceD_4 = std::make_shared<FuzzyRuleAntecedent>();
    ifShiftS_0AndDistanceD_4->joinWithAND(s_0, d_4);
    // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_0 = std::make_shared<FuzzyRuleConsequent>();
    // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
    // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule21 = std::make_shared<FuzzyRule>(21, ifShiftS_0AndDistanceD_4, thenSteeringangleAng_0AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule21);

    float target_x = 21.88; //    key in the digital value
    float target_y = 32;

    // target_x and target_y are the inputs
    fuzzy->setInput(1, target_x); // shift
    fuzzy->setInput(2, target_y); // deistance

    fuzzy->fuzzify(); // Executing the fuzzification

    float output1 = fuzzy->defuzzify(1); // steering angle
    float output2 = fuzzy->defuzzify(2); // running speed

    ASSERT_NEAR(70.0, output1, 0.01);
    ASSERT_NEAR(75.0, output2, 0.01);
}

// ##### MAIN

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
