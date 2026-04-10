# compiler
CC = gcc

# flags (good practice for marks)
CFLAGS = -Wall -std=c99

# output names
MAIN = dashboard
TEST = test

# source files
SRC = DB.c DB_impl.c dashboard.c
TEST_SRC = DB.c DB_impl.c testing/test_main.c

# =========================
# build main program
# =========================
all: $(MAIN)

$(MAIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(MAIN)

# =========================
# run program
# =========================
run:
	./$(MAIN) -c PicnicTable.csv

# =========================
# build and run tests
# =========================
tests: $(TEST)
	./$(TEST)

$(TEST): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST)

# =========================
# clean files
# =========================
clean:
	rm -f $(MAIN) $(TEST) *.o *.csv *.bin

# =========================
# create submission archive
# =========================
tar:
	tar -czvf A3_submission.tar.gz \
	DB.c DB.h DB_impl.c DB_impl.h dashboard.c \
	makefile design.txt \
	testing \
	PicnicTable.bin