#include "ComboInterface.hpp"

using namespace beans;

ComboInterface::~ComboInterface() {
    for (auto child : children) {
        delete child;
    }
}

void ComboInterface::AddChild(DMXInterface* child) {
    children.push_back(child);
}

bool ComboInterface::RemoveChild(DMXInterface* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            delete children[i];
            children.erase(children.begin() + i);
            return true;
        }
    }
    return false;
}

void ComboInterface::SetLevels(uint16_t addr, DMXData data) {
    for (auto child : children) {
        child->SetLevels(addr, data);
    }
}