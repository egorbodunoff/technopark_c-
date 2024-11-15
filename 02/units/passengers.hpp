#ifndef PASSENGERS_HPP
#define PASSENGERS_HPP

#include <string>

#include "unit.hpp"

class Passenger : public Unit {
   protected:
    int maxHandLuggageWeight;  // Максимальный вес ручной клади
    int maxLuggageWeight;      // Максимальный вес багажа
    size_t maxLuggageItems;    // Максимальное количество мест багажа

   public:
    Passenger(int id, const std::string& type, int maxHandLuggage, int maxLuggage, int maxItems);

    bool canAddHandLuggage(int weight) const override;
    bool canAddLuggage(int weight) const override;
    void addHandLuggage(int weight) override;
    void addLuggage(int weight) override;
};

class EconomyPassenger : public Passenger {
   public:
    EconomyPassenger(int id);
};

class BusinessPassenger : public Passenger {
   public:
    BusinessPassenger(int id);
};

class FirstClassPassenger : public Passenger {
   public:
    FirstClassPassenger(int id);
};

#endif
