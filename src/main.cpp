#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CCScheduler.hpp>

//set the main channel group for audio
FMOD::ChannelGroup* masterGroup;

int updateValue;

int randomInt = rand() % 30 + 85;   //generate a random number in range 85 - 115
float randomNum = randomNum / 100; //divide it to make it 0.85 - 1.15

//thanks to TheSillyDoggo and his QOLMod code to show me how to edit game speed
class $modify (CCScheduler)
{
    void update(float dt)
    {
        if (!masterGroup)
        {
            FMODAudioEngine::sharedEngine()->m_system->getMasterChannelGroup(&masterGroup); //if the original set failed, set it again.
        }

        updateValue += 1;

        if (updateValue >= 20)
        {
            //update the value every 40 frames. I'm aware it can be buggy with higher frame rate but this is all I got for now
            randomNum = rand() % 30 + 85;
            randomNum = randomNum / 100;
            updateValue = 0;
        }
        masterGroup->setPitch(randomNum);
                
        CCScheduler::update(dt * randomNum);
        return;
    }
};
