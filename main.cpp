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
    sellOrder.price = -100;
    sellOrder.amount = 5;
    sellOrder.side = Side::Sell;

    // Order sellOrder2;
    // sellOrder2.orderId = 2;
    // sellOrder2.price = 100;
    // sellOrder2.amount = 56;
    // sellOrder2.side = Side::Sell;
    //
    // Order buyOrder;
    // buyOrder.orderId = 3;
    // buyOrder.price = 100;
    // buyOrder.amount = 3;
    // buyOrder.side = Side::Buy;
    // Order buyOrder2;
    // buyOrder.orderId = 4;
    // buyOrder.price = 100;
    // buyOrder.amount = 35;
    // buyOrder.side = Side::Buy;

    client1->placeOrder(sellOrder);
    // client1->placeOrder(sellOrder2);
    //
    // client2->placeOrder(buyOrder);
    // client2->placeOrder(buyOrder2);
    // client1->cancelOrder(4);
    engine.print();


    std::this_thread::sleep_for(std::chrono::milliseconds(9000));
    engine.print();


    client1->stop();
    client2->stop();

    engine.stop();

    // TODO: Missing some considerations about destroing obj in the multi-threading env. That's why
    // there is a sigabort at the end while the system is closing, something that I could do if i had more timee

    return EXIT_SUCCESS;
}
