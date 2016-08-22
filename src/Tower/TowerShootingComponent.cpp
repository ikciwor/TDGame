#include "../Bullet/BulletFactory.hpp"
#include "../Tower/TowerShootingComponent.hpp"
#include<iostream>
TowerLinearShootingComponent::TowerLinearShootingComponent(float shotsPerSecond,int type)
	: charge_(0.f)
	, maxCharge_(shotsPerSecond)
  , type_(type)
{}

void TowerLinearShootingComponent::update(sf::Time dt, BulletFactory & bulletFactory)
{
	charge_ -= dt.asSeconds();
  std::string bulletName;
  // if(type_==TowerLinearShootingComponent::SLOW)
   switch (type_) {
   case TowerLinearShootingComponent::SLOW: {
     std::cerr <<"SLOW triggered\n";
     bulletName= "GenericBullet";
     break;
   }
   case TowerLinearShootingComponent::NEUTRAL: {
     bulletName= "Bomb";
     break;
   }
   // case TowerLinearShootingComponent//  {
   //   break;
   // };
default:
  bulletName= "GenericBullet";
     break;
   }
	if (charge_ <= 0.f) {
		bulletFactory.shoot(bulletName);
		charge_ += maxCharge_;
	}
}
