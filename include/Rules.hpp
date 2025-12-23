#ifndef RULES_HPP
#define RULES_HPP

#include "Enums.hpp"
#include <map>
#include <vector>

class RuleKey
{
    public:
        RuleSubject subject;
        RuleProperty property;
        bool operator==(const RuleKey& other) const;
        bool operator<(const RuleKey& other) const;
};

class Rules
{
    public:
        Rules();
        bool haveRule(RuleSubject ruleSubject, RuleProperty ruleProperty) const;
        void setRule(RuleSubject ruleSubject, RuleProperty ruleProperty);
        void clearRules();
    private:
        std::map<RuleKey, bool> rules;
        std::vector<RuleSubject> getRuleSubjects(RuleProperty ruleProperty);
        static std::vector<RuleSubject> getRuleSubjects();
        //static std::vector<RuleSubject> getAllRuleSubjects();
        static std::vector<RuleProperty> getRuleProperties();
};

#endif
