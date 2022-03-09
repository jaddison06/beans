#pragma once

#include <string>
#include <map>
#include <vector>

#include "Parameter.hpp"

namespace beans {
    // maps group names (Position, Colour, Beam, etc) to lists of parameters
    typedef std::map<std::string, std::vector<Parameter>> ParamGroupList;

    // Addressing info & metadata for ONE MODE of a fixture
    class FixtureData {
        public:
            FixtureData(std::string dataFile, std::string mode);

            bool FindParam(std::string name, Parameter* out);

            std::string name;
            std::string manufacturer;
            ParamGroupList paramGroups;
    };
}