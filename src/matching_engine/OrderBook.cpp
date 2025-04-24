//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#include "OrderBook.h"
#include <functional>
#include <iostream>

using namespace theter::matching_engine;

OrderBook::OrderBook(Side side): m_side(side),
                                 m_ordersByPrice(
                                     side == Side::Buy
                                         ? std::function<bool(int, int)>(std::greater<int>())
                                         : std::function<bool(int, int)>(std::less<int>())
                                 ) {
}

void OrderBook::addOrder(std::unique_ptr<Order> order) {
    std::lock_guard lock(m_mutex);
    if (order->amount > 0 && m_side == order->side && !m_orderIndex.contains(order->orderId)) {
        m_orderIndex[order->orderId] = order.get();
        m_ordersByPrice[order->price].push_back(std::move(order));
        std::cout << "✅ Order inserted\n";
    } else {
        std::cout << "❌ Order rejected (amount? side match? duplicate ID?)\n";
    }
}

bool OrderBook::cancelOrder(int orderId) {
    std::lock_guard lock(m_mutex);
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

std::pair<std::list<MatchResult>, std::unique_ptr<Order> > OrderBook::match(std::unique_ptr<Order> incomingOrder) {
    std::lock_guard lock(m_mutex);
    std::list<MatchResult> results;
    int remaining = incomingOrder->amount;

    std::list<int> ordersToBeRemoved;

    for (auto priceIt = m_ordersByPrice.begin(); priceIt != m_ordersByPrice.end() && remaining > 0;) {
        if ((m_side == Side::Buy && priceIt->first > incomingOrder->price) ||
            (m_side == Side::Sell && priceIt->first < incomingOrder->price)) {
            break;
        }

        auto &orderList = priceIt->second;
        processPriceLevel(orderList, priceIt->first, incomingOrder, remaining, results, ordersToBeRemoved);

        if (orderList.empty()) {
            priceIt = m_ordersByPrice.erase(priceIt);
        } else {
            ++priceIt;
        }
    }

    if (!ordersToBeRemoved.empty())
        removeFilledOrders(ordersToBeRemoved);

    if (remaining > 0) {
        incomingOrder->amount = remaining;
        return {results, std::move(incomingOrder)};
    }

    return {results, nullptr};
}

void OrderBook::processPriceLevel(std::list<std::unique_ptr<Order> > &orderList,
                                  int price,
                                  std::unique_ptr<Order> &incomingOrder,
                                  int &remaining,
                                  std::list<MatchResult> &results,
                                  std::list<int>& ordersToBeRemoved) {
    for (auto orderIt = orderList.begin(); orderIt != orderList.end() && remaining > 0; ++orderIt) {
        auto &resting = *orderIt;
        int tradedAmount = std::min(remaining, resting->amount);

        std::cout << "Traded amount " << tradedAmount << " @ " << resting->price << "\n";
        remaining -= tradedAmount;
        resting->amount -= tradedAmount;

        MatchResult result = createMatchResult(incomingOrder, remaining, resting, tradedAmount);
        results.push_back(result);

        if (resting->amount == 0) {
            std::cout << "🗑️  Fully filled order removed → ID: " << resting->orderId << "\n";
            ordersToBeRemoved.push_back(resting->orderId);
        }
    }
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

void OrderBook::removeFilledOrders(std::list<int> orderIds) {
    for (int id : orderIds) {
        auto order = m_orderIndex[id];
        if (m_ordersByPrice.contains(order->price)) {
            auto& orderList = m_ordersByPrice[order->price];
            auto it = std::find_if(orderList.begin(), orderList.end(), [&](std::unique_ptr<Order> &item) {
                return item->orderId == id;
            });

            if (orderList.end() != it) {
                orderList.erase(it);
            }

            if (orderList.empty()) {
                m_ordersByPrice.erase(order->price);
            }
        }

        if (m_orderIndex.contains(id)) {
            m_orderIndex.erase(id);
        }
    }
}

void OrderBook::print() const {
    std::cout << (m_side == Side::Buy ? "Buy Book:\n" : "Sell Book:\n");
    for (const auto &[price, orders]: m_ordersByPrice) {
        for (const auto &order: orders) {
            std::cout << "  Order ID: " << order->orderId
                    << " | Price: " << price
                    << " | Amount: " << order->amount << '\n';
        }
    }
}
