// Include lib:
#include <Arduino.h>
#include <DataTome.h>

// Create an Arithmetic Moving Average object of unsigned int type,
// 10 in size
DataTomeMvAvg<int, long int> test(10);
DataTomeAnalysis<int, long int> test2(10);
DataTomeCumulative<double> test3;
DataTomeExpAvg<double> test4;

// This variable just generates input for average test
int delta_x = 0;

void setup() {
  // Initialize serial interface
  Serial.begin(9600);
}

void loop() {
  // Pushes the input in the moving average object
  test.push(delta_x);
  test2.push(delta_x);
  test3.push(delta_x);
  test4.push(delta_x);

  // Generates the next input
  delta_x += 3;
  if (delta_x > 1000) delta_x = 0;

  // Prints each value stored in the moving average
  for (uint8_t i = 0; i < test.size(); i++) {
    Serial.print(test[i]);
    Serial.print(" ");
  }
  // Prints the result of the average
  Serial.print("= ");
  Serial.print(test.get());
  // Prints the value stored in the first and last indexes
  Serial.print(" | f: ");
  Serial.print(test.front());
  Serial.print(" b: ");
  Serial.println(test.back());

  Serial.print("Analysis: ");
  Serial.print(test2.mean());
  Serial.print(" | Std: ");
  Serial.print(test2.std());
  Serial.print(" | Median: ");
  Serial.println(test2.median());

  Serial.print("Cumulative: ");
  Serial.println(test3.get());

  Serial.print(" | ExpAvg: ");
  Serial.println(test4.get());

  delay(1000);
}
