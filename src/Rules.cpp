#include "Rules.hpp"
#include "Enums.hpp"

RuleKey::RuleKey(RuleSubject subject, RuleProperty property): subject{subject}, property{property}
{
}

bool RuleKey::operator==(const RuleKey& other) const
{
    return (this->subject == other.subject) and (this->property == other.property);
}

bool RuleKey::operator<(const RuleKey& other) const
{
    return (subject < other.subject || (subject == other.subject && property < other.property) );
}

Rules::Rules(): rules{}
{
    std::vector<RuleSubject> ruleSubjects = Rules::getRuleSubjects();
    std::vector<RuleProperty> ruleProperties = Rules::getRuleProperties();
    for (int i = 0 ; i < static_cast<int>(ruleSubjects.size()) ; i++)
    {
        for(int j = 0 ; j < static_cast<int>(ruleProperties.size()) ; j++)
        {
            RuleKey ruleKey{ruleSubjects[i], ruleProperties[j]};
            rules[ruleKey] = false;
        }
    }
}

bool Rules::haveRule(RuleSubject ruleSubject, RuleProperty ruleProperty) const
{
    RuleKey ruleKey{ruleSubject, ruleProperty};
    return rules.at(ruleKey);
}

std::vector<RuleSubject> Rules::getRuleSubjects()
{
    std::vector<RuleSubject> ruleSubjects{};
    ruleSubjects.reserve(5);
    ruleSubjects.push_back(RuleSubject::BABA);
    ruleSubjects.push_back(RuleSubject::WALL);
    ruleSubjects.push_back(RuleSubject::FLAG);
    ruleSubjects.push_back(RuleSubject::ROCK);
    ruleSubjects.push_back(RuleSubject::WATER);
    return ruleSubjects;
}

std::vector<RuleProperty> Rules::getRuleProperties()
{
    std::vector<RuleProperty> ruleProperties{};
    ruleProperties.reserve(10);
    ruleProperties.push_back(RuleProperty::BABA);
    ruleProperties.push_back(RuleProperty::WALL);
    ruleProperties.push_back(RuleProperty::FLAG);
    ruleProperties.push_back(RuleProperty::ROCK);
    ruleProperties.push_back(RuleProperty::PUSH);
    ruleProperties.push_back(RuleProperty::YOU);
    ruleProperties.push_back(RuleProperty::STOP);
    ruleProperties.push_back(RuleProperty::WIN);
    ruleProperties.push_back(RuleProperty::SINK);
    ruleProperties.push_back(RuleProperty::WATER);
    return ruleProperties;
}

std::vector<RuleSubject> Rules::getRuleSubjects(RuleProperty ruleProperty)
{
    std::vector<RuleSubject> allRuleSubjects = Rules::getRuleSubjects();
    std::vector<RuleSubject> ruleSubjects{};
    for (int i = 0 ; i < static_cast<int>(allRuleSubjects.size()) ; i++)
    {
        if (this->haveRule(allRuleSubjects[i], ruleProperty))
        {
            ruleSubjects.push_back(allRuleSubjects[i]);
        }
    }
    return ruleSubjects;
}

void Rules::setRule(RuleSubject ruleSubject, RuleProperty ruleProperty)
{
    RuleKey ruleKey {ruleSubject, ruleProperty};
    rules[ruleKey] = true;
}

void Rules::clearRules()
{
    std::vector<RuleSubject> ruleSubjects = Rules::getRuleSubjects();
    std::vector<RuleProperty> ruleProperties = Rules::getRuleProperties();
    for (int i = 0 ; i < static_cast<int>(ruleSubjects.size()) ; i++)
    {
        for(int j = 0 ; j < static_cast<int>(ruleProperties.size()) ; j++)
        {
            RuleKey ruleKey {ruleSubjects[i], ruleProperties[j]};
            rules[ruleKey] = false;
        }
    }
}
