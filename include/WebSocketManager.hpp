#pragma once

#include <string>

using string = std::string;

class WebSocketManager {
private:
    string urlBase;
    string apiKey;

public:
    explicit WebSocketManager(string urlBase, string apiKey);

    void establishConnection();
    void disconnectConnection();
};