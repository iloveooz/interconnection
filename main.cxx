#include <iostream>
#include "Server.hxx"
#include "Client.hxx"

int main(int argc, char ** argv) {

    std::cout << "Simple chat, v. 0.1" << '\n';

    int clients = std::atoi(argv[2]);

    if ((argc <= 4) || (clients * 2 + 3) != argc) {
        std::cout << "Использование программы:" << '\n';
        std::cout << argv[0] << " (путь к файлу) (количество клиентов) ";
        std::cout
                << "(задержка первого клиента) (выводимое им сообщение) (задержка второго клиента) (выводимое им сообщение) "
                << '\n';
        return 0;
    }

        // запуск сервера с указанием пути до файла:
        Server server(argv[1]);

        // инициализация клиентов:
        for (int i = 3; i < argc; i += 2) {
            auto const delayS = std::chrono::seconds{atol(argv[i])};
            std::string tempMessage = argv[i + 1];
            server.createClient(delayS, tempMessage);
        }

        server.work();

    return 0;
}