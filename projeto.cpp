#include <iostream>
#include <fstream>
using namespace std;

struct games
{
    int id;
    string nome, plat, empresa;
    float preco;
    bool exists = true;
};

games leitura(ifstream &arq, int &i)
{
    games acervo;
    acervo.id = i + 1;
    getline(arq, acervo.nome, ',');
    getline(arq, acervo.plat, ',');
    getline(arq, acervo.empresa, ',');
    arq >> acervo.preco;
    arq.ignore();
    return acervo;
}

games *aumentar(games *acervos, int &n)
{
    games *newAcervos = new games[n + 1];
    copy(acervos, acervos + n, newAcervos);
    delete[] acervos;
    n += 1;
    return newAcervos;
}

void imprime(games *acervos, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (acervos[i].exists == true)
        {
            cout << "ID: " << acervos[i].id << endl
                 << "Nome: " << acervos[i].nome << endl
                 << "Plataforma: " << acervos[i].plat << endl
                 << "Empresa: " << acervos[i].empresa << endl
                 << "Preço: R$" << acervos[i].preco << endl
                 << endl;
        }
    }
}

void apagar(games *acervos)
{

    int idApagar;
    cout << "Digite o ID do registro que você deseja apagar: ";
    cin >> idApagar;

    if (acervos[idApagar - 1].exists)
    {
        acervos[idApagar - 1].exists = false;
        cout << "Jogo do ID: " << idApagar << " foi apagado do acervo de jogos!" << endl
             << endl;
    }
    else
    {
        cout << endl
             << "Esse jogo não existe na lista!" << endl
             << endl;
    }
}

void inserir(games *acervos, int &n, int &jogoInserido)
{

    int foundFalse = n - 1;

    for (int i = 0; i < n; i++)
    {
        if (acervos[i].exists == false)
        {
            foundFalse = i;
            acervos[i].exists = true;
            i = n;
        }
    }

    acervos[n - 1].id = n;
    cin.ignore();
    getline(cin, acervos[foundFalse].nome, ',');
    getline(cin, acervos[foundFalse].plat, ',');
    getline(cin, acervos[foundFalse].empresa, ',');
    cin >> acervos[foundFalse].preco;
    cin.ignore();

    jogoInserido = foundFalse;
}

void buscar(games *acervos, int n, bool &verified)
{

    int search;
    cout << "Por qual informação você deseja pesquisar:\n1: ID\n2: Nome\n3: Plataforma\n4: Empresa\n";
    cin >> search;

    if (search == 1)
    {
        int idSearch;
        cout << "Informe o id do jogo: ";
        cin >> idSearch;
        for (int i = 0; i < n; i++)
        {
            if (acervos[i].id == idSearch)
            {
                cout << endl
                     << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: " << acervos[i].preco << endl;
                verified = true;
            }
        }
    }
    else if (search == 2)
    {
        string nomeSearch;
        cout << "Informe o nome do jogo: ";
        cin.ignore();
        getline(cin, nomeSearch);
        for (int i = 0; i < n; i++)
        {
            if (acervos[i].nome == nomeSearch)
            {
                cout << endl
                     << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: " << acervos[i].preco << endl;
                verified = true;
            }
        }
    }
    else if (search == 3)
    {
        string platSearch;
        cout << "Informe a plataforma do jogo: ";
        cin.ignore();
        getline(cin, platSearch);
        for (int i = 0; i < n; i++)
        {
            if (acervos[i].plat == platSearch)
            {
                cout << endl
                     << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: " << acervos[i].preco << endl;
                verified = true;
            }
        }
    }
    else if (search == 4)
    {
        string empresaSearch;
        cout << "Informe a empresa do jogo: ";
        cin.ignore();
        getline(cin, empresaSearch);
        for (int i = 0; i < n; i++)
        {
            if (acervos[i].empresa == empresaSearch)
            {
                cout << endl
                     << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: " << acervos[i].preco << endl;
                verified = true;
            }
        }
    }
    else
    {
        cout << endl
             << "Digite uma opção válida!!" << endl
             << endl;
        buscar(acervos, n, verified);
    }
}

void editar(games *acervos, int idEdit, int edit)
{
    if (acervos[idEdit - 1].exists)
    {
        if (edit == 1)
        {
            string newName;
            cin.ignore();
            getline(cin, newName);
            acervos[idEdit - 1].nome = newName;
        }
        else if (edit == 2)
        {
            string newPlat;
            cin.ignore();
            getline(cin, newPlat);
            acervos[idEdit - 1].plat = newPlat;
        }
        else if (edit == 3)
        {
            string newEmp;
            cin.ignore();
            getline(cin, newEmp);
            acervos[idEdit - 1].empresa = newEmp;
        }
        else if (edit == 4)
        {
            float newPrice;
            cin >> newPrice;
            acervos[idEdit - 1].preco = newPrice;
        }
        else
        {
            cout << endl
                 << "Digite uma opção válida!!" << endl
                 << endl;
        }
    }
    else
    {
        cout << endl
             << "Esse jogo não existe na lista!" << endl
             << endl;
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
    ifstream arq("jogos.csv");
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

        cout << endl
             << "########## Bem-Vindo(a) ##########" << endl
             << endl;

        do
        {

            cout << "1: Mostrar os registros\n2: Apagar um registro\n3: Inserir um Registro\n4: Editar um registro\n5: Buscar registros\n6: Ordenar o vetor\n0: Sair" << endl
                 << endl;
            cin >> h;

            if (h == 1)
            {
                imprime(acervos, n);
                cout << endl;
            }
            else if (h == 2)
            {
                apagar(acervos);
                cout << endl;
            }
            else if (h == 3)
            {
                cout << "Digite o nome do jogo, a plataforma de venda, a empresa do jogo e o seu valor.(Separados por vírgula)" << endl;
                int jogoInserido = 0;
                bool verify = true;
                for (int i = 0; i < n; i++)
                {
                    if (acervos[i].exists == false)
                    {
                        verify = false;
                        i = n;
                    }
                }

                if (verify)
                {
                    acervos = aumentar(acervos, n);
                }

                inserir(acervos, n, jogoInserido);
                cout << endl
                     << "O jogo '" << acervos[jogoInserido].nome << "' foi inserido com sucesso!" << endl
                     << endl;
            }
            else if (h == 4)
            {
                int idEdit, edit = 0;
                cout << "Digite o ID do registro que voce deseja Editar: ";
                cin >> idEdit;
                cout << endl
                     << "O que voce deseja editar?\n1: Nome\n2: Plataforma\n3: Empresa\n4: Preco\n";
                cin >> edit;
                cout << endl
                     << "Digite a informação que substituirá a atual:" << endl;
                editar(acervos, idEdit, edit);
                cout << "Jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl
                     << endl;
            }
            else if (h == 5)
            {
                bool verified = false;
                buscar(acervos, n, verified);
                if (verified == true)
                {
                    cout << endl
                         << "Estes foram os resultados encontrados!" << endl
                         << endl;
                }
                else
                {
                    cout << endl
                         << "Não foi encontrado nenhum valor referente a pesquisa!" << endl
                         << endl;
                }
            }
            else if (h == 0)
            {
                cout << endl
                     << "Até mais!!" << endl
                     << endl;
            }
            /*else if(h == 6)
            {
                int ord;
                cout << "Por qual dado você deseja ordenar:\n1: ID em ordem crescente\n2: Nome em ordem alfabética\n3: Plataforma em ordem alfabética\n4: Empresa em ordem alfabética\n5: Valor em ordem crescente\n";
                cin >> ord;
                ordenar(acervos, n, ord);
                cout << endl << "O vetor foi ordenado!" << endl << endl;
            }
            */
            else
            {
                cout << endl
                     << "Digite uma opção válida!!" << endl
                     << endl;
            }

        } while (h != 0);
    }
    else
        cout << "Erro ao ler o arquivo!";

    delete[] acervos;

    return 0;
}