

#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *DB;
    char *messageError;
    int exit = sqlite3_open("characters.db", &DB);
    string query = "SELECT * FROM PERSON;";

    cout << "STATE OF TABLE BEFORE INSERT" << endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    // Ввод данных нового персонажа
    string name = "Aratorn";
    string race = "Human";
    string classType = "Ranger";
    int age = 87;
    string alignment = "Lawful Good";

    int strength = 18;
    int dexterity = 14;
    int constitution = 16;
    int intelligence = 12;
    int wisdom = 15;
    int charisma = 17;

    string insertCharacter = "INSERT INTO CHARACTER (NAME, RACE, CLASS, AGE, ALIGNMENT) VALUES('" + name + "', '" + race + "', '" + classType + "', " + to_string(age) + ", '" + alignment + "');";

    string insertStats = "INSERT INTO STATS (NAME, STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA) VALUES('" + name + "', " + to_string(strength) + ", " + to_string(dexterity) + ", " + to_string(constitution) + ", " + to_string(intelligence) + ", " + to_string(wisdom) + ", " + to_string(charisma) + ");";

    exit = sqlite3_exec(DB, insertCharacter.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        cerr << "Error inserting into CHARACTER table: " << messageError << endl;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Character added successfully" << endl;
    }

    exit = sqlite3_exec(DB, insertStats.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        cerr << "Error inserting into STATS table: " << messageError << endl;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Stats added successfully" << endl;
    }

    // Вывод содержимого таблиц
    string queryCharacter = "SELECT c.NAME, c.RACE, c.CLASS, c.AGE, c.ALIGNMENT, s.STRENGTH, s.DEXTERITY, s.CONSTITUTION, s.INTELLIGENCE, s.WISDOM, s.CHARISMA FROM CHARACTER c JOIN STATS s ON c.NAME = s.NAME;";

    cout<< "CHARACTER TABLE:" << endl;
    sqlite3_exec(DB, queryCharacter.c_str(), callback, NULL, NULL);

    // cout << "STATS TABLE:" << endl;
    // sqlite3_exec(DB, queryStats.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
    return 0;
}
