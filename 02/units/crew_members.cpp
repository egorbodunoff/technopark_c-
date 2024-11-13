#include "crew_members.hpp"

CrewMember::CrewMember(int id, const std::string& type) : Unit(id, type) {}

Pilot::Pilot(int id) : CrewMember(id, "PILOT") {}

Steward::Steward(int id) : CrewMember(id, "FLIGHT ATTENDANT") {}
