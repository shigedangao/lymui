# Base image
FROM ubuntu:18.04

# Env variable
ENV APP_PATH = "app"
ENV MINUNIT_HEADER_PATH "lib"

# Upgrade package
RUN apt-get update

# Install git, gcov & locv
RUN apt-get install -y git && \
    apt-get install -y build-essential && \
    apt-get install -y lcov

# Set workdir
WORKDIR ${APP_PATH}

# Get minunit
RUN git clone https://github.com/siu/minunit.git ${MINUNIT_HEADER_PATH}
