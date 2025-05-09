#include "Graf.h"

using namespace std;

Node::Node(int x, int y, int cost, Node* parent)
    : x(x), y(y), cost(cost), parent(parent) {}

Graf::Graf(int rows, int cols) : rows(rows), cols(cols) {
    labirent = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        labirent[i] = new int[cols];
    }
}

Graf::~Graf() {
    for (int i = 0; i < rows; ++i) {
        delete[] labirent[i];
    }
    delete[] labirent;
}

void Graf::labirentOku(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int i = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string value;
            int j = 0;
            while (getline(ss, value, ',')) {
                labirent[i][j] = stoi(value);
                j++;
            }
            i++;
        }
        file.close();
    } else {
        cerr << "Dosya açılamadı!" << endl;
    }
}

void Graf::setStartEndNode() {
    bool startFound = false, endFound = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (labirent[i][j] == 2) {
                startNode = new Node(i, j);
                startFound = true;
            } else if (labirent[i][j] == 3) {
                endNode = new Node(i, j);
                endFound = true;
            }
            if (startFound && endFound) return;
        }
    }
    if (!startFound || !endFound) {
        cerr << "Başlangıç veya varış noktası bulunamadı!" << endl;
        exit(EXIT_FAILURE);
    }
}

bool Graf::isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && labirent[x][y] != 0;
}

Node** Graf::getNeighbors(Node* node) {
    Node** neighbors = new Node*[4];
    int x = node->x;
    int y = node->y;
    int count = 0;

    if (x > 0 && labirent[x - 1][y] != 0) neighbors[count++] = new Node(x - 1, y);
    if (x < rows - 1 && labirent[x + 1][y] != 0) neighbors[count++] = new Node(x + 1, y);
    if (y > 0 && labirent[x][y - 1] != 0) neighbors[count++] = new Node(x, y - 1);
    if (y < cols - 1 && labirent[x][y + 1] != 0) neighbors[count++] = new Node(x, y + 1);

    for (int i = count; i < 4; ++i) {
        neighbors[i] = nullptr;
    }

    return neighbors;
}

MyQueue::MyQueue(int capacity) : capacity(capacity), frontIdx(0), backIdx(-1), size(0) {
    data = new Node*[capacity];
}

MyQueue::~MyQueue() {
    delete[] data;
}

void MyQueue::push(Node* node) {
    backIdx = (backIdx + 1) % capacity;
    data[backIdx] = node;
    size++;
}

void MyQueue::pop() {
    frontIdx = (frontIdx + 1) % capacity;
    size--;
}

Node* MyQueue::front() {
    return data[frontIdx];
}

bool MyQueue::empty() {
    return size == 0;
}

MyStack::MyStack(int capacity) : capacity(capacity), topIdx(-1) {
    data = new Node*[capacity];
}

MyStack::~MyStack() {
    delete[] data;
}

void MyStack::push(Node* node) {
    data[++topIdx] = node;
}

void MyStack::pop() {
    topIdx--;
}

Node* MyStack::top() {
    return data[topIdx];
}

bool MyStack::empty() {
    return topIdx == -1;
}

bool BFS(Graf& graf, Node** path, int& totalCost, int& attemptCount) {
    MyQueue q(graf.rows * graf.cols);
    q.push(graf.startNode);
    vector<vector<bool>> visited(graf.rows, vector<bool>(graf.cols, false));
    visited[graf.startNode->x][graf.startNode->y] = true;

    attemptCount = 0;
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        attemptCount++;

        if (current->x == graf.endNode->x && current->y == graf.endNode->y) {
            totalCost = current->cost;
            while (current) {
                *(path++) = current;
                current = current->parent;
            }
            return true;
        }

        Node** neighbors = graf.getNeighbors(current);
        for (int i = 0; i < 4; ++i) {
            Node* neighbor = neighbors[i];
            if (neighbor && !visited[neighbor->x][neighbor->y]) {
                neighbor->cost = current->cost + 1;
                neighbor->parent = current;
                q.push(neighbor);
                visited[neighbor->x][neighbor->y] = true;
            }
        }
        delete[] neighbors;
    }
    return false;
}

bool DFS(Graf& graf, Node** path, int& totalCost, int& attemptCount) {
    MyStack s(graf.rows * graf.cols);
    s.push(graf.startNode);
    vector<vector<bool>> visited(graf.rows, vector<bool>(graf.cols, false));
    visited[graf.startNode->x][graf.startNode->y] = true;

    attemptCount = 0;
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        attemptCount++;

        if (current->x == graf.endNode->x && current->y == graf.endNode->y) {
            totalCost = current->cost;
            while (current) {
                *(path++) = current;
                current = current->parent;
            }
            return true;
        }

        Node** neighbors = graf.getNeighbors(current);
        for (int i = 0; i < 4; ++i) {
            Node* neighbor = neighbors[i];
            if (neighbor && !visited[neighbor->x][neighbor->y]) {
                neighbor->cost = current->cost + 1;
                neighbor->parent = current;
                s.push(neighbor);
                visited[neighbor->x][neighbor->y] = true;
            }
        }
        delete[] neighbors;
    }
    return false;
}

void cikisYolu(Node** path, int pathSize, const string& filename, int attemptCount) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Bulunan yol:\n";
        for (int i = pathSize - 1; i >= 0; --i) {
            Node* node = path[i];
            file << "(" << node->x << "," << node->y << "-" << node->cost << ") ";
            if (i != pathSize - 1) {
                Node* prevNode = path[i + 1];
                if (node->x == prevNode->x) {
                    if (node->y < prevNode->y) file << "sol ";
                    else file << "sağ ";
                } else if (node->y == prevNode->y) {
                    if (node->x < prevNode->x) file << "yukarı ";
                    else file << "aşağı ";
                }
            }
            file << "\n";
        }
        file << "Deneme sayısı: " << attemptCount << endl;
        file.close();
    } else {
        cerr << "Dosya açılamadı!" << endl;
    }
}