#ifndef TESTCASEGENERATOR_H
#define TESTCASEGENERATOR_H

#include "pch.h"
#include <vector>
#include <string>
#include <random>
#include <cstring>
#include <iostream>
#include "wordSort.h"

std::string getPunct();

std::vector<char*> getInputsAlpha(int);

std::vector<Pair*> getInputsAlphaPairArr(int);

std::vector<Pair*> getInputsComplete(int);

#endif