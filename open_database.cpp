

#include <iostream> 
#include <sqlite3.h> 
  
using namespace std; 
  
static int callback(void* data, int argc, char** argv, char** azColName) 
{ 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    printf("\n"); 
    return 0; 
} 
  
int main(int argc, char** argv) 
{ 
    sqlite3* DB; 
    int exit = 0; 
    exit = sqlite3_open("characters.db", &DB); 
    string data("CALLBACK FUNCTION"); 
  
    string sql("SELECT c.NAME, c.RACE, c.CLASS, c.AGE, c.ALIGNMENT, s.STRENGTH, s.DEXTERITY, s.CONSTITUTION, s.INTELLIGENCE, s.WISDOM, s.CHARISMA FROM CHARACTER c JOIN STATS s ON c.NAME = s.NAME;"); 
    if (exit) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl; 
        return (-1); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl; 
  
    int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL); 
  
    if (rc != SQLITE_OK) 
        cerr << "Error SELECT" << endl; 
    else { 
        cout << "Operation OK!" << endl; 
    } 
  
    sqlite3_close(DB); 
    return (0); 
} 
