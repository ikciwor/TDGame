//
// Created by radek on 21.08.16.
//

#ifndef TDGAME_BOMBMOVEMENTCOMPONENT_H
#define TDGAME_BOMBMOVEMENTCOMPONENT_H

#include "BulletMovementComponent.hpp"

class DecorationFactory;

class BombMovementComponent final : public BulletMovementComponent
{
private:
	sf::Vector2f position_;
	float timeToHit_;
	std::weak_ptr<Creep> target_;
	int32_t damage_;
	std::shared_ptr<DecorationFactory> decorationFactory;

public:
	BombMovementComponent(
		float time,
		const std::shared_ptr<Creep> & target,
		const std::shared_ptr<DecorationFactory> factory,
		int32_t damage,
		sf::Vector2f startingPosition);
	void update(sf::Time dt) override;
	virtual sf::Vector2f getPosition() const override;
	virtual bool isAlive() const override;
};


#endif //TDGAME_BOMBMOVEMENTCOMPONENT_H
