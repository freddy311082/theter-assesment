#include <iostream>

#include "src/client/TradingClient.h"
#include "src/matching_engine/MatchingEngine.h"

int main() {
    using namespace std;
    using namespace theter::matching_engine;

    MatchingEngine engine;

    auto client1 = std::make_shared<TradingClient>();
    auto client2 = std::make_shared<TradingClient>();

    engine.registerClient(client1);
    engine.registerClient(client2);

    Order sellOrder;
    sellOrder.orderId = 1;
    sellOrder.price = 100;
    sellOrder.amount = 5;
    sellOrder.side = Side::Sell;

    Order sellOrder2;
    sellOrder2.orderId = 2;
    sellOrder2.price = 100;
    sellOrder2.amount = 56;
    sellOrder2.side = Side::Sell;
    //
    Order buyOrder;
    buyOrder.orderId = 3;
    buyOrder.price = 100;
    buyOrder.amount = 3;
    buyOrder.side = Side::Buy;

    Order buyOrder2;
    buyOrder2.orderId = 4;
    buyOrder2.price = 100;
    buyOrder2.amount = 35;
    buyOrder2.side = Side::Buy;

    Order buyOrder3;
    buyOrder3.orderId = 4;
    buyOrder3.price = 100;
    buyOrder3.amount = 35;
    buyOrder3.side = Side::Buy;

    client1->placeOrder(sellOrder);
    client1->placeOrder(sellOrder2);
    // client1->placeOrder(sellOrder2);
    //
    client2->placeOrder(buyOrder);
    client2->placeOrder(buyOrder2);
    client2->placeOrder(buyOrder3);
    client2->cancelOrder(4);
    engine.print();


    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    engine.print();


    client1->stop();
    client2->stop();


    // TODO: Missing some considerations about destroing obj in the multi-threading env. That's why
    // there is a sigabort at the end while the system is closing, something that I could do if i had more timee

    return EXIT_SUCCESS;
}
