#include <memory>
#include <string>
#include <ctime>
#include <set>

namespace cms {
class File {
    protected:
    std::string _filename;
    tm _created_on;
    std::string _author;
    std::string getName();
    std::string getAuthor();
    std::string getCreatedDate();
    void setName(std::string);
    File(std::string filename, std::string author);
    virtual ~File() {};
    friend class SecretaryInterface;
    friend class WriterInterface;
    friend class Catalogue;
};

class Illustration : public File {
    protected:
    Illustration(std::string filename, std::string author) : File(filename, author) {};
    friend class IllustratorInterface;
};

class Document : public File {
    protected:
    std::string _text;
    std::set<std::shared_ptr<Illustration>> _attachments;
    std::string getText();
    void setText(std::string);
    std::set<std::shared_ptr<Illustration>> getAttachments();
    void addAttachment(std::shared_ptr<Illustration>);
    void removeAttachment(std::shared_ptr<Illustration>);
    Document(std::string filename, std::string author, std::string text);
    friend class WriterInterface;
};


class Catalogue {
    protected:
    std::string _name;
    std::set<std::shared_ptr<File>> _files;
    std::set<std::shared_ptr<Catalogue>> _catalogues;
    //it's appropriate to use void if operation can't fail silently (exception is thrown).
    void insertFile(std::shared_ptr<File>);
    void insertCatalogue(std::shared_ptr<Catalogue>);
    void removeFile(std::shared_ptr<File>);
    void removeCatalogue(std::shared_ptr<Catalogue>);
    std::set<std::shared_ptr<File>> getFiles() const;
    std::set<std::shared_ptr<Catalogue>> getCatalogues() const;
    std::string getName();
    Catalogue(std::string name);
    friend class AdminInterface;
    friend class IllustratorInterface;
    friend class WriterInterface;
    friend class SecretaryInterface;
    friend class Storage;
};

class Storage {
    private:
    std::shared_ptr<Catalogue> _rootCatalogue;
    std::shared_ptr<Catalogue> _draftsCatalogue;
    //adds a newly constructed file to the drafts folder
    void createDraft(std::shared_ptr<File>);
    public:
    std::shared_ptr<Catalogue> getRoot();
    std::shared_ptr<Catalogue> getDrafts();
    Storage();
    Storage(std::string root_name, std::string drafts_name);
    friend class IllustratorInterface;
};

class CMSInterface {
    protected:
    std::string _name;
    std::shared_ptr<Storage> _storage;
    CMSInterface(std::string name, std::shared_ptr<Storage> storage);
    virtual ~CMSInterface() {};

};

//single responsibility principle tip: it's best to create interfaces to not tightly interconnect the entities and their implementations. That way, we can also define how each actor interacts (huh, get it?) with the classes.
//Source 1: https://stackoverflow.com/questions/3441853/single-responsibility-in-c-should-i-implement-it-using-friend-classes-or-mor
//Source 2: https://hackernoon.com/single-responsibility-principle-in-c-solid-as-a-rock-4d323ygo
class SecretaryInterface: public CMSInterface {
    protected:
    //helper functions, recursive
    void NameSearchTraversal(std::shared_ptr<std::set<std::shared_ptr<Document>>> results, std::string term, std::shared_ptr<Catalogue> catalogue);
    void AuthorSearchTraversal(std::shared_ptr<std::set<std::shared_ptr<Document>>>, std::string term, std::shared_ptr<Catalogue> catalogue);
    public:
    void insertFile(std::shared_ptr<File> file, std::shared_ptr<Catalogue> catalogue);
    std::shared_ptr<std::set<std::shared_ptr<Document>>> searchDocumentByAuthor(std::string author);
    std::shared_ptr<std::set<std::shared_ptr<Document>>> searchDocumentByName(std::string name);
    SecretaryInterface(std::string name, std::shared_ptr<Storage> storage) : CMSInterface(name, storage) {};

};

class WriterInterface: public CMSInterface {
    protected:
    //helper functions, recursive
    void updateNameChecker(std::string new_name, std::shared_ptr<Catalogue> catalogue);
    public:
    void createDocument(std::string name, std::string text);
    void updateDocumentName(std::shared_ptr<Document> doc, std::string new_name);
    void updateDocumentText(std::shared_ptr<Document> doc, std::string text);
    void linkIllustration(std::shared_ptr<Document> doc, std::shared_ptr<Illustration> illustration);
    //may "fail" (no changes made) silently if the Illustration is not linked to the document already.
    void unlinkIllustration(std::shared_ptr<Document> doc, std::shared_ptr<Illustration>);
    WriterInterface(std::string name, std::shared_ptr<Storage> storage) : CMSInterface(name, storage) {};
};

class IllustratorInterface: public CMSInterface {
    protected:
    //helper function, needed for recursion
    void deleteIllustration(std::shared_ptr<Illustration>, std::shared_ptr<Catalogue>);
    public:
    void createIllustration(std::string name);
    //Functions that don't impact object's lifetime should take a plain reference
    //Source: https://www.youtube.com/watch?v=xnqTKD8uD64
    void insertIllustration(Catalogue *folder, std::shared_ptr<Illustration>);
    //will throw exception if the illustration is linked to any document
    void deleteIllustration(std::shared_ptr<Illustration>);
    IllustratorInterface(std::string name, std::shared_ptr<Storage> storage) : CMSInterface(name, storage) {};

};

class AdminInterface: public CMSInterface {
    protected:
    //helper function, recursive
    void deleteFile(std::shared_ptr<File>,std::shared_ptr<Catalogue>);
    public:
    void deleteFile(std::shared_ptr<File>);
    void createCatalogue(std::string name, std::shared_ptr<Catalogue> parent_catalogue);
    //will throw exception if there is no such file in the old_catalogue
    void moveFile(std::shared_ptr<Catalogue> old_catalogue, std::shared_ptr<Catalogue> new_catalogue, std::shared_ptr<File> file);
    AdminInterface(std::string name, std::shared_ptr<Storage> storage) : CMSInterface(name, storage) {};

};


struct NameAlreadyTakenException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Name is already taken. Please, name your file differently.";
    }
};

}