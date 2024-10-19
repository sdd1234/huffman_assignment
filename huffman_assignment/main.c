#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define MAX_ELEMENT 200
typedef struct TreeNode { //허프만구조체
    char ch;                          
    int weight;   
    struct TreeNode* left;     
    struct TreeNode* right;   
} TreeNode;

typedef struct { //힙에 저장되는 값들
    TreeNode* ptree;           
    char ch;                   
    int key;                    
} element;

typedef struct { //힙 구조체
    element heap[MAX_ELEMENT]; 
    int heap_size;              
} HeapType;

HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}
void insert_min_heap(HeapType* h, element item) { //가장작은 빈도수가 가장높은 우선순위를 가지기에 min_heap사용해야함
    int i;
    i = ++(h->heap_size);
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}
element delete_min_heap(HeapType* h) { //최소 힙에서 요소 삭제
    int parent, child;
    element item, temp;

    item = h->heap[1];                  
    temp = h->heap[(h->heap_size)--];  
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key < h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}


void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);  
    destroy_tree(root->right);
    free(root);
}

// 리프노드확인
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 베열 출력
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 트리출력
void printCodes(TreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(arr, top);
    }
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];                           
    int top = 0;
    bool first_print = true;
    heap = create();                           
    init(heap);                                
    for (i = 0; i < size; i++) {
        node = make_tree(NULL, NULL);         
        e.ch = node->ch = characters[i];        
        e.key = node->weight = frequencies[i]; 
        e.ptree = node;
        insert_min_heap(heap, e);                  
        print_heap(heap);
    }
    for (i = 1; i < size; i++) {
        e1 = delete_min_heap(heap);            
        e2 = delete_min_heap(heap);            
        x = make_tree(e1.ptree, e2.ptree);      
        e.key = x->weight = e1.key + e2.key;    
        e.ptree = x;   
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);               
        if (first_print || heap->heap_size != 6) { 
            print_heap(heap);
            first_print = false;                
        }
    }
    e = delete_min_heap(heap);                 
    printCodes(e.ptree, codes, top);           
    destroy_tree(e.ptree);                     
    free(heap);                                 
}

int main(void) {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}