#include <iostream>

using namespace std;
class Noeud {
public:
    int valeur;
    Noeud* suivant;
    Noeud(int val) {
        valeur = val;
        suivant = nullptr;
    }
};
class ListeChainee {
private:
    Noeud* tete;

public:
    ListeChainee() {
        tete = nullptr;
    }
    ~ListeChainee() {
        Noeud* actuel = tete;
        while (actuel != nullptr) {
            Noeud* suivantTemp = actuel->suivant;
            delete actuel;
            actuel = suivantTemp;
        }
    }
    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);
        nouveau->suivant = tete;
        tete = nouveau;
    }
    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);
        if (tete == nullptr) {
            tete = nouveau;
            return;
        }
        Noeud* temp = tete;
        while (temp->suivant != nullptr) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
    }
    void supprimer(int valeur) {
        if (tete == nullptr) return;
        if (tete->valeur == valeur) {
            Noeud* aSupprimer = tete;
            tete = tete->suivant;
            delete aSupprimer;
            return;
        }

        Noeud* tmp = tete;
        while (tmp->suivant != nullptr && tmp->suivant->valeur != valeur) {
            tmp = tmp->suivant;
        }
        if (tmp->suivant != nullptr) {
            Noeud* aSupprimer = tmp->suivant;
            tmp->suivant = tmp->suivant->suivant;
            delete aSupprimer;
        }
    }
    void afficher() {
        Noeud* tmp = tete;
        cout << "Liste : ";
        while (tmp != nullptr) {
            cout << tmp->valeur << " -> ";
            tmp = tmp->suivant;
        }
        cout << "NULL" << endl;
    }
    int taille() {
        int cmp = 0;
        Noeud* tmp = tete;
        while (tmp != nullptr) {
            cmp++;
            tmp = tmp->suivant;
        }
        return cmp;
    }
    class Iterator {
    private:
        Noeud* courant;
    public:
        Iterator(Noeud* n) {
            courant = n;
        }
        bool operator!=(const Iterator& autre) {
            return courant != autre.courant;
        }
        int& operator*() {
            return courant->valeur;
        }
        Iterator& operator++() {
            courant = courant->suivant;
            return *this;
        }
    };
    Iterator begin() {
        return Iterator(tete);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};
int main() {
    ListeChainee maListe;
    maListe.ajouterFin(15);
    maListe.ajouterFin(22);
    maListe.ajouterDebut(3);
    
    maListe.afficher(); 
    cout << "Taille de la liste : " << maListe.taille() << endl;
    cout << "\nSuppression de l'element 10..." << endl;
    maListe.supprimer(10);
    maListe.afficher();
    cout << "Nouvelle taille : " << maListe.taille() << endl;
    cout << "\nTest (Iterateur):" << endl;
    cout << "Elements parcourus avec l'iterateur : ";
    for (auto it = maListe.begin(); it != maListe.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}