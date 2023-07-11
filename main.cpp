#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <filesystem>
#include <string>
#include <cstring>
#include <locale>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <fileapi.h>
#include <dirent.h>
using namespace std;

BOOL DiretorioExiste(LPCTSTR caminho) //verifica se o diretorio existe
{
  DWORD dwAttrib = GetFileAttributes(caminho);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void deletar_conteudo_dir(string caminho){//deleta o conte�do do diretorio
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (caminho.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string name = ent->d_name;
            if(name != "." && name != ".."){
                string fullPath = caminho + "\\" + name;
                if(DiretorioExiste(fullPath.c_str())){
                    deletar_conteudo_dir(fullPath);
                    RemoveDirectoryA(fullPath.c_str());
                } else {
                    DeleteFileA(fullPath.c_str());
                }
            }
        }
        closedir (dir);
    }
}

BOOL Arq_existe(LPCTSTR caminho)//verifica se o arquivo existe
{
  DWORD dwAttrib = GetFileAttributes(caminho);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         (dwAttrib & FILE_ATTRIBUTE_ARCHIVE));
}

int main()
{
    setlocale(LC_ALL,"portuguese");
    char funcao[100];
    for(;;){
    cin>>funcao;
        if(strcmp(funcao, "SAIR") == 0){
        break;
    }
        if(strcmp(funcao, "LIMPAR") == 0){
        system("clear||cls");
    }
        if(strcmp(funcao, "CRIAR") == 0){
            cout<<"Deseja criar um diretorio (d), ou um arquivo (a)?"<<endl;
            char DouA;
            cin>>DouA;

            if (DouA == 'd'){
                string filePath;
                cout << "Digite o caminho do arquivo: "<<endl;
                cin >> filePath;
                string strn1 = "mkdir ";
                strn1.append(filePath); //concatena strn1 e filepath
                    if(DiretorioExiste(strn1.c_str())){
                    puts("O diret�rio existe!");
                    break;
                    }
                std::system(strn1.c_str());
                cout<<"Arquivo criado com sucesso"<<endl;
            }
            if(DouA == 'a'){
                cout<<"Qual o endere�o"<<endl;
                string filePath;
                cout << "Digite o caminho do arquivo:"<<endl;
                cin >> filePath;
                ofstream MyFile(filePath.c_str());
                cout << "Diretorio criado com sucesso"<<endl;
            }
        }
        if(strcmp(funcao,"INSERIR") == 0 ){

            string filePath;
            cout << "Digite o caminho do arquivo: ";
            cin >> filePath;

            cout<<"Digite o texto que dever� ser inserido"<<endl;
            string txt;
            cin.ignore(); // limpa o buffer
            std::getline(cin,txt); //funcao para ler espaco na string
            ofstream arq;
            arq.open(filePath.c_str());
            arq<<txt;
            cout<<"Texto inserido com sucesso"<<endl;
        }
        if(strcmp(funcao,"APAGAR") == 0 ){
            int ver=0;
            cout<<"Deseja apagar um diretorio (d), ou um arquivo (a)?"<<endl;
            char DouA;
            cin>>DouA;
            if (DouA == 'd'){
                int ver=0;
                string filePath;
                cout << "Digite o caminho do arquivo: ";
                cin >> filePath;
                if(!DiretorioExiste(filePath.c_str())){
                    puts("O diret�rio n�o existe!\n");
                    ver++;
                }
                RemoveDirectoryA(LPCSTR (filePath.c_str()));
                cout<<"Arquivo deletado com sucesso"<<endl;
                if(ver = 0){
                    if(!DiretorioExiste(filePath.c_str())){
                    puts("Diret�rio apagado!\n");
                    }
                }
            }

            if (DouA == 'a'){
                string filePath;
                cout << "Digite o caminho do arquivo: ";
                cin >> filePath;
                if(DeleteFileA(LPCSTR(filePath.c_str())))
                    cout<<"Arquivo deletado com sucesso";
                else if(!Arq_existe(filePath.c_str())){
                    puts("Arquivo n�o existe!\n");
                }
            }
        }
        if(strcmp(funcao,"DATA") == 0 ){

        std::time_t currentTime = std::time(nullptr); // Obt�m o tempo atual
        std::tm* localTime = std::localtime(&currentTime);  // Converte o tempo atual para uma estrutura tm
        std::cout << "Data atual: " << (localTime->tm_mday) << "/"    // Imprime a data formatada
              << (localTime->tm_mon + 1) << "/"
              << (localTime->tm_year + 1900) << std::endl;
    }
        if(strcmp(funcao,"HORA") == 0){
            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime); // Converte o tempo atual para uma estrutura tm

            std::cout << "Hora atual: " << (localTime->tm_hour) << ":" // Imprime a hora formatada
            << (localTime->tm_min) << ":"
            << (localTime->tm_sec) << std::endl;

    }
        if(strcmp(funcao,"VER") == 0){ //verifica versao windows
            OSVERSIONINFOEX osVersion;
            ZeroMemory(&osVersion, sizeof(OSVERSIONINFOEX));
            osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

            if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&osVersion))) {
                std::cout << "Vers�o do Windows: " << osVersion.dwMajorVersion << "."
                << osVersion.dwMinorVersion << " (Build " << osVersion.dwBuildNumber << ")" << std::endl;
            } else {
                std::cout << "N�o foi poss�vel obter a vers�o do Windows." << std::endl;
            }
        }
        if(strcmp(funcao,"AJUDA") == 0){
        cout<<"CRIAR = Cria um arquivo ou diret�rio "<<endl;
        cout<<"INSERIR = Insere um texto em um arquivo."<<endl;
        cout<<"LISTAR = Lista arquivos e diret�rios da pasta."<<endl;
        cout<<"APAGAR = Apaga um arquivo ou diret�rio."<<endl;
        cout<<"RENOMEAR = Renomeia um arquivo ou diret�rio."<<endl;
        cout<<"MOVER = Move um arquivo ou diret�rio."<<endl;
        cout<<"DELETAR = Deleta um arquivo ou diret�rio."<<endl;
        cout<<"AJUDA = Lista todos os comandos juntamente com descri��es."<<endl;
        cout<<"VER = Imprime a vers�o do sistema operacional."<<endl;
        cout<<"DATA = Imprime a data do sistema operacional."<<endl;
        cout<<"HORA = Imprime a hora do sistema operacional"<<endl;
        cout<<"LIMPAR = Limpa o conte�do atual da tela."<<endl;
        cout<<"SAIR = Finaliza o programa."<<endl;
     }
        if(strcmp(funcao,"MOVER") == 0){
            cout << "Deseja mover um arquivo (a) ou um diret�rio (d)?" << endl;
            char DouA;
            cin >> DouA;
            if (DouA == 'a' || DouA == 'd'){
                string oldPath, newPath;
                cout << "Digite o caminho atual do arquivo/diret�rio: "<<endl;
                cin >> oldPath;
                cout << "Digite o novo caminho do arquivo/diret�rio: "<<endl;
                cin >> newPath;
                if(rename(oldPath.c_str(), newPath.c_str()) == 0){
                    cout << "Arquivo/diret�rio movido com sucesso!" << endl;
                } else {
                    cout << "Erro ao mover arquivo/diret�rio." << endl;
                }
            }
        }
        if(strcmp(funcao,"RENOMEAR") == 0){
            cout << "Deseja renomear um arquivo (a) ou um diret�rio (d)?" << endl;
            char DouA;
            cin >> DouA;
            if (DouA == 'a' || DouA == 'd'){
                string oldName, newName;
                string filePath;
                cout << "Digite o local do arquivo: ";
                cin >> filePath;
                cout << "Digite o nome atual do arquivo/diret�rio: "<<endl;
                cin >> oldName;
                cout << "Digite o novo nome do arquivo/diret�rio: "<<endl;
                cin >> newName;
                oldName = filePath + oldName;
                newName = filePath + newName;
                if(rename(oldName.c_str(), newName.c_str()) == 0){
                    cout << "Arquivo/diret�rio renomeado com sucesso!" << endl;
                } else {
                    cout << "Erro ao renomear arquivo/diret�rio." << endl;
                }
            }
        }
        if(strcmp(funcao,"LISTAR") == 0){
            string caminho;
            cout << "Digite o caminho do diret�rio: "<<endl;
            cin >> caminho;
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir (caminho.c_str())) != NULL) {
                while ((ent = readdir (dir)) != NULL) {
                    string name = ent->d_name;
                    if(name != "." && name != ".."){
                        string fullPath = caminho + "\\" + name;
                        if(DiretorioExiste(fullPath.c_str())){
                            cout << name << " [diret�rio]" << endl;
                        } else {
                            cout << name << " [arquivo]" << endl;
                        }
                    }
                }
            closedir (dir);
            } else {
                cout << "Erro ao abrir o diret�rio." << endl;
            }
        }
        if(strcmp(funcao,"DELETAR") == 0){
            cout << "Deseja deletar o conte�do de um arquivo (a) ou de um diret�rio (d)?" << endl;
            char DouA;
            cin >> DouA;
            if (DouA == 'a'){
                string filePath;
                cout << "Digite o caminho do arquivo: "<<endl;
                cin >> filePath;
                ofstream ofs(filePath, ios::trunc);
                ofs.close();
                cout << "Conte�do do arquivo deletado com sucesso!" << endl;
            } else if (DouA == 'd'){
                string dirPath;
                cout << "Digite o caminho do diret�rio: "<<endl;
                cin >> dirPath;
                deletar_conteudo_dir(dirPath);
                cout << "Conte�do do diret�rio deletado com sucesso!" << endl;
            }
        }

    }
    return 0;
}
