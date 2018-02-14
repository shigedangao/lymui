# clean the project
make clean

# compile the project (generate GCNO)
make

# test the project (generate GCDA)

./lym

# coverage the lib
gcov rgb.gcno -b