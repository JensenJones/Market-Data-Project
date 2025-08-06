//
// Created by Jensen Jones on 31/7/2025.
//

#include "WebSocketManager.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


WebSocketManager::WebSocketManager(string urlBase_,
                                   string apiKey_): urlBase{std::move( urlBase_ )},
                                                    apiKey{std::move( apiKey_ )} {}

void WebSocketManager::establishConnection() {

}

