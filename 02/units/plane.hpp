#ifndef PLANE_HPP
#define PLANE_HPP

#include <memory>
#include <vector>

#include "passengers.hpp"
#include "unit.hpp"

class PlaneSegment {
   private:
    int maxTotalWeight;  // Максимальный общий вес для багажа и ручной клади
    std::vector<std::pair<int, int>> luggage;  // Пара (вес багажа, ID пассажира)
    std::vector<std::pair<int, int>> handLuggage;  // Вектор для хранения веса ручной клади
    std::vector<std::shared_ptr<Passenger>> occupants;

   public:
    PlaneSegment(int maxWeight);
    bool canAddLuggage(int weight) const;
    void addLuggage(int weight, int passengerID);
    void addHandLuggage(int weight, int passengerID);
    void addOccupant(std::shared_ptr<Passenger> unit);
    bool isOverloaded() const;
    int getCurrentLuggageWeight() const;
    int getCurrentHandLuggageWeight() const;
    int getCurrentTotalWeight() const;
    int getMaxTotalWeight() const;
    bool removeMinLuggageUnits(int requiredWeight);
};

class Plane {
   private:
    PlaneSegment firstClassSegment;
    PlaneSegment businessClassSegment;
    PlaneSegment economyClassSegment;

    bool tryAddPassengerToSegment(PlaneSegment& segment, std::shared_ptr<Passenger> passenger);

   public:
    Plane(int maxFirstClassWeight, int maxBusinessClassWeight, int maxEconomyClassWeight);
    void boardUnit(std::shared_ptr<Passenger> passenger);
    int getTotalLuggageWeight() const;
    int getTotalHandLuggageWeight() const;
    void printSegmentDetails() const;
};

#endif
