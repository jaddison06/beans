#include "Channel.hpp"

using namespace beans;

Channel::Channel(FixtureData fixture) {
    this->fixture = fixture;

    dmxData.length = 0;

    for (auto group : fixture.paramGroups) {
        for (auto param : group.second) {
            dmxData.length++;
            if (param.is16bit) dmxData.length++;

            auto channelParam = new ChannelParameter;
            channelParam->min = param.min;
            channelParam->max = param.max;
            channelParam->home = channelParam->level = param.home;

            levels[param.name] = channelParam;
        }
    }

    dmxData.data = new uint8_t[dmxData.length];

    UpdateDmxData();

}

Channel::~Channel() {
    for (auto param : levels) {
        delete param.second;
    }
    delete dmxData.data;
}

ChannelData Channel::GetLevels() {
    return levels;
}

void Channel::SetLevels(ChannelData newLevels) {
    levels = newLevels;
    UpdateDmxData();
}

DMXData Channel::GetDmx() {
    return dmxData;
}

void Channel::UpdateDmxData() {
    Parameter dmxInfo;
    for (auto param : levels) {
        fixture.FindParam(param.first, &dmxInfo);

        // normalise min, max, level -> between 0 and newMax
        // (level - min) / (max - min) * newMax
        uint16_t dmxLevel = (
            (double)param.second->level - param.second->min) /
            ((double)param.second->max - param.second->min) *
            (dmxInfo.is16bit ? 65535L : 255L);
        
        if (dmxInfo.is16bit) {
            dmxData.data[dmxInfo.offset] = dmxLevel >> 8;
            dmxData.data[dmxInfo.offset + 1] = dmxLevel & 0xFF;
        } else {
            dmxData.data[dmxInfo.offset] = dmxLevel;
        }
    }
}