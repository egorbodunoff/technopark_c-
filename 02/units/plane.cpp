#include "plane.hpp"

#include <algorithm>
#include <iostream>

PlaneSegment::PlaneSegment(int maxWeight) : maxTotalWeight(maxWeight) {}

bool PlaneSegment::canAddLuggage(int weight) const {
    return (getCurrentLuggageWeight() + weight + getCurrentHandLuggageWeight()) <= maxTotalWeight;
}

void PlaneSegment::addLuggage(int weight, int passengerID) {
    if (canAddLuggage(weight)) {
        luggage.emplace_back(weight, passengerID);
    }
}

void PlaneSegment::addHandLuggage(int weight, int passengerID) {
    if (canAddLuggage(weight)) {
        handLuggage.emplace_back(weight, passengerID);
    }
}

bool PlaneSegment::isOverloaded() const { return getCurrentTotalWeight() >= maxTotalWeight; }

bool PlaneSegment::removeMinLuggageUnits(int requiredWeight,
                                         std::unordered_map<int, std::shared_ptr<Passenger>> passengers) {
    int weightToRemove = requiredWeight;
    std::vector<std::pair<int, int>> removedLuggage;

    std::sort(luggage.begin(), luggage.end(), [](const auto& a, const auto& b) { return a.first > b.first; });

    for (auto it = luggage.begin(); it != luggage.end() && weightToRemove > 0;) {
        int passengerID = it->second;
        if (passengers[passengerID]->getType() == "ECONOMY") {
            weightToRemove -= it->first;
            removedLuggage.push_back(*it);
            it = luggage.erase(it);
            // std::cout << "!!PASSENGER’S LUGGAGE REMOVED FROM FLIGHT, ID = " << passengerID << "!!" <<
            // std::endl;
        } else {
            ++it;
        }
    }
    if (weightToRemove > 0) {
        for (const auto& item : removedLuggage) {
            luggage.push_back(item);
        }
        return false;
    }
    for (const auto& item : removedLuggage) {
        int passengerID = item.second;
        std::cout << "!!PASSENGER’S LUGGAGE REMOVED FROM FLIGHT, ID = " << passengerID << "!!" << std::endl;
    }

    return true;
}

int PlaneSegment::getCurrentLuggageWeight() const {
    int totalWeight = 0;
    for (const auto& item : luggage) {
        totalWeight += item.first;
    }
    return totalWeight;
}

int PlaneSegment::getCurrentHandLuggageWeight() const {
    int totalWeight = 0;
    for (const auto& item : handLuggage) {
        totalWeight += item.first;
    }
    return totalWeight;
}

int PlaneSegment::getCurrentTotalWeight() const {
    return getCurrentLuggageWeight() + getCurrentHandLuggageWeight();
}

int PlaneSegment::getMaxTotalWeight() const { return maxTotalWeight; }

Plane::Plane(int maxFirstClassWeight, int maxBusinessClassWeight, int maxEconomyClassWeight)
    : firstClassSegment(maxFirstClassWeight),
      businessClassSegment(maxBusinessClassWeight),
      economyClassSegment(maxEconomyClassWeight) {}

bool Plane::tryAddPassengerToSegment(PlaneSegment& segment, std::shared_ptr<Passenger> passenger) {
    int luggageWeight = passenger->getTotalLuggageWeight();
    int handLuggageWeight = passenger->getTotalHandLuggageWeight();
    int totalWeight = luggageWeight + handLuggageWeight;

    if (!segment.canAddLuggage(totalWeight)) {
        if (passenger->getType() == "BUSINESS" || passenger->getType() == "FIRST_CLASS") {
            int availableSpaceInEconomy =
                economyClassSegment.getMaxTotalWeight() - economyClassSegment.getCurrentTotalWeight();

            if (totalWeight <= availableSpaceInEconomy) {
                economyClassSegment.addLuggage(luggageWeight, passenger->getId());
                economyClassSegment.addHandLuggage(handLuggageWeight, passenger->getId());
                return true;
            } else {
                int requiredWeight = totalWeight - availableSpaceInEconomy;

                if (economyClassSegment.removeMinLuggageUnits(requiredWeight, passengers)) {
                    economyClassSegment.addLuggage(luggageWeight, passenger->getId());
                    economyClassSegment.addHandLuggage(handLuggageWeight, passenger->getId());
                    return true;
                }
            }
        }
        return false;
    }

    segment.addLuggage(luggageWeight, passenger->getId());
    segment.addHandLuggage(handLuggageWeight, passenger->getId());
    return true;
}

void Plane::boardUnit(std::shared_ptr<Passenger> passenger) {
    PlaneSegment* segment = nullptr;

    if (passenger->getType() == "ECONOMY") {
        segment = &economyClassSegment;
    } else if (passenger->getType() == "BUSINESS") {
        segment = &businessClassSegment;
    } else if (passenger->getType() == "FIRST_CLASS") {
        segment = &firstClassSegment;
    }

    if (segment) {
        if (!tryAddPassengerToSegment(*segment, passenger)) {
            std::cout << "!!CANT REGISTER " << passenger->getType()
                      << " PASSENGER, ID = " << passenger->getId() << "!!" << std::endl;
        } else {
            passengers[passenger->getId()] = passenger;
        }
    }
}

int Plane::getTotalLuggageWeight() const {
    return firstClassSegment.getCurrentLuggageWeight() + businessClassSegment.getCurrentLuggageWeight() +
           economyClassSegment.getCurrentLuggageWeight();
}

int Plane::getTotalHandLuggageWeight() const {
    return firstClassSegment.getCurrentHandLuggageWeight() +
           businessClassSegment.getCurrentHandLuggageWeight() +
           economyClassSegment.getCurrentHandLuggageWeight();
}

void Plane::printSegmentDetails() const {
    std::cout << "First class total weight: " << firstClassSegment.getCurrentTotalWeight() << "/"
              << firstClassSegment.getMaxTotalWeight() << std::endl;
    std::cout << "Business class total weight: " << businessClassSegment.getCurrentTotalWeight() << "/"
              << businessClassSegment.getMaxTotalWeight() << std::endl;
    std::cout << "Economy class total weight: " << economyClassSegment.getCurrentTotalWeight() << "/"
              << economyClassSegment.getMaxTotalWeight() << std::endl;
}
