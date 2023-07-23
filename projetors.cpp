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

int particionaQuick(games *acervos, int c, int f, int ord)
{
    if (ord == 1)
    {
        games pivo = acervos[c];
        int i = c + 1, j = f;
        while (i <= j)
        {
            if (acervos[i].id <= pivo.id)
                i++;
            else if (pivo.id <= acervos[j].id)
                j--;
            else
            {
                swap(acervos[i], acervos[j]);
                i++;
                j--;
            }
        }
        acervos[c] = acervos[j];
        acervos[j] = pivo;
        return j;
    }
    else if (ord == 2)
    {
        games pivo = acervos[c];
        int i = c + 1, j = f;
        while (i <= j)
        {
            if (acervos[i].nome <= pivo.nome)
                i++;
            else if (pivo.nome <= acervos[j].nome)
                j--;
            else
            {
                swap(acervos[i], acervos[j]);
                i++;
                j--;
            }
        }
        acervos[c] = acervos[j];
        acervos[j] = pivo;
        return j;
    }
    else if (ord == 3)
    {
        games pivo = acervos[c];
        int i = c + 1, j = f;
        while (i <= j)
        {
            if (acervos[i].plat <= pivo.plat)
                i++;
            else if (pivo.plat <= acervos[j].plat)
                j--;
            else
            {
                swap(acervos[i], acervos[j]);
                i++;
                j--;
            }
        }
        acervos[c] = acervos[j];
        acervos[j] = pivo;
        return j;
    }
    else if (ord == 4)
    {
        games pivo = acervos[c];
        int i = c + 1, j = f;
        while (i <= j)
        {
            if (acervos[i].empresa <= pivo.empresa)
                i++;
            else if (pivo.empresa <= acervos[j].empresa)
                j--;
            else
            {
                swap(acervos[i], acervos[j]);
                i++;
                j--;
            }
        }
        acervos[c] = acervos[j];
        acervos[j] = pivo;
        return j;
    }
    else if (ord == 5)
    {
        games pivo = acervos[c];
        int i = c + 1, j = f;
        while (i <= j)
        {
            if (acervos[i].preco <= pivo.preco)
                i++;
            else if (pivo.preco <= acervos[j].preco)
                j--;
            else
            {
                swap(acervos[i], acervos[j]);
                i++;
                j--;
            }
        }
        acervos[c] = acervos[j];
        acervos[j] = pivo;
        return j;
    }
}

int buscaBinariaNum(games *acervos, int c, int f, float procurado, int ord)
{
    if (c <= f)
    {
        int meio = (c + f) / 2;
        if (procurado > acervos[meio].id)
            return buscaBinariaNum(acervos, meio + 1, f, procurado, ord);
        else if (procurado < acervos[meio].id)
            return buscaBinariaNum(acervos, c, meio - 1, procurado, ord);
        else
            return meio;
    }
    return -1;
}

int buscaBinariaString(games *acervos, int c, int f, string procurado, int ord)
{

    if (ord == 2)
    {
        if (c <= f)
        {
            int meio = (c + f) / 2;
            if (procurado > acervos[meio].nome)
                return buscaBinariaString(acervos, meio + 1, f, procurado, ord);
            else if (procurado < acervos[meio].nome)
                return buscaBinariaString(acervos, c, meio - 1, procurado, ord);
            else
                return meio;
        }
        return -1;
    }

    else if (ord == 3)
    {
        if (c <= f)
        {
            int meio = (c + f) / 2;
            if (procurado > acervos[meio].plat)
                return buscaBinariaString(acervos, meio + 1, f, procurado, ord);
            else if (procurado < acervos[meio].plat)
                return buscaBinariaString(acervos, c, meio - 1, procurado, ord);
            else
                return meio;
        }
        return -1;
    }

    else if (ord == 4)
    {
        if (c <= f)
        {
            int meio = (c + f) / 2;
            if (procurado > acervos[meio].empresa)
                return buscaBinariaString(acervos, meio + 1, f, procurado, ord);
            else if (procurado < acervos[meio].empresa)
                return buscaBinariaString(acervos, c, meio - 1, procurado, ord);
            else
                return meio;
        }
        return -1;
    }
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

void ordenar(games *acervos, int c, int f, int &ord)
{
    int posNovoC;
    if (c < f)
    {
         posNovoC = particionaQuick(acervos, c, f, ord);
         ordenar(acervos, c, posNovoC - 1, ord);
         ordenar(acervos, posNovoC + 1, f, ord);
    }
}

void buscar(games *acervos, int c, int f, bool &verified)
{

    int ord;
    cout << "Por qual informação você deseja pesquisar:\n1: ID\n2: Nome\n3: Plataforma\n4: Empresa\n0: Cancelar operação\n";
    cin >> ord;

    if (ord == 1)
    {
        ordenar(acervos, c, f, ord);
        int idSearch;
        cout << "Informe o id do jogo: ";
        cin >> idSearch;
        int i = buscaBinariaNum(acervos, c, f, idSearch, ord);
        if (buscaBinariaNum(acervos, c, f, idSearch, ord) != -1)
        {
            verified = true;
        }

        cout << endl << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: R$" << acervos[i].preco << endl
                     << endl;
    }
    else if (ord == 2)
    {
        ordenar(acervos, c, f, ord);
        string nomeSearch;
        cout << "Informe o nome do jogo: ";
        cin.ignore();
        getline(cin, nomeSearch);
        int i = buscaBinariaString(acervos, c, f, nomeSearch, ord);
        if (buscaBinariaString(acervos, c, f, nomeSearch, ord) != -1)
        {
            verified = true;
        }

        cout << endl << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: R$" << acervos[i].preco << endl
                     << endl;
    }
    else if (ord == 3)
    {
        ordenar(acervos, c, f, ord);
        string platSearch;
        cout << "Informe a plataforma do jogo: ";
        cin.ignore();
        getline(cin, platSearch);
        int i = buscaBinariaString(acervos, c, f, platSearch, ord);
        if (buscaBinariaString(acervos, c, f, platSearch, ord) != -1)
        {
            verified = true;
        }

        cout << endl << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: R$" << acervos[i].preco << endl
                     << endl;
    }
    else if (ord == 4)
    {
        ordenar(acervos, c, f, ord);
        string empresaSearch;
        cout << "Informe a empresa do jogo: ";
        cin.ignore();
        getline(cin, empresaSearch);
        int i = buscaBinariaString(acervos, c, f, empresaSearch, ord);
        if (buscaBinariaString(acervos, c, f, empresaSearch, ord != -1))
        {
            verified = true;
        }

        cout << endl << "ID: " << acervos[i].id << endl
                     << "Nome: " << acervos[i].nome << endl
                     << "Plataforma: " << acervos[i].plat << endl
                     << "Empresa: " << acervos[i].empresa << endl
                     << "Preço: R$" << acervos[i].preco << endl
                     << endl;

    }
    else if (ord == 0)
    {
         cout << endl
              << "Operação cancelada" << endl
              << endl;
    }
    else
    {
         cout << endl
              << "Digite uma opção válida!!" << endl
              << endl;
         cin >> ord;
         buscar(acervos, c, f, verified);
    }
}

void editar(games *acervos)
{

    int idEdit, edit = 0;
    cout << "Digite o ID do registro que voce deseja Editar: ";
    cin >> idEdit;

    if (acervos[idEdit - 1].exists)
    {
         cout << endl
              << "O que voce deseja editar?\n1: Nome\n2: Plataforma\n3: Empresa\n4: Preco\n0: Cancelar operação\n";
         cin >> edit;
         if (edit == 1)
         {
             cout << endl
                  << "Digite a informação que substituirá a atual:" << endl;
             string newName;
             cin.ignore();
             getline(cin, newName);
             acervos[idEdit - 1].nome = newName;
             cout << "O nome do jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl
                  << endl;
         }
         else if (edit == 2)
         {
             cout << endl
                  << "Digite a informação que substituirá a atual:" << endl;
             string newPlat;
             cin.ignore();
             getline(cin, newPlat);
             acervos[idEdit - 1].plat = newPlat;
             cout << "A plataforma do jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl
                  << endl;
         }
         else if (edit == 3)
         {
             cout << endl
                  << "Digite a informação que substituirá a atual:" << endl;
             string newEmp;
             cin.ignore();
             getline(cin, newEmp);
             acervos[idEdit - 1].empresa = newEmp;
             cout << "A empresa do jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl
                  << endl;
         }
         else if (edit == 4)
         {
             cout << endl
                  << "Digite a informação que substituirá a atual:" << endl;
             float newPrice;
             cin >> newPrice;
             acervos[idEdit - 1].preco = newPrice;
             cout << "O valor do jogo do ID: " << idEdit << " foi editado no acervo de jogos!" << endl
                  << endl;
         }
         else if (edit == 0)
         {
             cout << endl
                  << "Operação cancelada" << endl
                  << endl;
         }
         else
         {
             cout << endl
                  << "Digite uma opção válida!!" << endl
                  << endl;
             editar(acervos);
         }
    }
    else
    {
         cout << endl
              << "Esse jogo não existe na lista!" << endl
              << endl;
    }
}


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
                 editar(acervos);
                 cout << endl;
             }
             else if (h == 5)
             {
                 bool verified = false;

                 buscar(acervos, 0, n - 1, verified);
                 if (verified == true)
                 {
                     cout << endl
                          << "Este foi o resultado encontrado!" << endl
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
             else if (h == 6)
             {
                 int ord;
                 cout << "Por qual dado você deseja ordenar:\n1: ID em ordem crescente\n2: Nome em ordem alfabética\n3: Plataforma em ordem alfabética\n4: Empresa em ordem alfabética\n5: Valor em ordem crescente\n";
                 cin >> ord;
                 ordenar(acervos, 0, n - 1, ord);
                 cout << endl
                      << "O vetor foi ordenado!" << endl
                      << endl;
             }

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