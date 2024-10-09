#ifndef PONCHAT_FLAGS_FLAGS_H_
#define PONCHAT_FLAGS_FLAGS_H_

#include <bitset>
#include <type_traits>

namespace pon_chat::flags {

template <typename EnumT>
class Flags {
    static_assert(std::is_enum_v<EnumT>,
                  "Flags can only be specialized for enum types");

    using UnderlyingT =
        typename std::make_unsigned_t<typename std::underlying_type_t<EnumT>>;

  public:
    Flags(EnumT e, bool value = true) noexcept;
    Flags& set(EnumT e, bool value = true) noexcept;
    Flags& reset(EnumT e) noexcept;
    Flags& reset() noexcept;

    [[nodiscard]] bool all() const noexcept;
    [[nodiscard]] bool any() const noexcept;
    [[nodiscard]] bool none() const noexcept;
    [[nodiscard]] constexpr std::size_t size() const noexcept;
    [[nodiscard]] std::size_t count() const noexcept;

    constexpr bool operator[](EnumT e) const;

  private:
    static constexpr UnderlyingT underlying(EnumT e);
    std::bitset<underlying(EnumT::SIZE)> bits_;
};

}  // namespace pon_chat::flags

#include "../../../src/flags_impl.h"

#endif  // PONCHAT_FLAGS_FLAGS_H_
