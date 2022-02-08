#include "cms.hpp"

using namespace cms;

Document::Document(std::string filename, std::string author, std::string text) : File::File( filename, author) {
    _text = text;
}

std::string Document::getText() {
    return _text;
}

void Document::setText(std::string text) {
    _text = text;
}

std::set<std::shared_ptr<Illustration> > Document::getAttachments() {
    return _attachments;
}

void Document::addAttachment(std::shared_ptr<Illustration> attachment) {
    _attachments.insert(attachment);
}

void Document::removeAttachment(std::shared_ptr<Illustration> attachment) {
    _attachments.erase(attachment);
}