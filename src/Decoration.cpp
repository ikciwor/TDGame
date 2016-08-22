#define _USE_MATH_DEFINES
#include <cmath>
#include "Decoration.hpp"

static const float ROTATION_SPEED = 45.f;
static const float PULSE_SPEED = 2.f;
static const float MAX_RADIUS = 0.45f;
static const float MIN_RADIUS = 0.1f;

CreepSourceDecoration::CreepSourceDecoration(sf::Vector2f position)
{
	rectangleShape_.setPosition(position);
	rectangleShape_.setSize({ 0.5f, 0.5f });
	rectangleShape_.setOrigin({ 0.25f, 0.25f });
	rectangleShape_.setFillColor(sf::Color(255, 127, 0));
}

bool CreepSourceDecoration::update(sf::Time dt)
{
	rectangleShape_.rotate(dt.asSeconds() * ROTATION_SPEED);
	return false;
}

void CreepSourceDecoration::render(sf::RenderTarget & target)
{
	target.draw(rectangleShape_);
}

GoalDecoration::GoalDecoration(sf::Vector2f position)
	: phase_(0.f)
{
	circleShape_.setPosition(position);
	circleShape_.setFillColor(sf::Color::Cyan);
}

bool GoalDecoration::update(sf::Time dt)
{
	phase_ += dt.asSeconds() * PULSE_SPEED;
	if (phase_ > M_PI)
		phase_ -= 2.f * M_PI;
	return false;
}

void GoalDecoration::render(sf::RenderTarget & target)
{
	const float radius = 
		(MAX_RADIUS + MIN_RADIUS) * 0.5f
		+ sin(phase_) * (MAX_RADIUS - MIN_RADIUS) * 0.5f;
	circleShape_.setRadius(radius);
	circleShape_.setOrigin({ radius, radius });
	target.draw(circleShape_);
}

Explosion::Explosion(sf::Vector2f position) {
	inside.setPosition(position);
	outside.setPosition(position);

	inside.setFillColor(sf::Color::Yellow);
	outside.setFillColor(sf::Color::Red);
}

bool Explosion::update(sf::Time dt) {
	size+=0.1;
	inside.setOrigin(size * 0.75, size*0.75);
	outside.setOrigin(size, size);
	outside.setRadius(size);
	inside.setRadius(size*0.75f);

	return size > 1;
}

void Explosion::render(sf::RenderTarget &target) {
	target.draw(outside);
	target.draw(inside);
}
