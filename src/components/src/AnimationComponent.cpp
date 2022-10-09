#include "../../handlers/ImageHandler.h"
#include "../AnimationComponent.h"
#include "../../Game.h"

using namespace std;
//map<string,AnimationConfiguration> AnimationComponent::animationConfigurations;

AnimationComponent::AnimationComponent(Sprite *sprite):ImageComponent(sprite)
{
    deltaAccumulator = 0;
    currentFrame = 0;
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
    cout << "added animation!" << endl;
    cout << animationConfigurations[configurationName]->deltaThreshold << endl;
}

void AnimationComponent::changeConfiguration(string configurationName)
{
    currentConfigurationName = configurationName;
    cout << "got past here" << endl;
    currentFrame = 0;
    deltaAccumulator = 0;
    cout << currentConfigurationName << endl;
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
    }
    setImage(animationConfigurations[currentConfigurationName]->paths[0]);
    
}

void AnimationComponent::update()
{
    cout << "updating Animation component" << endl;
    deltaAccumulator += game->deltaTime;
    cout << "Current Config Delta Thres: " <<  animationConfigurations[currentConfigurationName]->deltaThreshold << endl;
    while (deltaAccumulator >= animationConfigurations[currentConfigurationName]->deltaThreshold)
    {
        //cout << "still updating!" << endl;
        //cout << currentFrame << endl;
        //cout << deltaAccumulator << endl;
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
    cout << "finished updating Animation component" << endl;
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
    cout << "First Dimensions:  " << animationConfigurations[currentConfigurationName]->dimensions[0].first << " , " << animationConfigurations[currentConfigurationName]->dimensions[0].second  << endl;
    cout << "Looping? " << animationConfigurations[currentConfigurationName]->looping << endl;
}