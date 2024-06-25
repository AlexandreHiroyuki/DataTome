#include <DataTomeMvAvg.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

long int data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

void test_getAverage(void) {
  DataTomeMvAvg<int, long int> testMV(5);

  testMV.push(data[0]).push(data[1]).push(data[2]);

  long int mock_average = (data[0] + data[1] + data[2]) / 3;
  long int mock_brute_average = (data[1] + data[2]) / 2;
  TEST_ASSERT_EQUAL(mock_average, testMV.get());
  TEST_ASSERT_EQUAL(mock_brute_average, testMV.get_by_brute(2));
}

void test_getFrontAndBackElements(void) {
  DataTomeMvAvg<int, long int> testMV(5);

  testMV.push(data[0]).push(data[1]).push(data[2]).push(data[3]).push(data[4]);

  TEST_ASSERT_EQUAL(data[4], testMV.front());
  TEST_ASSERT_EQUAL(data[0], testMV.back());
}

void test_getElementsByIndex(void) {
  DataTomeMvAvg<int, long int> testMV(5);

  testMV.push(data[0]).push(data[1]).push(data[2]);

  TEST_ASSERT_EQUAL(data[2], testMV[0]);
  TEST_ASSERT_EQUAL(data[1], testMV[1]);
  TEST_ASSERT_EQUAL(data[0], testMV[2]);
  TEST_ASSERT_EQUAL(data[0], testMV.at_index(0));
  TEST_ASSERT_EQUAL(data[1], testMV.at_index(1));
  TEST_ASSERT_EQUAL(data[2], testMV.at_index(2));
}

void test_sizeGrowAndPointCount(void) {
  DataTomeMvAvg<int, long int> testMV(5);
  size_t expected_size = 5;
  size_t expected_memory_size = expected_size * sizeof(int);
  size_t new_expected_size = 10;
  size_t new_expected_memory_size = new_expected_size * sizeof(int);

  long int expected_sum = 0;
  for (size_t i = 0; i < expected_size + 1; i++) {
    testMV.push(data[i]);
    expected_sum += data[i];

    TEST_ASSERT_EQUAL((i < expected_size) ? i + 1 : expected_size,
                      testMV.point_count());
  }
  expected_sum -= data[0];

  TEST_ASSERT_EQUAL(expected_size, testMV.size());
  TEST_ASSERT_EQUAL(expected_memory_size, testMV.size_of_memory());

  long int old_average = testMV.get();
  testMV.grow(new_expected_size);
  TEST_ASSERT_EQUAL(new_expected_size, testMV.size());
  TEST_ASSERT_EQUAL(new_expected_memory_size, testMV.size_of_memory());
  TEST_ASSERT_EQUAL(expected_size, testMV.point_count());
  TEST_ASSERT_EQUAL(old_average, testMV.get());

  testMV.push(data[6]);
  expected_sum += data[6];
  TEST_ASSERT_EQUAL(expected_size + 1, testMV.point_count());
  TEST_ASSERT_EQUAL(expected_sum / 6, testMV.get());
}

void test_smallerGrow(void) {
  DataTomeMvAvg<int, long int> testMV(5);
  size_t expected_size = 5;
  size_t expected_memory_size = expected_size * sizeof(int);
  size_t new_unexpected_size = 3;

  for (size_t i = 0; i < expected_size + 1; i++) {
    testMV.push(data[i]);

    TEST_ASSERT_EQUAL((i < expected_size) ? i + 1 : expected_size,
                      testMV.point_count());
  }

  TEST_ASSERT_EQUAL(expected_size, testMV.size());
  TEST_ASSERT_EQUAL(expected_memory_size, testMV.size_of_memory());

  testMV.grow(new_unexpected_size);

  TEST_ASSERT_EQUAL(expected_size, testMV.size());
  TEST_ASSERT_EQUAL(expected_memory_size, testMV.size_of_memory());
  TEST_ASSERT_EQUAL(expected_size, testMV.point_count());
}

void test_clear(void) {
  DataTomeMvAvg<int, long int> testMV(5);

  testMV.push(data[0]);

  TEST_ASSERT_EQUAL(data[0], testMV.get());

  testMV.clear();
  TEST_ASSERT_EQUAL(0, testMV.get());
}

void test_partialAverage(void) {
  DataTomeMvAvg<int, long int> testMV(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = testMV.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    testMV.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_sum += data[i];
  }

  TEST_ASSERT_EQUAL((mock_sum / partial_size), testMV.partial_get(partial_id));
}

void test_partialSizeAndPointCount(void) {
  DataTomeMvAvg<int, long int> testMV(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = testMV.partial_create(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    testMV.push(data[i]);
    TEST_ASSERT_EQUAL((i < partial_size) ? i + 1 : partial_size,
                      testMV.partial_point_count(partial_id));
  }

  TEST_ASSERT_EQUAL(partial_size, testMV.partial_size(partial_id));
  TEST_ASSERT_EQUAL(partial_size, testMV.partial_point_count(partial_id));
}

void process() {
  UNITY_BEGIN();

  RUN_TEST(test_getAverage);
  RUN_TEST(test_getFrontAndBackElements);
  RUN_TEST(test_getElementsByIndex);
  RUN_TEST(test_sizeGrowAndPointCount);
  RUN_TEST(test_smallerGrow);
  RUN_TEST(test_clear);

  RUN_TEST(test_partialAverage);
  RUN_TEST(test_partialSizeAndPointCount);

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