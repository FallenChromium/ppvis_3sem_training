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

//because unique_ptrs can't be copied, we'll return raw pointers instead. As long as nobody calls delete[] on them out of ownership context (Storage, in this case) it's fine.
Catalogue* Storage::getRoot() {
    return _rootCatalogue.get();
}

Catalogue* Storage::getDrafts() {
    return _draftsCatalogue.get();
}