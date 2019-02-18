#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>

#include "Server.hxx"
#include "Client.hxx"

Server::Server(std::string const &path) :
    _file(path),
    _path(path)
    {}

void Server::createClient(std::chrono::seconds delay, std::string &message) {
    _clients.emplace_back(Client(_maxID, delay, message));
    _maxID++;
    sort();
    _optDelay = _optDelay != std::chrono::seconds{0} ? NOD(_optDelay, delay) : delay;
}

void Server::work() {
    std::chrono::seconds const optTime = getDelay();

    while (true) {
        std::this_thread::sleep_for(optTime);

        update(optTime);

        std::list <Client> result;
        for (auto const client : _clients) {
            if (_elapsed % client.delay() == std::chrono::seconds{0}) {
                result.push_back(client);
            }
            if (client.delay() >= _elapsed) {
                break;
            }
        }

        for (auto const &client : result) {
            write(client);
        }
    }
}

void Server::write(const Client &client) {
    auto const time_now = std::chrono::system_clock::now();
    auto const time_now_c = std::chrono::system_clock::to_time_t(time_now);

    _file.open(_path, std::ios_base::app);
    _file  << std::put_time(localtime(&time_now_c), "%T") << "; " << client.id() << ": " << client.message() << '\n';
    _file.close();
}

void Server::update(std::chrono::seconds elapsed_time) {
    if (!_clients.empty()) {
        auto const max_delay_s = _clients.crbegin()->delay();
        if (_elapsed > max_delay_s) {
            elapsed_time += _elapsed - max_delay_s;
            _elapsed = std::chrono::seconds{0};
        }

        _elapsed += elapsed_time;
    }
}

std::chrono::seconds Server::getDelay() const {
    return _optDelay;
}

void Server::sort() {
    auto const by_delay = [] (Client const &l, Client const &r) {
        return l.delay() < r.delay();
    };
    _clients.sort(by_delay);
}

std::chrono::seconds Server::NOD(std::chrono::seconds a, std::chrono::seconds b) const {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

Server::~Server() {}