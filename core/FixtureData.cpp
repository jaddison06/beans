#include "FixtureData.hpp"

using namespace beans;

FixtureData::FixtureData(std::string dataFile, std::string mode) {
    
}

bool FixtureData::FindParam(std::string name, Parameter* out) {
    for (auto group : paramGroups) {
        for (auto param : group.second) {
            if (param.name == name) {
                *out = param;
                return;
            }
        }
    }
}