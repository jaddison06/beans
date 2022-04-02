#pragma once

#include <functional>
#include<string>

#include "core/commandline/nouns/Channel.hpp"
#include "core/commandline/nouns/Cue.hpp"

namespace beans::commandline {
    enum class Noun {
        Channel,
        Cue
    };

    using NounLookup = std::function< void*(Noun, uint32_t) >;

    struct Config {
        NounLookup lookup;
    };

    void Init(Config config);

    // If the user uses a shortcut, turn the sequence of keys into a valid one.
    std::string Complete(std::string keys);
    // Execute a command
    void Execute(std::string keys);
}
