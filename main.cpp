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

    Order buyOrder;
    buyOrder.orderId = 2;
    buyOrder.price = 100;
    buyOrder.amount = 5;
    buyOrder.side = Side::Buy;

    client1->placeOrder(sellOrder);
    client2->placeOrder(buyOrder);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    client1->stop();
    client2->stop();
    engine.stop();

    return EXIT_SUCCESS;
}
