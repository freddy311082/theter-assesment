//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "OrderBook.h"
#include <functional>


using namespace theter::matching_engine;

OrderBook::OrderBook(Side side): m_side(side),
                                 m_ordersByPrice(
                                     side == Side::Buy
                                         ? std::function<bool(int, int)>(std::greater<int>())
                                         : std::function<bool(int, int)>(std::less<int>())
                                 ) {
}

void OrderBook::addOrder(std::unique_ptr<Order> order) {
    if (order->amount > 0 && m_side == order->side && !m_orderIndex.contains(order->orderId)) {
        m_orderIndex[order->orderId] = order.get();
        m_ordersByPrice[order->price].push_back(std::move(order));
    } else {
        throw std::runtime_error("Invalid order");
    }
}

bool OrderBook::cancelOrder(int orderId) {
    auto it = m_orderIndex.find(orderId);

    if (it == m_orderIndex.end()) {
        return false;
    }

    // order founded
    Order *order = it->second;
    int price = order->price;

    auto &orderList = m_ordersByPrice[price];
    auto order_it = std::find_if(orderList.begin(), orderList.end(), [&](std::unique_ptr<Order> &item) {
        return item->orderId == orderId;
    });

    if (order_it != orderList.end())
        orderList.erase(order_it);

    if (orderList.empty())
        m_ordersByPrice.erase(price);

    m_orderIndex.erase(it);
    return true;
}

std::list<MatchResult> OrderBook::match(std::unique_ptr<Order> incomingOrder) {
    std::list<MatchResult> results;
    int remaining = incomingOrder->amount;

    for (auto priceIt = m_ordersByPrice.begin(); priceIt != m_ordersByPrice.end() && remaining > 0;) {
        if ((m_side == Side::Buy && priceIt->first > incomingOrder->price) ||
            (m_side == Side::Sell && priceIt->first < incomingOrder->price)) {
            break;
        }

        auto &orderList = priceIt->second;
        processPriceLevel(orderList, priceIt->first, incomingOrder, remaining, results);

        if (orderList.empty()) {
            priceIt = m_ordersByPrice.erase(priceIt);
        } else {
            ++priceIt;
        }
    }

    if (remaining > 0) {
        incomingOrder->amount = remaining;
        addOrder(std::move(incomingOrder));
    }

    return results;
}

MatchResult OrderBook::createMatchResult(std::unique_ptr<Order> &incomingOrder, int &remaining,
                                  std::list<std::unique_ptr<Order> >::value_type &resting, int tradedAmount) {
    MatchResult result;
    result.buyOrderId = (incomingOrder->side == Side::Buy) ? incomingOrder->orderId : resting->orderId;
    result.sellOrderId = (incomingOrder->side == Side::Sell) ? incomingOrder->orderId : resting->orderId;
    result.tradedPrice = resting->price;
    result.tradedAmount = tradedAmount;
    result.buyOrderFilled = (incomingOrder->side == Side::Buy && remaining == 0) ||
                            (incomingOrder->side == Side::Sell && resting->amount == 0);
    result.sellOrderFilled = !result.buyOrderFilled;

    return result;
}

void OrderBook::processPriceLevel(std::list<std::unique_ptr<Order> > &orderList,
                                  int price,
                                  std::unique_ptr<Order> &incomingOrder,
                                  int &remaining,
                                  std::list<MatchResult> &results) {
    for (auto orderIt = orderList.begin(); orderIt != orderList.end() && remaining > 0;) {
        auto &resting = *orderIt;

        int tradedAmount = std::min(remaining, resting->amount);
        remaining -= tradedAmount;
        resting->amount -= tradedAmount;

        MatchResult result = createMatchResult(incomingOrder, remaining, resting, tradedAmount);
        results.push_back(result);

        if (resting->amount == 0) {
            m_orderIndex.erase(resting->orderId);
            orderIt = orderList.erase(orderIt);
        } else {
            ++orderIt;
        }
    }
}
