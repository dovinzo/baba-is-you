#ifndef RULES_HPP
#define RULES_HPP

#include "Enums.hpp"
#include <map>
#include <vector>

/* Classe qui gère les règles du jeu. Une règle est une association entre un sujet et une propriété, 
par le mot IS. C'est la sous-classe RuleKey qui encapsule cela. */

class Rules
{

    friend class Model;
    public : 
        // vérifie si une règle donnée est active
        bool haveRule(RuleSubject ruleSubject, RuleProperty ruleProperty) const;

    private:

        class RuleKey // clé pour la map des règles
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

        Rules();
        virtual ~Rules() = default;
        void setRule(RuleSubject ruleSubject, RuleProperty ruleProperty);
        void clearRules();

        std::map<RuleKey, bool> rules;
        std::vector<RuleSubject> getRuleSubjects(RuleProperty ruleProperty);
        static std::vector<RuleSubject> getRuleSubjects();
        static std::vector<RuleProperty> getRuleProperties();
};

#endif
