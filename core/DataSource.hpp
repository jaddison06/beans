#pragma once

namespace beans {
    class DataSource {
        public:
            // Needs to be able to return an empty value if it doesn't know what
            // to do with a channel
            virtual ?? GetDataForChannel(int channel);
    };
}