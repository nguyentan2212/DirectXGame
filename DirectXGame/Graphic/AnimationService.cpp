#include "AnimationService.h"
#include <fstream>
#include "../Utils/Debug.h"

AnimationService* AnimationService::_instance = nullptr;

AnimationService::AnimationService()
{

}

AnimationService* AnimationService::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AnimationService();
    }
    return _instance;
}

void AnimationService::Init(json config)
{
    for (string animationPath : config)
    {
        fstream file(animationPath);

        json fileJson = json::parse(file);
        json animationsJson = fileJson["animations"];

        for (json ani : animationsJson)
        {
            string animationName = ani["name"].get<string>();
            DWORD defaultTime = ani["defaultTime"].get<DWORD>();
            Animation* animation = new Animation(defaultTime);

            json frames = ani["frames"];
            for (json frame : frames)
            {
                string spriteName = frame["sprite"].get<string>();
                if (frame["time"].is_null())
                {
                    animation->AddFrame(spriteName);
                }
                else
                {
                    DWORD time = frame["time"].get<DWORD>();
                    animation->AddFrame(spriteName, time);
                }
            }
            this->_animations[animationName] = animation;
        }
    }
}

Animation* AnimationService::GetAnimation(string name)
{
    Animation* animation = this->_animations[name];
    if (animation == nullptr)
    {
        DebugOut(L"[ERROR] Sprite name: '%s' not found !\n", name);
    }
    return animation;
}

AnimationService::~AnimationService()
{
}
