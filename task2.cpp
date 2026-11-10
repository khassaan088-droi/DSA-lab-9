#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string word;
    int frequency;
    Node* left;
    Node* right;
    Node(string w) {
        word = w;
        frequency = 1;
        left = NULL;
        right = NULL;
    }
};
string cleanWord(string str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];      
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            
            if (c >= 'A' && c <= 'Z') {
                c = c + 32; 
            }
            result += c;
        }
    }
    return result;
}
//part 2
Node* insert(Node* root, string word) {
    if (root == NULL) {
        return new Node(word);
    }
    if (word == root->word) {
        root->frequency++;
    } else if (word < root->word) {
        root->left = insert(root->left, word);
    } else {
        root->right = insert(root->right, word);
    }
    return root;
}

// Part 3A
void displayAlphabetical(Node* root) {
    if (root == NULL) return;
    displayAlphabetical(root->left);
    cout << "  " << root->word << "===>" << root->frequency << " time" << endl;
    displayAlphabetical(root->right);
}
void getMaxFrequency(Node* root, int& maxFreq) {
    if (root == NULL) return;
    getMaxFrequency(root->left, maxFreq);
    if (root->frequency > maxFreq) {
        maxFreq = root->frequency;
    }
    getMaxFrequency(root->right, maxFreq);
}
// Helper
void printByFrequencyHelper(Node* root, int targetFreq) {
    if (root == NULL) return;
    printByFrequencyHelper(root->left, targetFreq);
    if (root->frequency == targetFreq) {
        cout << "  " << root->word << "===>" << root->frequency << " times" << endl;
    }
    printByFrequencyHelper(root->right, targetFreq);
}

//Part 3C
void findMostFrequentWord(Node* root) {
    int maxFreq = 0;
    getMaxFrequency(root, maxFreq);

    cout << "\n====Most Frequent Words====" << endl;
    cout << "Highest Frequency: " << maxFreq << " times" << endl;
    cout << "Word(s):" << endl;
    printByFrequencyHelper(root, maxFreq);
}


void getSummary(Node* root, int& uniqueCount, int& totalWordCount) {
    if (root == NULL) return;
    getSummary(root->left, uniqueCount, totalWordCount);
    uniqueCount++;
    totalWordCount += root->frequency;
    getSummary(root->right, uniqueCount, totalWordCount);
}
int main() {
    string words[] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", "The", "fox", "is", "quick", "and", "smart"};
    Node* root = NULL;
    for (int i = 0; i < 15; i++) {
        string cleaned = cleanWord(words[i]);
        if (cleaned != "") {
            root = insert(root, cleaned);
        }
    }
    cout << "=======Inorder Alphabets ======" << endl;
    displayAlphabetical(root);
    findMostFrequentWord(root);
    int uniqueWords = 0;
    int totalWordCount = 0;
    getSummary(root, uniqueWords, totalWordCount);

    cout << "\n=== 4. Summary Information ===" << endl;
    cout << "  Total Unique Words: " << uniqueWords << endl;
    cout << "  Total Word Count:   " << totalWordCount << endl;

    return 0;
}