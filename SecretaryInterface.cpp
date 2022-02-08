#include "cms.hpp"
#include <memory>

using namespace cms;

void SecretaryInterface::insertFile(std::shared_ptr<File> file, std::shared_ptr<Catalogue> catalogue) {
    catalogue->insertFile(file);
}

//this solution is NOT THAT GREAT

//For search result, I use a pointer to a set of pointers to the documents, which looks hilariously horrible in code, but in my opinion makes sense, because it allows to effortlessly bounce result between functions AND change the original files, not the copies.
void SecretaryInterface::NameSearchTraversal(std::shared_ptr<std::set<std::shared_ptr<Document> > > results, 
                                             std::string term, 
                                             std::shared_ptr<Catalogue> catalogue) 
{
    for (auto file : catalogue->getFiles()) {
        //if file is of a type Document and name == term
        //this should also ensure the type cast will be successful
        std::shared_ptr<Document> document = std::dynamic_pointer_cast<Document>(file);
        if (document != nullptr && document->getName() == term) {
            //cast ptr<File> to ptr<Document>, because we're sure it's possible
            results->insert(document);
        }
    }
    for (auto subcatalogue : catalogue->getCatalogues()) {
        NameSearchTraversal(results, term, subcatalogue);
    }
};

void SecretaryInterface::AuthorSearchTraversal(std::shared_ptr<std::set<std::shared_ptr<Document> > > results, 
                                               std::string term, 
                                               std::shared_ptr<Catalogue> catalogue) 
{
    for (auto file : catalogue->getFiles()) {
        std::shared_ptr<Document> document = std::dynamic_pointer_cast<Document>(file);
        if (document != nullptr && document->getAuthor() == term) {
            //cast ptr<File> to ptr<Document>, because we're sure it's possible
            results->insert(document);
        }
    }
    for (auto subcatalogue : catalogue->getCatalogues()) {
        AuthorSearchTraversal(results, term, subcatalogue);
    }
};

std::shared_ptr<std::set<std::shared_ptr<Document> > > SecretaryInterface::searchDocumentByAuthor(std::string author) {
    std::shared_ptr<std::set<std::shared_ptr<Document> > > results(new std::set<std::shared_ptr<Document> >);
    AuthorSearchTraversal(results, author, _storage->getRoot());
    return results;
}

std::shared_ptr<std::set<std::shared_ptr<Document> > > SecretaryInterface::searchDocumentByName(std::string name) {
    std::shared_ptr<std::set<std::shared_ptr<Document> > > results(new std::set<std::shared_ptr<Document> >);
    NameSearchTraversal(results, name, _storage->getRoot());
    return results;
}