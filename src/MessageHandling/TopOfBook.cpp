#include "../../include/MessageHandling/TopOfBook.hpp"

#include <utility>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// payload:
// {
//     "u":400900217,     // order book updateId    // int
//     "s":"BNBUSDT",     // symbol                 // string
//     "b":"25.35190000", // best bid price         // double
//     "B":"31.21000000", // best bid qty           // ..
//     "a":"25.36520000", // best ask price         // ..
//     "A":"40.66000000"  // best ask qty           // ..
//   }

double as_double(const json& j, const std::string& key) {
    return std::stod(j.at(key).get<std::string>());
}

TopOfBook::TopOfBook(const json& marketMessage) : updateId( marketMessage.at("u").get<int64_t>() ),
                                         symbol( marketMessage.at("s").get<std::string>()){
    bestBid.set_price(as_double(marketMessage, "b"));
    bestBid.set_quantity(as_double(marketMessage, "B"));
    bestAsk.set_price(as_double(marketMessage, "a"));
    bestAsk.set_quantity(as_double(marketMessage, "A"));
}

TopOfBook::TopOfBook(const uint64_t updateId, std::string symbol, const Order &bestBid, const Order &bestAsk): updateId(updateId),
                                                                                                               symbol(std::move(symbol)),
                                                                                                               bestBid(bestBid),
                                                                                                               bestAsk(bestAsk) {
}

std::ostream & operator<<(std::ostream &os, const TopOfBook &obj) {
    return os
           << "updateId: " << obj.updateId << ", symbol: " << obj.symbol << '\n'
           << "Top of order book: " << obj.bestBid << " | " << obj.bestAsk;
}
