#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <queue>
#include <forward_list>


using namespace std;


struct Code {
    int index;
    string symbol;
    char sym;

    Code(int index, string symbol) : index(index), symbol(symbol), sym(NULL) {}
    Code(int index, char symbol) : index(index), symbol(""), sym(symbol) {}
};

bool find(string str, vector<Code*> nodes, int& n) {
    for (int i = 0; i < nodes.size(); i++)
        if (str == nodes[i]->symbol) {
            n = nodes[i]->index;
            return true;
        }

    return false;
}

vector<Code*> lz78Encode(const string& phrase) {

    string str = "";
    vector <Code*> dictionary;
    vector <Code*> nodes;
    int n = 0;

    for (int i = 0; i <= phrase.size(); i++) {
        str += phrase[i];
        if (!find(str, dictionary, n)) {
            dictionary.push_back(new Code(dictionary.size() + 1, str));
            nodes.push_back(new Code(n, phrase[i]));
            n = 0;
            str = "";
        }
    }

    for (Code* node : nodes) {
        cout << "<" << node->index << ", " << node->sym << "> ";
    }
    return nodes;

}
struct Token {
    int offset;
    int len;
    char symbol;
};

vector<Token> lz77Encode(const string& phrase) {
    vector<Token> tokens;
    int windowSize = 5;
    int lookAheadBufferSize = 5;

    int currentIndex = 0;
    while (currentIndex < phrase.length()) {
        int matchLength = 0;
        int matchIndex = 0;
        char nextChar = phrase[currentIndex + matchLength];

        for (int i = max(0, currentIndex - windowSize); i < currentIndex; ++i) {
            int length = 0;
            while (phrase[i + length] == phrase[currentIndex + length] && length < lookAheadBufferSize) {
                length++;
            }
            if (length > matchLength) {
                matchIndex = i;
                matchLength = length;
                nextChar = phrase[currentIndex + matchLength];
            }
        }

        Token token;
        token.offset = currentIndex - matchIndex;
        token.len = matchLength;
        token.symbol = nextChar;

        tokens.push_back(token);
        currentIndex += (matchLength + 1);
    }
    return tokens;
}

string lz77Decode(vector<Token> tokens) {
    string decompressedString;
    for (Token token : tokens) {
        if (token.len == 0) {
            decompressedString += token.symbol;
        } else {
            int startIndex = decompressedString.length() - token.offset;
            for (int i = 0; i < token.len; ++i) {
                decompressedString += decompressedString[startIndex + i];
            }
            decompressedString += token.symbol;
        }
    }
    return decompressedString;
}
struct TreeNode
{
    char ch;
    int freq;
    TreeNode *left, *right;
};

TreeNode* getTreeNode(char ch, int freq, TreeNode* left, TreeNode* right)
{
    TreeNode* node = new TreeNode();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp
{
    bool operator()(TreeNode* l, TreeNode* r)
    {
        return l->freq > r->freq;
    }
};

void Haff_encode(TreeNode* root, string str,unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    Haff_encode(root->left, str + "0", huffmanCode);
    Haff_encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and Haff_decode the encoded string
void Haff_decode(TreeNode* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] =='0')
        Haff_decode(root->left, index, str);
    else
        Haff_decode(root->right, index, str);
}

// Builds Huffman Tree and Haff_decode given input text
void buildHuffmanTree(string text)
{

    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<TreeNode*, vector<TreeNode*>, comp > pq;


    for (auto pair: freq) {
        pq.push(getTreeNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {
        TreeNode *left = pq.top(); pq.pop();
        TreeNode *right = pq.top();	pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getTreeNode('\0', sum, left, right));
    }

    TreeNode* root = pq.top();

    unordered_map<char, string> huffmanCode;
    Haff_encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n" << '\n';
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string was :\n" << text << '\n';

    string str = "";
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    cout << "\nEncoded string is :\n" << str << '\n';

    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 2) {
        Haff_decode(root, index, str);
    }
}



struct Node {
    char symbol;
    float probability;
    string code;
};

vector<Node> createNodes(string input) {
    map<char, int> charCount;
    for (char c : input) {
        charCount[c]++;
    }

    vector<Node> nodes;
    for (auto pair : charCount) {
        float probability = static_cast<float>(pair.second) / input.size();
        nodes.push_back({pair.first, probability, ""});
    }

    std::sort(nodes.begin(), nodes.end(), [](Node a, Node b) {
        return a.probability > b.probability;
    });

    return nodes;
}

void shannonFano(vector<Node>& nodes, int start, int end) {
    if (start == end) {
        return;
    }

    float totalProb = 0;
    for (int i = start; i <= end; i++) {
        totalProb += nodes[i].probability;
    }

    float currProb = 0;
    int splitIndex = start;
    float currDiff = abs(2 * currProb - totalProb);
    for (int i = start; i <= end; i++) {
        float diff = abs(2 * (currProb + nodes[i].probability) - totalProb);
        if (diff < currDiff) {
            currDiff = diff;
            splitIndex = i;
        }
        currProb += nodes[i].probability;
    }

    for (int i = start; i <= end; i++) {
        if (i <= splitIndex) {
            nodes[i].code += "0";
        } else {
            nodes[i].code += "1";
        }
    }

    shannonFano(nodes, start, splitIndex);
    shannonFano(nodes, splitIndex + 1, end);
}
string encodeShannonFano(string input, vector<Node> nodes) {
    map<char, string> codeMap;
    for (Node node : nodes) {
        codeMap[node.symbol] = node.code;
    }

    string encodedString;
    for (char c : input) {
        encodedString += codeMap[c];
    }

    return encodedString;
}


string decodeShannonFano(string input, vector<Node> nodes) {
    map<string, char> codeMap;
    for (Node node : nodes) {
        cout << node.code << " " << node.symbol << "\n";
        codeMap[node.code] = node.symbol;
    }

    string result = "";
    string currentString = "";
    for (char ch : input) {
        currentString += ch;
        if (codeMap.find(currentString) != codeMap.end()) {
            result += codeMap[currentString];
            currentString = "";
        }
    }
    return result;
}
string decompress78(vector<Code*> encodedData) {
    vector<string> dictionary;
    dictionary.push_back("");
    string decodedString = "";

    for (Code* token: encodedData) {
        string sequence = dictionary[token->index] + token->sym;
        decodedString += sequence;
        dictionary.push_back(sequence);
    }
    return decodedString;
}
int main() {
    cout << "11111111111111111111111111111111111111"<< endl;
    vector<Node> nodes = createNodes("Hush, mice, the cat's on the roof,   And the kittens are even higher. The cat went to get milk,   And the kittens are tumbling.");
    shannonFano(nodes, 0, nodes.size());
    string encodedString = encodeShannonFano("Hush, mice, the cat's on the roof,   And the kittens are even higher. The cat went to get milk,   And the kittens are tumbling.", nodes);
    cout << encodedString << endl;
    cout << decodeShannonFano(encodedString, nodes)<< endl;

    string text = "Hush, mice, the cat's on the roof,   And the kittens are even higher. The cat went to get milk,   And the kittens are tumbling.";

    buildHuffmanTree(text);
    cout << endl;
    cout << "22222222222222222222222222222222222222"<< endl;
    string inputPhrase = "kot_ot_okon_otosel";
    vector<Token> encoded = lz77Encode(inputPhrase);
    string decodedString = lz77Decode(encoded);
    cout << "Original String: " << inputPhrase << endl;
    cout << "Encoded: ";
    for (const Token& token : encoded) {
        cout << "<" << token.offset << ", " << token.len << ", " << (char)token.symbol << "> ";
    }
    cout << endl;
    cout << "Decoded: " << decodedString << endl;

    inputPhrase = "110101011001100001001";
    encoded = lz77Encode(inputPhrase);
    decodedString = lz77Decode(encoded);
    cout << "Original String: " << inputPhrase << endl;
    cout << "Encoded: ";
    for (const Token& token : encoded) {
        cout << "<" << token.offset << ", " << token.len << ", " << (char)token.symbol << "> ";
    }
    cout << endl;
    cout << "Decoded: " << decodedString << endl;

    cout << "3333333333333333333333333333333333333333333333"<< endl;
    vector<Code*> en78 = lz78Encode("doldeldoldildeldil");
    cout << decompress78(en78);
    return 0;
}
