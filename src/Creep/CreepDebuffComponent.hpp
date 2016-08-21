#pragma once
#ifndef TDF_CREEP_DEBUFF_COMPONENT_HPP
#define TDF_CREEP_DEBUFF_COMPONENT_HPP

#include "CreepWalkComponent.hpp"

class CreepDebuffComponent{
public:
  enum TYPES{
    SLOW,
    BURN,
    FREEZE
  };
  CreepDebuffComponent(int type);
  void update(CreepWalkComponent &walkComp);
  int getType();
private:
  int type_;
  float timeToLive_;
};




#endif /* TDF_CREEP_DEBUFF_COMPONENT_HPP */
