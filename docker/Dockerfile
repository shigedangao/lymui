# Base image
FROM ubuntu:18.04

# Env variable
ENV APP_PATH "app"

# Upgrade package
RUN apt-get update

# Install git, gcov & locv
RUN apt-get install -y git && \
    apt-get install -y lcov

# Get minunit
RUN git clone https://github.com/siu/minunit.git

# Create the work folder
RUN mkdir -p ${APP_PATH}

# Set workdir
WORKDIR ${APP_PATH}
