#include <Geode/Geode.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace geode::prelude;

// define main channel variable
FMOD::ChannelGroup* masterGroup;

int updateValue = 0;

int randomInt = rand() % 30 + 85;   // generate a random number in range 85 - 115
float randomNum = static_cast<float>(randomInt) / 100; // divide it to make it 0.85 - 1.15

class $modify (CCScheduler)
{
    void update(float dt)
    {
        if (!masterGroup)
        {
            FMODAudioEngine::sharedEngine()->m_system->getMasterChannelGroup(&masterGroup); // if it doesn't have a value attached, give it one
        }

        updateValue += 1;
        
        if (updateValue >= 30)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed the randomizer or smth idk how it works
            // update the value every 30 frames. I'm aware it can be buggy with higher frame rate but this is all I got for now
            randomInt = rand() % 30 + 85;
            randomNum = static_cast<float>(randomInt) / 100;
            updateValue = 0;
        }
        
        masterGroup->setPitch(randomNum); // set audio pitch (which also affects speed, which is quite convenient)
        
        CCScheduler::update(dt * randomNum);
        return;
    }
};