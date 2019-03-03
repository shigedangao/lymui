# Run the steps to do coverage

# build the lib (generate gcda)
make lym

# Run the test (generate gcno)
make tests

# prepare the coverage
make prepare_coverage

# Generate the coverage file
make run_coverage