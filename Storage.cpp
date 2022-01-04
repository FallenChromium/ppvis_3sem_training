#include "cms.hpp"

using namespace cms;

Storage::Storage() {
    _rootCatalogue = std::make_unique<Catalogue>(Catalogue("/"));
    _draftsCatalogue = std::make_unique<Catalogue>(Catalogue("Drafts"));
}

Storage::Storage(std::string rootName, std::string draftsName) {
    _rootCatalogue = std::make_unique<Catalogue>(Catalogue(rootName));
    _draftsCatalogue = std::make_unique<Catalogue>(Catalogue(draftsName));
}