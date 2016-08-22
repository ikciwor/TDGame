#pragma once

#ifndef TDF_DECORATION_HPP
#define TDF_DECORATION_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Renderable.hpp"

class Decoration : public Renderable
{
public:
	virtual bool update(sf::Time dt) = 0;
};

class CreepSourceDecoration : public Decoration
{
	sf::RectangleShape rectangleShape_;

public:
	CreepSourceDecoration(sf::Vector2f position);
	virtual bool update(sf::Time dt) override;
	virtual void render(sf::RenderTarget & target) override;
};

class GoalDecoration : public Decoration
{
	sf::CircleShape circleShape_;
	float phase_;

public:
	GoalDecoration(sf::Vector2f position);
	virtual bool update(sf::Time dt) override;
	virtual void render(sf::RenderTarget & target) override;
};

class Explosion : public Decoration {
	sf::CircleShape inside,outside;
    float size = 0;

public:
	Explosion(sf::Vector2f position);
	virtual bool update(sf::Time dt) override;
	virtual void render(sf::RenderTarget & target) override;
};

#endif // TDF_DECORATION_HPP
