all: clean db_ tables obase character

db_: new_database.cpp 
	clang++ -std=c++17 -Wall -o db_ new_database.cpp -lsqlite3
tables: new_tables.cpp 
	clang++ -std=c++17 -Wall -o tables new_tables.cpp -lsqlite3
character:
	clang++ -std=c++17 -Wall -o character new_character.cpp -lsqlite3
open:
	clang++ -std=c++17 -Wall -o obase open_database.cpp -lsqlite3
clean:
	rm -f db_ tables obase character *.o