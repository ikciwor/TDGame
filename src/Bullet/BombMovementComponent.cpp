//
// Created by radek on 21.08.16.
//

#include "BombMovementComponent.h"
#include "../Creep/Creep.hpp"
#include "../DecorationFactory.h"

BombMovementComponent::BombMovementComponent(float time, const std::shared_ptr<Creep> &target, const std::shared_ptr<DecorationFactory> factory, int32_t damage,
                                             sf::Vector2f startingPosition) : timeToHit_(time), target_(target), decorationFactory(factory), damage_(damage), position_(startingPosition){}

void BombMovementComponent::update(sf::Time dt) {
    auto lockedTarget = target_.lock();
    if (!lockedTarget)
        return;

    const float nextTime = std::max(timeToHit_ - dt.asSeconds(), 0.f);
    const float factor = (nextTime == 0.f) ? 0.f : (nextTime / timeToHit_);
    const auto creepPosition = lockedTarget->getPosition();

    position_ = creepPosition + factor * (position_ - creepPosition);
    timeToHit_ = nextTime;

    if (nextTime == 0.f) {
        lockedTarget->inflictDamage(damage_);
        decorationFactory->createDecoration(std::make_shared<Explosion>(creepPosition), creepPosition);
        target_.reset();
    }
}

sf::Vector2f BombMovementComponent::getPosition() const {
    return position_;
}

bool BombMovementComponent::isAlive() const {
    if (timeToHit_ <= 0.f)
        return false;

    auto lockedTarget = target_.lock();
    return lockedTarget && lockedTarget->isAlive();
}
