#include <Geode/Geode.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>

using namespace geode::prelude;

bool enabled = Mod::get()->getSettingValue<bool>("enabled");

$execute {
    listenForSettingChanges("enabled", [](bool value) {
        enabled = value;
    });
}

class $modify(FMODAudioEngine) {
    void loadMusic(gd::string path, float speed, float p2, float volume, bool shouldLoop, int musicID, int channelID, bool dontReset) {
        if (enabled) {
            FMODAudioEngine::loadMusic(path, 0.75, p2, volume, shouldLoop, musicID, channelID, dontReset);
        } else {
            FMODAudioEngine::loadMusic(path, speed, p2, volume, shouldLoop, musicID, channelID, dontReset);
        }
    }
};

class $modify(PlayLayer) {
    virtual void postUpdate(float p0) {
        if (enabled) {
            if (m_isPlatformer != true) {
                PlayLayer::applyTimeWarp(0.75);
            }
            PlayLayer::postUpdate(p0);
            PlayLayer::m_isTestMode = true;
        } else {
            PlayLayer::postUpdate(p0);
        }
    }
};
