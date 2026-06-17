#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#endif

using std::cin;
using std::cout;
using std::string;
using std::endl;

void ClearScreen();
bool SalvarArquivo(const string& caminho, const string& texto);
std::vector<std::string> CarregarArquivo(const std::string& caminho);

int main(int argc, char* argv[])
{

    ClearScreen();

    std::vector<string> linhas;

    while (true){

        cout << "------------Azazel's To Do List------------" << endl;
        cout << "Comandos\n:save Salvar | :exit Sair | :undo Desfazer | :delete N Deletar linha | :edit N editar linha | :load <caminho> carrega um arquivo" << endl;

        for (size_t i = 0; i < linhas.size(); ++i)
        {
            cout << i + 1 << ": " << linhas[i] << '\n';
        }

        cout << "> ";
        string line;
        if (!std::getline(std::cin, line))
            break;

        std::stringstream ss(line);
        std::string comando;
        ss >> comando;


        if (comando == ":edit")
        {
            int indice;

            if (!(ss >> indice) || indice < 1 || indice > (int)linhas.size())
            {
                cout << "Informe uma linha válida para editar \n";
                continue;
            }

            std::string novoTexto;
            std::getline(ss, novoTexto);
            if (!novoTexto.empty() && novoTexto[0] == ' ')
                novoTexto.erase(0, 1);

            if (novoTexto.empty())
            {
                cout << "Conteúdo atual: " << linhas[indice - 1] << "\n";
                cout << "Novo conteúdo [mantém se vazio]: ";
                if (!std::getline(std::cin, novoTexto))
                    break;
            }

            if (!novoTexto.empty())
                linhas[indice - 1] = novoTexto;

            ClearScreen();
            continue;
        }
        else if (comando == ":delete")
        {
            int indice;

            if (!(ss >> indice) || indice < 1 || indice > (int)linhas.size())
            {
                cout << "Informe uma linha válida para apagar \n";
                continue;
            }

            linhas.erase(linhas.begin() + (indice - 1));
            ClearScreen();
            continue;
        }
        else if (comando == ":undo")
        {
            if (!linhas.empty())
                linhas.pop_back();

            ClearScreen();
            continue;
        }
        else if (comando == ":exit")
        {
            ClearScreen();
            break;
        }
        else if (comando == ":save")
        {
            string fileLocation;
            std::getline(ss, fileLocation);
            if (!fileLocation.empty() && fileLocation[0] == ' ')
                fileLocation = fileLocation.substr(1);
            
            if (fileLocation.empty())
            {
                cout << "Informe um local para salvar \n";
                continue;
            }
            
            string texto;
            for(const auto& linha : linhas)
            {
                texto += linha + '\n';
            }

            if (SalvarArquivo(fileLocation, texto)) cout << "Arquivo Salvo com Succeso!" << endl;
            
            ClearScreen();
            continue;
        }else if (comando == ":load")
        {
            string caminho;

            if (!(ss >> caminho))
            {
                cout << "Informe um caminho calido \n";
                continue;
            }else{
                linhas.clear();
                linhas = CarregarArquivo(caminho);
                ClearScreen();
                continue;
            }
        }
        else
        {
            linhas.push_back(line);
            ClearScreen();
        }
        
    }

    return 0;
}


std::vector<std::string> CarregarArquivo(const std::string& caminho)
{
    std::ifstream arquivo(caminho);

    if (!arquivo.is_open())
    {
        std::cerr << "Não foi possivel encontrar: "
                  << caminho << std::endl;

        return {};
    }

    std::vector<std::string> linhas;
    std::string linha;

    while (std::getline(arquivo, linha))
    {
        linhas.push_back(linha);
    }

    return linhas;
}

bool SalvarArquivo(const string& caminho, const string& texto)
{
    std::ofstream file(caminho) ;

    if(!file)
    {
        cout << "ERROR CREATING FILE!" << endl;
        return false;
    }

    file << texto;

    return true;
}

void ClearScreen()
{
#ifdef _WIN32
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#else
    std::cout << "\033[2J\033[H";
#endif
}