//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <list>
#include <map>
#include <memory>

#include "../messages/matching_engine_messages/OrderTradedMsg.h"
#include "../orders/Order.h"


namespace theter::matching_engine {
    struct MatchResult {
        int buyOrderId;
        int sellOrderId;
        int tradedPrice;
        int tradedAmount;

        bool buyOrderFilled = false;
        bool sellOrderFilled = false;
    };

    class OrderBook {
    public:
        OrderBook(Side side);

        void addOrder(std::unique_ptr<Order> order);

        bool cancelOrder(int orderId);


        std::list<MatchResult> match(std::unique_ptr<Order> incomingOrder);

        Side side() const { return m_side; }

    private:
        void processPriceLevel(std::list<std::unique_ptr<Order>>& orderList,
                                   int price,
                                   std::unique_ptr<Order>& incomingOrder,
                                   int& remaining,
                                   std::list<MatchResult>& results);
        MatchResult createMatchResult(std::unique_ptr<Order> &incomingOrder, int &remaining,
                               std::list<std::unique_ptr<Order>>::value_type &resting, int tradedAmount);

        Side m_side;
        std::map<int, std::list<std::unique_ptr<Order> >, std::function<bool(int, int)> > m_ordersByPrice;
        std::unordered_map<int, Order *> m_orderIndex;


    };
}


#endif //ORDERBOOK_H
