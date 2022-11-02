#include "Platform.h"
#include <iostream>
#include "../components/ImageComponent.h"
using namespace std;

Platform::Platform(const unsigned int platformLength, const bool direction): platformLength(platformLength), direction(direction), platformSections(new ImageComponent*[platformLength])
{
    position = {10,200};
    cout << "created platform!" << endl;
    scale = 4;
}

void Platform::setPlatformImages(const std::string &imageL, const std::string &imageM, const std::string &imageR)
{
    for (int i = 0; i < platformLength; ++i)
    {
        platformSections[i] = new ImageComponent(this);
        if (i == 0)
        {
            platformSections[i]->setImage(imageL);
        }
        else if (i == platformLength - 1)
        {
            platformSections[i]->setImage(imageR);
        }
        else
        {
            platformSections[i]->setImage(imageM);
        }
        if (direction == left)
        {
            platformSections[i]->setImageOffset({(platformSections[0]->getWidth() / scale) * i,0});
        }
        else if (direction == right)
        {
            platformSections[i]->setImageOffset({0,(platformSections[0]->getHeight() / scale) * i});
        }
    }

}

float Platform::getWidth()
{
    return platformSections[0]->getWidth() * platformLength;
}


Platform::~Platform()
{
    delete[] platformSections;
}

void Platform::update()
{}
