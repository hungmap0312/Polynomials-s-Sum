#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một hạng tử trong đa thức
struct Term {
    int coeff;  // Hệ số của hạng tử
    int degree; // Bậc của hạng tử
    Term* next; // Con trỏ đến hạng tử tiếp theo trong danh sách liên kết

    Term(int c, int d) : coeff(c), degree(d), next(nullptr) {} // Constructor khởi tạo
};

// Hàm để thêm một hạng tử vào danh sách liên kết (theo thứ tự bậc giảm dần)
void insertTerm(Term*& poly, int coeff, int degree) {
    Term* newTerm = new Term(coeff, degree);
    if (!poly || poly->degree < degree) {  // Nếu poly rỗng hoặc hạng tử mới có bậc lớn hơn bậc đầu tiên
        newTerm->next = poly;
        poly = newTerm;
    } else {
        Term* curr = poly;
        while (curr->next && curr->next->degree >= degree) {  // Tìm vị trí thích hợp để chèn
            curr = curr->next;
        }
        if (curr->degree == degree) {  // Nếu đã có hạng tử có cùng bậc
            curr->coeff += coeff;
            delete newTerm; // Xóa hạng tử mới vì đã cộng vào hệ số
        } else {
            newTerm->next = curr->next;
            curr->next = newTerm;
        }
    }
}

// Hàm để in ra đa thức theo định dạng yêu cầu
void printPolynomial(Term* poly) {
    if (!poly) {
        cout << "0";
        return;
    }

    Term* curr = poly;
    bool first = true;
    while (curr) {
        if (curr->coeff != 0) {
            if (!first) cout << " + "; // Thêm dấu cộng nếu không phải phần tử đầu tiên
            first = false;
            cout << curr->coeff << ".x^" << curr->degree;
        }
        curr = curr->next;
    }
    cout << endl;
}

// Hàm cộng 2 đa thức
Term* addPolynomials(Term* f, Term* g) {
    Term* result = nullptr;
    Term* ptrF = f;
    Term* ptrG = g;

    // Cộng các hạng tử từ hai đa thức
    while (ptrF && ptrG) {
        if (ptrF->degree > ptrG->degree) {
            insertTerm(result, ptrF->coeff, ptrF->degree);
            ptrF = ptrF->next;
        } else if (ptrF->degree < ptrG->degree) {
            insertTerm(result, ptrG->coeff, ptrG->degree);
            ptrG = ptrG->next;
        } else {
            int sumCoeff = ptrF->coeff + ptrG->coeff;
            if (sumCoeff != 0) {
                insertTerm(result, sumCoeff, ptrF->degree);
            }
            ptrF = ptrF->next;
            ptrG = ptrG->next;
        }
    }

    // Nếu còn hạng tử trong f
    while (ptrF) {
        insertTerm(result, ptrF->coeff, ptrF->degree);
        ptrF = ptrF->next;
    }

    // Nếu còn hạng tử trong g
    while (ptrG) {
        insertTerm(result, ptrG->coeff, ptrG->degree);
        ptrG = ptrG->next;
    }

    return result;
}

int main() {
    Term* f = nullptr;
    Term* g = nullptr;

    // Nhập đa thức f(x) = 5.x^10 + 1
    insertTerm(f, 5, 10);  // 5.x^10
    insertTerm(f, 1, 0);   // 1

    // Nhập đa thức g(x) = 10.x^15 - 2.x^7 + 3.x^2 - 7
    insertTerm(g, 10, 15); // 10.x^15
    insertTerm(g, -2, 7);  // -2.x^7
    insertTerm(g, 3, 2);   // 3.x^2
    insertTerm(g, -7, 0);  // -7

    // In ra các đa thức f(x) và g(x)
    cout << "f(x) = ";
    printPolynomial(f);
    cout << "g(x) = ";
    printPolynomial(g);

    // Cộng 2 đa thức f(x) và g(x)
    Term* h = addPolynomials(f, g);

    // In ra tổng h(x) = f(x) + g(x)
    cout << "h(x) = f(x) + g(x) = ";
    printPolynomial(h);

    // Giải phóng bộ nhớ (Xóa các hạng tử trong danh sách liên kết)
    while (f) {
        Term* temp = f;
        f = f->next;
        delete temp;
    }
    while (g) {
        Term* temp = g;
        g = g->next;
        delete temp;
    }
    while (h) {
        Term* temp = h;
        h = h->next;
        delete temp;
    }

    return 0;
}
