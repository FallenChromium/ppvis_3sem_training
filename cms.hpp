#include <memory>
#include <string>
#include <ctime>
#include <set>

class File {
    protected:
    std::string _filename;
    tm _created_on;
    std::string _author;
    //this class is abstract and thus the constructor shouldn't be available to the user.
    File(std::string filename, std::string author);
};

//classes Document and Illustration exist mostly to be able to determine the file type.
class Illustration : protected File {

};

class Document : protected File {
    protected:
    std::string text;
    std::set<std::unique_ptr<Illustration>> attachments;
    Document(std::string filename, std::string author, std::string text, std::string name) : File(filename, author) {};
};


class Catalogue {
    protected:
    std::string name;
    std::set<std::unique_ptr<File>> _files;
    std::set<std::unique_ptr<Catalogue>> _catalogues;
    //it's appropriate to use void if operation can't fail silently (exception is thrown).
    void insertFile(std::unique_ptr<File>);
    void insertCatalogue(std::unique_ptr<Catalogue>);
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
    void createDocument();
    void updateDocumentName(Document doc, std::string new_name);
    void updateDocumentText(Document doc, std::string text);
    void linkIllustration(Document doc, Illustration illustration);
    //may "fail" (no changes made) silently if the Illustration is not linked to the document already.
    void unlinkIllustration(Document doc, std::unique_ptr<Illustration>);
};

class IllustratorInterface {
    public:
    void createIllustration(std::string name);
    void insertIllustration(Catalogue folder, std::unique_ptr<Illustration>);
    //will throw exception if the illustration is linked to any document
    void deleteIllustration(std::unique_ptr<Illustration>);
};

class AdminInterface {
    public:
    void deleteFile(std::unique_ptr<File>);
    void createCatalogue(std::string name, std::unique_ptr<Catalogue> parent_catalogue);
    //will throw exception if there is no such file in the old_catalogue
    void moveFile(Catalogue old_catalogue, Catalogue new_catalogue, File file);
};