

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <map>
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

void assignPriorityValues(map<string, int> &stats, map<string, int> priorities)
{
    map<int, int> priorityValues = {{1, 16}, {2, 13}, {3, 11}, {4, 9}, {5, 7}, {6, 5}};

    for (auto &stat : stats)
    {
        stat.second += priorityValues[priorities[stat.first]];
    }
}

int main()
{
    sqlite3 *DB;
    char *messageError;
    int exit = sqlite3_open("characters.db", &DB);
    string query = "SELECT * FROM PERSON;";

    cout << "STATE OF TABLE BEFORE INSERT" << endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    // Ввод данных нового персонажа
    string name = "Helm";
    string race = "Human";
    string classType = "Ranger";
    int age = 87;
    string alignment = "Lawful Good";

    map<string, int> stats = {{"strength", 0}, {"dexterity", 0}, {"constitution", 0}, {"intelligence", 0}, {"wisdom", 0}, {"charisma", 0}};


    map<string, int> priorities;

    priorities["strength"] = 1;
    priorities["dexterity"] = 2;
    priorities["constitution"] = 3;
    priorities["intelligence"] = 4;
    priorities["wisdom"] = 5;
    priorities["charisma"] = 6;

    if (race == "Human")
    {
        for (auto &stat : stats)
        {
            stat.second++;
        }
    }
    else if (race == "Elf")
    {
        stats["dexterity"]++;
    }

    assignPriorityValues(stats, priorities);

    string insertCharacter = "INSERT INTO CHARACTER (NAME, RACE, CLASS, AGE, ALIGNMENT) VALUES('" + name + "', '" + race + "', '" + classType + "', " + to_string(age) + ", '" + alignment + "');";

    string insertStats = "INSERT INTO STATS (NAME, STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA) VALUES('" + name + "', " + to_string(stats["strength"]) + ", " + to_string(stats["dexterity"]) + ", " + to_string(stats["constitution"]) + ", " + to_string(stats["intelligence"]) + ", " + to_string(stats["wisdom"]) + ", " + to_string(stats["charisma"]) + ");";

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

    cout << "CHARACTER TABLE:" << endl;
    sqlite3_exec(DB, queryCharacter.c_str(), callback, NULL, NULL);

    // cout << "STATS TABLE:" << endl;
    // sqlite3_exec(DB, queryStats.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
    return 0;
}
