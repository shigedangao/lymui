IDIR = lymui/include
ILIB_DIR = lib/cunit/include
CC = gcc

CFLAGS = -fprofile-arcs -ftest-coverage

ICFLAGS = -I$(IDIR) -I$(ILIB_DIR) -Wall -fprofile-arcs -ftest-coverage

ODIR = output
TARGET = cov

DEPS = lymui/main.h \
			 lymui/rgb.h \
			 lymui/hex.h \
			 lymui/ycbcr.h \
			 lymui/helper.h

OBJ  = lymui/main.c \
			 lymui/rgb.c \
			 lymui/hex.c \
			 lymui/ycbcr.c \
			 lymui/helper.c

LDFLAGS += -Llib/cunit
LIBFLAGS += -lcunit

%.o: %.c $(DEPS)
	$(CC) -c -o $(COV)/$@ $< $(ICFLAGS)

lym: $(OBJ)
	$(CC) -o $@ $^ $(ICFLAGS) $(LDFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*o *~	core $(INCDIR)/*~ *.o *.gcda *.gcno *.gcov

test:
	./lym