template<typename T>
void LinkedList<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::insertAt(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        pushFront(value);
        return;
    }
    
    if (index == size) {
        pushBack(value);
        return;
    }
    
    Node* current = getNodeAt(index);
    Node* newNode = new Node(value);
    
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    size++;
}

template<typename T>
void LinkedList<T>::insertBefore(const T& value, const T& before) {
    int index = find(before);
    if (index == -1) {
        throw std::runtime_error("Value not found");
    }
    insertAt(index, value);
}

template<typename T>
void LinkedList<T>::insertAfter(const T& value, const T& after) {
    int index = find(after);
    if (index == -1) {
        throw std::runtime_error("Value not found");
    }
    insertAt(index + 1, value);
}

template<typename T>
T LinkedList<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* temp = head;
    T value = temp->data;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    delete temp;
    size--;
    return value;
}

template<typename T>
T LinkedList<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* temp = tail;
    T value = temp->data;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    delete temp;
    size--;
    return value;
}

template<typename T>
T LinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        return popFront();
    }
    
    if (index == size - 1) {
        return popBack();
    }
    
    Node* current = getNodeAt(index);
    T value = current->data;
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    delete current;
    size--;
    return value;
}

template<typename T>
bool LinkedList<T>::removeValue(const T& value) {
    int index = find(value);
    if (index == -1) {
        return false;
    }
    removeAt(index);
    return true;
}

template<typename T>
void LinkedList<T>::reverse() {
    if (size <= 1) return;
    
    Node* current = head;
    Node* temp = nullptr;
    
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (temp) {
        head = temp->prev;
    }
}

template<typename T>
int LinkedList<T>::find(const T& value) const {
    Node* current = head;
    int index = 0;
    
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}

template<typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(int index) const {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template<typename T>
T LinkedList<T>::getAt(int index) const {
    Node* node = getNodeAt(index);
    if (!node) {
        throw std::out_of_range("Index out of range");
    }
    return node->data;
}

template<typename T>
QString LinkedList<T>::toString() const {
    QString result;
    Node* current = head;
    
    result += "[";
    while (current) {
        result += QString::number(current->data);
        if (current->next) {
            result += ", ";
        }
        current = current->next;
    }
    result += "]";
    
    return result;
}

template<typename T>
QList<T> LinkedList<T>::toList() const {
    QList<T> list;
    Node* current = head;
    
    while (current) {
        list.append(current->data);
        current = current->next;
    }
    
    return list;
}
