#include <memory>
#include <json.hpp>
#include "../MakeUnique.hpp"
#include "Tower.hpp"
#include "TowerFactory.hpp"

using json = nlohmann::json;

static std::vector<std::pair<std::string, towerTypeInfo_t>> typeInfos = []() {
	std::vector<std::pair<std::string, towerTypeInfo_t>> ret;

	ret.push_back({"GenericTower", {
			35, // Cost
			3.f, // Range (in game units)
			[](sf::Vector2f position) -> std::shared_ptr<Tower> {
				auto targeting = std::make_unique<TowerClosestTargetingComponent>(position);
        auto shooting = std::make_unique<TowerLinearShootingComponent>(1.f, TowerLinearShootingComponent::SLOW);
				auto display = std::make_unique<TowerSimpleDisplayComponent>(*targeting.get(), position);
				return std::make_shared<Tower>(
						position,
						std::move(targeting),
						std::move(shooting),
						std::move(display));
			}
	}});
	ret.push_back({"Bombard", {
			55, // Cost
			2.f, // Range (in game units)
			[](sf::Vector2f position) -> std::shared_ptr<Tower> {
				auto targeting = std::make_unique<TowerStrongestTargetingComponent>(position);
        auto shooting = std::make_unique<TowerLinearShootingComponent>(1.f, TowerLinearShootingComponent::NEUTRAL);
				auto display = std::make_unique<BombardDisplayComponent>(*targeting.get(), position);
				return std::make_shared<Tower>(
						position,
						std::move(targeting),
						std::move(shooting),
						std::move(display));
			}
	}});
	return ret;
}();

towerTypeInfo_t TowerFactory::getTowerTypeInfo(const std::string &typeName) {
	for (const auto &p : typeInfos) {
		if (p.first == typeName)
			return p.second;
	}

	throw std::runtime_error("Unknown Tower type: " + typeName);
}

const std::vector<std::pair<std::string, towerTypeInfo_t>> &TowerFactory::getAllTowerTypeInfos() {
	return typeInfos;
}
