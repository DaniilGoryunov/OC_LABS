#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

constexpr int PIPE_READ = 0;
constexpr int PIPE_WRITE = 1;

void ParentRoutine(const char *pathToChild, std::istream &in);