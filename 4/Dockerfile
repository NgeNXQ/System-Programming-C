# Use a base image with a Linux distribution of your choice
FROM ubuntu:latest

# Install build tools and kernel headers
RUN apt-get update && \
    apt-get install -y build-essential linux-headers-$(uname -r)

# Set the working directory
WORKDIR /module

# Copy your module source code and Makefile into the container
COPY mymodule.c .
COPY Makefile .

# Build the module
RUN make

# Command to run when the container starts
CMD ["bash"]