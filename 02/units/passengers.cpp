#include "passengers.hpp"

#include <iostream>
#include <limits>

Passenger::Passenger(int id, const std::string& type, int maxHandLuggage, int maxLuggage, int maxItems)
    : Unit(id, type),
      maxHandLuggageWeight(maxHandLuggage),
      maxLuggageWeight(maxLuggage),
      maxLuggageItems(maxItems) {}

bool Passenger::canAddHandLuggage(int weight) const {
    // std::cout << luggageWeights.size() << std::endl;
    return (getTotalHandLuggageWeight() + weight <= maxHandLuggageWeight &&
            (handLuggageWeights.size() < maxLuggageItems));
}

bool Passenger::canAddLuggage(int weight) const {
    return (getTotalLuggageWeight() + weight <= maxLuggageWeight) &&
           (luggageWeights.size() < maxLuggageItems);
}

void Passenger::addHandLuggage(int weight) {
    if (canAddHandLuggage(weight)) {
        handLuggageWeights.push_back(weight);
    } else {
        std::cout << "!!CANT REGISTER " << type << " HAND LUGGAGE, ID = " << id << "!!" << std::endl;
    }
}

void Passenger::addLuggage(int weight) {
    if (canAddLuggage(weight)) {
        luggageWeights.push_back(weight);
    } else {
        std::cout << "!!CANT REGISTER " << type << " LUGGAGE, ID = " << id << "!!" << std::endl;
    }
}

EconomyPassenger::EconomyPassenger(int id) : Passenger(id, "ECONOMY", 10, 24, 1) {}

BusinessPassenger::BusinessPassenger(int id) : Passenger(id, "BUSINESS", 24, 40, 2) {}

FirstClassPassenger::FirstClassPassenger(int id)
    : Passenger(id, "FIRST_CLASS", 60, std::numeric_limits<int>::max(), 2) {}
