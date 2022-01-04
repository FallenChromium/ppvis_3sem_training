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
};

class Illustration : protected File {
    protected:
    Illustration(std::string filename, std::string author) : File(filename, author) {};
};

class Document : protected File {
    protected:
    std::string _text;
    std::set<std::shared_ptr<Illustration>> _attachments;
    std::string getText();
    void setText(std::string);
    std::set<std::shared_ptr<Illustration>> getAttachments();
    void addAttachment(std::shared_ptr<Illustration>);
    void removeAttachment(std::shared_ptr<Illustration>);
    Document(std::string filename, std::string author, std::string text, std::string name);
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
    Catalogue(std::string name);
    friend class AdminInterface;
    friend class Storage;
};



//single responsibility principle tip: it's best to create interfaces to not tightly interconnect the entities and their implementations. That way, we can also define how each actor interacts (huh, get it?) with the classes.
//Source 1: https://stackoverflow.com/questions/3441853/single-responsibility-in-c-should-i-implement-it-using-friend-classes-or-mor
//Source 2: https://hackernoon.com/single-responsibility-principle-in-c-solid-as-a-rock-4d323ygo
class SecretaryInterface {
    public:
    void insertFile();
    void searchDocumentByAuthor(std::string author);
    void searchDocumentByName(std::string name);
};

class WriterInterface {
    public:
    void createDocument(std::string name, std::string text);
    void updateDocumentName(Document doc, std::string new_name);
    void updateDocumentText(Document doc, std::string text);
    void linkIllustration(Document doc, Illustration illustration);
    //may "fail" (no changes made) silently if the Illustration is not linked to the document already.
    void unlinkIllustration(Document doc, std::shared_ptr<Illustration>);
};

class IllustratorInterface {
    public:
    void createIllustration(std::string name);
    void insertIllustration(Catalogue folder, std::shared_ptr<Illustration>);
    //will throw exception if the illustration is linked to any document
    void deleteIllustration(std::shared_ptr<Illustration>);
};

class AdminInterface {
    public:
    //delete file from ALL catalogues. Second argument is needed for the recursion.
    void deleteFile(std::shared_ptr<File>,std::shared_ptr<Catalogue>);
    void createCatalogue(std::string name, std::shared_ptr<Catalogue> parent_catalogue);
    //will throw exception if there is no such file in the old_catalogue
    void moveFile(std::shared_ptr<Catalogue> old_catalogue, std::shared_ptr<Catalogue> new_catalogue, std::shared_ptr<File> file);
};

class Storage {
    protected:
    std::unique_ptr<Catalogue> _rootCatalogue;
    std::unique_ptr<Catalogue> _draftsCatalogue;
    public:
    std::unique_ptr<Catalogue> getRoot();
    std::unique_ptr<Catalogue> getDrafts();
    Storage();
    Storage(std::string root_name, std::string drafts_name);
};

}