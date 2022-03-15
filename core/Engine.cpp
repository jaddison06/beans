#include "Engine.hpp"
#include "../3rdparty/pugi/pugixml.hpp"

#include "../DMX/SACN.hpp"

using namespace beans;

void Engine::LoadPatch(std::string dataFile, DMXManager* manager) {
    universes.clear();
    manager->Clear();

    pugi::xml_document doc;
    auto parseResult = doc.load_file(dataFile.c_str());
    if (!parseResult) throw std::runtime_error("Error while parsing XML file");

    auto patch = doc.child("patch");

    for (auto uni : patch.children("uni")) {
        uint16_t uniNum = uni.attribute("num").as_uint();
        auto combo = manager->GetInterface(uniNum);
        auto interfaceList = uni.child("interfaces");
        if (interfaceList.child("sacn")) {
            // todo: actual configurable SACN
            combo->AddChild(new SACNInterface("beans", "127.0.0.1", uniNum));
        }

        universes.push_back({
            uniNum,
            {},
            combo
        });

        for (auto channel : uni.child("channels").children("chan")) {
            universes.back().channels.push_back({
                (uint16_t)channel.attribute("num").as_uint(),
                (uint16_t)channel.attribute("address").as_uint(),
                // todo: free??
                new Channel(FixtureData(
                    channel.attribute("type").value(),
                    channel.attribute("mode").value()
                ))
            });
        }
    }
}

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