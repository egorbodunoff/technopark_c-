#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "units/crew_members.hpp"
#include "units/passengers.hpp"
#include "units/plane.hpp"

void addEconomyLuggageToPassenger(std::shared_ptr<EconomyPassenger> passenger,
                                  const std::vector<int>& luggage) {
    if (!luggage.empty()) {
        passenger->addHandLuggage(luggage[0]);  // первый элемент — ручная кладь
    }
    if (luggage.size() > 1) {
        passenger->addLuggage(luggage[1]);  // второй элемент — багаж
    }
}

void addLuggageToPassenger(std::shared_ptr<Passenger> passenger, const std::vector<int>& luggage) {
    if (!luggage.empty()) {
        passenger->addHandLuggage(luggage[0]);  // ручная кладь
    }
    if (luggage.size() > 1) {
        passenger->addHandLuggage(luggage[1]);  // дополнительная ручная кладь
    }
    if (luggage.size() > 2) {
        passenger->addLuggage(luggage[2]);  // багаж
    }
    if (luggage.size() > 3) {
        passenger->addLuggage(luggage[3]);  // дополнительный багаж
    }
}

std::shared_ptr<Passenger> createPassenger(const std::string& passengerType, int id,
                                           const std::vector<int>& luggage) {
    std::shared_ptr<Passenger> passenger = nullptr;
    if (passengerType == "ECONOMY") {
        passenger = std::make_shared<EconomyPassenger>(id);
        addEconomyLuggageToPassenger(std::dynamic_pointer_cast<EconomyPassenger>(passenger), luggage);
    } else if (passengerType == "BUSINESS") {
        passenger = std::make_shared<BusinessPassenger>(id);
        addLuggageToPassenger(passenger, luggage);
    } else if (passengerType == "FIRST_CLASS") {
        passenger = std::make_shared<FirstClassPassenger>(id);
        addLuggageToPassenger(passenger, luggage);
    }

    return passenger;
}

int main() {
    int maxFirstClassWeight, maxBusinessClassWeight, maxEconomyClassWeight;
    std::vector<std::shared_ptr<Unit>> units;

    std::string segmentType;
    std::cin >> segmentType >> maxFirstClassWeight;
    std::cin >> segmentType >> maxBusinessClassWeight;
    std::cin >> segmentType >> maxEconomyClassWeight;

    Plane plane(maxFirstClassWeight, maxBusinessClassWeight, maxEconomyClassWeight);

    int luggage, handLuggage;
    std::string crewMemberType;
    for (int i = 0; i < 8; ++i) {
        std::cin >> crewMemberType >> luggage >> handLuggage;
        if (crewMemberType == "PILOT") {
            units.push_back(std::make_shared<Pilot>(i + 1));
        } else if (crewMemberType == "FLIGHT_ATTENDANT") {
            units.push_back(std::make_shared<Steward>(i + 1));
        }
    }

    int i = 8;
    std::string passengerType;
    while (std::cin >> passengerType) {
        std::vector<int> luggage;
        int luggageWeight;
        std::string input;

        std::getline(std::cin, input);
        std::stringstream ss(input);

        while (ss >> luggageWeight) {
            luggage.push_back(luggageWeight);
        }

        auto passenger = createPassenger(passengerType, i, luggage);

        if (passenger != nullptr) {
            plane.boardUnit(passenger);
        }

        i++;
    }

    plane.printSegmentDetails();

    return 0;
}
