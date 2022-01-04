#include "cms.hpp"

using namespace cms;

void IllustratorInterface::createIllustration(std::string name) {
    _storage->createDraft(std::make_shared<Illustration>(name, _name));
}

void IllustratorInterface::insertIllustration(Catalogue* folder, std::shared_ptr<Illustration> file) {
    folder->insertFile(file);
}

void IllustratorInterface::deleteIllustration(std::shared_ptr<Illustration> illustration, std::shared_ptr<Catalogue> catalogue) {
        //delete file in current directory
    catalogue->removeFile(illustration);
    //traverse catalogue system with dfs
    for(auto subcatalogue : catalogue->getCatalogues() ) {
        deleteIllustration(illustration, subcatalogue);
    }
}

void IllustratorInterface::deleteIllustration(std::shared_ptr<Illustration> illustration) {
    //TODO: check if it's linked to any document, throw if it is
    deleteIllustration(illustration, _storage->getRoot());
}
