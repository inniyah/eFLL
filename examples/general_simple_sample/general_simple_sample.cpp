#include <iostream>
#include <memory>
#include <time.h>

#include "../../source/Fuzzy.h"

using namespace std;
using namespace eFLL;

int random(int from, int to)
{
    return (rand() % (to - from)) + from;
}

int main(int argc, char *argv[])
{
    // Set a seed to rand
    srand((unsigned)time(0));

    // Instantiating a Fuzzy object
    auto fuzzy = std::make_shared<Fuzzy>();

    // Instantiating a FuzzyInput object
    auto distance = std::make_shared<FuzzyInput>(1);
    // Instantiating a FuzzySet object
    auto small = std::make_shared<FuzzySet>(0, 20, 20, 40);
    // Including the FuzzySet into FuzzyInput
    distance->addFuzzySet(small);
    // Instantiating a FuzzySet object
    auto safe = std::make_shared<FuzzySet>(30, 50, 50, 70);
    // Including the FuzzySet into FuzzyInput
    distance->addFuzzySet(safe);
    // Instantiating a FuzzySet object
    auto big = std::make_shared<FuzzySet>(60, 80, 80, 80);
    // Including the FuzzySet into FuzzyInput
    distance->addFuzzySet(big);
    // Including the FuzzyInput into Fuzzy
    fuzzy->addFuzzyInput(distance);

    // Instantiating a FuzzyOutput objects
    auto speed = std::make_shared<FuzzyOutput>(1);
    // Instantiating a FuzzySet object
    auto slow = std::make_shared<FuzzySet>(0, 10, 10, 20);
    // Including the FuzzySet into FuzzyOutput
    speed->addFuzzySet(slow);
    // Instantiating a FuzzySet object
    auto average = std::make_shared<FuzzySet>(10, 20, 30, 40);
    // Including the FuzzySet into FuzzyOutput
    speed->addFuzzySet(average);
    // Instantiating a FuzzySet object
    auto fast = std::make_shared<FuzzySet>(30, 40, 40, 50);
    // Including the FuzzySet into FuzzyOutput
    speed->addFuzzySet(fast);
    // Including the FuzzyOutput into Fuzzy
    fuzzy->addFuzzyOutput(speed);

    // Building FuzzyRule "IF distance = small THEN speed = slow"
    // Instantiating a FuzzyRuleAntecedent objects
    auto ifDistanceSmall = std::make_shared<FuzzyRuleAntecedent>();
    // Creating a FuzzyRuleAntecedent with just a single FuzzySet
    ifDistanceSmall->joinSingle(small);
    // Instantiating a FuzzyRuleConsequent objects
    auto thenSpeedSlow = std::make_shared<FuzzyRuleConsequent>();
    // Including a FuzzySet to this FuzzyRuleConsequent
    thenSpeedSlow->addOutput(slow);
    // Instantiating a FuzzyRule objects
    auto fuzzyRule01 = std::make_shared<FuzzyRule>(1, ifDistanceSmall, thenSpeedSlow);
    // Including the FuzzyRule into Fuzzy
    fuzzy->addFuzzyRule(fuzzyRule01);

    // Building FuzzyRule "IF distance = safe THEN speed = average"
    // Instantiating a FuzzyRuleAntecedent objects
    auto ifDistanceSafe = std::make_shared<FuzzyRuleAntecedent>();
    // Creating a FuzzyRuleAntecedent with just a single FuzzySet
    ifDistanceSafe->joinSingle(safe);
    // Instantiating a FuzzyRuleConsequent objects
    auto thenSpeedAverage = std::make_shared<FuzzyRuleConsequent>();
    // Including a FuzzySet to this FuzzyRuleConsequent
    thenSpeedAverage->addOutput(average);
    // Instantiating a FuzzyRule objects
    auto fuzzyRule02 = std::make_shared<FuzzyRule>(2, ifDistanceSafe, thenSpeedAverage);
    // Including the FuzzyRule into Fuzzy
    fuzzy->addFuzzyRule(fuzzyRule02);

    // Building FuzzyRule "IF distance = big THEN speed = high"
    // Instantiating a FuzzyRuleAntecedent objects
    auto ifDistanceBig = std::make_shared<FuzzyRuleAntecedent>();
    // Creating a FuzzyRuleAntecedent with just a single FuzzySet
    ifDistanceBig->joinSingle(big);
    // Instantiating a FuzzyRuleConsequent objects
    auto thenSpeedFast = std::make_shared<FuzzyRuleConsequent>();
    // Including a FuzzySet to this FuzzyRuleConsequent
    thenSpeedFast->addOutput(fast);
    // Instantiating a FuzzyRule objects
    auto fuzzyRule03 = std::make_shared<FuzzyRule>(3, ifDistanceBig, thenSpeedFast);
    // Including the FuzzyRule into Fuzzy
    fuzzy->addFuzzyRule(fuzzyRule03);

    // get a random value
    int input = random(0, 100);
    // Printing something
    cout << "\n\n\nEntrance: \n\t\t\tDistance: " << input << endl;
    // Set the random value as an input
    fuzzy->setInput(1, input);
    // Running the Fuzzification
    fuzzy->fuzzify();
    // Running the Defuzzification
    float output = fuzzy->defuzzify(1);
    // Printing something
    cout << "Result: \n\t\t\tSpeed: " << output << endl;
    return 0;
}