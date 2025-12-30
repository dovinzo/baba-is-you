#ifndef RULES_HPP
#define RULES_HPP

#include "Enums.hpp"
#include <map>
#include <vector>

class Rules; 

class RuleKey
{
    friend class Rules;

    public:

        RuleKey() = delete;
    
        bool operator==(const RuleKey& other) const;
        bool operator<(const RuleKey& other) const;

    private:
        RuleKey(RuleSubject subject, RuleProperty property);
        RuleSubject subject;
        RuleProperty property;
        
};

class Rules
{

    friend class Model;
    public : 

        bool haveRule(RuleSubject ruleSubject, RuleProperty ruleProperty) const;

    private:

        Rules();
        void setRule(RuleSubject ruleSubject, RuleProperty ruleProperty);
        void clearRules();

        std::map<RuleKey, bool> rules;
        std::vector<RuleSubject> getRuleSubjects(RuleProperty ruleProperty);
        static std::vector<RuleSubject> getRuleSubjects();
        static std::vector<RuleProperty> getRuleProperties();
};

#endif
