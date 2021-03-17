#include <iostream>
#include <fstream>

#include "../source/Fuzzy.h"

using namespace std;
using namespace eFLL;

int main(int argc, char *argv[])
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
    ofstream outputFile;
    outputFile.open("tests/output.txt");

    for (int t = 0; t <= 45; t++)
    {
        for (int h = 0; h <= 100; h++)
        {
            fuzzy->setInput(1, t);
            fuzzy->setInput(2, h);

            fuzzy->fuzzify();

            float o = fuzzy->defuzzify(1);

            std::cout
                << "Running with: Temperature->" << t << ", Humidity->" << h << ". Result: " << o << std::endl;

            outputFile << o << ",";
        }
        outputFile << "\n";
    }
    outputFile.close();
    return 0;
}