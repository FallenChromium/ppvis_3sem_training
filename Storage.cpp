#include "cms.hpp"

using namespace cms;

Storage::Storage() {
    _rootCatalogue = std::make_unique<Catalogue>(Catalogue("/"));
    _draftsCatalogue = std::make_shared<Catalogue>(Catalogue("Drafts"));
    _rootCatalogue->insertCatalogue(_draftsCatalogue);
}

Storage::Storage(std::string rootName, std::string draftsName) {
    _rootCatalogue = std::make_unique<Catalogue>(Catalogue(rootName));
    _draftsCatalogue = std::make_shared<Catalogue>(Catalogue(draftsName));
    _rootCatalogue->insertCatalogue(_draftsCatalogue);
}

std::shared_ptr<Catalogue> Storage::getRoot() {
    return _rootCatalogue;
}

std::shared_ptr<Catalogue> Storage::getDrafts() {
    return _draftsCatalogue;
}

void Storage::createDraft(std::shared_ptr<File> file) {
    _draftsCatalogue->insertFile(file);
}