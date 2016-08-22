#pragma once

#ifndef TDF_CREEP_DISPLAY_COMPONENT_HPP
#define TDF_CREEP_DISPLAY_COMPONENT_HPP

#include "../Renderable.hpp"
#include <Thor/Animations.hpp>
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
class CreepWalkComponent;

//! Component of the Creep implementing its look.
class CreepDisplayComponent : public Renderable {};

class CreepCompositeDisplayComponent final
	: public CompositeRenderable<CreepDisplayComponent> {};

//! A very simple look for the creep.
class CreepDotDisplayComponent final : public CreepDisplayComponent
{
private:
	sf::CircleShape circle_;
	float radius_;
	const CreepWalkComponent & walkComponent_;

public:
	CreepDotDisplayComponent(const CreepWalkComponent & walkComponent, float radius);
	virtual void render(sf::RenderTarget & target) override;
	virtual bool isHit(sf::Vector2f point) const override;
    virtual bool update(sf::Time dt);
};
class CreepTextureDisplayComponent final : public CreepDisplayComponent
{
private:
    const CreepWalkComponent & walkComponent_;
    float x_my,y_my;
    sf::Texture textu;
    sf::Sprite spri;
    float radius_;
    bool aktyw;
    int id_k;//only for debugging
    thor::ResourceHolder<sf::Texture, std::string> holder;
    thor::Animator<sf::Sprite, std::string> animator;
public:
    CreepTextureDisplayComponent(const CreepWalkComponent & walkComponent,float x_my1,float y_my1,float radius
                                 , const thor::ResourceLoader<sf::Texture> &key,
                                 thor::Animator<sf::Sprite,std::string>animator1);//,int x1,int y1);
    virtual void render(sf::RenderTarget & target) override;
    virtual bool isHit(sf::Vector2f point) const override;
    virtual bool update(sf::Time dt)override;
};
#endif // TDF_CREEP_DISPLAY_COMPONENT_HPP
