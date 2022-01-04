#include "cms.hpp"

using namespace cms;

std::shared_ptr<Illustration> IllustratorInterface::createIllustration(std::string name) {
    std::shared_ptr<Illustration> illustration = std::shared_ptr<Illustration>(new Illustration(name, _name));
    _storage->createDraft(illustration);
    return illustration;
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
