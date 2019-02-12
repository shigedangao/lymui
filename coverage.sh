# create folder for cunit
mkdir testlib
cd testlib

# clone cunit
git clone https://github.com/itzseven/cunit.git

# go to cunit folder
cd cunit

# build the cunit test lib
if [ "$1" = "window" ]
then
  mingw32-make.exe lib
else
  make lib
fi

# copy the bin folder
cp bin/include/* ../../lib/cunit/include
cp bin/libcunit.a ../../lib/cunit

# go back to main folder
cd ../../

# If it's windows we will use mingw in order to compile the project
# First clean the project
# Execute the lym executable
if [ "$1" = "window" ]
then
  mingw32-make.exe cleanTest &&
  mingw32-make.exe lym;
else
  make cleanTest &&
  make lym
fi

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