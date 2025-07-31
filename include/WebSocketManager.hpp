#ifndef WEBSOCKETMANAGER_HPP
#define WEBSOCKETMANAGER_HPP
#include <string>
using string = std::string;

class WebSocketManager {
private:
    string url;

public:
    explicit WebSocketManager(const string& url);

    void establishConnection();
    void disconnectConnection();
};

#endif //WEBSOCKETMANAGER_HPP
