#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define tamNome 40
#define tamPlat 40
#define tamEmp 40

using namespace std;

struct games {
    int id;
    char nome[tamNome];
    char plat[tamPlat];
    char empresa[tamEmp];
    float preco;
};

int main() {
    ifstream a("jogos.csv");

    if (!a.is_open()) {
        cout << "Erro ao abrir o arquivo jogos.csv." << endl;
        return 1;
    }

    string unused;
    int tam = 0;
    while (getline(a, unused))
        ++tam;
    a.close();
    cout << "O arquivo contem um total de " << tam << " linhas.\n\n";

    games* v = new games[tam];

    ifstream entrada("jogos.csv");

    if (!entrada.is_open()) {
        cout << "Erro ao abrir o arquivo jogos.csv." << endl;
        return 1;
    }

    for (int i = 0; i < tam; i++) {
        string buffer;
        getline(entrada, buffer, ',');
        strcpy(v[i].nome, buffer.c_str());
        getline(entrada, buffer, ',');
        strcpy(v[i].plat, buffer.c_str());
        getline(entrada, buffer, ',');
        strcpy(v[i].empresa, buffer.c_str());
        entrada >> v[i].id;
        entrada.ignore();
        entrada >> v[i].preco;
        entrada.ignore();

        // Descartar o restante da linha (caso haja campos adicionais no CSV)
        getline(entrada, unused);
    }
    entrada.close();

    ofstream saida("jogos.dat", ios::binary);
    if (!saida.is_open()) {
        cout << "Erro ao abrir o arquivo jogos.dat." << endl;
        return 1;
    }

    for (int i = 0; i < tam; i++) {
        cout << v[i].nome << endl;
    }

    saida.write((char*)&v[0], sizeof(games) * tam);
    saida.close();

    // Liberar a memória alocada
    delete[] v;

    return 0;
}
