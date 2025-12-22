#include "Rules.hpp"
#include "Enums.hpp"

bool RuleKey::operator==(const RuleKey& other) const
{
    return (this->subject == other.subject) and (this->property == other.property);
}

bool RuleKey::operator<(const RuleKey& other) const
{
    return (this->subject <= other.subject) and ((this->subject < other.subject) or (this->property < other.property));
}

Rules::Rules(): rules{}
{
    std::vector<RuleSubject> ruleSubjects = Rules::getRuleSubjects();
    std::vector<RuleProperty> ruleProperties = Rules::getRuleProperties();
    RuleKey ruleKey{};
    for (int i = 0 ; i < static_cast<int>(ruleSubjects.size()) ; i++)
    {
        for(int j = 0 ; j < static_cast<int>(ruleProperties.size()) ; j++)
        {
            ruleKey.subject = ruleSubjects[i];
            ruleKey.property = ruleProperties[j];
            rules[ruleKey] = false;
        }
    }
}

bool Rules::haveRule(RuleSubject ruleSubject, RuleProperty ruleProperty) const
{
    RuleKey ruleKey{};
    ruleKey.subject = ruleSubject;
    ruleKey.property = ruleProperty;
    return rules.at(ruleKey);
}

std::vector<RuleSubject> Rules::getRuleSubjects()
{
    std::vector<RuleSubject> ruleSubjects{};
    ruleSubjects.reserve(4);
    ruleSubjects.push_back(RuleSubject::BABA);
    ruleSubjects.push_back(RuleSubject::WALL);
    ruleSubjects.push_back(RuleSubject::FLAG);
    ruleSubjects.push_back(RuleSubject::ROCK);
    return ruleSubjects;
}

std::vector<RuleProperty> Rules::getRuleProperties()
{
    std::vector<RuleProperty> ruleProperties{};
    ruleProperties.reserve(8);
    ruleProperties.push_back(RuleProperty::BABA);
    ruleProperties.push_back(RuleProperty::WALL);
    ruleProperties.push_back(RuleProperty::FLAG);
    ruleProperties.push_back(RuleProperty::ROCK);
    ruleProperties.push_back(RuleProperty::PUSH);
    ruleProperties.push_back(RuleProperty::YOU);
    ruleProperties.push_back(RuleProperty::STOP);
    ruleProperties.push_back(RuleProperty::WIN);
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
    RuleKey ruleKey;
    ruleKey.subject = ruleSubject;
    ruleKey.property = ruleProperty;
    rules[ruleKey] = true;
}

void Rules::clearRules()
{
    std::vector<RuleSubject> ruleSubjects = Rules::getRuleSubjects();
    std::vector<RuleProperty> ruleProperties = Rules::getRuleProperties();
    RuleKey ruleKey;
    for (int i = 0 ; i < static_cast<int>(ruleSubjects.size()) ; i++)
    {
        for(int j = 0 ; j < static_cast<int>(ruleProperties.size()) ; j++)
        {
            ruleKey.subject = ruleSubjects[i];
            ruleKey.property = ruleProperties[j];
            rules[ruleKey] = false;
        }
    }
}
