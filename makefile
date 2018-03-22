IDIR = lymui/include
ILIB_DIR = lib/cunit/include
ITEST_DIR = lymui/tests
CC = gcc

CFLAGS = -fprofile-arcs -ftest-coverage

ICFLAGS = -I$(IDIR) -I$(ILIB_DIR) -I$(ITEST_DIR) -Wall -fprofile-arcs -ftest-coverage

ODIR = output
TARGET = cov

DEPS = lymui/main.h \
			 lymui/rgb.h \
			 lymui/hex.h \
			 lymui/ycbcr.h \
			 lymui/cymk.h \
			 lymui/hue.h \
			 lymui/hsl.h \
			 lymui/hsv.h \
			 lymui/yuv.h \
			 lymui/xyz.h \
			 lymui/argb.h \
			 lymui/srgb.h \
			 lymui/lab.h \
			 lymui/helper.h \
			 lymui/test_header.h

OBJ  = lymui/main.c \
			 lymui/rgb.c \
			 lymui/hex.c \
			 lymui/ycbcr.c \
			 lymui/cymk.c \
			 lymui/hue.c \
			 lymui/hsl.c \
			 lymui/hsv.c \
			 lymui/yuv.c \
			 lymui/xyz.c \
			 lymui/srgb.c \
			 lymui/argb.c \
			 lymui/lab.c \
			 lymui/helper.c \
			 lymui/tests/rgb_test.c \
			 lymui/tests/hex_test.c \
			 lymui/tests/ycbcr_test.c \
			 lymui/tests/cymk_test.c \
			 lymui/tests/hue_test.c \
			 lymui/tests/hsl_test.c \
			 lymui/tests/hsv_test.c \
			 lymui/tests/yuv_test.c \
			 lymui/tests/xyz_test.c \
			 lymui/tests/srgb_test.c \
			 lymui/tests/argb_test.c \
			 lymui/tests/lab_test.c 

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