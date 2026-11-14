#include <iostream>
#include <string>

using namespace std;
class HashNode {
public:
    int cle;
    string valeur;
    HashNode* suivant;
    HashNode(int k, string v) {
        cle = k;
        valeur = v;
        suivant = nullptr;
    }
};
class TableHachage {
private:
    int capacite;     
    HashNode** table; 
    int hacher(int cle) {
        int index = cle % capacite;
        if (index < 0) {
            index = index + capacite;
        }
        return index;
    }

public:
    TableHachage(int cap) {
        capacite = cap;
        table = new HashNode*[capacite];
        for (int i = 0; i < capacite; i++) {
            table[i] = nullptr;
        }
    }
    ~TableHachage() {
        for (int i = 0; i < capacite; i++) {
            HashNode* actuel = table[i];
            while (actuel != nullptr) {
                HashNode* suivantTemp = actuel->suivant;
                delete actuel;
                actuel = suivantTemp;
            }
        }
        delete[] table;
    }
    void inserer(int cle, string valeur) {
        int index = hacher(cle);
        HashNode* actuel = table[index];
        while (actuel != nullptr) {
            if (actuel->cle == cle) {
                actuel->valeur = valeur; 
                return;
            }
            actuel = actuel->suivant;
        }
        HashNode* nouveau = new HashNode(cle, valeur);
        nouveau->suivant = table[index];
        table[index] = nouveau;
    }
    string rechercher(int cle) {
        int index = hacher(cle);
        HashNode* actuel = table[index];

        while (actuel != nullptr) {
            if (actuel->cle == cle) {
                return actuel->valeur;
            }
            actuel = actuel->suivant;
        }
        return "";
    }
    void supprimer(int cle) {
        int index = hacher(cle);
        HashNode* actuel = table[index];
        HashNode* precedent = nullptr;

        while (actuel != nullptr) {
            if (actuel->cle == cle) {
                if (precedent == nullptr) {
                    table[index] = actuel->suivant;
                } else {
                    precedent->suivant = actuel->suivant;
                }
                delete actuel;
                cout << "Cle " << cle << " supprimee avec succes." << endl;
                return;
            }
            precedent = actuel;
            actuel = actuel->suivant;
        }
        cout << "Cle " << cle << " introuvable." << endl;
    }
    void afficher() {
        cout << "\nTABLE DE HACHAGE" << endl;
        for (int i = 0; i < capacite; i++) {
            cout << "Case " << i << " : ";
            HashNode* actuel = table[i];
            if (actuel == nullptr) {
                cout << "NULL" << endl;
            } else {
                while (actuel != nullptr) {
                    cout << "[" << actuel->cle << " -> " << actuel->valeur << "] -> ";
                    actuel = actuel->suivant;
                }
                cout << "NULL" << endl;
            }
        }
    }
};
int main() {
    TableHachage map(5);
    map.inserer(11, "Amine");   
    map.inserer(44, "Karim");     
    map.inserer(9, "Chaima");  
    map.inserer(67, "Salma");    
    map.inserer(4, "Kawtar");    
    map.afficher();
    cout << "\nRecherche de la cle 11 : " << map.rechercher(11) << endl;
    cout << "Recherche de la cle 81 (inexistante) : " << (map.rechercher(81).empty() ? "Non trouve" : map.rechercher(81)) << endl;
    cout << "\nSuppression de la cle 9" << endl;
    map.supprimer(9);
    map.afficher();
    return 0;
}