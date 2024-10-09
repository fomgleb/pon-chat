#ifndef PONCHAT_FLAGS_FLAGS_IMPL_H_
#define PONCHAT_FLAGS_FLAGS_IMPL_H_

#include "pon-chat/flags/flags.h"

namespace pon_chat::flags {

template <typename EnumT>
Flags<EnumT>::Flags(EnumT e, bool value) noexcept
{}

template <typename EnumT>
Flags<EnumT>& Flags<EnumT>::set(EnumT e, bool value) noexcept
{
    bits_.set(underlying(e), value);
    return *this;
}

template <typename EnumT>
Flags<EnumT>& Flags<EnumT>::reset(EnumT e) noexcept
{
    set(e, false);
    return *this;
}

template <typename EnumT>
Flags<EnumT>& Flags<EnumT>::reset() noexcept
{
    bits_.reset();
    return *this;
}

template <typename EnumT>
[[nodiscard]] bool Flags<EnumT>::all() const noexcept
{
    return bits_.all();
}

template <typename EnumT>
[[nodiscard]] bool Flags<EnumT>::any() const noexcept
{
    return bits_.any();
}

template <typename EnumT>
[[nodiscard]] bool Flags<EnumT>::none() const noexcept
{
    return bits_.none();
}

template <typename EnumT>
[[nodiscard]] constexpr std::size_t Flags<EnumT>::size() const noexcept
{
    return bits_.size();
}

template <typename EnumT>
[[nodiscard]] std::size_t Flags<EnumT>::count() const noexcept
{
    return bits_.count();
}

template <typename EnumT>
constexpr bool Flags<EnumT>::operator[](EnumT e) const
{
    return bits_[underlying(e)];
}

template <typename EnumT>
constexpr typename Flags<EnumT>::UnderlyingT Flags<EnumT>::underlying(EnumT e)
{
    return static_cast<UnderlyingT>(e);
}

}  // namespace pon_chat::flags

#endif  // PONCHAT_FLAGS_FLAGS_IMPL_H_
