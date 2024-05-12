#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/alias.hpp"
#include "nmtools/utility/ct_map.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/utility/tuple_slice.hpp"
#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/utils/isclose/isclose.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::meta
{
    using view::resolve_attribute_type;
    using view::resolve_attribute_type_t;

    template <typename F, typename operands_t, typename...new_operands_t>
    struct pack_operands_type;

    template <typename F, typename...new_operands_t>
    struct pack_operands_type<F,empty_operands_t,new_operands_t...>
    {
        using type = nmtools_tuple<fwd_operand_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, template<typename...>typename operand_tuple, typename...operands_t, typename...new_operands_t>
    struct pack_operands_type<F,operand_tuple<operands_t...>,new_operands_t...>
    {
        using type = nmtools_tuple<operands_t...,fwd_operand_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, typename operands_t, typename...new_operands_t>
    using pack_operands_type_t = type_t<pack_operands_type<F,operands_t,new_operands_t...>>;
} // namespace nmtools::meta

namespace nmtools::functional
{
    // TODO: refactor to not use empty_operands_t & empty_attributes_t
    constexpr inline auto EmptyOperands   = meta::empty_operands_t{};
    constexpr inline auto EmptyAttributes = meta::empty_attributes_t{};

    template <typename operand_pack_t, typename...operands_t>
    constexpr auto initialize_operands(meta::empty_operands_t,const operands_t&...operands)
    {
        return operand_pack_t{fwd_operand(operands)...};
    }

    template <typename operand_pack_t, template<typename...>typename operand_tuple, typename...operands_t, template<auto...>typename sequence, auto...Is, typename...new_operands_t>
    constexpr auto initialize_operands(sequence<Is...>,const operand_tuple<operands_t...>& operands,const new_operands_t&...new_operands)
    {
        return operand_pack_t{nmtools::get<Is>(operands)...,fwd_operand(new_operands)...};
    }

    template <typename operand_pack_t, template<typename...>typename operand_tuple, typename...operands_t, typename...new_operands_t>
    constexpr auto initialize_operands(const operand_tuple<operands_t...>& operands,const new_operands_t&...new_operands)
    {
        return initialize_operands<operand_pack_t>(meta::make_index_sequence_v<sizeof...(operands_t)>, operands, new_operands...);
    }

    template <typename F, typename operands_t=meta::empty_operands_t, typename attributes_t=meta::empty_attributes_t>
    struct functor_t;

    template <typename functors_t, typename operands_t=meta::empty_operands_t>
    struct functor_composition_t;

    template <typename F>
    struct apply_function_t;

    template <typename F, template<typename...>typename tuple, typename...new_operands_t>
    constexpr auto apply_function(const F& function, const tuple<new_operands_t...>& new_operands)
    {
        // TODO: better error handling
        if constexpr (meta::is_maybe_v<F>) {
            return apply_function(*function, new_operands);
        } else {
            // Triggers gcc error:
            // error: initializations for multiple members of 'std::_Optional_payload_base
            #if defined(__clang__)
            auto result = apply_function_t<F>{function}.apply(new_operands);
            if constexpr (meta::is_tuple_v<decltype(result)>) {
                meta::template_for<meta::len_v<decltype(result)>>([&](auto index){
                    using value_t = meta::at_t<decltype(result),decltype(index)::value>;
                    static_assert( !meta::is_fail_v<value_t>
                        , "the return of apply function is invalid!" );
                });
            } else {
                static_assert( !meta::is_fail_v<decltype(result)>
                    , "the return of apply function is invalid!" );
            }
            return result;
            #else
            return apply_function_t<F>{function}.apply(new_operands);
            #endif
        }
    } // apply_function

    /**
     * @brief Type constructor to compose functors.
     * 
     * Note that after composing, functor's attributes can't be specified.
     * Can only specify operands, or further composing with another functor/composition.
     * 
     * @tparam tuple 
     * @tparam functors_t 
     * @tparam operands_t 
     */
    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct functor_composition_t<tuple<functors_t...>,operands_t>
    {
        using functors_type = const tuple<functors_t...>;
        using operands_type = const operands_t;

        functors_type functors;
        operands_type operands;

        constexpr functor_composition_t()
            : functors{}
            , operands{}
        {}

        constexpr functor_composition_t(functors_type& functors)
            : functors(functors)
            , operands{}
        {}

        constexpr functor_composition_t(functors_type& functors, const operands_t& operands)
            : functors(functors)
            , operands{operands}
        {}

        nmtools_func_attribute
        ~functor_composition_t() = default;

        // TODO: also consider number of output, now that support multiple return
        static constexpr auto arity = [](){
            using functors = meta::type_list<functors_t...>;
            constexpr auto n_functors = sizeof...(functors_t);
            auto arity = 0;
            meta::template_for<n_functors>([&](auto index){
                constexpr auto I = decltype(index)::value;
                auto arity_i = meta::type_list_at_t<I,functors>::arity;
                // NOTE: the result from one functor will be passed to the following functor, so -1 except the right-most
                arity += (I == n_functors - 1 ? arity_i : (arity_i-1));
            });
            return arity;
        }();

        // NOTE: after composing functor, specifying attribute not supported anymore

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            return apply_function(*this,pack_operands(new_operands...));
        } // operator()
    }; // functor_composition_t

    template <template<typename...>typename tuple, typename...functors_t>
    nmtools_func_attribute
    functor_composition_t(const tuple<functors_t...>&) -> functor_composition_t<tuple<functors_t...>>;

    /**
     * @brief Type constructor for functor type.
     * 
     * Takes fmap, can curry operands and compose with another functors.
     * 
     * @tparam F 
     * @tparam operands_t 
     * @tparam attributes_t 
     */
    template <typename F, typename operands_t, typename attributes_t>
    struct functor_t
    {
        using fmap_type       = const F;
        using operands_type   = const operands_t;
        using attributes_type = const attributes_t;

        // TODO: also consider number of output, now that support multiple return
        static constexpr auto arity = [](){
            if constexpr (meta::is_same_v<operands_t,meta::empty_operands_t>) {
                return F::arity;
            } else {
                return F::arity - meta::len_v<operands_t>;
            }
        }();

        fmap_type       fmap;
        operands_type   operands;
        attributes_type attributes;

        // error on clang but fine on gcc
        // constexpr functor_t() = default;

        // error on gcc but fine on clang
        // constexpr functor_t() {}

        constexpr functor_t()
            : fmap{}
            , operands{}
            , attributes{}
        {}

        constexpr functor_t(const F& fmap)
            : fmap(fmap)
            , operands{}
            , attributes{}
        {}
        
        constexpr functor_t(const F& fmap, const operands_t& operands, const attributes_t& attributes)
            : fmap(fmap)
            , operands(operands)
            , attributes(attributes)
        {}

        template <typename other_f, typename other_operands, typename other_attributes>
        constexpr auto operator*(const functor_t<other_f,other_operands,other_attributes>& other) const noexcept
        {
            // TODO: check arity, only compose if there's enough arity left
            using other_functor_t = functor_t<other_f,other_operands,other_attributes>;
            using composition_t   = functor_composition_t<nmtools_tuple<functor_t,other_functor_t>>;
            return composition_t{{*this,other}};
        } // operator*

        template <template<typename...>typename tuple, typename...functors_t, typename m_operands_t>
        constexpr auto operator*(const functor_composition_t<tuple<functors_t...>,m_operands_t>& other) const noexcept
        {
            // TODO: check arity, only compose if there's enough arity left
            auto functors = utility::tuple_cat(nmtools_tuple{*this},other.functors);
            return functor_composition_t{functors};
        }

        template <typename m_attribute_t>
        constexpr auto operator[](const m_attribute_t& new_attribute) const noexcept
        {
            // NOTE: since operator[] can only takes SINGLE argument,
            // use nested operator[] to allow specifying multiple attributes.
            if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                // prefer to make functor copy-able and not taking ref/address
                // so it is safe to return local copy
                // TODO: use fwd_attribute
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                using function_t = functor_t<F,operands_t,nmtools_tuple<new_attribute_t>>;
                return function_t{fmap,operands,nmtools_tuple{view::init_attribute<new_attribute_t>(new_attribute)}};
            } else {
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                auto new_attributes = utility::tuple_append(attributes,view::init_attribute<new_attribute_t>(new_attribute));
                using new_attributes_t = decltype(new_attributes);
                using function_t = functor_t<F,operands_t,new_attributes_t>;
                return function_t{fmap,operands,new_attributes};
            }
        } // operator[]

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            return apply_function(*this,pack_operands(new_operands...));
        } // operator()
    }; // functor_t

    template <typename F>
    nmtools_func_attribute
    functor_t(const F) -> functor_t<F,meta::empty_operands_t,meta::empty_attributes_t>;

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , template<typename...>typename right_tp, typename...right_functors_t, typename right_operands_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_composition_t<right_tp<right_functors_t...>,right_operands_t>& right) noexcept
    {
        // NOTE: no need to check arity, assume will be applied if operands is complete
        auto joined_functors = utility::tuple_cat(left.functors,right.functors);
        return functor_composition_t{joined_functors};
    } // operator*

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , typename F, typename operands_t, typename attributes_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_t<F,operands_t,attributes_t>& right) noexcept
    {
        auto joined_functors = utility::tuple_append(left.functors,right);
        return functor_composition_t{joined_functors};
    } // operator*

    template <typename F, typename operands_t, typename attributes_t>
    struct apply_function_t<
        functor_t<F,operands_t,attributes_t>
    > {
        using functor_type = functor_t<F,operands_t,attributes_t>;

        static constexpr auto arity = functor_type::arity;

        functor_type functor;

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const
        {
            if constexpr (arity == 0 && sizeof...(m_operands_t) == 0) {
                // assume operands is empty_operands_t
                static_assert( meta::is_same_v<operands_t,meta::empty_operands_t>
                    , "internal error: expect operands is empty for arity 0" );
                return functor.fmap(functor.attributes,functor.operands);
            } else if constexpr (arity > 0 && sizeof...(m_operands_t) == 0) {
                return (*this);
            } else if constexpr (sizeof...(m_operands_t) > arity) {
                auto m_new_operands = pack_operands(new_operands...);
                auto operand = utility::tuple_slice(m_new_operands,None,meta::ct_v<arity>);
                auto curried_operands = utility::tuple_slice(m_new_operands,meta::ct_v<arity>);
                static_assert( meta::len_v<decltype(operand)> == arity );

                auto result = apply(operand);

                auto result_operands = [&](){
                    if constexpr (meta::is_tuple_v<decltype(result)>) {
                        return cat_operands(result,curried_operands);
                    } else {
                        return push_operands(result,curried_operands);
                    }
                }();
                return result_operands;
            } else {
                using operands_pack_t = meta::pack_operands_type_t<F,operands_t,m_operands_t...>;
                using function_t = functor_t<F,operands_pack_t,attributes_t>;
                [[maybe_unused]] auto function = function_t{functor.fmap
                    ,initialize_operands<operands_pack_t>(functor.operands,new_operands...)
                    ,functor.attributes
                };
                if constexpr (sizeof...(m_operands_t) < arity) {
                    // currying
                    return function;
                } else {
                    // apply
                    if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                        // NOTE: avoid passing empty_attributes_t to fmap, use empty tuple instead
                        return function.fmap(nmtools_tuple<>{},function.operands);
                    } else {
                        return function.fmap(function.attributes,function.operands);
                    }
                }
            }
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t, auto...Is>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands, meta::index_sequence<Is...>) const
        {
            return (*this)(nmtools::get<Is>(new_operands)...);
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands) const
        {
            return apply(new_operands,meta::make_index_sequence_v<sizeof...(m_operands_t)>);
        }
    }; // apply_function_t<functor_t<...>>

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct apply_function_t<
        functor_composition_t<tuple<functors_t...>,operands_t>
    > {
        using composition_type = functor_composition_t<tuple<functors_t...>,operands_t>;
        using functors_type = const tuple<functors_t...>;

        static constexpr auto arity = composition_type::arity;

        composition_type functors;

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const
        {
            using operands_pack_t = meta::pack_operands_type_t<void,operands_t,m_operands_t...>;
            // TODO: rename initialize_operands to forward_array/forward_operand
            auto operands_ = initialize_operands<operands_pack_t>(functors.operands,new_operands...);
            constexpr auto n_operands = meta::len_v<operands_pack_t>;

            auto functor = at(functors.functors,meta::ct_v<-1>);
            using functor_type = meta::remove_cvref_t<decltype(functor)>;
            constexpr auto functor_arity = functor_type::arity;

            if constexpr (n_operands >= functor_arity) {
                auto operand = utility::tuple_slice(operands_,None,meta::ct_v<functor_arity>);
                auto result  = apply_function_t<functor_type>{functor}.apply(operand);

                auto curried_operands = utility::tuple_slice(operands_,meta::ct_v<functor_arity>);
                [[maybe_unused]]
                constexpr auto n_curried_ops = meta::len_v<decltype(curried_operands)>;

                auto result_operands = [&](){
                    if constexpr (meta::is_tuple_v<decltype(result)>) {
                        return cat_operands(result,curried_operands);
                    } else {
                        return push_operands(result,curried_operands);
                    }
                }();

                auto curried_functors = utility::tuple_slice(functors.functors,None,meta::ct_v<-1>);
                using curried_functors_t = meta::remove_cvref_t<decltype(curried_functors)>;
                constexpr auto n_curried_functors = meta::len_v<curried_functors_t>;

                if constexpr (n_curried_functors > 0) {
                    return apply_function(functor_composition_t{curried_functors},result_operands);
                } else if constexpr (n_curried_ops > 0) {
                    return result_operands;
                } else {
                    return result;
                }
            } else if constexpr ((arity - n_operands) > 0) {
                // currying
                using function_t = functor_composition_t< tuple<functors_t...>,operands_pack_t>;
                auto function = function_t(functors.functors,operands_);
                return function;
            }
        } // operator()

        template <template<typename...>typename m_tuple, typename...m_operands_t, auto...Is>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands, meta::index_sequence<Is...>) const
        {
            return (*this)(nmtools::get<Is>(new_operands)...);
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands) const
        {
            return apply(new_operands,meta::make_index_sequence_v<sizeof...(m_operands_t)>);
        }
    }; // apply_function_t<functor_composition_t<...>>

    template <typename F>
    nmtools_func_attribute // host device
    apply_function_t(const F&) -> apply_function_t<F>;

    // helper function to "erase" pointer
    template <typename operand_t>
    static constexpr auto get_operand(const operand_t& operand)
        -> meta::conditional_t<
            meta::is_pointer_v<operand_t>
            , const meta::remove_pointer_t<operand_t>&
            , const operand_t&
        >
    {
        if constexpr (meta::is_pointer_v<operand_t>) {
            return *operand;
        } else {
            return operand;
        }
    }

    template <typename F, nm_size_t Arity, nm_size_t N_OUT=1>
    struct fmap_t
    {
        static constexpr auto arity = Arity;
        static constexpr auto n_outputs = N_OUT;
        using arity_type = meta::integral_constant<nm_size_t,arity>;
        using n_outputs_type = meta::integral_constant<nm_size_t,n_outputs>;

        const F fn;
        arity_type m_arity = arity_type{};

        template<
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename operand_tuple, typename...operands_t,
            typename...attributes_t
        >
        constexpr auto expand_operands(sequence<Is...>, const operand_tuple<operands_t...>& operands, const attributes_t&...attributes) const
        {
            return fn(get_operand(nmtools::get<Is>(operands))...,attributes...);
        }

        template<
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...operands_t
        >
        constexpr auto expand_attributes(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<operands_t...>& operands) const
        {
            auto operands_sequence = meta::make_index_sequence_v<sizeof...(operands_t)>;
            return expand_operands(operands_sequence,operands,nmtools::get<Is>(attributes)...);
            }

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...operands_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<operands_t...>& operands) const
        {
            auto attributes_sequence = meta::make_index_sequence_v<sizeof...(attributes_t)>;
            return expand_attributes(attributes_sequence, attributes, operands);
        } // operator()
    };

    template <typename F, nm_size_t Arity>
    fmap_t(F&&,meta::integral_constant<nm_size_t,Arity>) -> fmap_t<F,Arity>;

    template <typename F>
    struct fmap_t<F,0>
    {
        static constexpr auto arity = 0;
        using arity_type = meta::integral_constant<nm_size_t,arity>;

        F fn;
        arity_type m_arity = arity_type{};

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, meta::empty_operands_t) const
        {
            return fn(nmtools::get<Is>(attributes)...);
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, meta::empty_operands_t operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    };

    /**
     * @brief Type constructor for binary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using binary_fmap_t = fmap_t<F,2>;

    template <typename F>
    using nullary_fmap_t = fmap_t<F,0>;

    /**
     * @brief Type constructor for unary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using unary_fmap_t = fmap_t<F,1>;

    /**
     * @brief Type constructor for ternary (arity of 3) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using ternary_fmap_t = fmap_t<F,3>;

    /**
     * @brief Type constructor for quaternary (arity of 4) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using quaternary_fmap_t = fmap_t<F,4>;

    /**
     * @brief Type constructor for quinary (arity of 5) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using quinary_fmap_t = fmap_t<F,5>;

    namespace error
    {
        template <typename...>
        struct GET_FUNCTION_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_FUNCTION_COMPOSITION_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_OPERANDS_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_FUNCTION_OPERANDS_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_GRAPH_UNSUPPORTED : meta::detail::fail_t {};
    }

    template <typename view_t>
    struct get_function_t
    {
        view_t view;

        constexpr auto operator()() const noexcept 
        {
            return error::GET_FUNCTION_UNSUPPORTED<view_t>{};
        }
    }; // get_function_t

    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto get_function(const view::decorator_t<view_t,Ts...>& view)
    {
        using view_type = view::decorator_t<view_t,Ts...>;
        auto get_fn = get_function_t<view_type>{view};
        return get_fn();
    } // get_function

    template <typename view_t>
    struct get_operands_t
    {
        view_t view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (meta::has_operands_fn_v<view_t>) {
                return view.operands();
            } else {
                return error::GET_OPERANDS_UNSUPPORTED<view_t>{};
            }
        }
    };

    template <typename view_t>
    constexpr auto get_operands(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using view_type   = meta::get_maybe_type_t<view_t>;
            using result_type = decltype(get_operands(meta::declval<view_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(view)) {
                return return_type{get_operands(*view)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            using view_type = view_t;
            auto get_operands = get_operands_t<view_type>{view};
            return get_operands();
        }
    }

    template <typename view_t>
    struct get_function_operands_t;

    template <typename view_t>
    struct get_function_composition_t;

    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto get_function_operands(const view::decorator_t<view_t,Ts...>& view)
    {
        using view_type = view::decorator_t<view_t,Ts...>;
        auto get_op = get_function_operands_t<view_type>{view};
        return get_op();
    } // get_function_operands

    template <typename view_type>
    constexpr auto get_function_composition(const view_type& view)
    {
        if constexpr (meta::is_maybe_v<view_type>) {
            using result_type = meta::remove_cvref_t<decltype(get_function_composition(*view))>;
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(view)) {
                return return_type{get_function_composition(*view)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            auto get_fn = get_function_composition_t<view_type>{view};
            return get_fn();
        }
    } // get_function_composition

    template <template<typename...>typename view_t, typename...args_t>
    struct get_function_operands_t<
        view::decorator_t<view_t,args_t...>
    > {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)>);
            constexpr auto N = view_type::arity;
            auto all_operands = meta::template_reduce<N>([&](auto init, auto index){
                const auto& operand = nmtools::at(operands,index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                if constexpr (meta::is_view_v<operand_t>) {
                    return utility::tuple_cat(init, get_function_operands(operand));
                } else if constexpr ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    if constexpr ( meta::is_num_v<operand_t> || meta::is_pointer_v<meta::remove_cvref_t<decltype(operand)>> ) {
                        return utility::tuple_append(init, operand);
                    } else /* if constexpr (meta::is_bounded_array_v<operand_t>) */ {
                        return utility::tuple_append<const operand_t&>(init, operand);
                    }
                }
            }, nmtools_tuple{});
            return all_operands;
        }
    }; // get_function_operands_t

    template <template<typename...>typename view_t, typename...args_t>
    struct get_function_composition_t<
        view::decorator_t<view_t,args_t...>
    > {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto function = get_function(view);
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)> );
            constexpr auto N = view_type::arity;
            auto composition = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto r_index = meta::ct_v<(N-1)-I>;
                const auto& operand = nmtools::at(operands,r_index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                if constexpr (meta::is_view_v<operand_t>) {
                    auto sub_composition = get_function_composition(operand);
                    return init * sub_composition;
                } else if constexpr ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    return init;
                }
            }, function);
            return composition;
        }
    }; // get_function_composition_t

    template <typename function_t, template<typename...>typename tuple, typename...operands_t>
    nmtools_func_attribute
    constexpr auto apply(const function_t& function, const tuple<operands_t...>& operands)
    {
        if constexpr (meta::is_maybe_v<function_t>) {
            using result_type = meta::remove_cvref_t<decltype(apply(*function,operands))>;
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(function)) {
                return return_type{apply(*function,operands)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            constexpr auto arity = function_t::arity;
            constexpr auto n_operands = sizeof...(operands_t);
            static_assert( arity == n_operands );
            return meta::template_reduce<sizeof...(operands_t)>([&](auto init, auto index){
                return init (nmtools::at(operands,index));
            }, function());
        }
    } // apply

    namespace fun
    {
        struct alias_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::alias(args...);
            }
        };
    }

    constexpr inline auto alias = functor_t(unary_fmap_t<fun::alias_t>{});

    template <typename view_t>
    struct get_compute_graph_t;

    template <typename view_t>
    constexpr auto get_compute_graph(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using view_type = meta::get_maybe_type_t<view_t>;
            using result_type = decltype(get_compute_graph(meta::declval<view_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(view)) {
                return return_type{get_compute_graph(*view)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            using view_type = view_t;
            auto get_graph = get_compute_graph_t<view_type>{view};
            return get_graph();
        }
    } // get_graph

    template <typename functor_t, typename operands_t>
    struct node_t
    {
        // TODO: assert functor_t is functor or functor composition
        // TODO: assert operands_t is tuple of integral constant
        // TODO: record out_shape

        using functor_type = functor_t;
        using operands_type = operands_t;

        functor_type functor;
        operands_type operands;
    };

    template <typename functor_t, typename operands_t>
    node_t(const functor_t&, const operands_t&) -> node_t<functor_t,operands_t>;

    template <typename nodes_t=nmtools_tuple<>, typename edges_t=nmtools_tuple<>, typename node_data_t=nmtools_tuple<>>
    struct compute_graph_t : utility::ct_digraph<nodes_t,edges_t,node_data_t>
    {
        // TODO: validate that node_data_t is tuple of node_t
        using base_type = utility::ct_digraph<nodes_t,edges_t,node_data_t>;
    };

    template <template <typename...> typename view_t, typename...args_t>
    struct get_compute_graph_t<view::decorator_t<view_t,args_t...>>
    {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);
            constexpr auto operand_ids = view_type::operands_ids;

            constexpr auto N = meta::len_v<decltype(operands)>;
            auto sub_graph = meta::template_reduce<N>([&](auto graph, auto index){

                constexpr auto I = decltype(index)::value;
                const auto& operand = nmtools::get<I>(operands);
                using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
                static_assert(
                    meta::is_pointer_v<operand_t>
                    || meta::is_num_v<operand_t>
                    || meta::is_view_v<operand_t>
                    , "expect operand to be pointer, number or view for get_compute_graph"
                );
                if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {
                    constexpr auto NODE_ID = typename operand_t::id_type{};
                    // static_assert( meta::is_pointer_v<decltype(operand)> );
                    return graph.add_node(NODE_ID,operand.array);
                } else if constexpr (meta::is_view_v<operand_t>) {
                    auto sub_graph = get_compute_graph(operand);
                    auto sub_keys = sub_graph.digraph.keys();
                    constexpr auto N_SUB = meta::len_v<decltype(sub_keys)>;
                    // MERGE Graph
                    auto result_graph = meta::template_reduce<N_SUB>([&](auto g, auto index){
                        auto node_id = nmtools::get<decltype(index)::value>(sub_keys);
                        auto node = sub_graph.nodes(node_id);
                        auto out_edges = sub_graph.out_edges(node_id);
                        constexpr auto N_OUT = meta::len_v<decltype(out_edges)>;
                        return meta::template_reduce<N_OUT>([&](auto g, auto out_idx){
                            auto out_edge = nmtools::get<decltype(out_idx)::value>(out_edges);
                            return g.add_edge(node_id,out_edge);
                        }, g.add_node(node_id,node));
                    }, graph);
                    return result_graph;
                } else /* if constexpr (meta::is_ndarray_v<operand_t>) */ {
                    constexpr auto N_NODES = decltype(graph.size())::value;
                    constexpr auto NODE_ID = meta::ct_v<N_NODES>;
                    return graph.add_node(NODE_ID,operand);
                }
            }, compute_graph_t<>());

            // TODO: support aliasing
            constexpr auto node_id = typename view_type::id_type{};
            auto functor = get_function(view);

            auto graph = sub_graph
                .add_node(node_id,node_t{functor,operand_ids})
            ;
            return meta::template_reduce<N>([&](auto graph, auto index){
                auto operand_id = nmtools::get<decltype(index)::value>(operand_ids);
                return graph.add_edge(operand_id,node_id);
            }, graph);
        }
    };
} // namespace nmtools::functional

namespace nmtools::utils
{
    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    struct isequal_t<
        functional::functor_t<F,lhs_operands_t,lhs_attributes_t>
        , functional::functor_t<G,rhs_operands_t,rhs_attributes_t>
    > {
        constexpr auto operator()(
            const functional::functor_t<F,lhs_operands_t,lhs_attributes_t>& lhs
            , const functional::functor_t<G,rhs_operands_t,rhs_attributes_t>& rhs
        ) {
            if constexpr ( !meta::is_same_v<F,G> || 
                !meta::is_same_v<lhs_operands_t,rhs_operands_t>
            ) {
                // TODO: also check the values of operands
                return false;
            } else if constexpr (
                !meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
                && !meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
            ) {
                constexpr auto M = meta::len_v<lhs_attributes_t>;
                constexpr auto N = meta::len_v<rhs_attributes_t>;
                if constexpr (M != N) {
                    return false;
                } else {
                    auto equal = true;
                    meta::template_for<M>([&](auto index){
                        auto equal_attribute = [&](){
                            auto lhs_attribute = at(lhs.attributes,index);
                            auto rhs_attribute = at(rhs.attributes,index);
                            if constexpr (meta::is_floating_point_v<decltype(lhs_attribute)>
                                && meta::is_floating_point_v<decltype(rhs_attribute)>)
                            {
                                return isclose(lhs_attribute,rhs_attribute);
                            } else {
                                return isequal(lhs_attribute,rhs_attribute);
                            }
                        }();
                        equal = equal && equal_attribute;
                    });
                    return equal;
                }
            } else if constexpr ( meta::is_same_v<F,G>
                && meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
                && meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
            ) {
                return true;
            } else {
                return false;
            }
        }
    };

    template <
        template<typename...>typename lhs_tuple, typename...lhs_functors_t, typename lhs_operands_t,
        template<typename...>typename rhs_tuple, typename...rhs_functors_t, typename rhs_operands_t
    >
    struct isequal_t
    <
        functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>
        , functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>
    >
    {
        constexpr auto operator()(
            const functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>& lhs
            , const functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>& rhs
        ) {
            constexpr auto N_LHS = meta::len_v<decltype(lhs.functors)>;
            constexpr auto N_RHS = meta::len_v<decltype(rhs.functors)>;

            auto equal = N_LHS == N_RHS;
            constexpr auto N = (N_LHS < N_RHS) ? N_LHS : N_RHS;
            meta::template_for<N>([&](auto index){
                equal = equal && isequal(at(lhs.functors,index),at(rhs.functors,index));
            });
            return equal;
        }
    };

    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , template<typename...>typename rhs_tuple, typename...rhs_functors_t, typename rhs_operands_t
    >
    struct isequal_t<
        functional::functor_t<F,lhs_operands_t,lhs_attributes_t>
        , functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>
    > {
        constexpr auto operator()(
            const functional::functor_t<F,lhs_operands_t,lhs_attributes_t>& lhs
            , const functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>& rhs
        ) {
            if constexpr (sizeof...(rhs_functors_t) == 1) {
                return isequal(lhs,at(rhs.functors,meta::ct_v<0>));
            } else {
                return false;
            }
        }
    };

    template <
        template<typename...>typename lhs_tuple, typename...lhs_functors_t, typename lhs_operands_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t
    >
    struct isequal_t<
        functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>
        , functional::functor_t<G,rhs_operands_t,rhs_attributes_t>
    >
    {
        constexpr auto operator()(
            const functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>& lhs
            , const functional::functor_t<G,rhs_operands_t,rhs_attributes_t>& rhs
        ) {
            if constexpr (sizeof...(lhs_functors_t) == 1) {
                return isequal(at(lhs.functors,meta::ct_v<0>),rhs);
            } else {
                return false;
            }
        }
    };
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP