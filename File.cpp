#include "cms.hpp"

using namespace cms;

File::File(std::string filename, std::string author) {
    _author = author;
    _filename = filename;
    //insert current timestamp
    timegm(&_created_on);
}

std::string File::getName() {
    return _filename;
}

std::string File::getAuthor() {
    return _author;
}

void File::setName(std::string name) {
    _filename = name;
}