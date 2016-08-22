#pragma once
#ifndef TDF_CREEP_DEBUFF_COMPONENT_HPP
#define TDF_CREEP_DEBUFF_COMPONENT_HPP

#include "CreepWalkComponent.hpp"
#include "Thor/Time.hpp"
#include "SFML/System.hpp"

class CreepDebuffComponent{
public:
  enum TYPES{
    SLOW,
    BURN,
    FREEZE
  };
  CreepDebuffComponent(int type, float timeToLive);
  void update();
  int getType();
  bool isFinished;
private:
  int counter;
  int type_;
  int timeToLive_;
};




#endif /* TDF_CREEP_DEBUFF_COMPONENT_HPP */
