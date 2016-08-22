#include "CreepQueryService.hpp"

CreepVectorQueryService::CreepVectorQueryService(const std::vector<std::shared_ptr<Creep>> &creeps)
        : creeps_(creeps) {}

std::shared_ptr<Creep> CreepVectorQueryService::getClosestCreep(
        sf::Vector2f center,
        float maxRange) {
    if (creeps_.empty())
        return nullptr;

    auto sqDistanceTo = [&](std::shared_ptr<Creep> creep) -> float {
        auto d = creep->getPosition() - center;
        return d.x * d.x + d.y * d.y;
    };

    std::shared_ptr<Creep> closest = nullptr;
    float smallestDistance = maxRange * maxRange;

    for (const auto &creep : creeps_) {
        const float newDistance = sqDistanceTo(creep);
        if (smallestDistance > newDistance) {
            smallestDistance = newDistance;
            closest = creep;
        }
    }

    return closest;
}

std::shared_ptr<Creep> CreepVectorQueryService::getStrongestCreep(sf::Vector2f center, float maxRange) {
	if (creeps_.empty())
		return nullptr;
    std::vector<std::shared_ptr<Creep>> inRange;
    auto sqDistanceTo = [&](std::shared_ptr<Creep> creep) -> float {
        auto d = creep->getPosition() - center;
        return d.x * d.x + d.y * d.y;
    };
    for (auto creep : creeps_) {
        if (sqDistanceTo(creep) <= maxRange) {
            inRange.push_back(creep);
        }
    }

    if(inRange.empty())
        return nullptr;
    auto top = *inRange.begin();
    for (auto creep : inRange) {
        if (creep->getMaxLife() > top->getMaxLife()) {
            top = creep;
        }
    }
    return top;
}
