# Base image
FROM ubuntu:18.04

# Env variable
ENV APP_PATH "app"
ENV MINUNIT_HEADER_PATH "lib"

# Upgrade package
RUN apt-get update

# Install git, gcov & locv
RUN apt-get install -y git && \
    apt-get install -y build-essential && \
    apt-get install -y lcov

# Get minunit
RUN git clone https://github.com/siu/minunit.git

# Create the work folder
RUN mkdir -p ${APP_PATH}/${MINUNIT_HEADER_PATH}

# Copy the minunit.h file into the lib
RUN cp minunit/minunit.h ${APP_PATH}/${MINUNIT_HEADER_PATH}

# Set workdir
WORKDIR ${APP_PATH}
