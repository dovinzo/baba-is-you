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

// c'est très laid : si on veux ajouter une propriété, 
// faut modifier ici et dans Rules.hpp et Rules.cpp

#endif // TYPES_HPP