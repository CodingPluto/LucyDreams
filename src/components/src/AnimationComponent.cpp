#include "handlers/inc/ImageHandler.h"
#include "AnimationComponent.h"
#include "Game.h"

using namespace std;
map<string,AnimationConfiguration> AnimationComponent::animationConfigurations;

AnimationComponent::AnimationComponent(Sprite *sprite):ImageComponent(sprite)
{
    deltaAccumulator = 0;
    currentFrame = 0;
}

AnimationComponent::~AnimationComponent()
{}

void AnimationComponent::addAnimation(vector<string> imagePaths, string configurationName, float deltaThreshold, bool looping)
{
    AnimationConfiguration animationConfiguration = {.paths = imagePaths, .deltaThreshold = deltaThreshold, .looping = looping};
    animationConfigurations[configurationName] = animationConfiguration;
    cout << "added animation configuration. Name: " << configurationName << endl;


}

void AnimationComponent::changeConfiguration(string configurationName)
{
    currentConfigurationName = configurationName;
    AnimationConfiguration &currentConfiguration = animationConfigurations[currentConfigurationName];
    currentFrame = 0;
    deltaAccumulator = 0;
    if (currentConfiguration.dimensions.size() == 0)
    {
        int i = 0;
        for (std::string &path : currentConfiguration.paths)
        {
            currentConfiguration.dimensions.emplace_back(pair<int,int>{0,0});
            SDL_QueryTexture(getLoadedImage(path),nullptr,nullptr,&(currentConfiguration.dimensions[i].first),&(currentConfiguration.dimensions[i].second));
            i++;
        }
    }
    if (!imageComponentInitalized)
    {
        game->imageHandler->addImageDrawer(this);
        imageComponentInitalized = true;
        game->imageHandler->reloadImageDrawerProrities();
    }
    
}

void AnimationComponent::update()
{
    AnimationConfiguration &currentConfiguration = animationConfigurations[currentConfigurationName];
    deltaAccumulator += game->deltaTime;
    while (deltaAccumulator >= currentConfiguration.deltaThreshold)
    {
        currentFrame++;
        if (currentFrame >= (int) currentConfiguration.paths.size())
        {
            if (currentConfiguration.looping)
            {
                currentFrame = 0;
            }
            else
            {
                deltaAccumulator = 0;
                currentFrame -= 1;
            }

        }
        deltaAccumulator -= currentConfiguration.deltaThreshold;
        
    }
    imageName = currentConfiguration.paths[currentFrame];
    textureWidth = currentConfiguration.dimensions[currentFrame].first;
    textureHeight = currentConfiguration.dimensions[currentFrame].second;
}

void AnimationComponent::setDeltaThreshold(string animationConfigurationName, float newThreshold)
{
    animationConfigurations[animationConfigurationName].deltaThreshold = newThreshold;
}
void AnimationComponent::setLooping(std::string animationConfigurationName, bool newLoopingValue)
{
    animationConfigurations[animationConfigurationName].looping = newLoopingValue;
}

