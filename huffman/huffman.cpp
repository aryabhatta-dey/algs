#include <iostream>
#include <string>
#include <queue>

// A huffman tree node
struct MinHeapNode {
        char character;
        unsigned frequency;
        struct MinHeapNode *left;
        struct MinHeapNode *right;
        
        MinHeapNode(char character, unsigned frequency){
                left = nullptr;
                right = nullptr;
                this -> character = character;
                this -> frequency = frequency;
        }
};

// Comparator
struct Compare {
        bool operator() (struct MinHeapNode* left, struct MinHeapNode* right) {
                return (left -> frequency > right -> frequency);
        }
};

void PrintCodes (struct MinHeapNode* node, std::string str) {
        if (!node) return;
        if (node -> character != '\0') std::cout << node -> character << ": " << str << "\n";
        PrintCodes(node -> left, str + "0");
        PrintCodes(node -> right, str + "1");
}

void HuffmanCodes (char characters[], unsigned frequencies[], int size){
        struct MinHeapNode *left, *right, *top;
        std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, Compare> minHeap;

        for (auto i = 0; i < size; ++i) minHeap.push(new MinHeapNode(characters[i], frequencies[i]));

        while (minHeap.size() != 1) {
                left = minHeap.top();
                minHeap.pop();

                right = minHeap.top();
                minHeap.pop();

                top = new MinHeapNode('\0', left -> frequency + right -> frequency);

                top -> left = left;
                top -> right = right;

                minHeap.push(top);
        }

        PrintCodes(minHeap.top(), "");
}

int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    unsigned freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
}
