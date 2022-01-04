#include "cms.hpp"

using namespace cms;

void WriterInterface::createDocument(std::string title, std::string text) {
    _storage->getDrafts()->insertFile(std::make_shared<Document>(title, text));
}

void WriterInterface::updateDocumentName(std::shared_ptr<Document> doc, std::string new_name) {
    //TODO: throw if in any folder with this file there's another file with new_name as a name
    doc->setName(new_name);
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