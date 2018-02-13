IDIR = lymui/include
CC = gcc
CFLAGS = -I$(IDIR)
ODIR = output
DEPS = lymui/main.h lymui/rgb.h lymui/hex.h lymui/ycbcr.h lymui/helper.h
OBJ = lymui/main.c lymui/rgb.c lymui/hex.c lymui/ycbcr.c lymui/helper.c

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lym: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*o *~	core $(INCDIR)/*~

test:
	./lym