#include <iostream>
#include <cmath>

using namespace std;

// Constants
const double g = 9.8; // Gravity (m/s^2)
const double rho = 1.225; // Air density (kg/m^3)
const double Cd = 0.47; // Drag coefficient for a sphere
const double A = 0.01; // Cross-sectional area (m^2)
const double m = 0.1; // Mass (kg)
const double dt = 0.01; // Time step (s)

// Function to calculate acceleration with drag
void update(double &vx, double &vy, double &x, double &y) {
    double v = sqrt(vx * vx + vy * vy); // Magnitude of velocity
    double drag = (0.5 * Cd * rho * A * v) / m; // Drag acceleration

    // Update accelerations
    double ax = -drag * vx; // Drag slows horizontal velocity
    double ay = -g - drag * vy; // Gravity + drag slows vertical velocity

    // Update velocities
    vx += ax * dt;
    vy += ay * dt;

    // Update positions
    x += vx * dt;
    y += vy * dt;
}

int main() {
    // Initial conditions
    double v0 = 50.0; // Initial velocity (m/s)
    double angle = 45.0; // Launch angle (degrees)
    double vx = v0 * cos(angle * M_PI / 180); // Initial horizontal velocity
    double vy = v0 * sin(angle * M_PI / 180); // Initial vertical velocity
    double x = 0.0, y = 0.0; // Initial position

    // Simulate motion
    cout << "Time\tX\tY" << endl;
    double t = 0.0;
    while (y >= 0.0) { // Stop when the projectile hits the ground
        cout << t << "\t" << x << "\t" << y << endl;
        update(vx, vy, x, y);
        t += dt;
    }

    return 0;
}
