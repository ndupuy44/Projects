#include <iostream>
#include "huffman_tree.h"

int main() {
    huffman_tree x("mississippi");
    cout << x.encode("mississippi");
    return 0;
}
