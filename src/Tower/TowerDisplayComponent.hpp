#pragma once

#ifndef TDF_TOWER_DISPLAY_COMPONENT_HPP
#define TDF_TOWER_DISPLAY_COMPONENT_HPP

#include <SFML/System.hpp>
#include "../Renderable.hpp"

class TowerTargetingComponent;

//! A Tower component implementing the look of the tower.
class TowerDisplayComponent : public Renderable {};

//! A simple look for the tower.
class TowerSimpleDisplayComponent final : public TowerDisplayComponent
{
	sf::CircleShape baseShape_;
	sf::RectangleShape barrelShape_;
	TowerTargetingComponent & targetingComponent_;
	float angle_;
	sf::Vector2f position_;

public:
	TowerSimpleDisplayComponent(
		TowerTargetingComponent & targeting,
		sf::Vector2f position);
	virtual void render(sf::RenderTarget & target) override;
};

class BombardDisplayComponent final : public TowerDisplayComponent {
	sf::CircleShape krztaut_; // wyalić przy robieniu tekstur
	sf::Vector2f position_;
public:
	BombardDisplayComponent (TowerTargetingComponent &targeting, sf::Vector2f position);
	virtual void render(sf::RenderTarget & target) override;
};

#endif // TDF_TOWER_DISPLAY_COMPONENT_HPP
