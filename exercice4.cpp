#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;
class PileVideException : public exception {
private:
    string message;
public:
    PileVideException(string msg) {
        this->message = msg;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};
template <typename T>
class Pile {
private:
    vector<T> elements;

public:
    void empiler(T element) {
        elements.push_back(element);
        cout << "Element " << element << " empile avec succes." << endl;
    }
    T depiler() {
        if (estVide()) {
            throw PileVideException("Erreur : Impossible de depiler,la pile vide");
        }
        T sommetVal = elements.back();
        elements.pop_back();
        return sommetVal;
    }
    T sommet() const {
        if (estVide()) {
            throw PileVideException("Erreur : La pile est vide, aucun sommet disponible");
        }
        return elements.back();
    }
    bool estVide() const {
        return elements.empty();
    }
    void inverser() {
        int n = elements.size();
        for (int i = 0; i < n / 2; i++) {
            T temp = elements[i];
            elements[i] = elements[n - 1 - i];
            elements[n - 1 - i] = temp;
        }
    }
    void afficher() const {
        cout << "Pile du bas vers le sommet: ";
        for (int i = 0; i < elements.size(); i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};
int main() {
    cout << "Test 1 : Pile de type int" << endl;
    Pile<int> pileInt;
    pileInt.empiler(87);
    pileInt.empiler(23);
    pileInt.empiler(64);
    pileInt.afficher();

    cout << "Sommet actuel : " << pileInt.sommet() << endl;
    cout << "Element depile : " << pileInt.depiler() << endl;
    pileInt.afficher();

    cout << "\nInversion de la pile des entiers" << endl;
    pileInt.inverser();
    pileInt.afficher();
    cout << "Test 2 : Pile de type string " << endl;
    Pile<string> pileString;
    pileString.empiler("Cpp");
    pileString.empiler("Formation");
    pileString.empiler("POO");
    pileString.afficher();
    cout << "Test 3 : Gestion d'exception double" << endl;
    Pile<double> pileDouble;

    try {
        cout << "Tentative de depiler sur une pile vide" << endl;
        pileDouble.depiler();
    } 
    catch (const exception& e) {
        cout << "Exception interceptee -> " << e.what() << endl;
    }
    return 0;
}