#include "cms.hpp"

using namespace cms;

const Catalogue *rootCatalogue;


void AdminInterface::createCatalogue(std::string name, std::shared_ptr<Catalogue> parent_catalogue) {
    parent_catalogue->insertCatalogue(std::make_unique<Catalogue>(Catalogue(name)));
}

void AdminInterface::createRootCatalogue() {
    rootCatalogue = new Catalogue("/");
}

void AdminInterface::moveFile(std::shared_ptr<Catalogue> old_catalogue, std::shared_ptr<Catalogue> new_catalogue, std::shared_ptr<File> file) {
    //insert first, because if in new_catalog there's another file with the same name, it'll throw
    new_catalogue->insertFile(file);
    old_catalogue->removeFile(file);
}