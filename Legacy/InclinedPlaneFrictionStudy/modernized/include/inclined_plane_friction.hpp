#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <numbers>
#include <stdexcept>
#include <vector>

namespace code_samples::friction_study_2016 {

inline constexpr double standard_gravity = 9.81;

struct system_parameters {
    double incline_mass;
    double hanging_mass;
    double friction_coefficient;
    double angle_degrees;
    double gravity = standard_gravity;
};

enum class motion_direction {
    static_equilibrium,
    hanging_mass_down,
    incline_mass_down,
};

struct solution {
    motion_direction direction;
    double signed_acceleration;
    double tension;
    double normal_force;
    double friction_force;
    double drive_without_friction;
};

[[nodiscard]] inline double degrees_to_radians(double angle_degrees) noexcept
{
    return angle_degrees * std::numbers::pi / 180.0;
}

inline void validate(system_parameters parameters)
{
    const bool finite = std::isfinite(parameters.incline_mass)
        && std::isfinite(parameters.hanging_mass)
        && std::isfinite(parameters.friction_coefficient)
        && std::isfinite(parameters.angle_degrees)
        && std::isfinite(parameters.gravity);
    if (!finite) {
        throw std::invalid_argument("all system parameters must be finite");
    }
    if (parameters.incline_mass <= 0.0 || parameters.hanging_mass <= 0.0) {
        throw std::invalid_argument("both masses must be positive");
    }
    if (parameters.friction_coefficient < 0.0) {
        throw std::invalid_argument("friction coefficient cannot be negative");
    }
    if (parameters.angle_degrees < 0.0 || parameters.angle_degrees > 90.0) {
        throw std::invalid_argument("incline angle must be between 0 and 90 degrees");
    }
    if (parameters.gravity <= 0.0) {
        throw std::invalid_argument("gravity must be positive");
    }
}

[[nodiscard]] inline solution solve(system_parameters parameters)
{
    validate(parameters);

    const double angle = degrees_to_radians(parameters.angle_degrees);
    const double normal_force = parameters.incline_mass * parameters.gravity * std::cos(angle);
    const double drive = parameters.gravity
        * (parameters.hanging_mass - parameters.incline_mass * std::sin(angle));
    const double friction_limit = parameters.friction_coefficient * normal_force;
    const double scale = std::max({ 1.0, std::abs(drive), std::abs(friction_limit) });
    const double tolerance = 32.0 * std::numeric_limits<double>::epsilon() * scale;

    // Positive coordinates follow the hanging mass downward. Friction first
    // holds against the friction-free drive, then opposes that drive in motion.
    if (std::abs(drive) <= friction_limit + tolerance) {
        return {
            motion_direction::static_equilibrium,
            0.0,
            parameters.hanging_mass * parameters.gravity,
            normal_force,
            std::abs(drive),
            drive,
        };
    }

    const double sign = drive > 0.0 ? 1.0 : -1.0;
    const double acceleration = sign * (std::abs(drive) - friction_limit)
        / (parameters.incline_mass + parameters.hanging_mass);
    const double tension = parameters.hanging_mass * (parameters.gravity - acceleration);
    return {
        sign > 0.0 ? motion_direction::hanging_mass_down : motion_direction::incline_mass_down,
        acceleration,
        tension,
        normal_force,
        friction_limit,
        drive,
    };
}

[[nodiscard]] inline double pulley_support_force(double tension, double included_angle_degrees)
{
    if (!std::isfinite(tension) || tension < 0.0) {
        throw std::invalid_argument("tension must be finite and non-negative");
    }
    if (!std::isfinite(included_angle_degrees)
        || included_angle_degrees < 0.0
        || included_angle_degrees > 180.0) {
        throw std::invalid_argument("included angle must be between 0 and 180 degrees");
    }

    const double value = 2.0 * tension * tension
        * (1.0 + std::cos(degrees_to_radians(included_angle_degrees)));
    return std::sqrt(std::max(0.0, value));
}

enum class sweep_variable {
    friction_coefficient,
    angle_degrees,
};

struct sweep_sample {
    double input;
    solution result;
};

[[nodiscard]] inline std::vector<sweep_sample> sweep(
    system_parameters base,
    sweep_variable variable,
    double start,
    double end,
    double step)
{
    if (!std::isfinite(start) || !std::isfinite(end) || !std::isfinite(step)) {
        throw std::invalid_argument("sweep bounds and step must be finite");
    }
    if (step <= 0.0 || start > end) {
        throw std::invalid_argument("sweep requires a positive step and start <= end");
    }

    std::vector<sweep_sample> samples;
    const double tolerance = 16.0 * std::numeric_limits<double>::epsilon()
        * std::max({ 1.0, std::abs(start), std::abs(end) });
    for (std::size_t index = 0; index <= 1'000'000; ++index) {
        double input = start + static_cast<double>(index) * step;
        if (input > end + tolerance) {
            return samples;
        }
        if (input > end) {
            input = end;
        }

        system_parameters current = base;
        if (variable == sweep_variable::friction_coefficient) {
            current.friction_coefficient = input;
        } else {
            current.angle_degrees = input;
        }
        samples.push_back({ input, solve(current) });
        if (input == end) {
            return samples;
        }
    }
    throw std::length_error("sweep exceeds one million samples");
}

} // namespace code_samples::friction_study_2016
