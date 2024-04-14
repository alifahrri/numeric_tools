#ifndef NMTOOLS_ARRAY_AS_STATIC_HPP
#define NMTOOLS_ARRAY_AS_STATIC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/array/ndarray.hpp" // for nmtools_static_vector

namespace nmtools::array
{
    template <typename attribute_t, auto max_dim=8>
    struct as_static_t
    {
        using attribute_type = attribute_t;

        attribute_type attribute;

        auto operator()() const noexcept
        {
            if constexpr (meta::is_dynamic_index_array_v<attribute_type>) {
                using element_type = meta::get_element_type_t<attribute_t>;
                using result_type  = nmtools_static_vector<element_type,max_dim>;
                auto result = result_type{};
                result.resize(attribute.size());
                for (size_t i=0; i<len(result); i++) {
                    at(result,i) = at(attribute,i);
                }
                return result;
            } else {
                return fwd_attribute(attribute);
            }
        }
    };

    template <auto max_dim=8, typename attribute_t>
    auto as_static(const attribute_t& attribute)
    {
        auto mapper = as_static_t<attribute_t,max_dim>{attribute};
        return mapper();
    } // as_static
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_AS_STATIC_HPP