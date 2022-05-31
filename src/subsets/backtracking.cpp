#include "assignment/subsets/backtracking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set, set_bit, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetsBacktracking::generate(const std::vector<int>& set) const {
    assert(set.size() <= 16);

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    auto subsets = std::vector<std::vector<int>>();
    subsets.reserve(num_subsets);

    // вызов вспомогательной функции: обратите внимание на начальное значение индекса и маски
    generate(set, -1, 0, subsets);

    return subsets;
  }

  void SubsetsBacktracking::generate(const std::vector<int>& set, int index, int mask,
                                     std::vector<std::vector<int>>& subsets) const {
    assert(mask >= 0 && index >= -1);

    // Ограничение: рассмотрены все элементы множества
    if (index == static_cast<int>(set.size()) - 1) {

      // ... сохранение полученного подмножества
      std::vector<int> cur;
      for (int i = 0; i < set.size(); i++) {
        if (is_bit_set(mask, i)) {
          cur.push_back(i);
        }
      }
      subsets.push_back(cur);

      return;  // возвращаемся по дереву рекурсии
    }

    index += 1;  // рассматриваем следующий элемент

    // здесь должны быть рекурсивные вызовы ...
    // включаем или не включаем элемент с текущим индексом в подмножество (используя битовую маску)
    generate(set, index, mask + (1 << index), subsets);
    generate(set, index, mask, subsets);

  }

}  // namespace assignment