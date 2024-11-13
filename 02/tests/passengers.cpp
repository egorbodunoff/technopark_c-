#include "../units/passengers.hpp"

#include <cassert>
#include <iostream>
#include <limits>

void test_Passenger_basic_properties() {
    Passenger passenger(1, "PASSENGER", 20, 40, 2);
    assert(passenger.getId() == 1);
    assert(passenger.getType() == "PASSENGER");
    assert(passenger.canAddHandLuggage(10));
    assert(passenger.canAddLuggage(30));
}

void test_EconomyPassenger_properties() {
    EconomyPassenger economy(2);
    assert(economy.getId() == 2);
    assert(economy.getType() == "ECONOMY");
    assert(economy.canAddHandLuggage(10));  // Максимум для эконома: 10 кг
    assert(economy.canAddLuggage(24));      // Максимум для эконома: 24 кг
}

void test_BusinessPassenger_properties() {
    BusinessPassenger business(3);
    assert(business.getId() == 3);
    assert(business.getType() == "BUSINESS");
    assert(business.canAddHandLuggage(24));  // Максимум для бизнеса: 24 кг
    assert(business.canAddLuggage(40));      // Максимум для бизнеса: 40 кг
}

void test_FirstClassPassenger_properties() {
    FirstClassPassenger firstClass(4);
    assert(firstClass.getId() == 4);
    assert(firstClass.getType() == "FIRST_CLASS");
    assert(firstClass.canAddHandLuggage(60));  // Максимум для первого класса: 60 кг
    assert(firstClass.canAddLuggage(1000));
}

void test_add_hand_luggage_for_all() {
    EconomyPassenger economy(2);
    BusinessPassenger business(3);
    FirstClassPassenger firstClass(4);

    economy.addHandLuggage(10);
    business.addHandLuggage(24);
    firstClass.addHandLuggage(60);

    assert(economy.getTotalHandLuggageWeight() == 10);
    assert(business.getTotalHandLuggageWeight() == 24);
    assert(firstClass.getTotalHandLuggageWeight() == 60);

    assert(economy.canAddHandLuggage(15) == false);
    assert(business.canAddHandLuggage(25) == false);
    assert(firstClass.canAddHandLuggage(65) == false);
}

void test_add_luggage_for_all() {
    EconomyPassenger economy(2);
    BusinessPassenger business(3);
    FirstClassPassenger firstClass(4);

    economy.addLuggage(24);
    business.addLuggage(40);
    firstClass.addLuggage(1000);

    assert(economy.getTotalLuggageWeight() == 24);
    assert(business.getTotalLuggageWeight() == 40);
    assert(firstClass.getTotalLuggageWeight() == 1000);

    assert(economy.canAddLuggage(30) == false);
    assert(business.canAddLuggage(45) == false);
    assert(firstClass.canAddLuggage(1100) == true);
}

void test_luggage_overflow_for_all() {
    EconomyPassenger economy(2);
    BusinessPassenger business(3);
    FirstClassPassenger firstClass(4);

    economy.addHandLuggage(15);     // Не должно добавиться
    business.addHandLuggage(30);    // Не должно добавиться
    firstClass.addHandLuggage(70);  // Не должно добавиться

    assert(economy.getTotalHandLuggageWeight() == 0);
    assert(business.getTotalHandLuggageWeight() == 0);
    assert(firstClass.getTotalHandLuggageWeight() == 0);

    economy.addLuggage(30);   // Не должно добавиться
    business.addLuggage(50);  // Не должно добавиться
    firstClass.addLuggage(1100);

    assert(economy.getTotalLuggageWeight() == 0);
    assert(business.getTotalLuggageWeight() == 0);
    assert(firstClass.getTotalLuggageWeight() == 1100);
}

void test_passenger_total_baggage_and_luggage() {
    Passenger passenger(9, "PASSENGER", 30, 60, 2);

    passenger.addHandLuggage(10);
    passenger.addLuggage(30);

    assert(passenger.getTotalHandLuggageWeight() == 10);
    assert(passenger.getTotalLuggageWeight() == 30);

    passenger.addLuggage(35);
    assert(passenger.getTotalLuggageWeight() == 30);

    passenger.addHandLuggage(25);
    assert(passenger.getTotalHandLuggageWeight() == 10);
}

// Тест на корректность работы метода для максимального багажа
void test_max_baggage_item_limits() {
    EconomyPassenger economy(5);
    BusinessPassenger business(6);
    FirstClassPassenger firstClass(7);

    economy.addLuggage(5);
    assert(economy.canAddLuggage(5) == false);

    business.addLuggage(5);
    business.addLuggage(5);
    assert(business.canAddLuggage(5) == false);

    firstClass.addLuggage(5);
    firstClass.addLuggage(5);
    assert(firstClass.canAddLuggage(5) == false);
}

void test_max_handle_item_limits() {
    EconomyPassenger economy(5);
    BusinessPassenger business(6);
    FirstClassPassenger firstClass(7);

    economy.addHandLuggage(5);
    assert(economy.canAddHandLuggage(5) == false);

    business.addHandLuggage(5);
    business.addHandLuggage(5);
    assert(business.canAddHandLuggage(5) == false);

    firstClass.addHandLuggage(5);
    firstClass.addHandLuggage(5);
    assert(firstClass.canAddHandLuggage(5) == false);
}

int main() {
    test_Passenger_basic_properties();
    test_EconomyPassenger_properties();
    test_BusinessPassenger_properties();
    test_FirstClassPassenger_properties();

    test_add_hand_luggage_for_all();
    test_add_luggage_for_all();
    test_luggage_overflow_for_all();
    test_passenger_total_baggage_and_luggage();

    test_max_baggage_item_limits();
    test_max_handle_item_limits();

    std::cout << "All tests passed" << std::endl;
    return 0;
}
