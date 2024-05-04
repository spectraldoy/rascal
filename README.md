# rascal

A grammar and parser for a minimal server configuration language, inspiredby YAML, TOML, and NGINX.

# Building and Running

Standard CMake building procedure:

```sh
mkdir build
cd build
cmake ..
make
```

Then given an input file `path/to/file.rascal` written in the language, to check that it follows the grammar:

```
build/bin/rascal path/to/file.rascal
```

# The language

```yaml
# Preface is ignored, it's just for cool facts about the projects
preface:
	author Aditya Gomatam
	project rascal
	version 0.0.0

# Services configures what the server does at each path
# <service_name> <arg1> ... <arg_n> on <path>
# Every service is to be paired with a RequestHandler on your server
# that performs the service for requests directed to <path>
services:
	serve ./static on /test_path
	echo on /seventy_two

# TCP specifies connection stuff
tcp:
	port 8080
```

The exact grammar can be found in [grammar.h](include/grammar.h).

# TODO

This rascal parser requires that the content under sections be indented using `\t` characters. Hopefully we can improve the grammar so that it allows sections to be indented using spaces as well.
