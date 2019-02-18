#include "Client.hxx"

// конструктор по умолчанию
Client::Client(int id, std::chrono::seconds const &delay, std::string const &message) {
    _id = id;
    _delay = delay;
    _message = message;
}

// конструктор копирования
Client::Client(Client const &client) {
    _id = client._id;
    _delay = client._delay;
    _message = client._message;
}

// оператор присваивания
Client &Client::operator=(Client const &client) {
    if (this != &client) {
        _id = client._id;
        _delay = client._delay;
        _message = client._message;
    }
}

// возвращает идентификатор
int Client::id() const {
    return _id;
}

// возвращает задержку
std::chrono::seconds Client::delay() const {
    return _delay;
}

// возвращает выводимое сообщение
std::string Client::message() const {
    return _message;
}
