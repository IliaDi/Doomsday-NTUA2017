#include <iostream>
#include <fstream>
#include <vector>

class node {
public:
    char element;
    int t, i, j;
    node *next;
};

class queue {
    node *list_head, *list_tail;
public:
    queue();

    ~queue();

    void dequeue();

    void enqueue(char e, int time, int iq, int jq);

    bool isempty();

    node *gettop();

    void display();
};

queue::queue() {
    list_head = list_tail = NULL;
}

queue::~queue() {
    node *temp;
    while (list_head != NULL) {
        temp = list_head->next;
        delete list_head;
        list_head = temp;
    }
}

void queue::enqueue(char e, int time, int iq, int jq) {
    node *neo;
    neo = new node;
    neo->element = e;
    neo->t = time;
    neo->i = iq;
    neo->j = jq;
    if (list_tail != NULL) {
        list_tail->next = neo;
    }
    neo->next = NULL;
    list_tail = neo;
    if (list_head == NULL) {
        list_head = list_tail;
    }
    return;
}

void queue::dequeue() {
    node *temp;
    if (list_head == NULL) {
        return;
    }
    temp = list_head->next;
    delete list_head;
    list_head = temp;
}

bool queue::isempty() {
    if (list_head == NULL) return true;
    else return false;
}

node *queue::gettop() {
    if (!isempty()) return this->list_head;
    else return nullptr;
}

void queue::display() {
    node *p = list_head;
    if (isempty()) {
        return;
    }
    while (p != NULL) {
        std::cout << p->element << "\n";
        p = p->next;
    }
}

bool expansion(char matter, int i, int j, int time, char universeMap[][1000], queue &fQueue) {
    if (i >= 0 && j >= 0 && i < 1000 && j < 1000) {
        if (universeMap[i][j] == '.') {
            universeMap[i][j] = matter;
            fQueue.enqueue(matter, time + 1, i, j);
            return false;
        } else if( (universeMap[i][j] == '+' && matter == '-') ||( universeMap[i][j] == '-' && matter == '+')) {
            universeMap[i][j] = '*';
            return true;
        } else return false;
    } else return false;
}

int main(int argc, char *argv[]) {
    std::ifstream data;
    data.open(argv[1]);
    char universe[1000][1000], element;
    int i = 0, j = 0, endi = 0, endj = 0, timeofend = 0, flag;
    queue floodQueue;
    std::noskipws(data);
    while (data >> element) {
        if (element != '\r' && !data.eof() && element != '\n' && element!='\0') {
            universe[i][j] = element;
            j++;
            endj = j;
            if (element == '+' || element == '-') {
                floodQueue.enqueue(element, 0, i, j - 1);
            }
        } else {
            i++;
            j = 0;
        }
    }
    if (i == 0) endi = 1;
    else endi = i;
    flag = 0;
    node *it = floodQueue.gettop();
    while (!floodQueue.isempty()) {
        i = it->i;
        j = it->j;
        //check_universe
        if (expansion(it->element, i - 1, j, it->t, universe, floodQueue)) {
            timeofend = it->t + 1;
            flag = 1;
        }
        if (expansion(it->element, i + 1, j, it->t, universe, floodQueue)) {
            timeofend = it->t + 1;
            flag = 1;
        }
        if (expansion(it->element, i, j - 1, it->t, universe, floodQueue)) {
            timeofend = it->t + 1;
            flag = 1;
        }
        if (expansion(it->element, i, j + 1, it->t, universe, floodQueue)) {
            timeofend = it->t + 1;
            flag = 1;
        }
        floodQueue.dequeue();
        it = floodQueue.gettop();
        if (!floodQueue.isempty()) { if (it->t >= timeofend && flag == 1) flag = 2; }
        else if (flag==1) flag=2;
        if (flag == 2) {
            std::cout << timeofend << "\n";
            break;
        } else {
            if (floodQueue.isempty()) std::cout << "the world is saved\n";
        }
    }
    for (i = 0; i < endi ; i++) {
        if (i != 0) std::cout << "\n";
        for (j = 0; j < endj; j++) {
            std::cout << universe[i][j];

        }
    }
    return 0;
}