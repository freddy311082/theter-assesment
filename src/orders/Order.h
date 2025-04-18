//
// Created by Freddy Martinez Garcia on 18/04/2025.
//

#ifndef ORDER_H
#define ORDER_H

namespace theter::matching_engine {
    enum class Side {
        Buy,
        Sell
    };

    struct Order {
        int orderId;
        int price;
        int amount;
        Side side;
    };

}



#endif //ORDER_H
