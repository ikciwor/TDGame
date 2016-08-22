//
// Created by radek on 21.08.16.
//

#ifndef TDGAME_DECORATIONFACTORY_H
#define TDGAME_DECORATIONFACTORY_H


#include <SFML/System.hpp>
#include <memory>
#include "Level.hpp"

class DecorationFactory {
    std::shared_ptr<LevelInstance> level_;

public:
    DecorationFactory(std::shared_ptr<LevelInstance> level);
    void createDecoration(std::shared_ptr<Decoration> decoration, sf::Vector2f position);
};


#endif //TDGAME_DECORATIONFACTORY_H
