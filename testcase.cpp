#define CATCH_CONFIG_MAIN
#include "cms.hpp"
#include "catch2/catch.hpp"

using namespace cms;
//init memory
std::shared_ptr<Storage> storage = std::make_shared<Storage>();


TEST_CASE("Writer") {
        std::shared_ptr<Storage> storage = std::make_shared<Storage>();
        WriterInterface writer("Pavel", storage); 
        IllustratorInterface illustrator("Nick", storage);
        std::shared_ptr<Illustration> illustration_1 = illustrator.createIllustration("Waterfall");
 
        //naming check
        std::shared_ptr<Document> doc_test = writer.createDocument("My blog post!", "Lorem Ipsum");
        REQUIRE_THROWS_AS(writer.createDocument("My blog post!", "Should throw"), NameAlreadyTakenException);

        //linkIllustration
        writer.linkIllustration(doc_test, illustration_1);
        //Idemptoency of linkIllustration method
        REQUIRE_NOTHROW(writer.linkIllustration(doc_test, illustration_1));

        //unlinkIllustration
        writer.unlinkIllustration(doc_test, illustration_1);
        //Idempotency of unlinkIllustration method
        REQUIRE_NOTHROW(writer.unlinkIllustration(doc_test, illustration_1));

        //update name
        writer.updateDocumentName(doc_test, "Why 'using namespace std;' is bad.");
        
        //name already reserved by the other file in the same directory
        writer.createDocument("Test", "March");
        REQUIRE_THROWS_AS(writer.updateDocumentName(doc_test, "Test"), NameAlreadyTakenException);
}

TEST_CASE("Secretary") {
        //Data
        std::shared_ptr<Storage> storage = std::make_shared<Storage>();
        std::shared_ptr<Catalogue> test_catalogue = AdminInterface("Anon", storage).createCatalogue("Test folder", storage->getRoot());
        SecretaryInterface secretary("Alex", storage);
        //faux data for checking the search
        WriterInterface writer("Linus", storage);
        std::shared_ptr<Document> blogpost_1 = writer.createDocument("FOSS is live, FOSS is life!", "DWTFYWL");

        
        secretary.insertFile(blogpost_1, test_catalogue);
        //TODO: add assertion for insertFile. Works in debugger though.



        std::shared_ptr<std::set<std::shared_ptr<Document>>> results = secretary.searchDocumentByAuthor("Linus");
        REQUIRE(results->size() == 1);

        results.reset();
        results = secretary.searchDocumentByName("FOSS is live, FOSS is life!");
        REQUIRE(results->size() == 1);  
}

TEST_CASE("Admin") {
        std::shared_ptr<Storage> storage = std::make_shared<Storage>();
        AdminInterface admin("Paul", storage);
        std::shared_ptr<Catalogue> newFolder = admin.createCatalogue("fsociety", storage->getRoot());
        
        WriterInterface writer("Roman", storage);
        std::shared_ptr<Document> article = writer.createDocument("Lecture 1", "Object Oriented Programming. What, why and how.");


        admin.moveFile(storage->getDrafts(), newFolder, article);
        //TODO: make an assertion for this test

        //check moving edgecase: new folder already contains file with that name
        std::shared_ptr<Document> article_conflicting = writer.createDocument("Lecture 1", "Introduction to GameDev");
        REQUIRE_THROWS_AS(admin.moveFile(storage->getDrafts(), newFolder, article_conflicting), NameAlreadyTakenException);

        //Check deletion
        std::shared_ptr<Document> doc_for_deletion = writer.createDocument("Lecture 2", "");
        admin.deleteFile(doc_for_deletion);
        SecretaryInterface secretary("Ella", storage);
        REQUIRE(secretary.searchDocumentByName("Lecture 2")->size() == 0);
}

TEST_CASE("Illusrator") {
        std::shared_ptr<Storage> storage = std::make_shared<Storage>();
        IllustratorInterface illustrator("Minato", storage);
        WriterInterface writer("Minato", storage);
        AdminInterface admin("Mr.Gordon Freeman", storage);

        std::shared_ptr<Illustration> illustration = illustrator.createIllustration("Kushina");
        std::shared_ptr<Catalogue> folder = admin.createCatalogue("Naruto", storage->getRoot());
        illustrator.insertIllustration(folder.get(), illustration);
        
        //Setup for checking the deletion
        std::shared_ptr<Document> doc = writer.createDocument("How to abandon your son at birth and still be a good father", "Jokes on me, I'm not");
        writer.linkIllustration(doc, illustration);
        REQUIRE_THROWS_AS(illustrator.deleteIllustration(illustration), IllustrationisDependedUpon);

        
}