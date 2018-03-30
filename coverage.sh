# clean the project
make cleanTest

# compile the project (generate GCNO)
make lym

# test the project (generate GCDA)

output=$(./lym params); 
echo $output;
if [[ $output = *"failures"* ]]
then
  echo "exit";
  exit -1;
fi

# coverage the lib
gcov rgb.gcno -b