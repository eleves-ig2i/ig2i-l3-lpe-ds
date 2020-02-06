all: test_dynamic test_static

LIB=./lib/
SRC=./src/
INC=./include/
BIN=./build/

test_dynamic: dynamic test_date.o
	gcc -L$(LIB) $(BIN)test_date.o -o $(BIN)test_date_dynamic -ldate

test_static: static test_date.o
	gcc -static -L$(LIB) $(BIN)test_date.o -o $(BIN)test_date_static -ldate

static: date.o
	ar -qvs $(LIB)libdate.a $(LIB)date.o # production de la librairie statique

dynamic: date_fPIC.o
	gcc -shared $(LIB)date_fPIC.o -o $(LIB)libdate.so # production de la librairie dynamique

date.o: $(SRC)date.c
	gcc -I$(INC) -c $(SRC)date.c -o $(LIB)date.o # compilation
	
date_fPIC.o : $(SRC)date.c
	gcc -I$(INC) -c -fPIC $(SRC)date.c -o $(LIB)date_fPIC.o # compilation du fichier objet pour la librairie dynamique
	
test_date.o: $(SRC)example/test_date.c
	gcc -I$(INC) -c $(SRC)example/test_date.c -o $(BIN)test_date.o
	
clean:
	rm $(LIB)* $(BIN)*
