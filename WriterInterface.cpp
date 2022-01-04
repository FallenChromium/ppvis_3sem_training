#include "cms.hpp"

using namespace cms;

std::shared_ptr<Document> WriterInterface::createDocument(std::string title, std::string text) {
    std::shared_ptr<Document> document(new Document(title, _name, text));
    _storage->getDrafts()->insertFile(document);
    return document;
}

void WriterInterface::updateDocumentName(std::shared_ptr<Document> doc, std::string new_name) {
    //TODO: throw if in any folder with this file there's another file with new_name as a name
    updateNameChecker(new_name, _storage->getRoot());
    doc->setName(new_name);
}

void WriterInterface::updateNameChecker(std::string new_name, std::shared_ptr<Catalogue> catalogue) {
    for(auto file: catalogue->getFiles()) {
        if (file->getName() == new_name) throw NameAlreadyTakenException();
    }
    for(auto subcatalogue: catalogue->getCatalogues()) {
        updateNameChecker(new_name, subcatalogue);
    }
}

void WriterInterface::updateDocumentText(std::shared_ptr<Document> doc, std::string new_text) {
    doc->setText(new_text);
}

void WriterInterface::linkIllustration(std::shared_ptr<Document> doc, std::shared_ptr<Illustration> illustration) {
    doc->addAttachment(illustration);
}

void WriterInterface::unlinkIllustration(std::shared_ptr<Document> doc, std::shared_ptr<Illustration> illustration) {
    doc->removeAttachment(illustration);
}