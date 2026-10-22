#include <numeric>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <deque>
#include <limits>

using std::cin;
using std::cout;
using std::deque;
using std::ifstream;
using std::istream_iterator;
using std::list;
using std::map;
using std::ofstream;
using std::ostream_iterator;
using std::set;
using std::string;
using std::vector;

bool ReadInt(const string& prompt, int* value) {
  while (true) {
    cout << prompt;
    if (cin >> *value) {
      return true;
    }
    if (cin.eof()) {
      return false;
    }
    cout << "Ошибка: введите целое число.\n";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

bool ReadPositiveInt(const string& prompt, int* value) {
  while (ReadInt(prompt, value)) {
    if (*value > 0) return true;
    cout << "Ошибка: число должно быть больше нуля.\n";
  }
  return false;
}

bool ReadVector(const string& name, vector<int>* values, int min_size = 1,
                bool even_size = false) {
  int size = 0;
  while (true) {
    if (!ReadInt("Введите количество элементов " + name + ": ", &size)) {
      return false;
    }
    if (size >= min_size && (!even_size || size % 2 == 0)) break;
    cout << "Ошибка: размер должен быть не меньше " << min_size;
    if (even_size) cout << " и быть четным";
    cout << ".\n";
  }

  values->clear();
  values->reserve(size);
  cout << "Введите " << size << " целых чисел:\n";
  for (int i = 0; i < size; ++i) {
    int value = 0;
    if (!ReadInt("Элемент " + std::to_string(i + 1) + ": ", &value)) {
      return false;
    }
    values->push_back(value);
  }
  return true;
}

void PrintVector(const vector<int>& values) {
  for (auto it = values.begin(); it != values.end(); ++it) cout << *it << ' ';
  cout << '\n';
}

void PrintDeque(const deque<int>& values) {
  for (auto it = values.begin(); it != values.end(); ++it) cout << *it << ' ';
  cout << '\n';
}

void Task1() {
  cout << "\nЗадание 1.1. Чтение целых чисел из файла.\n";
  string filename;
  cout << "Введите имя входного файла: ";
  cin >> filename;
  ifstream input(filename);
  if (!input) {
    cout << "Не удалось открыть файл.\n";
    return;
  }
  vector<int> values((istream_iterator<int>(input)),
                     istream_iterator<int>());
  if (!input.eof()) {
    cout << "Ошибка: файл содержит значение, которое не является целым числом.\n";
    return;
  }
  cout << "Числа в исходном порядке: ";
  std::copy(values.begin(), values.end(), ostream_iterator<int>(std::cout, " "));
  cout << '\n';
}

void Task2() {
  cout << "\nЗадание 2.6. Вставка элементов в вектор и дек.\n";
  vector<int> values;
  if (!ReadVector("вектора V", &values, 2, true)) return;
  int size = 0;
  while (true) {
    if (!ReadInt("Введите четное количество элементов дека D: ", &size)) return;
    if (size >= 2 && size % 2 == 0) break;
    cout << "Ошибка: количество должно быть положительным и четным.\n";
  }
  deque<int> items;
  cout << "Введите " << size << " целых чисел для дека D:\n";
  for (int i = 0; i < size; ++i) {
    int value = 0;
    if (!ReadInt("Элемент " + std::to_string(i + 1) + ": ", &value)) return;
    items.push_back(value);
  }
  const auto original_values = values;
  const auto original_items = items;
  values.insert(values.end(), original_items.begin(),
                original_items.begin() + original_items.size() / 2);
  items.insert(items.begin(), original_values.rbegin(),
               original_values.rbegin() + original_values.size() / 2);
  cout << "Вектор V после вставки: ";
  PrintVector(values);
  cout << "Дек D после вставки: ";
  PrintDeque(items);
}

void Task3() {
  cout << "\nЗадание 3.8. Удаление элементов с нечетными номерами.\n";
  vector<int> values;
  if (!ReadVector("вектора V", &values)) return;
  auto it = values.begin();
  while (it != values.end()) {
    it = values.erase(it);
    if (it != values.end()) ++it;
  }
  cout << "Результат: ";
  PrintVector(values);
}

void Task4() {
  cout << "\nЗадание 4.2. Вывод чисел с нечетными порядковыми номерами из файла.\n";
  string filename;
  cout << "Введите имя входного файла: ";
  cin >> filename;
  ifstream input(filename);
  if (!input) {
    cout << "Не удалось открыть файл.\n";
    return;
  }
  vector<int> values((istream_iterator<int>(input)),
                     istream_iterator<int>());
  if (!input.eof()) {
    cout << "Ошибка: файл содержит значение, которое не является целым числом.\n";
    return;
  }
  cout << "Числа с нечетными порядковыми номерами: ";
  size_t index = 0;
  std::remove_copy_if(values.begin(), values.end(),
                      ostream_iterator<int>(std::cout, " "),
                      [&index](int) { return index++ % 2 == 1; });
  cout << '\n';
}

void Task5() {
  cout << "\nЗадание 5.1. Удаление второго нулевого элемента.\n";
  vector<int> values;
  if (!ReadVector("вектора V", &values)) return;
  auto first_zero = std::find(values.begin(), values.end(), 0);
  if (first_zero != values.end()) {
    auto second_zero = std::find(first_zero + 1, values.end(), 0);
    if (second_zero != values.end()) values.erase(second_zero);
  }
  cout << "Результат: ";
  PrintVector(values);
}

void Task6() {
  cout << "\nЗадание 6.9. Дублирование первой половины списка в обратном порядке.\n";
  int size = 0;
  while (true) {
    if (!ReadInt("Введите четное количество элементов списка L1: ", &size)) return;
    if (size >= 2 && size % 2 == 0) break;
    cout << "Ошибка: количество должно быть положительным и четным.\n";
  }
  list<int> first;
  cout << "Введите " << size << " целых чисел для L1:\n";
  for (int i = 0; i < size; ++i) {
    int value = 0;
    if (!ReadInt("Элемент " + std::to_string(i + 1) + ": ", &value)) return;
    first.push_back(value);
  }
  int second_size = 0;
  while (true) {
    if (!ReadInt("Введите четное количество элементов списка L2: ", &second_size)) return;
    if (second_size >= 2 && second_size % 2 == 0) break;
    cout << "Ошибка: количество должно быть положительным и четным.\n";
  }
  list<int> second;
  cout << "Введите " << second_size << " целых чисел для L2:\n";
  for (int i = 0; i < second_size; ++i) {
    int value = 0;
    if (!ReadInt("Элемент " + std::to_string(i + 1) + ": ", &value)) return;
    second.push_back(value);
  }
  auto middle_first = first.begin();
  std::advance(middle_first, first.size() / 2);
  std::reverse_copy(first.begin(), middle_first, std::back_inserter(first));

  auto middle_second = second.begin();
  std::advance(middle_second, second.size() / 2);
  second.insert(second.end(), std::make_reverse_iterator(middle_second),
                second.rend());
  cout << "L1 после дублирования: ";
  for (auto it = first.begin(); it != first.end(); ++it) cout << *it << ' ';
  cout << "\nL2 после дублирования: ";
  for (auto it = second.begin(); it != second.end(); ++it) cout << *it << ' ';
  cout << '\n';
}

void Task7() {
  cout << "\nЗадание 7.2. Три наименьших элемента вектора.\n";
  vector<int> values;
  if (!ReadVector("вектора V", &values, 3)) return;
  std::partial_sort(values.begin(), values.begin() + 3, values.end());
  cout << "Три наименьших элемента по возрастанию: ";
  std::copy(values.begin(), values.begin() + 3, ostream_iterator<int>(std::cout, " "));
  cout << '\n';
}

void Task8() {
  cout << "\nЗадание 8.2. Формирование строк по соседним словам.\n";
  int size = 0;
  if (!ReadPositiveInt("Введите количество английских слов (не менее 2): ", &size)) return;
  while (size < 2) {
    cout << "Ошибка: необходимо не менее двух слов.\n";
    if (!ReadPositiveInt("Введите количество английских слов: ", &size)) return;
  }
  list<string> words;
  cout << "Введите " << size << " непустых английских слов:\n";
  for (int i = 0; i < size; ++i) {
    string word;
    while (true) {
      cout << "Слово " << i + 1 << ": ";
      if (!(cin >> word)) return;
      bool valid = !word.empty();
      for (unsigned char ch : word) {
        valid = valid && ch < 128 && std::isalpha(ch);
      }
      if (valid) break;
      cout << "Ошибка: используйте только английские буквы.\n";
    }
    words.push_back(word);
  }
  list<string> result;
  auto operation = [](const string& left, const string& right) {
    return string(1, left.front()) + right.back();
  };
  std::adjacent_difference(words.begin(), words.end(), std::back_inserter(result), operation);
  if (!result.empty()) result.erase(result.begin());
  cout << "Результат: ";
  for (auto it = result.begin(); it != result.end(); ++it) cout << *it << ' ';
  cout << '\n';
}

void Task9() {
  cout << "\nЗадание 9.1. Подсчет векторов, содержащих все элементы V0.\n";
  vector<int> base;
  if (!ReadVector("вектора V0", &base)) return;
  int count = 0;
  if (!ReadPositiveInt("Введите количество векторов N: ", &count)) return;
  set<int> base_set(base.begin(), base.end());
  int matching = 0;
  for (int i = 0; i < count; ++i) {
    vector<int> values;
    cout << "Вектор V" << i + 1 << ":\n";
    if (!ReadVector("V" + std::to_string(i + 1), &values,
                    static_cast<int>(base.size()))) return;
    set<int> current_set(values.begin(), values.end());
    if (std::includes(current_set.begin(), current_set.end(),
                      base_set.begin(), base_set.end())) {
      ++matching;
    }
  }
  cout << "Количество подходящих векторов: " << matching << '\n';
}

void Task10() {
  cout << "\nЗадание 10.1. Подсчет повторений чисел.\n";
  vector<int> values;
  if (!ReadVector("вектора V", &values)) return;
  map<int, int> counts;
  for (auto it = values.begin(); it != values.end(); ++it) ++counts[*it];
  cout << "Число и количество повторений (по возрастанию):\n";
  for (auto it = counts.begin(); it != counts.end(); ++it) {
    cout << it->first << " — " << it->second << '\n';
  }
}

int main() {
  cout << "Выберите задачу для запуска:\n"
       << "1 — Задание 1.1\n2 — Задание 2.6\n3 — Задание 3.8\n"
       << "4 — Задание 4.2\n5 — Задание 5.1\n6 — Задание 6.9\n"
       << "7 — Задание 7.2\n8 — Задание 8.2\n9 — Задание 9.1\n"
       << "10 — Задание 10.1\n0 — Выход\n";
  while (true) {
    int choice = 0;
    if (!ReadInt("Ваш выбор: ", &choice)) break;
    switch (choice) {
      case 0: return 0;
      case 1: Task1(); break;
      case 2: Task2(); break;
      case 3: Task3(); break;
      case 4: Task4(); break;
      case 5: Task5(); break;
      case 6: Task6(); break;
      case 7: Task7(); break;
      case 8: Task8(); break;
      case 9: Task9(); break;
      case 10: Task10(); break;
      default: cout << "Ошибка: выберите пункт от 0 до 10.\n";
    }
  }
  return 0;
}
