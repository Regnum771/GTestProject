#pragma once
#ifndef WORDSORT_H
#define WORDSORT_H

// include required libraries
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <cctype>

// define keywords
#define SIZE 50000 //the maximum words


// decalre data types
struct Pair {
    int occurance = 0;
    char word[101] = "";
};

struct TreeNode {
    Pair pair;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

// declare major methods (will all return 1 on "pass" and 0 on any fail)
bool count(std::string); //returns the count of each word in the order they appear
bool location(std::string, std::string); //returns the locations of the specified word
bool alphaSort(std::string); //sorts all words in the file alphabetically
bool completeSort(std::string); //sorts all words by alphabetical order and count

// declare minor methods
int readWords(std::ifstream&, int[], std::string);
void readWords(std::ifstream&);
void process(char*);
bool search(char*);
TreeNode* insertFirst(Pair);
TreeNode* insertAlpha(Pair, TreeNode*);
TreeNode* insertComplete(Pair, TreeNode*);
bool isEqual(char*, char*);
void copy(char*, char*);
bool comp(char*, char*);
void readAlpha(TreeNode*, std::ofstream&, std::vector<Pair*>&);
void readComplete(TreeNode*, std::ofstream&, std::vector<Pair*>&);
void deleteTree(TreeNode*);


extern Pair pairArr[SIZE];
extern int words;
extern int nextPos;
#endif