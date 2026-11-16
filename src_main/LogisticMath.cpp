
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>

using std::cout;
using std::endl;
using std::vector;

using vecDouble = vector<double>;


// ============================================================
// LOGISTIC MAP
// ============================================================

// Computes one iteration of the logistic map:
// x(n+1) = r * x(n) * (1 - x(n))

double logisticMap(double x, double r) {
    return r * x * (1.0 - x);
}


// ============================================================
// SIMULATION
// ============================================================

// Generates a sequence of logistic-map states.
// The returned vector contains x0 and all subsequent states.
// Therefore, its size is iterations + 1.

vecDouble simulate(double x0, double r, int iterations) {

    vecDouble states;
    states.reserve(iterations + 1);

    states.push_back(x0);

    double x = x0;

    for (int i = 0; i < iterations; i++) {

        x = logisticMap(x, r);
        states.push_back(x);
    }

    return states;
}


// ============================================================
// LYAPUNOV EXPONENT
// ============================================================

// Calculates the Lyapunov exponent after discarding
// the transient portion of the simulation.
//
// lambda = (1/N) * sum(log(abs(f'(x))))
//
// For the logistic map:
// f'(x) = r * (1 - 2x)

double calculateLyapunov(
    const vecDouble& states,
    double r,
    int transient,
    int measurementIterations
) {

    if (transient < 0 || measurementIterations <= 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    const std::size_t start =
        static_cast<std::size_t>(transient);

    const std::size_t end =
        start + static_cast<std::size_t>(measurementIterations);

    if (end > states.size()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double sum = 0.0;

    for (std::size_t i = start; i < end; i++) {

        const double x = states[i];

        const double derivative = r * (1.0 - 2.0 * x);

        if (derivative == 0.0) {
            return -std::numeric_limits<double>::infinity();
        }

        sum += std::log(std::abs(derivative));
    }

    return sum / measurementIterations;
}


// ============================================================
// EXPERIMENT 1: BASIC LOGISTIC SIMULATION
// ============================================================

// Generates a single logistic-map trajectory.
//
// Output:
// logistic_simulation.csv
//
// Columns:
// iteration, state

void runSimulation() {

    cout << "\n[Simulation] Starting...\n";

    const double x0 = 0.2;
    const double r = 3.5;
    const int iterations = 1000;

    const vecDouble states = simulate(x0, r, iterations);

    std::ofstream file("logistic_simulation.csv");

    if (!file.is_open()) {
        cout << "[Simulation] Could not create CSV file.\n";
        return;
    }

    file << "iteration,state\n";

    for (std::size_t i = 0; i < states.size(); i++) {

        file << i << ","
             << std::setprecision(17) << states[i]
             << "\n";
    }

    file.close();

    cout << "[Simulation] Generated logistic_simulation.csv\n";
}


// ============================================================
// EXPERIMENT 2: BIFURCATION ANALYSIS
// ============================================================

// Generates logistic-map trajectories for a range of r values.
//
// Initial iterations are discarded as transient behaviour.
// The remaining states are written to simulation.csv.
//
// Output columns:
// r, iteration, state

void runBifurcation() {

    cout << "\n[Bifurcation] Starting...\n";

    const double x0 = 0.2;

    const double r_min = 2.5;
    const double r_max = 4.0;
    const double r_step = 0.01;

    const int iterations = 1000;
    const int transient = 800;

    std::ofstream file("simulation.csv");

    if (!file.is_open()) {
        cout << "[Bifurcation] Could not create CSV file.\n";
        return;
    }

    file << "r,iteration,state\n";

    for (double r = r_min; r <= r_max + 1e-12; r += r_step) {

        const vecDouble states = simulate(x0, r, iterations);

        for (int i = transient; i <= iterations; i++) {

            file << std::setprecision(17)
                 << r << ","
                 << i << ","
                 << states[i]
                 << "\n";
        }
    }

    file.close();

    cout << "[Bifurcation] Generated simulation.csv\n";
}


// ============================================================
// EXPERIMENT 3: SENSITIVITY ANALYSIS
// ============================================================

// Compares two trajectories with very slightly different
// initial conditions.
//
// Both trajectories use the same logistic-map parameter r.
//
// The difference between the trajectories is:
// delta(n) = abs(x_a(n) - x_b(n))
//
// Output:
// sensitivity.csv
//
// Columns:
// iteration, state_a, state_b, difference

void runSensitivity() {

    cout << "\n[Sensitivity] Starting...\n";

    const double r = 4.0;

    const double x0_a = 0.2;
    const double x0_b = 0.200001;

    const int iterations = 200;

    const vecDouble states_a =
        simulate(x0_a, r, iterations);

    const vecDouble states_b =
        simulate(x0_b, r, iterations);

    std::ofstream file("sensitivity.csv");

    if (!file.is_open()) {
        cout << "[Sensitivity] Could not create CSV file.\n";
        return;
    }

    file << "iteration,state_a,state_b,difference\n";

    for (int i = 0; i <= iterations; i++) {

        const double difference =
            std::abs(states_a[i] - states_b[i]);

        file << i << ","
             << std::setprecision(17)
             << states_a[i] << ","
             << states_b[i] << ","
             << difference
             << "\n";
    }

    file.close();

    cout << "[Sensitivity] Generated sensitivity.csv\n";
}


// ============================================================
// EXPERIMENT 4: SINGLE LYAPUNOV CALCULATION
// ============================================================

// Calculates the Lyapunov exponent for one selected r value.
//
// Output:
// lyapunov.csv
//
// Columns:
// r, lyapunov_exponent

void runSingleLyapunov() {

    cout << "\n[Lyapunov] Starting single calculation...\n";

    const double x0 = 0.2;
    const double r = 4.0;

    const int transient = 1000;
    const int measurementIterations = 10000;

    const int totalIterations =
        transient + measurementIterations;

    const vecDouble states =
        simulate(x0, r, totalIterations);

    const double exponent =
        calculateLyapunov(
            states,
            r,
            transient,
            measurementIterations
        );

    std::ofstream file("lyapunov.csv");

    if (!file.is_open()) {
        cout << "[Lyapunov] Could not create CSV file.\n";
        return;
    }

    file << "r,lyapunov_exponent\n";

    file << std::setprecision(17)
         << r << ","
         << exponent
         << "\n";

    file.close();

    cout << "[Lyapunov] Exponent = " << exponent << endl;
    cout << "[Lyapunov] Generated lyapunov.csv\n";
}


// ============================================================
// EXPERIMENT 5: LYAPUNOV PARAMETER SWEEP
// ============================================================

// Calculates the Lyapunov exponent over a range of r values.
//
// This allows the Lyapunov exponent to be plotted against
// the logistic-map parameter.
//
// Output:
// lyapunov_plotting.csv
//
// Columns:
// r, lyapunov_exponent

void runLyapunovSweep() {

    cout << "\n[Lyapunov Sweep] Starting...\n";

    const double x0 = 0.2;

    const double r_min = 2.5;
    const double r_max = 4.0;
    const double r_step = 0.005;

    const int transient = 1000;
    const int measurementIterations = 10000;

    const int totalIterations =
        transient + measurementIterations;

    std::ofstream file("lyapunov_plotting.csv");

    if (!file.is_open()) {
        cout << "[Lyapunov Sweep] Could not create CSV file.\n";
        return;
    }

    file << "r,lyapunov_exponent\n";

    for (double r = r_min; r <= r_max + 1e-12; r += r_step) {

        const vecDouble states =
            simulate(x0, r, totalIterations);

        const double exponent =
            calculateLyapunov(
                states,
                r,
                transient,
                measurementIterations
            );

        file << std::setprecision(17)
             << r << ","
             << exponent
             << "\n";
    }

    file.close();

    cout << "[Lyapunov Sweep] Generated lyapunov_plotting.csv\n";
}


// ============================================================
// MAIN
// ============================================================

int main() {

    cout << "====================================\n";
    cout << "          CHAOSLAB 1.0\n";
    cout << "====================================\n";

    runSimulation(); // No file in python to run this currently

    runBifurcation();

    runSensitivity();

    runSingleLyapunov(); // No file in python to run this currently

    runLyapunovSweep();

    cout << "\n====================================\n";
    cout << "All experiments completed.\n";
    cout << "====================================\n";

    return 0;
}
