#ifndef INTERCONNECTION_CLIENT_HXX
#define INTERCONNECTION_CLIENT_HXX

#include <string>
#include <chrono>

class Client {
public:
    Client(int id, std::chrono::seconds const &delay, std::string const & message); // конструктор по умолчанию

    Client(Client const &); // конструктор копирования

    Client &operator = (Client const &); // оператор присваивания

    ~Client() {} // деструктор

    int id() const;
    std::chrono::seconds delay() const;
    std::string message() const;

protected:
    // none

private:
    int _id; // идентификатор клиента
    std::chrono::seconds _delay; // задержка в секундах
    std::string _message; // выводимое сообщение
};


#endif //INTERCONNECTION_CLIENT_HXX
