#include <QCoreApplication>
#include <iglmachine.h>
#include <pch.h>

IglMachine iglMachine;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc>1){
        for(int i=1;i<argc;i++){
            std::ifstream ifs;
            ifs.open (argv[i]);
            std::string line;
            while(std::getline( ifs, line )){
                std::cout << line << std::endl;
                iglMachine.command(line);
            }
        }

    }
    std::string line;
    while(std::getline( std::cin, line )){
        if(line=="exit"||line=="EXIT"||line=="quit"||line=="QUIT")break;
        if(line=="use"||line=="USE"){
            std::istringstream iss(line);
            std::string file;
            iss >> file;
            iss >> file;
            std::ifstream ifs;
            ifs.open (file);
            std::string line2;
            while(std::getline( ifs, line2 )){
                std::cout << line2 << std::endl;
                iglMachine.command(line2);
            }
        }
        iglMachine.command(line);
    }

    return a.exec();
}
