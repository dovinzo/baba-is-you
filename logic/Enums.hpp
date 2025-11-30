#ifndef TYPES_HPP
#define TYPES_HPP


enum class physical_type { // not words
    WALL,
    BABA, 
    FLAG, 
    ROCK,
    EMPTY
};

enum class meaningful_type { // words
    FLAG, 
    IS, 
    BABA,
    ROCK,
    PUSH, 
    YOU, 
    WALL,
    STOP,
    WIN,
    COUNT // pour le nombre total de meaningful types
};

enum class property_type {
    YOU,
    PUSH,
    STOP,
    WIN
};

inline char meaningful_char(meaningful_type t)
{
    switch (t) {
        case meaningful_type::FLAG: return 'f';
        case meaningful_type::IS:   return 'i';
        case meaningful_type::BABA: return 'b';
        case meaningful_type::ROCK: return 'r';
        case meaningful_type::PUSH: return 'p';
        case meaningful_type::YOU:  return 'y';
        case meaningful_type::WALL: return 'a'; 
        case meaningful_type::STOP: return 's';
        case meaningful_type::WIN:  return 'w';
        case meaningful_type::COUNT:return '?';
    }
    return '?';
}



// c'est très laid : si on veux ajouter une propriété, 
// faut modifier ici et dans Rules.hpp et Rules.cpp

#endif // TYPES_HPP