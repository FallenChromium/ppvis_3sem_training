#define CATCH_CONFIG_MAIN
#include "cms.hpp"
#include "catch2/catch.hpp"

using namespace cms;
//init memory
std::shared_ptr<Storage> storage = std::make_shared<Storage>();
WriterInterface writer("Pavel", storage);

TEST_CASE("Writer") {
        writer.createDocument("My blog post!", "Lorem Ipsum");
}