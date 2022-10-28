#include "../handlers/ImageHandler.h"
#include "AnimationComponent.h"
#include "../gameData/Game.h"

using namespace std;
//map<string,AnimationConfiguration> AnimationComponent::animationConfigurations;

AnimationComponent::AnimationComponent(Sprite *sprite) : ImageComponent(sprite)
{
    deltaAccumulator = 0;
    currentFrame = 0;
    setDebugName("AnimationComponent");
}

AnimationComponent::~AnimationComponent()
{
    for (map<string,AnimationConfiguration *>::iterator it = animationConfigurations.begin(); it != animationConfigurations.end(); it++)
    {
        delete (it->second);
    }
}

void AnimationComponent::addAnimation(vector<string> imagePaths, string configurationName, float deltaThreshold, bool looping)
{
    animationConfigurations[configurationName] = new AnimationConfiguration{.paths = imagePaths, .dimensions = {}, .deltaThreshold = deltaThreshold, .looping = looping};
    cout << "Added Animation: " << configurationName << endl;
}

void AnimationComponent::changeConfiguration(string configurationName)
{
    currentConfigurationName = configurationName;
    currentFrame = 0;
    deltaAccumulator = 0;
    try
    {
        animationConfigurations.at(currentConfigurationName);
    }
    catch (const exception &e)
    {
        throw runtime_error("The animation configuration set doesn't exist! - " + currentConfigurationName);
    }
    if (animationConfigurations[currentConfigurationName]->dimensions.size() == 0)
    {
        int i = 0;
        for (std::string &path : animationConfigurations[currentConfigurationName]->paths)
        {
            animationConfigurations[currentConfigurationName]->dimensions.emplace_back(pair<int,int>{0,0});
            SDL_QueryTexture(getLoadedImage(path),nullptr,nullptr,&(animationConfigurations[currentConfigurationName]->dimensions[i].first),&(animationConfigurations[currentConfigurationName]->dimensions[i].second));
            i++;
        }
    }
    if (game->debugMode)
    {
        debugCurrentAnimation();
    }
    if (!imageComponentInitalized)
    {
        game->imageHandler->addImageDrawer(this);
        imageComponentInitalized = true;
        game->imageHandler->reloadImageDrawerProrities();
        textureWidth = animationConfigurations[currentConfigurationName]->dimensions[0].first;
        textureHeight = animationConfigurations[currentConfigurationName]->dimensions[0].second;
    }
    
}

void AnimationComponent::update()
{
    deltaAccumulator += game->deltaTime;
    while (deltaAccumulator >= animationConfigurations[currentConfigurationName]->deltaThreshold)
    {
        currentFrame++;
        if (currentFrame >= (int) animationConfigurations[currentConfigurationName]->paths.size())
        {
            
            if (animationConfigurations[currentConfigurationName]->looping)
            {
                currentFrame = 0;
            }
            else
            {
                deltaAccumulator = 0;
                currentFrame -= 1;
            }

        }
        deltaAccumulator -= animationConfigurations[currentConfigurationName]->deltaThreshold;
        
    }
    imageName = animationConfigurations[currentConfigurationName]->paths[currentFrame];
    textureWidth = animationConfigurations[currentConfigurationName]->dimensions[currentFrame].first;
    textureHeight = animationConfigurations[currentConfigurationName]->dimensions[currentFrame].second;
}

void AnimationComponent::setDeltaThreshold(string animationConfigurationName, float newThreshold)
{
    animationConfigurations[animationConfigurationName]->deltaThreshold = newThreshold;
}
void AnimationComponent::setLooping(std::string animationConfigurationName, bool newLoopingValue)
{
    animationConfigurations[animationConfigurationName]->looping = newLoopingValue;
}


void AnimationComponent::debugCurrentAnimation()
{
    cout << "Current Configuration: " << currentConfigurationName << " (" << &animationConfigurations[currentConfigurationName] << ")" << endl;
    cout << "Delta Threshold: " << animationConfigurations[currentConfigurationName]->deltaThreshold << endl;
    cout << "Awake1 Dimensions:  " << animationConfigurations[currentConfigurationName]->dimensions[0].first << " , " << animationConfigurations[currentConfigurationName]->dimensions[0].second  << endl;
    cout << "Looping? " << animationConfigurations[currentConfigurationName]->looping << endl;
}