#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct games
{
    int id;
    char nome[40], plat[40], empresa[40];
    float preco;
    bool exists = true;
};

games leitura(ifstream &arq, int &i)
{
    games acervo;
    acervo.id = i + 1;
    arq.read(reinterpret_cast<char*>(&acervo.nome), sizeof(acervo.nome));
    arq.read(reinterpret_cast<char*>(&acervo.plat), sizeof(acervo.plat));
    arq.read(reinterpret_cast<char*>(&acervo.empresa), sizeof(acervo.empresa));
    arq.read(reinterpret_cast<char*>(&acervo.preco), sizeof(acervo.preco));
    return acervo;
}

void imprime(games *acervos, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "ID: " << acervos[i].id << endl
             << "Nome: " << acervos[i].nome << endl
             << "Plataforma: " << acervos[i].plat << endl
             << "Empresa: " << acervos[i].empresa << endl
             << "Preço: R$" << acervos[i].preco << endl << endl;
    }
}

void apagar(games *acervos, int idApagar)
{
    acervos[idApagar - 1].id = -1;
    acervos[idApagar - 1].nome[0] = '\0';
    acervos[idApagar - 1].plat[0] = '\0';
    acervos[idApagar - 1].empresa[0] = '\0';
    acervos[idApagar - 1].preco = -1;
}

games *aumentar(games *acervos, int& n)
{
    games *newAcervos = new games[n+1];
    copy(acervos, acervos + n, newAcervos);
    delete[] acervos;
    n += 1;
    return newAcervos;
}

void inserir(games* acervos, int& n, int& jogoInserido)
{
    int foundFalse = -1; // Variável para armazenar a posição onde será inserido o novo registro

    // Procura por um registro inativo (exists == false) para inserir o novo jogo
    for (int i = 0; i < n; i++) {
        if (!acervos[i].exists) {
            foundFalse = i;
            acervos[i].exists = true; // Marca o registro como ativo (exists == true)
            jogoInserido = i; // Guarda a posição onde o novo registro foi inserido
            break;
        }
    }

    // Se não foi encontrado um registro inativo, adicionamos um novo registro ao final do vetor
    if (foundFalse == -1) {
        acervos = aumentar(acervos, n);
        jogoInserido = n - 1; // Guarda a posição onde o novo registro foi inserido
    }

    acervos[jogoInserido].id = n;
    cin.ignore();
    cin.getline(acervos[jogoInserido].nome, sizeof(acervos[jogoInserido].nome), ',');
    cin.getline(acervos[jogoInserido].plat, sizeof(acervos[jogoInserido].plat), ',');
    cin.getline(acervos[jogoInserido].empresa, sizeof(acervos[jogoInserido].empresa), ',');
    cin >> acervos[jogoInserido].preco;
    cin.ignore();

    n++; // Atualiza o tamanho do vetor após inserir um novo registro

    // Grava os dados atualizados no arquivo binário

}


// Função para ler os dados do arquivo binário
void lerDadosDoArquivoBinario(games* acervos, int n) {
    ifstream arquivo("dados.bin", ios::binary);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        arquivo.read(reinterpret_cast<char*>(&acervos[i].nome), sizeof(acervos[i].nome));
        arquivo.read(reinterpret_cast<char*>(&acervos[i].plat), sizeof(acervos[i].plat));
        arquivo.read(reinterpret_cast<char*>(&acervos[i].empresa), sizeof(acervos[i].empresa));
        arquivo.read(reinterpret_cast<char*>(&acervos[i].preco), sizeof(acervos[i].preco));
    }

    arquivo.close();
}

// Função para gravar os dados no arquivo binário
void gravarDadosNoArquivoBinario(const games* acervos, int n) {
    ofstream arquivo("dados.bin", ios::binary);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        arquivo.write(reinterpret_cast<const char*>(&acervos[i].nome), sizeof(acervos[i].nome));
        arquivo.write(reinterpret_cast<const char*>(&acervos[i].plat), sizeof(acervos[i].plat));
        arquivo.write(reinterpret_cast<const char*>(&acervos[i].empresa), sizeof(acervos[i].empresa));
        arquivo.write(reinterpret_cast<const char*>(&acervos[i].preco), sizeof(acervos[i].preco));
    }

    arquivo.close();
}


void buscar(const games* acervos, int n, int search)
{
    switch (search)
    {
        case 1:{
            int idSearch;
            cout << "Informe o id do jogo: ";
            cin >> idSearch;
            for(int i = 0; i < n; i++){
                if(acervos[i].id == idSearch){
                    cout << endl
                         << "ID: " << acervos[i].id << endl
                         << "Nome: " << acervos[i].nome << endl
                         << "Plataforma: " << acervos[i].plat << endl
                         << "Empresa: " << acervos[i].empresa << endl
                         << "Preço: " << acervos[i].preco << endl;
                }
            }
            break;
        }

        case 2:{
            char nomeSearch[40];
            cout << "Informe o nome do jogo: ";
            cin.ignore();
            cin.getline(nomeSearch, sizeof(nomeSearch));
            for(int i = 0; i < n; i++){
                if (strcmp(acervos[i].nome, nomeSearch) == 0) {
                    cout << endl
                         << "ID: " << acervos[i].id << endl
                         << "Nome: " << acervos[i].nome << endl
                         << "Plataforma: " << acervos[i].plat << endl
                         << "Empresa: " << acervos[i].empresa << endl
                         << "Preço: " << acervos[i].preco << endl;
                }
            }
            break;
        }

        case 3:{
            char platSearch[40];
            cout << "Informe a plataforma do jogo: ";
            cin.ignore();
            cin.getline(platSearch, sizeof(platSearch));
            for(int i = 0; i < n; i++){
                if (strcmp(acervos[i].plat, platSearch) == 0) {
                    cout << endl
                         << "ID: " << acervos[i].id << endl
                         << "Nome: " << acervos[i].nome << endl
                         << "Plataforma: " << acervos[i].plat << endl
                         << "Empresa: " << acervos[i].empresa << endl
                         << "Preço: " << acervos[i].preco << endl;
                }
            }
            break;
        }

        case 4:{
            char empresaSearch[40];
            cout << "Informe a empresa do jogo: ";
            cin.ignore();
            cin.getline(empresaSearch, sizeof(empresaSearch));
            for(int i = 0; i < n; i++){
                if (strcmp(acervos[i].empresa, empresaSearch) == 0) {
                    cout << endl
                         << "ID: " << acervos[i].id << endl
                         << "Nome: " << acervos[i].nome << endl
                         << "Plataforma: " << acervos[i].plat << endl
                         << "Empresa: " << acervos[i].empresa << endl
                         << "Preço: " << acervos[i].preco << endl;
                }
            }
            break;
        }

        default:
            break;
    }
}
void editar(games* acervos, int idEdit, int edit)
{
    switch (edit){
        case 1:{
            char newName[40];
            cin.ignore();
            cin.getline(newName, sizeof(newName));
            strcpy(acervos[idEdit - 1].nome, newName);
            break;
        }

        case 2:{
            char newPlat[40];
            cin.ignore();
            cin.getline(newPlat, sizeof(newPlat));
            strcpy(acervos[idEdit - 1].plat, newPlat);
            break;
        }

        case 3:{
            char newEmp[40];
            cin.ignore();
            cin.getline(newEmp, sizeof(newEmp));
            strcpy(acervos[idEdit - 1].empresa, newEmp);
            break;
        }

        case 4:{
            float newPrice;
            cin >> newPrice;
            acervos[idEdit - 1].preco = newPrice;
            break;
        }

        default:
            break;
    }
}

/*void ordenar(games *acervos, int& n, int& ord){
	switch(ord){
		case 1:{
			for (int i = 0; i < n - 1; i++) {
				int indiceMenor = i;
				for (int j = i + 1; j < n; j++) {
					if (acervos[j].id < acervos[indiceMenor].id) {
						indiceMenor = j;
					}		
				}
				
				games temp = acervos[i];
				acervos[i] = acervos[indiceMenor];
				acervos[indiceMenor] = temp;
			}
		}
		
		case 2:{
			for (int i = 0; i < n - 1; i++) {
				int indiceMenor = i;
				for (int j = i + 1; j < n; j++) {
					if (acervos[j].nome < acervos[indiceMenor].nome) {
						indiceMenor = j;
					}		
				}
				
				games temp = acervos[i];
				acervos[i] = acervos[indiceMenor];
				acervos[indiceMenor] = temp;
			}
		}
		
		case 3:{
			for (int i = 0; i < n - 1; i++) {
				int indiceMenor = i;
				for (int j = i + 1; j < n; j++) {
					if (acervos[j].plat < acervos[indiceMenor].plat) {
						indiceMenor = j;
					}		
				}
				
				games temp = acervos[i];
				acervos[i] = acervos[indiceMenor];
				acervos[indiceMenor] = temp;
			}
		}
		
		case 4:{
			for (int i = 0; i < n - 1; i++) {
				int indiceMenor = i;
				for (int j = i + 1; j < n; j++) {
					if (acervos[j].empresa < acervos[indiceMenor].empresa) {
						indiceMenor = j;
					}		
				}
				
				games temp = acervos[i];
				acervos[i] = acervos[indiceMenor];
				acervos[indiceMenor] = temp;
			}
		}
		
		case 5:{
			for (int i = 0; i < n - 1; i++) {
				int indiceMenor = i;
				for (int j = i + 1; j < n; j++) {
					if (acervos[j].preco < acervos[indiceMenor].preco) {
						indiceMenor = j;
					}		
				}
				
				games temp = acervos[i];
				acervos[i] = acervos[indiceMenor];
				acervos[indiceMenor] = temp;
			}
		}
	}
}
*/
int main()
{
    int h;
    int n;
    string lixo;
    ifstream arq("jogos.dat");
    arq >> n;
    games *acervos = new games[n];

    if (arq)
    {
        arq.ignore();
        arq.ignore();
        getline(arq, lixo);
        for (int i = 0; i < n; i++)
        {
            acervos[i] = leitura(arq, i);
        }

        cout << endl << "########## Bem-Vindo(a) ##########" << endl << endl;

        // Gravando os dados no arquivo binário após a leitura do arquivo CSV
        gravarDadosNoArquivoBinario(acervos, n);

        do {

            cout << "1: Mostrar os registros\n2: Apagar um registro\n3: Inserir um Registro\n4: Editar um registro\n5: Buscar registros\n6: Ordenar o vetor\n0: Sair" << endl << endl;
            cin >> h;

            switch (h)
            {
            case 1:{
                imprime(acervos, n);
                cout << endl;
                break;
            }

            case 2:{
                int idApagar;
                cout << "Digite o ID do registro que você deseja apagar: ";
                cin >> idApagar;
                apagar(acervos, idApagar);
                gravarDadosNoArquivoBinario(acervos, n); // Gravar os dados atualizados no arquivo
                cout << "Jogo do ID: " << idApagar << " foi apagado do acervo de jogos!" << endl << endl;
                break;
            }
                
            case 3:{
                cout << "Digite o nome do jogo, a plataforma de venda, a empresa do jogo e o seu valor.(Separados por vírgula)" << endl;
                int jogoInserido = 0;
                bool verify = false;
                for (int i = 0; i < n; i++) {
                    if (acervos[i].exists == false) {
                        verify = true;
                        jogoInserido = i; // Guarda a posição onde o novo registro será inserido
                        break;
                    }
                }
                if (!verify) {
                    acervos = aumentar(acervos, n);
                    jogoInserido = n - 1; // Guarda a posição onde o novo registro foi inserido
                }
                inserir(acervos, n, jogoInserido);
                gravarDadosNoArquivoBinario(acervos, n);
                cout << endl << "O jogo '" << acervos[jogoInserido].nome << "' foi inserido com sucesso!" << endl << endl;
                break;
            }
            case 4:{
                int idEdit, edit = 0;
                cout << "Digite o ID do registro que voce deseja Editar: ";
                cin >> idEdit;
                cout << endl << "O que voce deseja editar?\n1: Nome\n2: Plataforma\n3: Empresa\n4: Preco\n";
                cin >> edit;
                cout << endl << "Digite a informação que substituirá a atual:" << endl;
                editar(acervos, idEdit, edit);
                gravarDadosNoArquivoBinario(acervos, n); // Gravar os dados atualizados no arquivo
                cout << "Jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl << endl;
                break;
            }

            case 5:{
                int search;
                cout << "Por qual informação você deseja pesquisar:\n1: ID\n2: Nome\n3: Plataforma\n4: Empresa\n";
                cin >> search;
                buscar(acervos, n, search);
                cout << endl << "Estes foram os resultados encontrados!" << endl << endl;
                break;
            }
            
            /*case 6:{
                int ord;
                cout << "Por qual dado você deseja ordenar:\n1: ID em ordem crescente\n2: Nome em ordem alfabética\n3: Plataforma em ordem alfabética\n4: Empresa em ordem alfabética\n5: Valor em ordem crescente\n";
                cin >> ord;
                ordenar(acervos, n, ord);
                gravarDadosNoArquivoBinario(acervos, n); // Gravar os dados ordenados no arquivo
                cout << endl << "O vetor foi ordenado!" << endl << endl;
                break;
            }*/

            default:
                break;
            }

        } while (h != 0);
    }
    else
        cout << "Erro ao ler o arquivo!";
        
    delete[] acervos;

    return 0;
}
