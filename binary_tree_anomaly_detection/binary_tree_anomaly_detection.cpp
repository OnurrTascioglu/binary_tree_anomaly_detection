#include <iostream>

bool result = false;

struct stack {
    int64_t data;
    stack* next;
};
stack* top = new stack;
int stack_size = 0;

class Node {
public:
    Node* left;
    Node* right;

    bool detect;

    Node()
    {
        left = NULL;
        right = NULL;
        detect = false;
    }
};

void push(int x)
{
    stack* member = new stack;
    member->data = x;
    member->next = top;
    top = member;
    stack_size++;
}
int getTop() {
    int64_t temp = 0;
    if (stack_size != 0) {
        temp = top->data;
        top = top->next;
        stack_size--;
    }
    return temp;
}

void pushElementsOfTree(Node* tree) {
    push(int64_t(tree));  //hexadecimal adresi int olarak kaydeder
    if (tree->left != NULL)
        pushElementsOfTree(tree->left);
    if (tree->right != NULL)
        pushElementsOfTree(tree->right);
}

bool detectAnomaly(Node* tree) {
    pushElementsOfTree(tree);          //agacin elemanlarini yigina iter
    const int max_size = stack_size;   //yiginin ulasabilecegi max boyut
    int* elements_array = new int[max_size];   //yigindaki elemanlarin karsilastirilacagi dizi
    int  elements_array_size = 0;
    int64_t temp = 0;

    for (int i = 0; i < max_size; i++) {
        temp = getTop();               //yiginin en ustteki elemani
        for (int j = 0; j < elements_array_size; j++) {   // yiginin en ustteki elemani ile diger elemanlari karsilastirir
            if (temp == elements_array[j]) {
                result = true;
                return result;
            }
        }
        elements_array[i] = temp;
        elements_array_size++;
    }

    return result;
}


int main()
{

    Node* root = new Node();

    root->left = new Node();
    root->left->right = new Node();
    root->left->left = new Node();
    root->left->left->left = new Node();
    root->left->left->right = new Node();
    root->left->left->right->right = new Node();
    root->left->left->left->right = new Node();
    root->right = new Node();
    root->right->left = new Node();
    root->right->left->left = new Node();
    root->right->right = new Node();
    root->right->right->left = new Node();

    root->right->left->left->left = root->left->left->right->right; // anomali durumu

    /*
                X
            /      \
           X         X
          / \       / \
         X   X     X   X
        /  \      /   /
       X    X    X   X
        \    \  /                 
         X    X
     */
         
    if (detectAnomaly(root))
        std::cout << std::endl << "Anomali Tespit Edildi" << std::endl;
    else {
        std::cout << "Anomali Yok" << std::endl;
    }

    return 0;
}
