#include <Geode/Geode.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace geode::prelude;

//set the main channel group for audio
FMOD::ChannelGroup* masterGroup;

int updateValue = 0;

int randomInt = rand() % 30 + 85;   //generate a random number in range 85 - 115
float randomNum = static_cast<float>(randomInt) / 100; //divide it to make it 0.85 - 1.15

class $modify (CCScheduler)
{
    void update(float dt)
    {
        if (!masterGroup)
        {
            FMODAudioEngine::sharedEngine()->m_system->getMasterChannelGroup(&masterGroup); //if the original set failed, set it again.
        }

        updateValue += 1;

        if (updateValue >= 30)
        {
            //update the value every 30 frames. I'm aware it can be buggy with higher frame rate but this is all I got for now
            randomInt = rand() % 30 + 85;
            randomNum = static_cast<float>(randomInt) / 100;
            updateValue = 0;
        }
        
        masterGroup->setPitch(randomNum);
                
        CCScheduler::update(dt * randomNum);
        return;
    }
};
