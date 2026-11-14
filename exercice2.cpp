#include <iostream>
#include <string>
#include <exception>

using namespace std;
class FileVideException : public exception {
private:
    string message;
public:
    FileVideException(string msg) {
        this->message = msg;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};
class FilePleineException : public exception {
private:
    string message;
public:
    FilePleineException(string msg) {
        this->message = msg;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};
class File {
private:
    int* tab;      
    int capacite;   
    int debut;     
    int fin;        
    int taille;     

public:
    File(int cap) {
        capacite = cap;
        tab = new int[capacite];
        debut = 0;
        fin = 0;
        taille = 0;
    }
    ~File() {
        delete[] tab;
    }

    bool estVide() {
        return taille == 0;
    }
    bool estPleine() {
        return taille == capacite;
    }
    void enfiler(int valeur) {
        if (estPleine()) {
            throw FilePleineException("Erreur : Impossible d'enfiler, la file est pleine");
        }
        tab[fin] = valeur;
        fin = (fin + 1) % capacite;
        taille++;
        cout << "Succes : " << valeur << " ajoute a la file." << endl;
    }
    int defiler() {
        if (estVide()) {
            throw FileVideException("Erreur : Impossible de defiler, la file est vide ");
        }
        int valeur = tab[debut];
        debut = (debut + 1) % capacite; 
        taille--;
        return valeur;
    }
    void afficher() {
        if (estVide()) {
            cout << "La file est vide." << endl;
            return;
        }
        cout << "Etat de la file (FIFO) : ";
        for (int i = 0; i < taille; i++) {
            int index = (debut + i) % capacite;
            cout << tab[index] << " ";
        }
        cout << endl;
    }
};
int main() {
    int capaciteMax;
    cout << "Entrer la capacite maximale de la file : ";
    cin >> capaciteMax;

    File maFile(capaciteMax);
    int choix, valeur;
    bool continuer = true;
    while (continuer) {
        cout << "\nMENU FILE" << endl;
        cout << "1-Ajouter" << endl;
        cout << "2-Retirer" << endl;
        cout << "3-Affichage de la file" << endl;
        cout << "4-Quitter" << endl;
        cout << "Votre choix : ";
        cin >> choix;
        switch (choix) {
            case 1:
                cout << "Entrer la valeur a ajouter : ";
                cin >> valeur;
                try {
                    maFile.enfiler(valeur);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
                break;
            case 2:
                try {
                    int elementSupprime = maFile.defiler();
                    cout << "Element defile : " << elementSupprime << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
                break;
            case 3:
                maFile.afficher();
                break;
            case 4:
                continuer = false;
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide, veuillez reessayer." << endl;
        }
    }
    return 0;
}