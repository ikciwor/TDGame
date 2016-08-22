#include "CreepDebuffComponent.hpp"
#include <iostream>



CreepDebuffComponent::CreepDebuffComponent(int type, float timeToLive) {
  timeToLive_ = (int)timeToLive*60;
  type_ = type;
  isFinished = false;
  counter = 0;
}

int CreepDebuffComponent::getType(){
  return type_;
}

void CreepDebuffComponent::update(){
  std::cerr << "c " << counter << "\n";
  counter++;
  if(counter >= timeToLive_){
    isFinished = true;
  }
}
