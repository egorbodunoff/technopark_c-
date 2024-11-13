#include "../units/crew_members.hpp"

#include <cassert>
#include <iostream>

void test_CrewMember_basic_properties() {
    CrewMember crew(1, "CREW_MEMBER");
    assert(crew.getId() == 1);
    assert(crew.getType() == "CREW_MEMBER");
}

void test_CrewMember_hand_luggage_restrictions() {
    CrewMember crew(2, "CREW_MEMBER");
    assert(!crew.canAddHandLuggage(5));  // Должно возвращать false
    assert(!crew.canAddLuggage(10));     // Должно возвращать false
}

void test_CrewMember_total_luggage_weight() {
    CrewMember crew(3, "CREW_MEMBER");
    assert(crew.getTotalHandLuggageWeight() == 0);  // Должно возвращать 0
    assert(crew.getTotalLuggageWeight() == 0);      // Должно возвращать 0
}

void test_Pilot_basic_properties() {
    Pilot pilot(4);
    assert(pilot.getId() == 4);
    assert(pilot.getType() == "PILOT");
}

void test_Pilot_hand_luggage_restrictions() {
    Pilot pilot(5);
    assert(!pilot.canAddHandLuggage(5));  // Должно возвращать false
    assert(!pilot.canAddLuggage(10));     // Должно возвращать false
}

void test_Pilot_total_luggage_weight() {
    Pilot pilot(6);
    assert(pilot.getTotalHandLuggageWeight() == 0);  // Должно возвращать 0
    assert(pilot.getTotalLuggageWeight() == 0);      // Должно возвращать 0
}

void test_Steward_basic_properties() {
    Steward steward(7);
    assert(steward.getId() == 7);
    assert(steward.getType() == "FLIGHT ATTENDANT");
}

void test_Steward_hand_luggage_restrictions() {
    Steward steward(8);
    assert(!steward.canAddHandLuggage(5));  // Должно возвращать false
    assert(!steward.canAddLuggage(10));     // Должно возвращать false
}

void test_Steward_total_luggage_weight() {
    Steward steward(9);
    assert(steward.getTotalHandLuggageWeight() == 0);  // Должно возвращать 0
    assert(steward.getTotalLuggageWeight() == 0);      // Должно возвращать 0
}

int main() {
    test_CrewMember_basic_properties();
    test_CrewMember_hand_luggage_restrictions();
    test_CrewMember_total_luggage_weight();

    test_Pilot_basic_properties();
    test_Pilot_hand_luggage_restrictions();
    test_Pilot_total_luggage_weight();

    test_Steward_basic_properties();
    test_Steward_hand_luggage_restrictions();
    test_Steward_total_luggage_weight();

    std::cout << "All tests passed" << std::endl;
    return 0;
}
