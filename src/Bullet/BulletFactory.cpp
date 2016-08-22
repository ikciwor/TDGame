#include "../MakeUnique.hpp"
#include "Bullet.hpp"
#include "BulletDisplayComponent.hpp"
#include "BulletMovementComponent.hpp"
#include "../Creep/CreepDebuffComponent.hpp"
#include "BombMovementComponent.h"
#include "BulletFactory.hpp"

#include "../Level.hpp"
#include "../DecorationFactory.h"

std::shared_ptr<Bullet> BulletFactory::innerCreateBullet(
	const std::string & bulletName) const
{
	if (bulletName == "GenericBullet") {
    auto debuff = std::make_unique<CreepDebuffComponent>(0, 2.f);
		auto movement = std::make_unique<BulletTimedMovementComponent>(
			1.f, target_, 20, position_, *debuff);
		auto display = std::make_unique<BulletSimpleDisplayComponent>(0.0625f, *movement.get());
		return std::make_shared<Bullet>(std::move(movement), std::move(display));
	} else if (bulletName == "Bomb") {
		auto movement = std::make_unique<BombMovementComponent>(2,target_,std::make_shared<DecorationFactory>(levelInstance_), 1000000, position_);
        auto display = std::make_unique<BulletSimpleDisplayComponent>(0.125f, *movement.get());
		return std::make_shared<Bullet>(std::move(movement), std::move(display));
	}


	throw std::runtime_error("Unknown Bullet type: " + bulletName);
}

BulletFactory::BulletFactory(std::shared_ptr<LevelInstance> levelInstance, sf::Vector2f position)
	: levelInstance_(levelInstance)
	, position_(position)
{}

void BulletFactory::createBullet(
	const std::string & bulletName)
{
	levelInstance_->registerBullet(innerCreateBullet(bulletName));
}
