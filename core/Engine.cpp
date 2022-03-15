#include "Engine.hpp"

using namespace beans;

void Engine::Tick() {
    for (auto universe : universes) {
        for (auto channel : universe.channels) {
            auto levels = channel.currentDataSource->GetChannelData(channel.channel);
            for (auto processor : channel.processors) {
                levels = processor->process(levels);
            }
            channel.channel->SetLevels(levels);
            auto dmxData = channel.channel->GetDmx();
            // todo: assumes no overflow - we should check that the channel's address allows it to fit inside the uni
            universe.iface->SetLevels(dmxData);
        }
    }
}