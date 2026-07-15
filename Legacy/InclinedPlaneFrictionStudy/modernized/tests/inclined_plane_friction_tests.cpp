#include "inclined_plane_friction.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

namespace study = code_samples::friction_study_2016;

namespace {

int failures = 0;

void expect(bool condition, const std::string& name)
{
    if (!condition) {
        ++failures;
        std::cerr << "FAILED: " << name << '\n';
    }
}

void expect_near(double actual, double expected, const std::string& name, double tolerance = 1e-10)
{
    expect(std::abs(actual - expected) <= tolerance * std::max({ 1.0, std::abs(actual), std::abs(expected) }), name);
}

template <typename Exception, typename Action>
void expect_throw(Action action, const std::string& name)
{
    try {
        action();
        expect(false, name);
    } catch (const Exception&) {
        expect(true, name);
    } catch (...) {
        expect(false, name + " (wrong exception)");
    }
}

void test_equilibrium_and_direction()
{
    const auto balanced = study::solve({ 2.0, 1.0, 0.0, 30.0 });
    expect(balanced.direction == study::motion_direction::static_equilibrium,
        "balanced friction-free system stays at rest");
    expect_near(balanced.signed_acceleration, 0.0, "balanced acceleration");
    expect_near(balanced.tension, study::standard_gravity, "balanced tension");

    const auto hanging_down = study::solve({ 1.0, 2.0, 0.0, 0.0 });
    expect(hanging_down.direction == study::motion_direction::hanging_mass_down,
        "classify hanging mass motion");
    expect_near(hanging_down.signed_acceleration, 2.0 * study::standard_gravity / 3.0,
        "hanging mass acceleration");

    const auto incline_down = study::solve({ 2.0, 1.0, 0.0, 90.0 });
    expect(incline_down.direction == study::motion_direction::incline_mass_down,
        "classify incline mass motion");
    expect_near(incline_down.signed_acceleration, -study::standard_gravity / 3.0,
        "incline mass acceleration uses negative sign");
}

void test_friction_and_tension()
{
    const auto held = study::solve({ 2.0, 1.0, 0.2, 20.0 });
    expect(held.direction == study::motion_direction::static_equilibrium,
        "friction can hold the system");
    expect_near(held.friction_force, std::abs(held.drive_without_friction),
        "static friction uses only the required force");

    const auto moving = study::solve({ 1.0, 2.0, 0.1, 0.0 });
    const double expected_acceleration = (2.0 * study::standard_gravity - 0.1 * study::standard_gravity) / 3.0;
    expect_near(moving.signed_acceleration, expected_acceleration,
        "kinetic friction reduces acceleration");
    expect_near(moving.tension, 2.0 * (study::standard_gravity - expected_acceleration),
        "tension follows hanging-mass equation");
}

void test_pulley_resultant()
{
    expect_near(study::pulley_support_force(10.0, 0.0), 20.0,
        "parallel tensions add");
    expect_near(study::pulley_support_force(10.0, 90.0), 10.0 * std::sqrt(2.0),
        "perpendicular tensions combine by Pythagoras");
    expect_near(study::pulley_support_force(10.0, 180.0), 0.0,
        "opposite tensions cancel");
}

void test_sweeps()
{
    const study::system_parameters base { 2.0, 1.0, 0.0, 20.0 };
    const auto friction = study::sweep(base, study::sweep_variable::friction_coefficient, 0.0, 0.3, 0.1);
    expect(friction.size() == 4, "friction sweep includes reachable endpoint");
    expect_near(friction.front().input, 0.0, "friction sweep start");
    expect_near(friction.back().input, 0.3, "friction sweep end");

    const auto angles = study::sweep(base, study::sweep_variable::angle_degrees, 0.0, 30.0, 10.0);
    expect(angles.size() == 4, "angle sweep includes reachable endpoint");
    expect_near(angles.back().input, 30.0, "angle sweep end");
}

void test_invalid_inputs()
{
    expect_throw<std::invalid_argument>(
        [] { (void)study::solve({ 0.0, 1.0, 0.1, 20.0 }); },
        "reject zero mass");
    expect_throw<std::invalid_argument>(
        [] { (void)study::solve({ 1.0, 1.0, -0.1, 20.0 }); },
        "reject negative friction");
    expect_throw<std::invalid_argument>(
        [] { (void)study::solve({ 1.0, 1.0, 0.1, 91.0 }); },
        "reject angle above 90 degrees");
    expect_throw<std::invalid_argument>(
        [] { (void)study::pulley_support_force(1.0, 181.0); },
        "reject pulley angle above 180 degrees");
    expect_throw<std::invalid_argument>(
        [] {
            (void)study::sweep(
                { 1.0, 1.0, 0.1, 20.0 },
                study::sweep_variable::angle_degrees,
                0.0,
                10.0,
                0.0);
        },
        "reject zero sweep step");
}

} // namespace

int main()
{
    test_equilibrium_and_direction();
    test_friction_and_tension();
    test_pulley_resultant();
    test_sweeps();
    test_invalid_inputs();

    if (failures == 0) {
        std::cout << "Inclined-plane friction tests passed\n";
        return 0;
    }
    std::cerr << failures << " test assertion(s) failed\n";
    return 1;
}
