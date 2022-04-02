#include "core/commandline/generated.hpp"

namespace beans::commandline {
    static Config config;
    void commandline::Init(Config config_) {
        config = config_;
    }

    std::string commandline::Complete(std::string keys) {}
    void commandline::Execute(std::string keys) {}
}
