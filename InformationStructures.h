#include <iostream>
#include "utilities.h"
using namespace std;

/*
Template MinHeap implementation.
*/
template <class T>
class MinHeap{
private:
    T* harr;
    int capacity;
    int heap_size;
public:
    void MinHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && harr[l]<harr[i]){
            smallest = l;
        }

        if (r < heap_size && harr[r]<harr[smallest]){
            smallest = r;
        }

        if(smallest!=i){
            swap_generic<T>(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }

    MinHeap(T arr[], int size){
        heap_size = size;
        capacity=heap_size;
        harr = arr;
        int i = (heap_size-1)/2; // excluding leaf nodes
        while(i>=0){
            MinHeapify(i);
            i--;
        }
    }

    MinHeap(vector<T> vec){
        heap_size = vec.size();
        capacity=heap_size;
        harr = new T[heap_size];
        for(int i=0; i<heap_size; i++)
            harr[i]=vec[i];

        int i = (heap_size-1)/2; // excluding leaf nodes
        while(i>=0){
            MinHeapify(i);
            i--;
        }
    }

    T ExtractMin() {
        if(heap_size==0) return INT_MIN;
        T min = harr[0];

        if (heap_size>1){
            harr[0] = harr[heap_size-1];
            heap_size--;
            MinHeapify(0);
        }
        return min;
    }

    void Insert(T data){
        if(heap_size<capacity){
            heap_size++;
            harr[heap_size-1] = data;

            // Keep swapping until we reach the root
            int curr = heap_size-1;
            // As long as you aren't in the root node, and while the parent of the last element is greater than it
            while (curr >= 0 && harr[parent(curr)]->data > harr[curr]->data) {
                // Swap and move up
                swap_generic<T>(&harr[parent(curr)], &harr[curr]);
                curr = parent(curr);
            }
        }
        else{
            cout << "MinHeap is out of capacity." << endl;
        }
    }

    void print(){
        cout << "MinHeap Array: ";
        for(int i=0; i<heap_size; ++i){
            cout << harr[i] << ", ";
        }
        cout << endl;
    }

    T GetMin() {  return harr[0]; }
    bool IsEmpty(){ return heap_size==0; }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right (int i) { return (2 * i + 2); }

};

/*
Template MaxHeap implementation.
*/
template <class T>
class MaxHeap{
private:
    T* harr;
    int capacity;
    int heap_size;
public:
    MaxHeap(T arr[], int size){
        heap_size = size;
        harr = arr;
        int i = (heap_size-1)/2;
        while(i>=0){
            MaxHeapify(i);
            i--;
        }
    }

    MaxHeap(vector<T> vec){
        heap_size = vec.size();
        capacity=heap_size;
        harr = new T[heap_size];
        for(int i=0; i<heap_size; i++)
            harr[i]=vec[i];

        int i = (heap_size-1)/2;
        while(i>=0){
            MaxHeapify(i);
            i--;
        }
    }

    T ExtractMax() {
        if(heap_size==0) return INT_MIN;
        int max = harr[0];

        if (heap_size>1){
            harr[0] = harr[heap_size-1];
            heap_size--;
            MaxHeapify(0);
        }
        return max;
    }

    void MaxHeapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap_size && harr[l]>harr[i]){
            largest = l;
        }

        if (r < heap_size && harr[r]>harr[largest]){
            largest = r;
        }

        if(largest!=i){
            swap_ptr(&harr[i], &harr[largest]);
            MaxHeapify(largest);
        }
    }

    void Insert(T data){
        if(heap_size<capacity){
            heap_size++;
            harr[heap_size-1] = data;

            // Keep swapping until we reach the root
            int curr = heap_size-1;
            // As long as you aren't in the root node, and while the parent of the last element is less than it
            while (curr >= 0 && harr[parent(curr)]->data < harr[curr]->data) {
                // Swap and move up
                swap_generic<T>(&harr[parent(curr)], &harr[curr]);
                curr = parent(curr);
            }
        }
        else{
            cout << "MaxHeap is out of capacity." << endl;
        }
    }

    void print(){
        cout << "MinHeap Array: ";
        for(int i=0; i<heap_size; ++i){
            cout << harr[i] << ", ";
        }
        cout << endl;
    }

    T GetMax() { return harr[0]; }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right (int i) { return (2 * i + 2); }
};

/*
Struct defining a point
*/
struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
};

/*
Struct defining a line of ax + by + c = 0 form
*/
struct line {
    int a, b, c;
    line(int a, int b, int c) : a(a), b(b), c(c) {}
};

/*
Node used for all types of LinkedLists (Singly, Doubly and Circular).
*/
template <typename T> class Node {
private:
    template <typename U> friend class LinkedList;
    template <typename U> friend class DLinkedList;
    template <typename U> friend class CLinkedList;
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node() : next{nullptr}, prev{nullptr} {}
    Node(T item) : next{nullptr}, prev{nullptr}, data{item} {}
    bool operator <(const Node<T>& ohterNode){
        cout << "less than invoked" << endl;
        return (data<ohterNode.data);
    }
    bool operator >(const Node<T>& ohterNode){
        cout << "greater than invoked" << endl;
        return (data>ohterNode.data);
    }
};

/*
Template implementation of Single LinkedList.
*/
template <typename T> class LinkedList {
private:
    int _length;
public:
    Node<T>* head;

    LinkedList() : _length(0), head(nullptr) {
    }

    void push_back(T item) { // O(n)
        Node<T>* node = new Node<T>[1];
        node->data = item;
        if (head == nullptr) {
            head=node;
            _length++;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp=temp->next;
        }
        temp->next=node;
        _length++;
    }

    void push_front(T item){ // O(1)
        Node<T>* node = new Node<T>[1];
        node->data=item;
        if(head==nullptr){
            head=node;
            _length++;
            return;
        }
        node->next=head;
        head=node;
        _length++;
    }

    void push_at(int index, T item){ // O(n)
        if(index>length() || index<0){
            return;
        }
        Node<T>* node = new Node<T>[1];
        node->data=item;

        int count=0;
        Node<T>* temp = head;
        while(temp!=nullptr && count<index){

            if(count==index-1){
                if(temp->next != nullptr){
                    node->next=temp->next;
                }
                temp->next=node;
                _length++;
                break;
            }

            count++;
            temp=temp->next;
        }
    }

    void remove_back(){ // O(n)
        if(head==nullptr){
            return;
        }
        if(head->next==nullptr){
            Node<T>* node_to_delete = head;
            head=nullptr;
            delete node_to_delete;
            _length--;
            return;
        }

        Node<T>* temp = head;
        while(temp!=nullptr){
            if(temp->next->next==nullptr){
                Node<T>* node_to_delete = temp->next;
                temp->next=nullptr;
                delete node_to_delete;
                _length--;
                break;
            }
            temp=temp->next;
        }
    }

    void remove_at(int index){ // O(n)
        if(head==nullptr){
            return;
        }
        if(index>=length() || index<0){
            return;
        }
        if(index==0){
            remove_front();
            return;
        }

        int count=0;
        Node<T>* temp = head;
        while(temp != nullptr){
            if(count==index-1){
                Node<T>* node_to_delete = temp->next;
                temp->next=temp->next->next;
                delete node_to_delete;
                _length--;
                break;
            }
            count++;
            temp=temp->next;
        }
    }

    void remove_front(){ // O(1)
        if(head==nullptr)
            return;
        Node<T>* node_to_delete = head;
        head=head->next;
        delete node_to_delete;
        _length--;
    }

    T at(int index){ // O(n)
        T res;
        if(head==nullptr)
            return res;
        if(index>=length() && index<0)
            return res;
        if(index==0){
            return head->data;
        }

        int count=0;
        Node<T>* temp = head;
        while(temp!=nullptr){
            if(count==index){
                res=temp->data;
                break;
            }
            temp=temp->next;
            count++;
        }
        return res;

    }

    int length(){ // O(1)
        return _length;
    }

    void display(string sep=","){ // O(n)
        if(head==nullptr){
            return;
        }
        cout << "------- linked list items -------" << endl;
        Node<T>* temp = head;
        while(temp!=nullptr){
            cout << temp->data << sep << " ";
            temp=temp->next;
        }
        cout << endl << "---------------------------------" << endl;
    }

};

/*
Template implementation of Doubly LinkedList.
*/
template <typename T> class DLinkedList {
private:
    int _length;
public:
    Node<T>* head;

    DLinkedList() : head(nullptr), _length(0) {
    }

    void push_back(T item) { // O(n)
        Node<T>* node = new Node<T>(item);
        if (head == nullptr) {
            head=node;
            _length++;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp=temp->next;
        }
        temp->next=node;
        node->prev=temp;
        _length++;
    }

    void push_front(T item){ // O(1)
        Node<T>* node = new Node<T>(item);
        if(head==nullptr){
            head=node;
            _length++;
            return;
        }
        head->prev=node;
        node->next=head;
        head=node;
        _length++;
    }

    void push_at(int index, T item){ // O(n)
        if(index>length() || index<0){
            return;
        }

        Node<T>* node = new Node<T>(item);
        int count=0;
        Node<T>* temp = head;
        while(temp!=nullptr && count<index){

            if(count==index-1){
                if(temp->next != nullptr){
                    node->next=temp->next;
                    temp->next->prev=node;
                }
                temp->next=node;
                node->prev=temp;
                _length++;
                break;
            }
            count++;
            temp=temp->next;
        }
    }

    void remove_back(){ // O(n)
        if(head==nullptr){
            return;
        }
        if(head->next==nullptr){
            Node<T>* node_to_delete = head;
            head=nullptr;
            delete node_to_delete;
            _length--;
            return;
        }

        Node<T>* temp = head;
        while(temp!=nullptr){
            if(temp->next->next==nullptr){
                Node<T>* node_to_delete = temp->next;
                temp->next=nullptr;
                delete node_to_delete;
                _length--;
                break;
            }
            temp=temp->next;
        }
    }

    void remove_at(int index){ // O(n)
        if(head==nullptr){
            return;
        }
        if(index>=length() || index<0){
            return;
        }
        if(index==0){
            remove_front();
            return;
        }

        int count=0;
        Node<T>* temp = head;
        while(temp != nullptr){
            if(count==index-1){
                Node<T>* node_to_delete = temp->next;
                if(node_to_delete->next!=nullptr){
                    node_to_delete->next->prev=temp;
                }
                temp->next=temp->next->next;
                delete node_to_delete;
                _length--;
                break;
            }
            count++;
            temp=temp->next;
        }
    }

    void remove_front(){ // O(1)
        if(head==nullptr)
            return;

        Node<T>* node_to_delete = head;
        head=head->next;
        head->prev=nullptr;
        delete node_to_delete;
        _length--;
    }

    T at(int index){ // O(n)
        T res;
        if(head==nullptr)
            return res;
        if(index>=length() && index<0)
            return res;
        if(index==0){
            return head->data;
        }

        int count=0;
        Node<T>* temp = head;
        while(temp!=nullptr){
            if(count==index){
                res=temp->data;
                break;
            }
            temp=temp->next;
            count++;
        }
        return res;
    }

    int length(){ // O(1)
        return _length;
    }

    void display(string sep=","){ // O(n)
        if(head==nullptr){
            return;
        }
        cout << "------- linked list items -------" << endl;
        Node<T>* temp = head;
        while(temp!=nullptr){
            cout << temp->data << sep << " ";
            temp=temp->next;
        }
        cout << endl << "---------------------------------" << endl;
    }

};

/*
Template implementation of Circular Doubly LinkedList.
*/
template <typename T> class CLinkedList {
private:
    int _length;
public:
    Node<T>* head;

    CLinkedList() : _length(0), head(nullptr) {
    }

    void push_back(T item) { // O(1)
        Node<T>* node = new Node<T>(item);
        // node->data = item;
        if (head == nullptr) {
            head=node;
            head->next=head;
            head->prev=head;
            _length++;
            return;
        }

        // Inserting one before the head
        Node<T>* tail = head->prev;
        tail->next=node;
        node->prev=tail;
        node->next=head;
        head->prev=node;

        _length++;
    }

    void push_front(T item){ // O(1)
        Node<T>* node = new Node<T>(item);
        // node->data=item;
        if(head==nullptr){
            head=node;
            head->next=head;
            head->prev=head;
            _length++;
            return;
        }
        // Inserting one before the head
        Node<T>* tail = head->prev;
        Node<T>* old_head = head;
        head=node;

        tail->next=node;
        head->prev=tail;
        head->next=old_head;
        old_head->prev=node;

        _length++;
    }

    void push_at(int index, T item){ // O(n)
        if(index>length() || index<0){
            return;
        }

        if(index==length()){
            push_back(item);
            return;
        }

        if(index==0){
            push_front(item);
            return;
        }

        Node<T>* node = new Node<T>(item);
        // node->data=item;

        int count=0;
        Node<T>* temp = head;
        Node<T>* tail = head->prev;
        while(temp!=tail && count<index){

            if(count==index-1){
                Node<T>* before_node = temp;
                Node<T>* after_node = temp->next;

                before_node->next=node;
                node->prev=before_node;
                node->next=after_node;
                after_node->prev=node;

                _length++;
                break;
            }

            count++;
            temp=temp->next;
        }
    }

    void remove_back(){ // O(1)
        if(head==nullptr){
            return;
        }
        if(head->next==head){ // means only 1 node
            Node<T>* node_to_delete = head;
            head=nullptr;
            delete node_to_delete;
            _length--;
            return;
        }

        Node<T>* new_tail = head->prev->prev;
        Node<T>* node_to_delete = head->prev;
        new_tail->next=head;
        head->prev=new_tail;
        delete node_to_delete;
    }

    void remove_front(){ // O(1)
        if(head==nullptr)
            return;

        if(head->next==head){ // means only 1 node
            Node<T>* node_to_delete = head;
            head=nullptr;
            delete node_to_delete;
            _length--;
            return;
        }

        Node<T>* node_to_delete = head;
        head->prev->next=head->next;
        head->next->prev=head->prev;
        head=head->next;
        delete node_to_delete;
        _length--;
    }

    void remove_at(int index){ // O(n)
        if(head==nullptr){
            return;
        }
        if(index>=length() || index<0){
            return;
        }
        if(index==length()-1){
            remove_back();
            return;
        }
        if(index==0){
            remove_front();
            return;
        }

        int count=0;
        Node<T>* temp = head;
        Node<T>* tail = head->prev;
        while(temp != tail){
            if(count==index-1){
                Node<T>* node_to_delete = temp->next;
                node_to_delete->prev->next=node_to_delete->next;
                node_to_delete->next->prev=node_to_delete->prev;
                delete node_to_delete;
                _length--;
                break;
            }
            count++;
            temp=temp->next;
        }
    }

    T at(int index){ // O(n)
        T res;
        if(head==nullptr)
            return res;
        if(index>=length() && index<0)
            return res;
        if(index==0){
            return head->data;
        }
        if(index==length()-1)
            return head->prev->data;

        int count=0;
        Node<T>* temp = head;
        Node<T>* tail = head->prev;
        while(temp!=tail){
            if(count==index){
                res=temp->data;
                break;
            }
            temp=temp->next;
            count++;
        }
        return res;
    }

    int length(){ // O(1)
        return _length;
    }

    void display(string sep=","){ // O(n)
        if(head==nullptr){
            return;
        }
        cout << "------- linked list items -------" << endl;
        Node<T>* temp = head;
        Node<T>* tail = head->prev;
        while(temp!=tail){
            cout << temp->data << sep << " ";
            temp=temp->next;
        }
        cout << temp->data << sep << " ";
        cout << endl << "---------------------------------" << endl;
    }

};

/*
Bubble sort used to sort LinkedList.
*/
template <typename T>
void SortLinkedList(LinkedList<T>& list){

    if (list.head==nullptr)
        return;

    Node<T>* head = list.head;
    Node<T>* ptr1;
    Node<T>* lptr = nullptr;
    int swapped, i;

    do
    {
        swapped = 0;
        ptr1 = list.head;

        while (ptr1->next != lptr){
            if (ptr1->data > ptr1->next->data){
                swap_generic(&ptr1->data, &ptr1->next->data);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/*
Utility function to print LinkedList.
*/
template <typename T>
void PrintLL(Node<T>* head, bool detailed=false){
    Node<T>* curr=head;
    cout << "LinkedList: ";
    while(curr!=nullptr){
        if(detailed)
            cout << "[" << curr << "|" << curr->data << "|" << curr->next << "]" << " -> ";
        else
            cout << "[" << curr->data << "]" << " -> ";
        curr=curr->next;
    }
    cout << endl;
}

/*
Utility function to print LinkedList.
*/
template <typename T>
void PrintDLL(Node<T>* head, bool detailed=false){
    Node<T>* curr=head;
    cout << "LinkedList: ";
    while(curr!=nullptr){
        if(detailed)
            cout << "[" << curr->prev << "|" << curr << "|" << curr->data << "|" << curr->next << "]" << " -> ";
        else
            cout << "[" << curr->data << "]" << " -> ";
        curr=curr->next;
    }
    cout << endl;
}

/*
Utility function to print Circular LinkedList.
*/
template <typename T>
void PrintCLL(Node<T>* head, bool detailed=false){
    Node<T>* curr=head;
    cout << "LinkedList: ";

    if(head==nullptr) return;

    if(detailed)
        cout << "[" << curr << "|" << curr->data << "|" << curr->next << "]" << " -> ";
    else
        cout << "[" << curr->data << "]" << " -> ";
    curr=curr->next;

    while(curr!=head){
        if(detailed)
            cout << "[" << curr << "|" << curr->data << "|" << curr->next << "]" << " -> ";
        else
            cout << "[" << curr->data << "]" << " -> ";
        curr=curr->next;
    }
    cout << endl;
}

/*
MinHeap implementation for pointers to the LinkedList nodes for integers only.
*/
class MinHeapPtrNode{
private:
    Node<int>** harr;
    int capacity;
    int heap_size;
public:
    void MinHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && harr[l]->data<harr[i]->data){
            smallest = l;
        }

        if (r < heap_size && harr[r]->data<harr[smallest]->data){
            smallest = r;
        }

        if(smallest!=i){
            swap_generic<Node<int>*>(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }
    MinHeapPtrNode(Node<int>* arr[], int size){
        heap_size = size;
        capacity=heap_size;
        harr = arr;
        int i = (heap_size-1)/2;
        while(i>=0){
            MinHeapify(i);
            i--;
        }
    }
    MinHeapPtrNode(vector<Node<int>*> vec){
        heap_size = vec.size();
        capacity=heap_size;
        harr = new Node<int>*[heap_size];
        for(int i=0; i<heap_size; i++)
            harr[i]=vec[i];

        int i = (heap_size-1)/2;
        while(i>=0){
            MinHeapify(i);
            i--;
        }
    }
    Node<int>* ExtractMin() {
        if(heap_size==0) return nullptr;
        Node<int>* min = harr[0];

        if (heap_size>=1){
            harr[0] = harr[heap_size-1];
            heap_size--;
            MinHeapify(0);
        }
        return min;
    }
    Node<int>* GetMin() { return harr[0]; }
    void Insert(Node<int>* data){
        if(heap_size<capacity){
            heap_size++;
            harr[heap_size-1] = data;

            // Keep swapping until we reach the root
            int curr = heap_size-1;
            // As long as you aren't in the root node, and while the parent of the last element is greater than it
            while (curr >= 0 && harr[parent(curr)]->data > harr[curr]->data) {
                // Swap and move up
                swap_generic<Node<int>*>(&harr[parent(curr)], &harr[curr]);
                curr = parent(curr);
            }
        }
        else{
            cout << "MinHeap is out of capacity." << endl;
        }
    }
    bool IsEmpty(){
        return heap_size==0;
    }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right (int i) { return (2 * i + 2); }
};

/*
Node to represent tree data structure.
*/
template <typename T>
class TreeNode{
    public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode() : left(nullptr), right(nullptr) {} // default constructor
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {} // 1-arg constructor
    TreeNode(T d, TreeNode<T>* l, TreeNode<T>* r) : data(d), left(l), right(r) {} // 3-arg constructor
};

/*
Data structure to edge data. u->v is the edge with weight w.
*/
class Edge{
public:
    int u;
    int v;
    int w;
    friend bool operator<(const Edge& e1, const Edge& e2){
        return e1.w<e2.w;
    }
    friend bool operator>(const Edge& e1, const Edge& e2){
        return e1.w>e2.w;
    }
};

/*
Union find data structure. Also knows and Disjoint Set.
*/
class DisjointSet{

private:
    vector<int> parent;
    vector<int> size;
    int count=0;

public:
    DisjointSet(int n){
        parent.resize(n);
        size.resize(n);
        count=n;
    }

    void MakeSet(int x){
        parent[x]=x;
        size[x]=1;
    }

    int Find(int x){
        int root=x;

        // this goes through to find the ultimate parent
        while(root!=parent[root]){
            root=parent[root];
        }

        // this updates the ultimate parent of intermediate node
        // which were merged but not updated so far
        while(x!=root){
            int p = parent[x];
            parent[x]=root;
            x=p;
        }
        return root;
    }

    void Union(int x, int y){
        int i = Find(x);
        int j = Find(y);

        if(i==j) return;

        if(size[i]<size[j]){
            parent[i]=j;
            size[j]+=size[i];
        }
        else{
            parent[j]=i;
            size[i]+=size[j];
        }
        count--;
    }

    // return count of disjoint set
    int Count(){
        return count;
    }
};
