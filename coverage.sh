# create folder for cunit
mkdir testlib
cd testlib

# clone cunit
git clone https://github.com/itzseven/cunit.git

# go to cunit folder
cd cunit

# build the cunit test lib
make lib

# copy the bin folder
cp bin/include/* ../../lib/cunit/include
cp bin/libcunit.a ../../lib/cunit

# go back to main folder
cd ../../

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