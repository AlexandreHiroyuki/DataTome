#include <DataTomeMvAvg.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

long int data[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

void test_get_average(void) {
  DataTomeMvAvg<int, long int> TestMV(5);

  TestMV.push(data[0]).push(data[1]).push(data[2]);

  long int mock_average = (data[0] + data[1] + data[2]) / 3;
  long int mock_brute_average = (data[1] + data[2]) / 2;
  TEST_ASSERT_EQUAL(mock_average, TestMV.get());
  TEST_ASSERT_EQUAL(mock_brute_average, TestMV.get_by_brute(2));
}

void test_get_front_n_back_elements(void) {
  DataTomeMvAvg<int, long int> TestMV(5);

  TestMV.push(data[0]).push(data[1]).push(data[2]).push(data[3]).push(data[4]);

  TEST_ASSERT_EQUAL(data[4], TestMV.front());
  TEST_ASSERT_EQUAL(data[0], TestMV.back());
}

void test_get_elements_by_index(void) {
  DataTomeMvAvg<int, long int> TestMV(5);

  TestMV.push(data[0]).push(data[1]).push(data[2]);

  TEST_ASSERT_EQUAL(data[2], TestMV[0]);
  TEST_ASSERT_EQUAL(data[1], TestMV[1]);
  TEST_ASSERT_EQUAL(data[0], TestMV[2]);
  TEST_ASSERT_EQUAL(data[0], TestMV.at_index(0));
  TEST_ASSERT_EQUAL(data[1], TestMV.at_index(1));
  TEST_ASSERT_EQUAL(data[2], TestMV.at_index(2));
}

void test_size_n_resize(void) {
  DataTomeMvAvg<int, long int> TestMV(5);
  size_t expected_size = 5;
  size_t new_expected_size = 10;

  long int mock_sum = 0;
  for (size_t i = 0; i < expected_size + 1; i++) {
    TestMV.push(data[i]);
    mock_sum += data[i];
  }
  mock_sum -= data[0];

  TEST_ASSERT_EQUAL(expected_size, TestMV.size());

  long int old_average = TestMV.get();
  TestMV.resize(new_expected_size);
  TEST_ASSERT_EQUAL(new_expected_size, TestMV.size());
  TEST_ASSERT_EQUAL(old_average, TestMV.get());

  TestMV.push(data[6]);
  mock_sum += data[6];
  TEST_ASSERT_EQUAL(mock_sum / 6, TestMV.get());
}

void test_clear(void) {
  DataTomeMvAvg<int, long int> TestMV(5);

  TestMV.push(data[0]);

  TEST_ASSERT_EQUAL(data[0], TestMV.get());

  TestMV.clear();
  TEST_ASSERT_EQUAL(0, TestMV.get());
}

void test_partials(void) {
  DataTomeMvAvg<int, long int> TestMV(10);
  size_t partial_size = 3;
  size_t data_count = 5;

  size_t partial_id = TestMV.create_partial(partial_size);

  for (size_t i = 0; i < data_count; i++) {
    TestMV.push(data[i]);
  }

  long int mock_sum = 0;
  for (size_t i = data_count - 1; i > data_count - partial_size - 1; i--) {
    mock_sum += data[i];
  }

  TEST_ASSERT_EQUAL((mock_sum / partial_size), TestMV.get_partial(partial_id));
}

void process() {
  UNITY_BEGIN();

  RUN_TEST(test_get_average);
  RUN_TEST(test_get_front_n_back_elements);
  RUN_TEST(test_get_elements_by_index);
  RUN_TEST(test_size_n_resize);
  RUN_TEST(test_clear);
  RUN_TEST(test_partials);

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