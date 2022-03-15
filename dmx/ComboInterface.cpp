#include "ComboInterface.hpp"

using namespace beans;

template<typename T>
void ComboInterface::AddChild() {
    children.push_back(new T);
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

void ComboInterface::SetLevels(DMXData data) {
    for (auto child : children) {
        child->SetLevels(data);
    }
}