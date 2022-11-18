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
    int data;
    Node* left;
    Node* right;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
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

    Node* root = new Node(1);

    root->left = new Node(2);
    root->left->right = new Node(3);
    root->left->left = new Node(4);
    root->left->left->left = new Node(5);
    root->left->left->right = new Node(6);
    root->left->left->right->right = new Node(7);
    root->left->left->left->right = new Node(8);
    root->right = new Node(9);
    root->right->left = new Node(10);
    root->right->left->left = new Node(11);
    root->right->right = new Node(12);
    root->right->right->left = new Node(13);

    root->right->left->left->left = root->left->left->right->right; // anomali durumu

    /*
                1
            /      \
           2         9
          / \       / \
         4   3    10   12
        /  \      /   /
       5    6   11   13
        \    \  /                 
         8    7
     */
         
    if (detectAnomaly(root))
        std::cout << std::endl << "Anomali Tespit Edildi" << std::endl;
    else {
        std::cout << "Anomali Yok" << std::endl;
    }

    return 0;
}
