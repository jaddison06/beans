#pragma once

#include "DMXInterface.hpp"
#include <vector>

namespace beans {
    // A ComboInterface can send levels to any amount of child DMXInterfaces.
    // AddChild() caller is responsible for allocating memory, ownership is then passed
    // to the ComboInterface and by extension the DMXManager.
    class ComboInterface : public DMXInterface {
        public:
            ~ComboInterface();

            void AddChild(DMXInterface* child);
            
            bool RemoveChild(DMXInterface* child);

            void SetLevels(DMXData data);
        
        private:
            std::vector<DMXInterface*> children;
    };
}