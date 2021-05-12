#include "pch.h"
#include "wordSort.h"

// define global variables
Pair pairArr[SIZE];
int words = 0;
int nextPos = 0;
bool rWBool = 0;
std::ofstream writeFileAlpha("alphaSort.txt"); //declared up here cause for some reasons insertAlpha seg faulted if it was declared in alphaSort, no idea why
std::ofstream writeFileComplete("completeSort.txt");

bool count(std::string fileName) {
    std::ifstream file(fileName);
    std::ofstream writeFile("count.txt");
    readWords(file);
    for (int i = 0; i < words; i++) {
        writeFile << pairArr[i].word << " - " << pairArr[i].occurance << "\n";
    }
    file.close();
    writeFile.close();
    std::cout << "\nrunning count\n...\nfinished count\n" << std::endl;//yes i understand this is all at the end but if some is at the start it seg faults this is all spaghetti code dont @ me
    return 1;
}

bool location(std::string searchWord, std::string fileName) {
    std::cout << "\nrunning location\n..." << std::endl;
    std::ifstream file(fileName);
    std::ofstream writeFile("location.txt");
    int locations[SIZE];
    int locationCount = readWords(file, locations, searchWord);
    if (locationCount > 0) {
        writeFile << searchWord << " found at location(s): ";
        writeFile << locations[0] + 1;
        for (int i = 1; i < locationCount; i++) {
            writeFile << ", " << locations[i] + 1;
        }
        writeFile << "\n";
    }
    else {
        writeFile << "no locations found" << "\n";
    }
    file.close();
    writeFile.close();
    std::cout << "finished location\n" << std::endl;
    return 1;
}

bool alphaSort(std::string fileName) {
    std::cout << "\nrunning alphaSort\n..." << std::endl;
    std::ifstream file(fileName);
    readWords(file);
    std::vector<Pair*> results;

    TreeNode* rootPtr = insertFirst(pairArr[0]);

    for (int i = 1; i < words; i++) {
        insertAlpha(pairArr[i], rootPtr);
    }

    readAlpha(rootPtr, writeFileAlpha, results);

    deleteTree(rootPtr);

    file.close();
    delete rootPtr;
    std::cout << "finished alphaSort\n" << std::endl;
    return 1;
}

bool completeSort(std::string fileName) {
    std::cout << "\nrunning completeSort\n..." << std::endl;
    std::ifstream file(fileName);
    readWords(file);
    std::vector<Pair*> results;

    TreeNode* rootPtr = insertFirst(pairArr[0]);

    for (int i = 1; i < words; i++) {
        insertComplete(pairArr[i], rootPtr);
    }

    readComplete(rootPtr, writeFileComplete, results);

    deleteTree(rootPtr);

    file.close();
    delete rootPtr;
    std::cout << "finished completeSort\n" << std::endl;
    return 1;
}

void readWords(std::ifstream& file) {
    if (rWBool) {
        return;
    }
    words = 0;
    bool inword = false;
    int len = 0;
    char word[101], c;
    while (file.get(c)) {
        if (ispunct(c) || isdigit(c)) {
            continue;
        }
        else if (inword) {
            if (isspace(c)) {
                word[len] = '\0';
                process(word);
                len = 0;
                inword = false;
            }
            else {
                word[len] = std::tolower(c);
                len++;
            }
        }
        else if (!isspace(c)) {
            inword = true;
            word[len] = std::tolower(c);
            len++;
        }
    }
    if (len > 0) {
        word[len] = '\0';
        process(word);
    }
    rWBool = true;
}

int readWords(std::ifstream& file, int locations[], std::string searchWord) {
    words = 0;
    bool inword = false;
    int len = 0;
    char word[101], c;
    int nextLocation = 0;
    while (file.get(c)) {
        if (ispunct(c) || isdigit(c)) {
            continue;
        }
        else if (inword) {
            if (isspace(c)) {
                word[len] = '\0';
                len = 0;
                inword = false;
                std::string cmp = word;
                if (searchWord == cmp) {
                    locations[nextLocation] = words;
                    nextLocation++;
                }
                words++;
            }
            else {
                word[len] = std::tolower(c);
                len++;
            }
        }
        else if (!isspace(c)) {
            inword = true;
            word[len] = std::tolower(c);
            len++;
        }
    }
    if (len > 0) {
        word[len] = '\0';
        std::string cmp = word;
        if (searchWord == cmp) {
            locations[nextLocation] = words;
            nextLocation++;
        }
        words++;
    }
    return nextLocation;
}

void process(char* word) {
    if (!search(word)) {
        words++;
        Pair p;
        copy(word, p.word);
        p.occurance++;

        pairArr[nextPos] = p;
        nextPos++;
    }
}

bool search(char* word) {
    for (int i = 0; i < words; i++) {
        if (isEqual(word, pairArr[i].word)) {
            pairArr[i].occurance++;
            return true;
        }
    }
    return false;
}

TreeNode* insertFirst(Pair p) {
    TreeNode* start = new TreeNode;
    start->pair = p;
    return start;

}

bool isEqual(char* word1, char* word2) {
    int i = 0;
    while (word1[i] != '\0') {
        if ((word1[i] - word2[i]) != 0) {
            return false;
        }
        i++;
    }
    if (word1[i] == '\0' && word2[i] != '\0') {
        return false;
    }
    return true;
}

void copy(char* word, char* p) {
    while (*word != '\0') {
        *p++ = *word++;
    }
    *p++ = '\0';
}

TreeNode* insertAlpha(Pair p, TreeNode* node) {
    TreeNode* next;
    bool left;

    if (comp(p.word, node->pair.word)) {
        next = node->left;
        left = true;
    }
    else {
        next = node->right;
        left = false;
    }
    if (next != nullptr) {
        insertAlpha(p, next);
    }
    else {
        next = new TreeNode;
        next->pair = p;
        if (left)
            node->left = next;
        else
            node->right = next;
        return next;
    }

}

void readAlpha(TreeNode* node, std::ofstream& writeFile, std::vector<Pair*>& results) {

    if (node == nullptr) {
        return;
    }
    readAlpha(node->left, writeFile, results);
    if (node->pair.word[0] != '\0') {
        results.push_back(&node->pair);
        writeFile << node->pair.word;
        writeFile << '\n';
    }
    readAlpha(node->right, writeFile, results);
}

TreeNode* insertComplete(Pair p, TreeNode* node) {
    TreeNode* next;
    bool left;
    if (p.occurance == node->pair.occurance) {
        if (!comp(p.word, node->pair.word)) {
            next = node->left;
            left = true;
        }
        else {
            next = node->right;
            left = false;
        }
    }
    else if (p.occurance > node->pair.occurance) {
        next = node->left;
        left = true;
    }
    else {
        next = node->right;
        left = false;
    }
    if (next != nullptr) {
        insertComplete(p, next);
    }
    else {
        next = new TreeNode;
        next->pair = p;
        if (left)
            node->left = next;
        else
            node->right = next;
        return next;
    }

}

void readComplete(TreeNode* node, std::ofstream& writeFile, std::vector<Pair*>& results) {
    if (node == nullptr) {
        return;
    }
    readComplete(node->left, writeFile, results);
    if (node->pair.word[0] != '\0') {
        results.push_back(&node->pair);
        writeFile << node->pair.word;
        writeFile << " - ";
        writeFile << node->pair.occurance;
        writeFile << '\n';
    }
    readComplete(node->right, writeFile, results);
}

bool comp(char* word1, char* word2) {
    int i;
    for (i = 0; word1[i] != '\0'; i++) {
        if (word1[i] - word2[i] < 0)
            return true;
        else if (word1[i] - word2[i] > 0)
            return false;
    }
    return true;
}

void deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);

    node->pair.occurance = 0;
    node->pair.word[0] = '\0';
}
