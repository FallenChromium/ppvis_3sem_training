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

void IllustratorInterface::IllustrationDependencyCheck(std::shared_ptr<Illustration> illustration, std::shared_ptr<Catalogue> catalogue) {
        //check if the illustration is linked to any document
    for(auto file: catalogue->getFiles()) {
        std::shared_ptr<Document> doc = std::dynamic_pointer_cast<Document>(file);
        if (doc != nullptr) {
            std::set<std::shared_ptr<Illustration>> attachments = doc->getAttachments();
            if (attachments.find(illustration) != attachments.end()) throw IllustrationisDependedUpon();
        }
    }
    for (auto subcatalogue : catalogue->getCatalogues()) {
       IllustrationDependencyCheck(illustration, subcatalogue); 
    }
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
    IllustrationDependencyCheck(illustration, _storage->getRoot());
    deleteIllustration(illustration, _storage->getRoot());
}
