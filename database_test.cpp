#include <gtest/gtest.h>
#include <sqlite3.h>
#include <iostream>

// Function to open the database
int openDatabase(sqlite3** DB) {
    return sqlite3_open("characters.db", DB);
}

// Function to close the database
void closeDatabase(sqlite3* DB) {
    sqlite3_close(DB);
}

void createTable(sqlite3* DB)
{
    char* messageError;
    std::string sql1 = "CREATE TABLE IF NOT EXISTS CHARACTER("
                   "NAME TEXT PRIMARY KEY NOT NULL, "
                   "RACE TEXT NOT NULL, "
                   "CLASS TEXT NOT NULL, "
                   "AGE INT NOT NULL, "
                   "ALIGNMENT TEXT NOT NULL);";
    sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messageError); 
}

void deleteTable(sqlite3* DB)
{
    char* messageError;
    std::string sql1 = "DROP TABLE CHARACTER;";
    sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messageError); 
}

// Test case for opening the database
TEST(DatabaseTest, OpenDatabase) {
    sqlite3* DB;
    int exit = openDatabase(&DB);
    EXPECT_EQ(exit, SQLITE_OK);
    if (exit == SQLITE_OK) {
        std::cout << "Opened Database Successfully!" << std::endl;
    } else {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
    }
    closeDatabase(DB);
}

// Test case for closing the database
TEST(DatabaseTest, CloseDatabase) {
    sqlite3* DB;
    openDatabase(&DB);
    closeDatabase(DB);
    // Check if the database pointer is not null after closing
    EXPECT_NE(DB, nullptr);
}

// Test case for creating the table
TEST(DatabaseTest, CreateTable) {
    sqlite3* DB;
    openDatabase(&DB);
    createTable(DB);
    // Check if the table was created successfully
    char* messageError;
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='CHARACTER';";
    int rc = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    EXPECT_EQ(rc, SQLITE_OK);
    if (rc != SQLITE_OK) {
        std::cerr << "Error: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    deleteTable(DB);
    closeDatabase(DB);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}