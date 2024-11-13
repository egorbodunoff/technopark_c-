#ifndef UNIT_HPP
#define UNIT_HPP

#include <string>
#include <vector>

class Unit {
   protected:
    int id;                               // Уникальный идентификатор
    std::string type;                     // Тип юнита
    std::vector<int> handLuggageWeights;  // Ручная кладь
    std::vector<int> luggageWeights;      // Багаж

   public:
    Unit(int id, std::string type) : id(id), type(type) {}
    virtual ~Unit() = default;

    virtual std::string getType() const { return type; }
    virtual int getId() const { return id; }

    virtual bool canAddHandLuggage(int weight) const = 0;
    virtual bool canAddLuggage(int weight) const = 0;
    virtual void addHandLuggage(int weight) = 0;
    virtual void addLuggage(int weight) = 0;

    virtual int getTotalHandLuggageWeight() const {
        int totalWeight = 0;
        for (int weight : handLuggageWeights) {
            totalWeight += weight;
        }
        return totalWeight;
    }

    virtual int getTotalLuggageWeight() const {
        int totalWeight = 0;
        for (int weight : luggageWeights) {
            totalWeight += weight;
        }
        return totalWeight;
    }
};

#endif
