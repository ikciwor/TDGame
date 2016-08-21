#include "CreepDebuffComponent.hpp"



CreepDebuffComponent::CreepDebuffComponent(int type) {
  type_ = type;
}

int CreepDebuffComponent::getType(){
  return type_;
}

void CreepDebuffComponent::update(CreepWalkComponent &walkComp){
  switch (type_) {
  case CreepDebuffComponent::SLOW: {
    walkComp.updateSpeed(0);
    break;
  }
  case CreepDebuffComponent::BURN:{
    break;
  }
  case CreepDebuffComponent::FREEZE: {
    break;
  }
default:
    break;
  }
}
