#include "pch.h"
#include "wordSort.h"
#include "testCaseGenerator.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct WordFixture : public testing::TestWithParam<int> {
	vector<char*> inputs;
	void SetUp() {
		inputs = getInputsAlpha(2);
	}
	void TearDown() {
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct SearchFixture : public testing::TestWithParam<int> {
	vector<char*> inputs;
	char newWord[101];
	void SetUp() {
		words = rand() % 6;
		nextPos = words;
		inputs = getInputsAlpha(words + 1);
		// The first 5 inputs are used to populate pairArr
		for (int i = 0; i < words; i++) {
			strcpy(pairArr[i].word, inputs[i]);
		}
		// The last input is used to populate a new word not in the pairArr
		strcpy(newWord, inputs.back());
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct ReadWordFixture : public testing::TestWithParam<int> {
	vector<Pair*> inputs;
	vector<string> text;
	ifstream ifs;
	void SetUp() { 
		srand(unsigned(time(0)));
		inputs = getInputsComplete(rand() % 6 + 1);

		// Generate text from distinct words
		for (Pair* p : inputs) {
			for (int i = 0; i < p->occurance; i++) {
				text.push_back(string(p->word));
			}
		}
		random_shuffle(text.begin(), text.end());

		// Output text to file
		ofstream ofs;
		ofs.open("test.txt", ofstream::out | ofstream::trunc);
		for (string w : text) {
			w.insert(rand() % w.length(), getPunct()); // Add punctuation
			ofs << w << getPunct() << " ";
		}
		ofs.close();
		ifs.open("test.txt", ofstream::in);
	}
	void TearDown() {
		ifs.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct ReadAlphaFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	ofstream writeFile;
	vector<Pair*> inputs;
	vector<Pair*> results;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsAlphaPairArr(15);
		//create tree root
		root = insertFirst(*inputs[0]);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			insertAlpha(*inputs[i], root);
		}
		
		writeFile.open("ReadAlpha.txt", ofstream::out);
	}
	void TearDown() {
		writeFile.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct ReadCompleteFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	ofstream writeFile;
	vector<Pair*> inputs;
	vector<Pair*> results;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsComplete(15);
		//create tree root
		root = insertFirst(*inputs[0]);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			insertComplete(*inputs[i], root);
		}

		writeFile.open("ReadComplete.txt", ofstream::out);
	}
	void TearDown() {
		writeFile.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct DeleteTreeFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;
	vector<TreeNode*> nodes;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsComplete(15);
		//create tree root
		root = insertFirst(*inputs[0]);
		nodes.push_back(root);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			nodes.push_back(insertComplete(*inputs[i], root));
		}
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct InsertNodeAlphaFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;

	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsAlphaPairArr(3);
		//create tree root
		root = insertFirst(*inputs[0]);
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct InsertNodeCompleteFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;

	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsComplete(3);
		//create tree root
		root = insertFirst(*inputs[0]);
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

// Run randomized test multiple times
INSTANTIATE_TEST_CASE_P(Instantiation, WordFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, SearchFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadWordFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadAlphaFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadCompleteFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, DeleteTreeFixture, ::testing::Range(1, 11), );

TEST_F(WordFixture, WordCompare) {
	// Input[0] > Input[1]
	EXPECT_TRUE(comp(inputs[0], inputs[1]));
	EXPECT_TRUE(comp(inputs[1], inputs[1]));
	EXPECT_FALSE(comp(inputs[1], inputs[0]));
}

TEST_F(WordFixture, WordEqual) {
	EXPECT_TRUE(isEqual(inputs[0], inputs[0]));
	EXPECT_FALSE(isEqual(inputs[0], inputs[1]));
}

TEST_F(WordFixture, WordCopy) {
	char newWord[101];
	copy(inputs[0], newWord);
	EXPECT_TRUE(strcmp(inputs[0], newWord) == 0);
}

TEST_F(SearchFixture, WordSearch) {
	// Randomly choose an existing word in pairArr and search for it
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	EXPECT_TRUE(search(pairArr[randIndx].word));
	EXPECT_TRUE(pairArr[randIndx].occurance - prevOccur == 1);
	// Search for new word
	EXPECT_FALSE(search(newWord));
}

TEST_F(SearchFixture, WordProcess) {
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	int prevWords = words;
	int prevNextPos = nextPos;
	// Randomly choose an existing word in pairArr and process it
	process(pairArr[randIndx].word);
	EXPECT_EQ(prevWords, words);
	EXPECT_EQ(prevNextPos, nextPos);
	// Process a new word
	process(newWord);
	EXPECT_EQ(prevWords, words - 1);
	EXPECT_EQ(prevNextPos, nextPos - 1);
}

TEST_F(ReadWordFixture, ReadWordsLoc) {
	// One of the words in the input
	int randIdx = rand() % inputs.size();
	string word = string(inputs[randIdx]->word);
	int checkNextLoc = 0;
	int checkloc[100]; // correct location array
	int location[100];
	
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == word)
			checkloc[checkNextLoc++] = i;
	}

	int nextLoc = readWords(ifs, location, word);

	EXPECT_EQ(words, text.size()); // Every word has been read
	// Correctly captured all occurances of search word
	EXPECT_EQ(nextLoc, inputs[randIdx]->occurance); 
	for (int i = 0; i < nextLoc; i++) {
		EXPECT_EQ(checkloc[i], location[i]);
	}
}

TEST_F(ReadWordFixture, ReadWordsPair) {
	readWords(ifs);
	for (int i = 0; i < words; i++) {
		bool found = false;
		for (Pair* p : inputs) {
			if (string(p->word) == string(pairArr[i].word) && p->occurance == pairArr[i].occurance) {
				found = true;
				break;
			}
		}
		// Number of words in pairArr is equal to that of words in inputs
		EXPECT_TRUE(found);
	}
	// Check for number of distinct words
	EXPECT_TRUE(words == nextPos && words == inputs.size());
}

TEST_F(ReadAlphaFixture, ReadBSTTreeAlphabetically) {
	readAlpha(root, writeFile, results);
	for (int i = 0; i < results.size(); i++) {
		EXPECT_TRUE(isEqual(results[i]->word, inputs[i]->word));
	}
}

TEST_F(InsertNodeAlphaFixture, insertFirst) {
	EXPECT_EQ(root->pair.occurance, inputs[0]->occurance);
	EXPECT_EQ(comp(root->pair.word, inputs[0]->word), true);
	EXPECT_EQ(root->left, nullptr);
	EXPECT_EQ(root->right, nullptr);
}

TEST_F(InsertNodeAlphaFixture, insertAlpha) {
	//The inputs array have the words arranged in alphabetical order
	//The insertAlpha function put "smaller" word on the left and "bigger" word on the right
	for (int i = 1; i < inputs.size(); i++) {
		insertAlpha(*inputs[i], root);
	}
	
	TreeNode* nodeCursor = root;
	for (int i = 0; i < inputs.size() - 1; i++) {
		EXPECT_TRUE(nodeCursor->pair.occurance == inputs[i]->occurance);
		EXPECT_TRUE(isEqual(nodeCursor->pair.word, inputs[i]->word));
		EXPECT_FALSE(comp(inputs[i+1]->word, inputs[i]->word));
		EXPECT_TRUE(nodeCursor->left == nullptr);
		EXPECT_FALSE(nodeCursor->right == nullptr);
		nodeCursor = nodeCursor->right;
	}
}

/*
TEST_F(InsertNodeCompleteFixture, insertComplete) {
	//The inputs array have the words arranged in alphanumeric order
	//The insertAlpha function put "smaller" word on the left and "bigger" word on the right
	for (int i = 1; i < inputs.size(); i++) {
		insertComplete(*inputs[i], root);
	}

	TreeNode* nodeCursor = root;
	for (int i = 0; i < inputs.size() - 1; i++) {
		EXPECT_TRUE(nodeCursor->pair.occurance == inputs[i]->occurance);
		EXPECT_TRUE(isEqual(nodeCursor->pair.word, inputs[i]->word));
		EXPECT_FALSE(comp(inputs[i + 1]->word, inputs[i]->word));
		EXPECT_TRUE(nodeCursor->left == nullptr);
		EXPECT_FALSE(nodeCursor->right == nullptr);
		nodeCursor = nodeCursor->right;
	}
}
*/


/*
TEST_F(ReadCompleteFixture, ReadBSTTreeCompletely) {
	readComplete(root, writeFile, results);
	for (int i = 0; i < results.size(); i++) {
		EXPECT_TRUE(isEqual(results[i]->word, inputs[i]->word));
		EXPECT_TRUE(results[i]->occurance == inputs[i]->occurance);		
	}
}
*/
/*
TEST_F(DeleteTreeFixture, DeleteTree) {
	delete(root);
	char expectedWord[101];
	expectedWord[0] = '\0';
	int expectedOccurance = 0;
	for (int i = 0; i < nodes.size(); i++) {
		EXPECT_TRUE(isEqual(nodes[i]->pair.word, expectedWord));
		EXPECT_TRUE(nodes[i]->pair.occurance == expectedOccurance);
	}
}
*/