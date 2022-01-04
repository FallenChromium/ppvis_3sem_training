#include "cms.hpp"

using namespace cms;

CMSInterface::CMSInterface(std::string name, std::shared_ptr<Storage> storage) {
    _storage = storage;
    _name = name;
}