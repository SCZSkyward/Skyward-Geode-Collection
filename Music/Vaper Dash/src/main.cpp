#include <Geode/Geode.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(FMODAudioEngine) {
    void loadMusic(gd::string path, float speed, float p2, float volume, bool shouldLoop, int p5, int p6) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            FMODAudioEngine::loadMusic(path, 0.75, p2, volume, shouldLoop, p5, p6);
        } else {
            FMODAudioEngine::loadMusic(path, speed, p2, volume, shouldLoop, p5, p6);
        }
    }
};

class $modify(PlayLayer) {
    virtual void postUpdate(float p0) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            PlayLayer::applyTimeWarp(0.75);
            PlayLayer::postUpdate(p0);
            PlayLayer::m_isTestMode = true;
        } else {
            PlayLayer::postUpdate(p0);
        }
    }
};
