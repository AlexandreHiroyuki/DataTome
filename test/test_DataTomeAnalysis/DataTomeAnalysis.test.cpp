#include <DataTomeAnalysis.h>
#include <unity.h>

void setUp(void) {}    // before test

void tearDown(void) {} // after test

long int data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

long int mode_data[10] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 4};

void test_minAndMax(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);

  for(size_t i = 0; i < 10; i++) {
    testAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[0], testAnalysis.minimum());
  TEST_ASSERT_EQUAL(data[9], testAnalysis.maximum());
}

void test_median(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);

  for(size_t i = 0; i < 10; i++) {
    testAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL((data[4] + data[5]) / 2, testAnalysis.median());
}

void test_lowestMode(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);

  for(size_t i = 0; i < 10; i++) {
    testAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(3, testAnalysis.lowest_mode());
}

void test_highestMode(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);

  for(size_t i = 0; i < 10; i++) {
    testAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(4, testAnalysis.highest_mode());
}

void test_getVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t data_count = 5;

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(data[i]);
  }

  long int mock_sum = 0;
  for(size_t i = 0; i < data_count; i++) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / data_count;
  TEST_ASSERT_EQUAL(mock_average, testAnalysis.get());

  long int mock_var = 0;
  for(size_t i = 0; i < data_count; i++) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, testAnalysis.var());

  TEST_ASSERT_EQUAL(sqrt(mock_var / data_count), testAnalysis.std());
}

void test_partialMinAndMax(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t partial_size = 3;
  size_t data_count   = 5;

  size_t partial_id = testAnalysis.partial_create(partial_size);

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[2], testAnalysis.partial_minimum(partial_id));
  TEST_ASSERT_EQUAL(data[4], testAnalysis.partial_maximum(partial_id));
}

void test_partialMedian(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t partial_size = 3;
  size_t data_count   = 5;

  size_t partial_id = testAnalysis.partial_create(partial_size);

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[3], testAnalysis.partial_median(partial_id));
}

void test_partialLowestMode(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t partial_size = 5;
  size_t data_count   = 5;

  size_t partial_id = testAnalysis.partial_create(partial_size);

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(3, testAnalysis.partial_lowest_mode(partial_id));
}

void test_partialHighestMode(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t partial_size = 5;
  size_t data_count   = 10;

  size_t partial_id = testAnalysis.partial_create(partial_size);

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(4, testAnalysis.partial_highest_mode(partial_id));
}

void test_partialVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> testAnalysis(10);
  size_t partial_size = 3;
  size_t data_count   = 5;

  size_t partial_id = testAnalysis.partial_create(partial_size);

  for(size_t i = 0; i < data_count; i++) {
    testAnalysis.push(data[i]);
  }

  long int mock_sum = 0;
  for(size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / partial_size;
  TEST_ASSERT_EQUAL(mock_average, testAnalysis.partial_get(partial_id));

  long int mock_var = 0;
  for(size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, testAnalysis.partial_var(partial_id));

  TEST_ASSERT_EQUAL(sqrt(mock_var / partial_size),
                    testAnalysis.partial_std(partial_id));
}

void process() {
  UNITY_BEGIN();

  RUN_TEST(test_minAndMax);
  RUN_TEST(test_median);
  RUN_TEST(test_lowestMode);
  RUN_TEST(test_highestMode);
  RUN_TEST(test_getVarianceAndStandardDeviation);

  RUN_TEST(test_partialMinAndMax);
  RUN_TEST(test_partialMedian);
  RUN_TEST(test_partialLowestMode);
  RUN_TEST(test_partialHighestMode);
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