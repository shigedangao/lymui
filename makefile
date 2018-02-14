IDIR = lymui/include
ILIB_DIR = lib/cunit/include
CC = gcc
CFLAGS = -I$(IDIR) -I$(ILIB_DIR)
ODIR = output
DEPS = lymui/main.h lymui/rgb.h lymui/hex.h lymui/ycbcr.h lymui/helper.h
OBJ = lymui/main.c lymui/rgb.c lymui/hex.c lymui/ycbcr.c lymui/helper.c

LDFLAGS += -Llib/cunit
LIBFLAGS += -lcunit 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lym: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*o *~	core $(INCDIR)/*~

test:
	./lym