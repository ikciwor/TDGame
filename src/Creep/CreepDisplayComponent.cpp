#include "CreepDisplayComponent.hpp"
#include "CreepWalkComponent.hpp"
#include <Thor/Animations.hpp>
#include <Thor/Resources.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>
CreepDotDisplayComponent::CreepDotDisplayComponent(
	const CreepWalkComponent & walkComponent,
	float radius)
	: circle_(radius)
	, radius_(radius)
	, walkComponent_(walkComponent)
{
	circle_.setFillColor(sf::Color::Black);
	circle_.setOrigin(radius, radius);
}

void CreepDotDisplayComponent::render(sf::RenderTarget & target)
{
	circle_.setPosition(walkComponent_.getPosition());
	target.draw(circle_);
}

bool CreepDotDisplayComponent::isHit(sf::Vector2f point) const
{
	const auto diff = point - walkComponent_.getPosition();
	return diff.x * diff.x + diff.y * diff.y <= radius_ * radius_;
}
void CreepDotDisplayComponent::update(sf::Time dt)
{
    printf("lol\n");
}
CreepTextureDisplayComponent::CreepTextureDisplayComponent(
        const CreepWalkComponent & walkComponent,float x_my1,float y_my1,float radius, const thor::ResourceLoader<sf::Texture> &key
        ,thor::Animator<sf::Sprite, std::string>animator1)//,int x1,int y1)
    :walkComponent_(walkComponent),
      x_my(x_my1),
      y_my(y_my1),
     radius_(radius),
     animator(animator1)
{
    static int id=0;
    id_k=id;
    id++;
    aktyw=0;
    holder.acquire("myID", key);
    //x=x1;
    //y=y1;
}

void CreepTextureDisplayComponent::render(sf::RenderTarget & target)
{
    spri.setTexture(holder["myID"]);
    animator.animate(spri);
    float x_my=50,y_my=50;
    spri.setScale(1/x_my,1/y_my);
    spri.setOrigin(x_my/2,y_my/2);
    float rot=0;
    if(walkComponent_.getFacingDirection().x>0)
    {
        rot=90;
    }
    if(walkComponent_.getFacingDirection().x<0)
    {
        rot=270;
    }
    if(walkComponent_.getFacingDirection().y<0)
    {
        rot=180;
    }
    spri.setPosition(walkComponent_.getPosition());
    spri.setRotation(rot);
#ifdef CREEPDISPLAYCOMPONENTDEBUG
    printf("%d %f %f %f %f %d %d\n",id_k,spri.getPosition().x,spri.getPosition().y,spri.getScale().x,spri.getRotation(),textu.getSize().x,textu.getSize().y);
    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",spri.getTransform().getMatrix()[0],spri.getTransform().getMatrix()[1]
            ,spri.getTransform().getMatrix()[2],spri.getTransform().getMatrix()[3],spri.getTransform().getMatrix()[4]
            ,spri.getTransform().getMatrix()[5],spri.getTransform().getMatrix()[6],spri.getTransform().getMatrix()[7]
            ,spri.getTransform().getMatrix()[8],spri.getTransform().getMatrix()[9],spri.getTransform().getMatrix()[10]
            ,spri.getTransform().getMatrix()[11],spri.getTransform().getMatrix()[12],spri.getTransform().getMatrix()[13]
            ,spri.getTransform().getMatrix()[14],spri.getTransform().getMatrix()[15]);
#endif
    //spri.setPosition(walkComponent_.getPosition()-sf::Vector2f(x/100,y/100));
    target.draw(spri);
}

bool CreepTextureDisplayComponent::isHit(sf::Vector2f point) const
{
    const auto diff = point - walkComponent_.getPosition();
    return diff.x * diff.x + diff.y * diff.y <= radius_ * radius_;
}
void CreepTextureDisplayComponent::update(sf::Time dt)
{
    auto onFinish=[this]()
    {
        this->aktyw=0;
    };
    //printf("aha%d\n",int(aktyw));
    if(aktyw==0)
    {
    animator.play()<<"my"<<thor::Playback::notify(onFinish);
    //printf("aha%d\n",int(aktyw));
    aktyw=1;
    //printf("aha%d\n",int(aktyw));
    }
    animator.update(dt);
    //printf("aha%d\n",int(aktyw));
}
