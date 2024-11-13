#ifndef CREW_MEMBERS_HPP
#define CREW_MEMBERS_HPP

#include <string>

#include "unit.hpp"

class CrewMember : public Unit {
   public:
    CrewMember(int id, const std::string& type);

    bool canAddHandLuggage(int) const override { return false; }
    bool canAddLuggage(int) const override { return false; }
    void addHandLuggage(int) override {}
    void addLuggage(int) override {}

    int getTotalHandLuggageWeight() const override { return 0; }
    int getTotalLuggageWeight() const override { return 0; }
};

class Pilot : public CrewMember {
   public:
    Pilot(int id);
};

class Steward : public CrewMember {
   public:
    Steward(int id);
};

#endif
