#include <iostream>
using namespace std;

struct Node {
    int coeff;
    int degree;
    Node* next;

    Node(int c, int d) : coeff(c), degree(d), next(nullptr) {}
};

void insertNode(Node*& poly, int coeff, int degree) {
    Node* newNode = new Node(coeff, degree);
    if (!poly || poly->degree < degree) {
        newNode->next = poly;
        poly = newNode;
    } else {
        Node* curr = poly;
        while (curr->next && curr->next->degree >= degree) {
            curr = curr->next;
        }
        if (curr->degree == degree) {
            curr->coeff += coeff;
            delete newNode;
        } else {
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
}

void printPolynomial(Node* poly) {
    if (!poly) {
        cout << "0";
        return;
    }

    Node* curr = poly;
    bool first = true;
    while (curr) {
        if (curr->coeff != 0) {
            if (!first) cout << " + ";
            first = false;
            cout << curr->coeff << ".x^" << curr->degree;
        }
        curr = curr->next;
    }
    cout << endl;
}

Node* addPolynomials(Node* f, Node* g) {
    Node* result = nullptr;
    Node* ptrF = f;
    Node* ptrG = g;

    while (ptrF && ptrG) {
        if (ptrF->degree > ptrG->degree) {
            insertNode(result, ptrF->coeff, ptrF->degree);
            ptrF = ptrF->next;
        } else if (ptrF->degree < ptrG->degree) {
            insertNode(result, ptrG->coeff, ptrG->degree);
            ptrG = ptrG->next;
        } else {
            int sumCoeff = ptrF->coeff + ptrG->coeff;
            if (sumCoeff != 0) {
                insertNode(result, sumCoeff, ptrF->degree);
            }
            ptrF = ptrF->next;
            ptrG = ptrG->next;
        }
    }

    while (ptrF) {
        insertNode(result, ptrF->coeff, ptrF->degree);
        ptrF = ptrF->next;
    }

    while (ptrG) {
        insertNode(result, ptrG->coeff, ptrG->degree);
        ptrG = ptrG->next;
    }

    return result;
}

int main() {
    Node* f = nullptr;
    Node* g = nullptr;
    int n;

    cout << "Nhap so luong hang tu cua da thuc f(x): ";
    cin >> n;

    cout << "Nhap cac hang tu cho da thuc f(x) (he so va bac):\n";
    for (int i = 0; i < n; i++) {
        int coeff, degree;
        cout << "Hang tu " << i + 1 << " - He so: ";
        cin >> coeff;
        cout << "Hang tu " << i + 1 << " - Bac: ";
        cin >> degree;
        insertNode(f, coeff, degree);
    }

    cout << "Nhap so luong hang tu cua da thuc g(x): ";
    cin >> n;

    cout << "Nhap cac hang tu cho da thuc g(x) (he so va bac):\n";
    for (int i = 0; i < n; i++) {
        int coeff, degree;
        cout << "Hang tu " << i + 1 << " - He so: ";
        cin >> coeff;
        cout << "Hang tu " << i + 1 << " - Bac: ";
        cin >> degree;
        insertNode(g, coeff, degree);
    }

    cout << "f(x) = ";
    printPolynomial(f);
    cout << "g(x) = ";
    printPolynomial(g);

    Node* h = addPolynomials(f, g);

    cout << "h(x) = f(x) + g(x) = ";
    printPolynomial(h);

    while (f) {
        Node* temp = f;
        f = f->next;
        delete temp;
    }
    while (g) {
        Node* temp = g;
        g = g->next;
        delete temp;
    }
    while (h) {
        Node* temp = h;
        h = h->next;
        delete temp;
    }

    return 0;
}
