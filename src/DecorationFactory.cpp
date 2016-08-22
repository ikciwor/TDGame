//
// Created by radek on 21.08.16.
//

#include "DecorationFactory.h"

DecorationFactory::DecorationFactory(std::shared_ptr<LevelInstance> level) : level_(level){

}

void DecorationFactory::createDecoration(std::shared_ptr<Decoration> decoration, sf::Vector2f position) {
    level_->addDecoration(decoration);
}
