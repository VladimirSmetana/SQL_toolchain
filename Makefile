all: clean gtest db_ tables character

db_: new_database.cpp 
	clang++ -std=c++17 -Wall -o build/db_ new_database.cpp -lsqlite3
tables: new_tables.cpp 
	clang++ -std=c++17 -Wall -o build/tables new_tables.cpp -lsqlite3
character:
	clang++ -std=c++17 -Wall -o build/character new_character.cpp -lsqlite3
open:
	clang++ -std=c++17 -Wall -o build/obase open_database.cpp -lsqlite3
clean:
	rm -f build/db_ build/tables build/obase build/test build/character *.o
gtest:
	clang++ -std=c++17 -Wall -o build/test database_test.cpp -lsqlite3 -lgtest -lgtest_main -lpthread