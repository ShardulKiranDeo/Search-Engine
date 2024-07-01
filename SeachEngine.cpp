#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
unordered_map<string, vector<pair<int, int>>> invertedIndex;

void indexDocument(const string& document, int docID) 
{   istringstream iss(document);
    string word;
    int position = 0;
    while (iss >> word) 
    {
        invertedIndex[word].push_back({docID, position});
        position++;
    }
}

void indexDocuments(const vector<string>& documents) 
{
    for (int i = 0; i < documents.size(); ++i)
    {
        indexDocument(documents[i], i);
    }
}
