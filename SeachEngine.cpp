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

vector<int> search(const string& query)
{vector<int> results;
    if (invertedIndex.find(query) != invertedIndex.end()) 
    {
        for (auto& entry : invertedIndex[query]) 
        {
           results.push_back(entry.first);
        }
    }
    return results;
}


struct TrieNode 
{unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie 
{
public:
    Trie()
     {
        root = new TrieNode();
    }

    void insert(const string& word) 
    {TrieNode* node = root;
        for (char c : word) 
        {
            if (node->children.find(c) == node->children.end())
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
     node->isEndOfWord = true;
    }

    vector<string> autocomplete(const string& prefix) 
    {vector<string> suggestions;
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) 
            {
                return suggestions;
            }
            node = node->children[c];
        }
        findAllWords(node, prefix, suggestions);
        return suggestions;
    }
    TrieNode* root;
    void findAllWords(TrieNode* node, const string& prefix, vector<string>& suggestions) 
    {
        if (node->isEndOfWord) 
        {suggestions.push_back(prefix);
        }
        for (auto& pair : node->children) 
        {
            findAllWords(pair.second, prefix + pair.first, suggestions);
        }
    }
};

int main() 
{
    vector<string> documents = 
    {"The quick brown fox jumps over the lazy dog",
        "The cat napped lazily under the warm afternoon sun",
        "Data structures and algorithms are fundamental to computer science"
    };

    indexDocuments(documents);
    string query;
    cout << "Enter your search query: ";
    getline(cin, query);
    vector<int> results = search(query);
    cout << "Search Results:" << endl;
    for (int docID : results) {
        cout << "Document ID: " << docID << " Content: " << documents[docID] << endl;
    }
    Trie trie;
    for (const auto& doc : documents) 
    {
        istringstream iss(doc);
        string word;
        while (iss >> word) {
            trie.insert(word);
        }
    }
    cout << "Enter prefix for autocomplete: ";
    string prefix;
    cin >> prefix;
    vector<string> suggestions = trie.autocomplete(prefix);
    cout << "Suggestions:" << endl;
    for (const auto& suggestion : suggestions) 
    {
        cout << suggestion << endl;
    }

    return 0;
}
