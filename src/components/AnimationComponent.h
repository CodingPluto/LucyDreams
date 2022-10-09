#ifndef SRC_ANIMATION_COMPONENT_H
#define SRC_ANIMATION_COMPONENT_H
#include "ImageComponent.h"

struct AnimationConfiguration
{
    std::vector<std::string> paths;
    std::vector<std::pair<int,int>> dimensions;
    float deltaThreshold;
    bool looping;

};


class AnimationComponent : public ImageComponent
{
private:
    void debugCurrentAnimation();
    std::map<std::string,AnimationConfiguration *> animationConfigurations;
    std::string currentConfigurationName;
    int currentFrame;
    float deltaAccumulator;

public:
    AnimationComponent(Sprite *sprite);
    ~AnimationComponent();
    void setDeltaThreshold(std::string animationConfigurationName, float newThreshold);
    void setLooping(std::string animationConfigurationName, bool newLoopingValue);
    void update();
    void addAnimation(std::vector<std::string> imagePaths, std::string configurationName, float deltaThreshold, bool looping = true);
    void changeConfiguration(std::string configurationName);

};

#endif