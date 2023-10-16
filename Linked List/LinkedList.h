#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;
    };

    //insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    //removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    //operators
    LinkedList<T> &operator=(const LinkedList<T> &rhs);
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    bool operator==(const LinkedList<T>& rhs) const;

    //accessors
    unsigned int NodeCount() const;
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;
    Node* Find(const T& data);
    const Node* Find(const T& data) const;
    void FindAll(vector<Node*>& ourData, const T& value) const;

    //behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    //constructors
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& list);

private:
    unsigned int nodeCount;
    Node* head;
    Node* tail;
};

//constructors
template<typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while(RemoveTail()){}
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
    Node* current = list.head;
    for(unsigned int i = 0; i < list.nodeCount; i++){
        AddTail(current->data);
        current = current->next;
    }
}

//insertion
template<typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* temp = new Node;
    if(head == nullptr){
        head = temp;
        head->data = data;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
    }
    else{
        temp->data = data;
        temp->next = head;
        temp->prev = nullptr;
        head->prev = temp;
        head = temp;
    }
    nodeCount++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data){
    Node* temp = new Node;
    if(tail == nullptr){
        tail = temp;
        tail->data = data;
        tail->next = nullptr;
        tail->prev = nullptr;
        head = tail;
    }
    else{
        temp->data = data;
        temp->next = nullptr;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    nodeCount++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for(unsigned int i = count - 1; i >= 0; i--){
        AddHead(data[i]);
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for(unsigned int i = 0; i < count; i++){
        AddTail(data[i]);
    }
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    Node* temp = new Node;
    temp->data = data;
    temp->prev = node;
    temp->next = node->next;
    node->next->prev = temp;
    node->next = temp;
    nodeCount++;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    Node* temp = new Node;
    temp->data = data;
    temp->next = node;
    temp->prev = node->prev;
    node->prev->next = temp;
    node->prev = temp;
    nodeCount++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if (index > nodeCount) {
        throw out_of_range("index out of range");
    }
    else if (index == nodeCount) {
        AddTail(data);
    }
    else if(index == 0){
        AddHead(data);
    }
    else {
        unsigned int count = 0;
        Node* current = head;
        while (count != index) {
            current = current->next;
            count++;
        }
        InsertBefore(current, data);
    }
}

//removal
template<typename T>
bool LinkedList<T>::RemoveHead() {
    if(nodeCount == 0){
        return false;
    }
    else if(nodeCount == 1){
        delete head;
        head = nullptr;
        tail = nullptr;
        nodeCount--;
        return true;
    }
    else {
        Node *temp = head;
        head->next->prev = nullptr;
        head = head->next;
        delete temp;
        nodeCount--;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
    if(nodeCount == 0){
        return false;
    }
    else if(nodeCount == 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        nodeCount--;
        return true;
    }
    else {
        Node *temp = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete temp;
        nodeCount--;
        return true;
    }
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data){
    unsigned int removed = 0;
    Node* current = head;
    while (current != nullptr){
        Node* temp = current->next;
        if (current->data == data){
            if (current == head){
                RemoveHead();
            }
            else if (current == tail){
                RemoveTail();
            }
            else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                nodeCount--;
                delete current;
            }
            removed++;
        }
        current = temp;
    }
    return removed;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
    if(index > nodeCount){
        return false;
    }
    Node* temp = GetNode(index);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    nodeCount--;
    return true;
}

template<typename T>
void LinkedList<T>::Clear(){
    nodeCount = 0;
    tail = nullptr;
    Node* temp;
    while(head != nullptr){
        temp = head->next;
        delete head;
        head = temp;
    }
}

//accessors
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const{
    return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const{
    return tail;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if(index > nodeCount ){
        throw out_of_range("index out of range");
    }
    unsigned int count = 0;
    Node* current = head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(count == index){
            return current;
        }
        count++;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const{
    if(index > nodeCount - 1){
        throw out_of_range("index out of range");
    }
    int count = 0;
    Node* current = head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(count == index){
            return current;
        }
        count++;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* current = head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const{
    Node* current = head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*> &ourData, const T &value) const {
    Node* current = head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(current->data == value){
            ourData.push_back(current);
        }
        current = current->next;
    }
}

//operators
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    Clear();
    Node* current = rhs.head;
    for(unsigned int i = 0; i < rhs.nodeCount; i++){
        AddTail(current->data);
        current = current->next;
    }
    return *this;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index){
    return GetNode(index)->data;
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const{
    return GetNode(index)->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const{
    Node* current = head;
    Node* objCurrent = rhs.head;
    for(unsigned int i = 0; i < nodeCount; i++){
        if(current->data != objCurrent->data){
            return false;
        }
        current = current->next;
        objCurrent = objCurrent->next;
    }
    return true;
}

//behaviors
template<typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while(current != nullptr){
        cout << current->data << endl;
        current = current->next;
    }
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;
    while(current != nullptr) {
        cout << current->data << endl;
        current = current->prev;
    }
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node *node) const {
    if(node == nullptr){
        return;
    }else{
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node *node) const {
    if(node == nullptr){
        return;
    }else{
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}
