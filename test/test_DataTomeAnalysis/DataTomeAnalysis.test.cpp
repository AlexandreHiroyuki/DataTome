#include <DataTomeAnalysis.h>
#include <unity.h>

void setUp(void) {}  // before test

void tearDown(void) {}  // after test

long int data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

void test_getVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> TestMV(10);
  size_t data_count = 5;

  for (size_t i = 0; i < data_count; i++) {
    TestMV.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = 0; i < data_count; i++) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / data_count;
  TEST_ASSERT_EQUAL(mock_average, TestMV.get());

  long int mock_var = 0;
  for (size_t i = 0; i < data_count; i++) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, TestMV.var());

  TEST_ASSERT_EQUAL(sqrt(mock_var / data_count), TestMV.std());
}

void test_partialVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> TestMV(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = TestMV.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestMV.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / partial_size;
  TEST_ASSERT_EQUAL(mock_average, TestMV.partial_get(partial_id));

  long int mock_var = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, TestMV.partial_var(partial_id));

  TEST_ASSERT_EQUAL(sqrt(mock_var / partial_size),
                    TestMV.partial_std(partial_id));
}

void process() {
  UNITY_BEGIN();

  RUN_TEST(test_getVarianceAndStandardDeviation);
  RUN_TEST(test_partialVarianceAndStandardDeviation);

  UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  process();
}

void loop() {
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}

#else

int main(int argc, char **argv) {
  process();
  return 0;
}

#endif