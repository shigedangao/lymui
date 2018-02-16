# clean the project
make clean

# compile the project (generate GCNO)
make

# test the project (generate GCDA)

output=$(./lym params); 
echo $output;
if [[ $output = *"failures"* ]]
then
  echo "exit";
  exit;
fi

# coverage the lib
gcov rgb.gcno -b