#include <iostream>
#include <sqlite3.h>

int main(int argc, char** argv) 
{ 
    sqlite3* DB; 
    int exit = sqlite3_open("characters.db", &DB); 
    char* messageError;

std::string sql1 = "CREATE TABLE IF NOT EXISTS CHARACTER("
                   "NAME TEXT PRIMARY KEY NOT NULL, "
                   "RACE TEXT NOT NULL, "
                   "CLASS TEXT NOT NULL, "
                   "AGE INT NOT NULL, "
                   "ALIGNMENT TEXT NOT NULL);";

std::string sql2 = "CREATE TABLE IF NOT EXISTS STATS("
                   "NAME TEXT PRIMARY KEY NOT NULL, "
                   "STRENGTH INT NOT NULL, "
                   "DEXTERITY INT NOT NULL, "
                   "CONSTITUTION INT NOT NULL, "
                   "INTELLIGENCE INT NOT NULL, "
                   "WISDOM INT NOT NULL, "
                   "CHARISMA INT NOT NULL);";

    exit = sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messageError); 
    if (exit != SQLITE_OK) { 
        std::cerr << "Error creating CHARACTER table: " << messageError << std::endl; 
        sqlite3_free(messageError); 
    } else {
        std::cout << "CHARACTER table created successfully" << std::endl; 
    }

    exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messageError); 
    if (exit != SQLITE_OK) { 
        std::cerr << "Error creating STATS table: " << messageError << std::endl; 
        sqlite3_free(messageError); 
    } else {
        std::cout << "STATS table created successfully" << std::endl; 
    }

    sqlite3_close(DB); 
    return 0; 
}
