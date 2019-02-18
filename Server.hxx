#ifndef INTERCONNECTION_SERVER_HXX
#define INTERCONNECTION_SERVER_HXX

#include <string>
#include <fstream>
#include <chrono>

#include <list>

#include "Client.hxx"

class Server {
public:
    Server(std::string const & path); // конструктор по умолчанию

    void createClient(std::chrono::seconds delay, std::string &message); // добавление клиента на сервер

    void work(); // цикл работы сервера

    void write(Client const & client); // запись сообщений клиентов в файл


    void update(std::chrono::seconds elapsed_time); // сколько прошло времени, сообщается клиентам
    void sort();

    std::chrono::seconds getDelay() const;

    ~Server(); // деструктор

protected:
    // none

private:
    Server(Server const &); // КК
    Server& operator=(Server const &); // ОП

    std::list <Client> _clients;

    std::chrono::seconds _optDelay {0};
    std::chrono::seconds _elapsed {0};

    int _maxID = 0;

    std::ofstream _file;
    std::string _path;

    std::chrono::seconds NOD(std::chrono::seconds a, std::chrono::seconds b) const;
};


#endif //INTERCONNECTION_SERVER_HXX
