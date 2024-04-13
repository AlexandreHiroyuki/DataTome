#include <DataTomeAnalysis.h>
#include <unity.h>

void setUp(void) {}  // before test

void tearDown(void) {}  // after test

long int data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

long int mode_data[10] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 4};

void test_minAndMax(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);

  for (size_t i = 0; i < 10; i++) {
    TestAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[0], TestAnalysis.min());
  TEST_ASSERT_EQUAL(data[9], TestAnalysis.max());
}

void test_median(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);

  for (size_t i = 0; i < 10; i++) {
    TestAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL((data[4] + data[5]) / 2, TestAnalysis.median());
}

void test_lowestMode(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);

  for (size_t i = 0; i < 10; i++) {
    TestAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(3, TestAnalysis.lowest_mode());
}

void test_highestMode(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);

  for (size_t i = 0; i < 10; i++) {
    TestAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(4, TestAnalysis.highest_mode());
}

void test_getVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t data_count = 5;

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = 0; i < data_count; i++) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / data_count;
  TEST_ASSERT_EQUAL(mock_average, TestAnalysis.get());

  long int mock_var = 0;
  for (size_t i = 0; i < data_count; i++) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, TestAnalysis.var());

  TEST_ASSERT_EQUAL(sqrt(mock_var / data_count), TestAnalysis.std());
}

void test_partialMinAndMax(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = TestAnalysis.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[2], TestAnalysis.partial_min(partial_id));
  TEST_ASSERT_EQUAL(data[4], TestAnalysis.partial_max(partial_id));
}

void test_partialMedian(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = TestAnalysis.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(data[i]);
  }

  TEST_ASSERT_EQUAL(data[3], TestAnalysis.partial_median(partial_id));
}

void test_partialLowestMode(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t partial_size = 5;
  size_t data_count = 5;

  size_t partial_id = TestAnalysis.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(3, TestAnalysis.partial_lowest_mode(partial_id));
}

void test_partialHighestMode(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t partial_size = 5;
  size_t data_count = 10;

  size_t partial_id = TestAnalysis.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(mode_data[i]);
  }

  TEST_ASSERT_EQUAL(4, TestAnalysis.partial_highest_mode(partial_id));
}

void test_partialVarianceAndStandardDeviation(void) {
  DataTomeAnalysis<int, long int> TestAnalysis(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = TestAnalysis.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestAnalysis.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_sum += data[i];
  }

  long int mock_average = mock_sum / partial_size;
  TEST_ASSERT_EQUAL(mock_average, TestAnalysis.partial_get(partial_id));

  long int mock_var = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_var += (data[i] - mock_average) * (data[i] - mock_average);
  }

  TEST_ASSERT_EQUAL(mock_var, TestAnalysis.partial_var(partial_id));

  TEST_ASSERT_EQUAL(sqrt(mock_var / partial_size),
                    TestAnalysis.partial_std(partial_id));
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