#include "FixtureData.hpp"
#include "../3rdparty/pugi/pugixml.hpp"
#include <stdio.h>

using namespace beans;

FixtureData::FixtureData(std::string dataFile, std::string targetMode) {
    pugi::xml_document doc;
    auto parseResult = doc.load_file(dataFile.c_str());
    if (!parseResult) throw std::runtime_error("Error while parsing XML file");

    auto fixture = doc.child("fixture");
    name = fixture.attribute("name").value();
    manufacturer = fixture.attribute("manufacturer").value();

    for (auto mode : fixture.children("mode")) {
        if (mode.attribute("name").value() == targetMode) {
            for (auto paramGroup : mode.children("group")) {
                auto groupName = paramGroup.attribute("name").value();
                paramGroups[groupName] = {};
                for (auto param : paramGroup.children("param")) {
                    paramGroups[groupName].push_back(
                        Parameter {
                            param.attribute("name").value(),
                            param.attribute("min").as_int(),
                            param.attribute("max").as_int(),
                            param.attribute("home").as_int(),
                            param.attribute("is16bit").as_bool(),
                            param.attribute("offset").as_int()
                        }
                    );
                }

            }
        }
    }
}

void FixtureData::Print() {
    printf("FixtureData: %s %s\nParameters:\n", manufacturer.c_str(), name.c_str());
    for (auto group : paramGroups) {
        printf("%s:\n", group.first.c_str());
        for (auto param : group.second) {
            printf("    - %s: (%i-%i), home %i\n", param.name.c_str(), param.min, param.max, param.home);
        }
    }
}

bool FixtureData::FindParam(std::string name, Parameter* out) {
    for (auto group : paramGroups) {
        for (auto param : group.second) {
            if (param.name == name) {
                *out = param;
                return true;
            }
        }
    }
    return false;
}