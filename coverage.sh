# clean the project
make clean

# compile the project (generate GCNO)
make

# test the project (generate GCDA)

output=$(./lym); 

if [output = -1]
then
  echo $output;
fi

# coverage the lib
gcov rgb.gcno -b