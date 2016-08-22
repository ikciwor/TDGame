#pragma once

#ifndef TDF_CREEP_FACTORY_HPP
#define TDF_CREEP_FACTORY_HPP
#include <Thor/Animations.hpp>
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
//! Its sole function is to create creeps.
struct Anim_data
{
    std::string name;
    thor::ResourceLoader<sf::Texture>texture;
    thor::Animator<sf::Sprite, std::string> animator;
    int klatki;
    int w,h;//szerokosc i wysokosc klatki
    Anim_data(std::string name1,
    thor::ResourceLoader<sf::Texture>texture1,
    thor::Animator<sf::Sprite, std::string> animator1,
    int klatki1,
    int w1,int h1);


};

class CreepFactory
{
public:
	std::shared_ptr<Creep> createCreep(
		const std::string & typeName,
		int32_t life, int32_t bounty,
		sf::Vector2i position);
};

#endif // TDF_CREEP_FACTORY_HPP
