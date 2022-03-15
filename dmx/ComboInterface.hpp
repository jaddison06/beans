#pragma once

#include "DMXInterface.hpp"
#include <vector>

namespace beans {
    // A ComboInterface can send levels to any amount of child DMXInterfaces.
    class ComboInterface : public DMXInterface {
        public:
            template<typename T>
            void AddChild();
            
            bool RemoveChild(DMXInterface* child);

            void SetLevels(DMXData data);
        
        private:
            std::vector<DMXInterface*> children;
    };
}