#include "cms.hpp"

using namespace cms;

Catalogue::Catalogue(std::string name) {
    _name = name;
}

std::string Catalogue::getName() {
    return _name;
}

void Catalogue::insertFile(std::shared_ptr<File> file) {
    for (auto i: _files) {
        if (i->getName() == file->getName()) throw NameAlreadyTakenException();
    }
    _files.insert(file);
}

void Catalogue::removeFile(std::shared_ptr<File> file) {
    _files.erase(file);
}

void Catalogue::insertCatalogue(std::shared_ptr<Catalogue> catalogue) {
    for (auto i: _catalogues) {
        if (i->getName() == catalogue->getName()) throw NameAlreadyTakenException();
    }
    _catalogues.insert(catalogue);
}

void Catalogue::removeCatalogue(std::shared_ptr<Catalogue> catalogue) {
    _catalogues.erase(catalogue);
}

std::set<std::shared_ptr<File>>  Catalogue::getFiles() const {
    return _files;
}

std::set<std::shared_ptr<Catalogue>>  Catalogue::getCatalogues() const {
    return _catalogues;
}