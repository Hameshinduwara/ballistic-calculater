#include <Servo.h>

Servo mortarServo;  // Servo motor controlling the mortar's angle
const float g = 9.8;  // Acceleration due to gravity (m/s^2)
const float u = 10.0; // Initial velocity (m/s)

void setup() {
  Serial.begin(9600);
  mortarServo.attach(9); // Connect servo to pin 9
  Serial.println("Enter values for x (horizontal) and y (vertical):");
}

void loop() {
  if (Serial.available() > 0) {
    float x = Serial.parseFloat(); // Read horizontal distance
    float y = Serial.parseFloat(); // Read vertical height

    // Calculate angles
    float angle1, angle2;
    bool success = calculateAngles(x, y, angle1, angle2);

    if (success) {
      Serial.print("Low angle: ");
      Serial.println(angle1);
      Serial.print("High angle: ");
      Serial.println(angle2);

      // Set servo to the low angle
      mortarServo.write(angle1); // Send the low angle to the servo
      delay(2000);               // Wait 2 seconds before resetting
    } else {
      Serial.println("Target unreachable with given parameters.");
    }
  }
}

// Function to calculate angles
bool calculateAngles(float x, float y, float &angle1, float &angle2) {
  float u2 = u * u;
  float discriminant = u2 * u2 - g * (g * x * x + 2 * y * u2);

  if (discriminant < 0) {
    return false; // No solution
  }

  float sqrtDisc = sqrt(discriminant);
  float tanTheta1 = (u2 + sqrtDisc) / (g * x);
  float tanTheta2 = (u2 - sqrtDisc) / (g * x);

  // Convert to degrees
  angle1 = atan(tanTheta1) * 180 / PI;
  angle2 = atan(tanTheta2) * 180 / PI;

  return true;
}

