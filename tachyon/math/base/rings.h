#ifndef TACHYON_MATH_BASE_RINGS_H_
#define TACHYON_MATH_BASE_RINGS_H_

#include <type_traits>

#include "tachyon/base/template_util.h"
#include "tachyon/math/base/groups.h"

namespace tachyon::math {

template <typename F>
class Ring : public AdditiveGroup<F>, public MultiplicativeSemigroup<F> {
 public:
  template <
      typename InputIterator,
      std::enable_if_t<std::is_same_v<F, base::iter_value_t<InputIterator>>>* =
          nullptr>
  constexpr static F SumOfProducts(InputIterator a_first, InputIterator a_last,
                                   InputIterator b_first,
                                   InputIterator b_last) {
    F sum = F::Zero();
    while (a_first != a_last) {
      sum += (*a_first * *b_first);
      ++a_first;
      ++b_first;
    }
    return sum;
  }

  template <typename Container>
  constexpr static F SumOfProducts(Container&& a, Container&& b) {
    return SumOfProducts(std::begin(a), std::end(a), std::begin(b),
                         std::end(b));
  }
};

}  // namespace tachyon::math

#endif  // TACHYON_MATH_BASE_RINGS_H_