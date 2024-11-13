#include "../units/plane.hpp"
#include <cassert>
#include <iostream>

void test_plane_segment_add_luggage() {
    PlaneSegment segment(100);

    segment.addLuggage(50, 1);  
    assert(segment.getCurrentLuggageWeight() == 50);

    segment.addLuggage(40, 2); 
    assert(segment.getCurrentLuggageWeight() == 90);

    segment.addLuggage(20, 3); 
    assert(segment.getCurrentLuggageWeight() == 90);
}

void test_plane_segment_remove_luggage() {
    PlaneSegment segment(100);
    segment.addLuggage(50, 1);
    segment.addLuggage(40, 2);

    segment.removeMinLuggageUnits(40); 
    assert(segment.getCurrentLuggageWeight() == 50);

    segment.removeMinLuggageUnits(30); 
    assert(segment.getCurrentLuggageWeight() == 0);
}

void test_plane_segment_overload() {
    PlaneSegment segment(100);
    segment.addLuggage(50, 1);
    segment.addHandLuggage(50, 2); 

    assert(segment.isOverloaded() == true);

    segment.removeMinLuggageUnits(50);
    assert(segment.isOverloaded() == false);
}

void test_plane_segment_max_weight() {
    PlaneSegment segment(100);

    assert(segment.getMaxTotalWeight() == 100);
}

void test_plane_boarding() {
    Plane plane(100, 100, 100);
    auto passenger1 = std::make_shared<EconomyPassenger>(1);
    auto passenger2 = std::make_shared<EconomyPassenger>(2);

    passenger1->addLuggage(5);
    passenger2->addLuggage(3);

    passenger1->addHandLuggage(5);
    passenger2->addHandLuggage(5);

    plane.boardUnit(passenger1);
    plane.boardUnit(passenger2);

    assert(plane.getTotalLuggageWeight() ==
           passenger1->getTotalLuggageWeight() + passenger2->getTotalLuggageWeight());
    assert(plane.getTotalHandLuggageWeight() ==
           passenger1->getTotalHandLuggageWeight() + passenger2->getTotalHandLuggageWeight());
}

void test_plane_segment_remove_min_luggage_units() {
    PlaneSegment segment(100);

    segment.addLuggage(30, 1);
    segment.addLuggage(20, 2);
    segment.addLuggage(50, 3);

    bool removed = segment.removeMinLuggageUnits(40);
    assert(removed == true); 
    assert(segment.getCurrentLuggageWeight() == 50); 
}

void test_plane_capacity_check() {
    Plane plane(100, 100, 100);
    auto passenger1 = std::make_shared<EconomyPassenger>(1);
    auto passenger2 = std::make_shared<EconomyPassenger>(2);

    plane.boardUnit(passenger1);
    plane.boardUnit(passenger2);

    assert(plane.getTotalLuggageWeight() <= 100);
}

void test_plane_boarding_with_full_class() {
    Plane plane(100, 100, 100);

    auto passenger1 = std::make_shared<EconomyPassenger>(1);
    auto passenger2 = std::make_shared<EconomyPassenger>(2);
    auto passenger3 = std::make_shared<EconomyPassenger>(3);

    plane.boardUnit(passenger1);
    plane.boardUnit(passenger2);
    plane.boardUnit(passenger3); 

    assert(plane.getTotalLuggageWeight() == 
           passenger1->getTotalLuggageWeight() + passenger2->getTotalLuggageWeight());
}

void test_remove_luggage_edge_case() {
    PlaneSegment segment(100);

    segment.removeMinLuggageUnits(10); 
    assert(segment.getCurrentLuggageWeight() == 0);

    segment.addLuggage(50, 1);
    segment.addLuggage(40, 2);

    segment.removeMinLuggageUnits(40);
    assert(segment.getCurrentLuggageWeight() == 50);
}

void test_max_min_luggage_weight() {
    PlaneSegment segment(100);

    segment.addLuggage(100, 1); 
    assert(segment.getCurrentLuggageWeight() == 100);

    segment.addLuggage(10, 2);
    assert(segment.getCurrentLuggageWeight() == 100); 
}

int main() {
    test_plane_segment_add_luggage();
    test_plane_segment_remove_luggage();
    test_plane_segment_overload();
    test_plane_segment_max_weight();
    test_plane_boarding();
    test_plane_segment_remove_min_luggage_units();
    test_plane_capacity_check();
    test_plane_boarding_with_full_class();
    test_remove_luggage_edge_case();
    test_max_min_luggage_weight();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
