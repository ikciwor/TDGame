#include <memory>
#include <string>
#include "../MakeUnique.hpp"
#include "Creep.hpp"
#include "CreepFactory.hpp"
#include "CreepLifeDisplayComponent.hpp"
#include "CreepDebuffComponent.hpp"
#include <vector>
#include <Thor/Animations.hpp>
#include <Thor/Resources.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>
std::vector<Anim_data>textury;

std::vector<thor::AnimationMap<sf::Sprite, std::string> > animations;
Anim_data::Anim_data(std::string name1,
    thor::ResourceLoader<sf::Texture>texture1,
    thor::Animator<sf::Sprite, std::string> animator1,
    int klatki1,
    int w1,int h1)
    :name(name1),
      texture(texture1),
      animator(animator1),
      klatki(klatki1),
      w(w1),
      h(h1)
{

}
std::shared_ptr<Creep> CreepFactory::createCreep(
	const std::string & typeName,
	int32_t life, int32_t bounty,
	sf::Vector2i position)
{
		auto walk = std::make_unique<CreepGridWalkComponent>(position);
        int kt=-1;
        for(unsigned int i=0;i<textury.size();i++)
        {
            if(textury[i].name==typeName)
            {
                kt=i;
            }
        }
        int w,h;
        if(kt==-1)
        {
            bool czy=1;
            FILE *f;
            f=fopen(("../../data/"+typeName+".txt").data(),"r");
            if (!f)
                throw std::runtime_error("Failed to load resource for turret type " + typeName);
            //char pom;
            //fseek(f,0,SEEK_END);
            char nazwa[256];
            int ilosc_klatek;
            fscanf(f,"%s",nazwa);
            printf("%s\n",nazwa);
            fscanf(f,"%d %d %d",&ilosc_klatek,&w,&h);

            fclose(f);

            if(czy)
            {
                printf("debug_creepfactory1.0\n");
                thor::ResourceLoader<sf::Texture>loader=thor::Resources::fromFile<sf::Texture>("../../data/"+std::string(nazwa));
                thor::FrameAnimation anim;
                printf("debug_creepfactory1.1\n");
                for (int i=0;i<ilosc_klatek;i++)
                {

                    anim.addFrame(1, sf::IntRect(0, h*i, w, h));
                }
                printf("debug_creepfactory1.2\n");
                printf("debug_creepfactory1.3\n");
                animations.push_back(thor::AnimationMap<sf::Sprite, std::string>());
                animations[animations.size()-1].addAnimation("my", anim, sf::seconds(1.f));
                thor::Animator<sf::Sprite, std::string> animator(animations[animations.size()-1]);
                printf("debug_creepfactory1.4\n");
            textury.push_back(Anim_data(typeName,loader,animator,ilosc_klatek,w,h));
            printf("debug_creepfactory1.5\n");
            kt=textury.size()-1;
            }
        }
        std::unique_ptr<CreepDotDisplayComponent> dotDisplay;
        std::unique_ptr<CreepTextureDisplayComponent> texDisplay;
        if(kt==-1)
        {
            dotDisplay =std::make_unique<CreepDotDisplayComponent>(*walk.get(), 0.125f);
        }
        else
        {
            texDisplay=std::make_unique<CreepTextureDisplayComponent>(*walk.get(),w,h,0.125f,textury[kt].texture,textury[kt].animator);
        }
		auto lifeDisplay = std::make_unique<CreepLifeDisplayComponent>(
			sf::Vector2f(0.f, 0.5f), sf::Vector2f(0.8f, 0.2f), true);
		auto lifeDisplayDirect = lifeDisplay.get();
		auto compositeDisplay = std::make_unique<CreepCompositeDisplayComponent>();
        if(kt==-1)
        {
        compositeDisplay->addChild(std::move(dotDisplay));
        }
        else
        {
            compositeDisplay->addChild(std::move(texDisplay));
        }
		compositeDisplay->addChild(std::move(lifeDisplay));

        auto ret = std::make_shared<Creep>(life, bounty, std::move(walk), std::move(compositeDisplay));
		lifeDisplayDirect->setOwner(ret.get());
		return ret;


	throw std::runtime_error("Unknown Creep type: " + typeName);
}
