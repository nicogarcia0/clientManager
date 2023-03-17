#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <windows.h>


// Variables
std::string adminName;
std::string adminMail;
std::string adminTelf;
std::string user;
std::string configFileDirW32; 
std::string createConfigDirW32;
std::string createClientDirW32;
std::string configFileDir2W32;
std::string clientFileDirW32;
std::string tempSelect;
std::string clientName;
std::string clientTelf;
std::string clientMail;
std::string clientDelete;
std::string confirmation;

// Functions
int clientHandle(std::string selection){
    if(selection == "1"){
        system("cls");
        std::cout << "Crear entrada de cliente \n";
        std::cout << "Introduce el nombre completo del cliente \n";
        std::getline(std::cin, clientName);
        std::cout << "Introduce el numero de telefono del cliente \n";
        std::getline(std::cin, clientTelf);
        std::cout << "Introduce el email del cliente \n";
        std::getline(std::cin, clientMail);
        std::cout << "Creando archivo del ciente \n";
        std::ofstream clientData(clientFileDirW32 + "\\" + clientTelf + ".cmg");
        clientData << clientName << "\n" << clientTelf << "\n" << clientMail;
        clientData.close();
        std::cout << "Almacenado correctamente \n";


    }else if (selection == "2"){
        system("cls");
        std::cout << "Borrar entrada de cliente\n";
        std::cout << "Introduce el numero de telefono del cliente a eliminar\n";
        std::getline(std::cin, clientTelf);
        std::ifstream clientData(clientFileDirW32 + "\\" + clientTelf + ".cmg");
        if(clientData.is_open()){
            clientDelete = "del /F /Q " + clientFileDirW32 + "\\" + clientTelf + ".cmg";
            clientData.close();
            system(clientDelete.c_str());
            std::cout << "Cliente eliminado correctamente \n";
        }else{
            std::cout << "Cliente no encontrado.";
        }

    }else if (selection == "3"){
        std::cout << "Buscar informacion de un cliente \n";
        std::cout << "Introduce el numero de telefono del cliente a buscar\n";
        std::getline(std::cin, clientTelf);
        std::ifstream clientData(clientFileDirW32 + "\\" + clientTelf + ".cmg");
        if(!clientData.is_open()){
            std::cout << "No se ha encontrado el cliente\n";
            exit(1);
        }
        std::getline(clientData, clientName);
        std::getline(clientData, clientTelf);
        std::getline(clientData, clientMail);
        system("cls");
        std::cout << "Cliente encontrado: \n" << "Nombre: " + clientName + "\nTelefono: " + clientTelf + "\nEmail: " + clientMail + "\n";
    }    
    return 0;
}

int mainMenuW32(){
    system("cls");
    clientName = "";
    clientTelf = "";
    clientMail = "";
    tempSelect = "";
    std::ifstream configFileW32(configFileDirW32);
    std::getline(configFileW32, adminName);
    std::getline(configFileW32, adminTelf);
    std::getline(configFileW32, adminMail);
    std::cout << "Bienvenido " + adminName <<  "\n";
    std::cout << "Que desea hacer? \n";
    std::cout << "1 - Crear entrada de cliente \n" << "2 - Borrar entrada de cliente \n" << "3 -  Mostrar informacion de un cliente \n";
    std::getline(std::cin, tempSelect);
    if(tempSelect == "1" || tempSelect == "2" || tempSelect == "3"){
        system("cls");
        clientHandle(tempSelect);
    }else{
        system("cls");
        std::cout << "No es ninguna seleccion valida \n";
    }

    return 0;
}



int w32(){
    std::cout << "Bienvenido a clientManager \n";
    // Comprobacion inicial windows
    std::ifstream stConfig("stConfig.cmg");
    if(!stConfig.is_open()){
        std::cout << "Introduce el usuario en el que deseas almacenar la configuracion (Windows) \n";
        std::cin >> user;
        stConfig.close();
        std::ofstream stConfig("stConfig.cmg");
        stConfig << user;
        stConfig.close();
         configFileDir2W32 = "C:\\Users\\" + user + "\\AppData\\Roaming\\clientManager";
        configFileDirW32 = "C:\\Users\\" + user + "\\AppData\\Roaming\\clientManager\\configFile.cmg";
    }else{
        std::getline(stConfig, user);
        configFileDir2W32 = "C:\\Users\\" + user + "\\AppData\\Roaming\\clientManager";
        clientFileDirW32 = "C:\\Users\\" + user + "\\AppData\\Roaming\\clientManager\\clients";
        configFileDirW32 = "C:\\Users\\" + user + "\\AppData\\Roaming\\clientManager\\configFile.cmg";
        stConfig.close();

    }
    std::ifstream configFileW32(configFileDirW32);
    if(!configFileW32.is_open()){
        configFileW32.close();

        std::cout << "Configuracion inicial no encontrada.\n";
        std::cout << "Introduce tu nombre completo\n";
        std::getline(std::cin, adminName);
        std::cout << "Introduce tu numero de telefono\n";
        std::getline(std::cin, adminTelf);
        std::cout << "Introduce tu mail\n";
        std::getline(std::cin, adminMail);
        system("cls");
        createConfigDirW32 = "mkdir " + configFileDir2W32;
        createClientDirW32 = "mkdir " + clientFileDirW32;
        system(createConfigDirW32.c_str());
        system(createClientDirW32.c_str());
        std::cout << "Creando archivo de configuracion\n";
    std::ofstream configFileW32(configFileDirW32);        
    if(!configFileW32.is_open()){
            std::cout << configFileDirW32 << "\n" << user;
            std::cout << "No se ha podido crear el archivo de configuracion\n";
            exit(1);
        }else{
            std::cout << "Creado correctamente, almacenando informacion\n";
            configFileW32 << adminName + "\n" + adminTelf + "\n" + adminMail + "\n";
            configFileW32.close();
            std::cout << "Almacenada correctamente.\n";
        }
    }
    mainMenuW32();
    return 0;
}
// Main function

int main(){
    // Comprobacion de sistema operativo
    #ifdef _WIN32
    w32();
    #elif 
    std::cout << "El sistema operativo detectado no es soportado por clientManager\n";
    #endif
    return 0;
}