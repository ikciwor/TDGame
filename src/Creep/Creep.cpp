#include <SFGUI/Widgets.hpp>
#include "Creep.hpp"

Creep::Creep(
	int32_t maxLife, int32_t bounty,
	std::unique_ptr<CreepWalkComponent> walkComponent,
	std::unique_ptr<CreepDisplayComponent> displayComponent)
	: walkComponent_(std::move(walkComponent))
	, displayComponent_(std::move(displayComponent))
	, life_(maxLife), maxLife_(maxLife)
	, bounty_(bounty)
{}

bool Creep::isHit(sf::Vector2f point) const
{
	return displayComponent_->isHit(point);
}

sfg::Widget::Ptr Creep::getPanel()
{
	return sfg::Label::Create("Creep #" + std::to_string((intptr_t)this));
}
