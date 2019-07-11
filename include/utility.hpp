#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <map>

namespace numeric {
    namespace helper {

        namespace tag {
            struct insert {};
            struct raw {};

            template <typename T, typename V, typename = void>
            struct resolve_insert_tag {};

            template <typename T, typename V>
            struct resolve_insert_tag<T,V
                , std::void_t<decltype(std::declval<T>().insert(std::declval<T>().end(),std::declval<V>()))>
            > { using type = insert; };

            template <typename T, typename V>
            struct resolve_insert_tag<T,V
                , std::enable_if_t< std::is_same_v<T,std::array<typename T::value_type,std::tuple_size<T>::value> > 
                > /* enable_if */
            > { using type = raw; };
        } // namespace tag

        namespace detail {
            template <typename Scalar, typename U>
            auto make_var(std::map<std::string,Scalar> &map, const U& u) {
                map[u.first] = u.second;
            }
            template <typename Scalar, typename U, typename ...T>
            auto make_var(std::map<std::string,Scalar> &map, const U& u, const T&... t) {
                make_var(map, u);
                make_var(map, t...);
            }
            template <typename Scalar, typename ...Args>
            auto log(const Args& ...args) {
                std::map<std::string,Scalar> map;
                make_var(map, args...);
                return map;
            }

            /* BEGIN : inserter boilerplate */
            template <typename Container, typename Value>
            auto insert(Container &d, Value v, tag::insert) 
                /* This decltype is actually redundant (?) */
                -> decltype(d.insert(std::begin(d),v),void()) 
            {
                d.insert(std::begin(d),v);
            }

            template <typename Container, typename Value>
            auto insert(Container &d, Value v, tag::raw) 
                /* This decltype is actually redundant (?) */
                -> decltype(*std::begin(d)=v,void()) 
            {
                *std::begin(d)=v;
            }

            template <typename Container, typename Value, typename Iterator>
            auto insert(Container &d, Iterator pos, Value v, tag::insert) 
                /* This decltype is actually redundant (?) */
                -> decltype(d.insert(pos,v),void()) 
            {
                d.insert(pos,v);
            }

            template <typename Container, typename Value, typename Iterator>
            auto insert(Container &d, Iterator pos, Value v, tag::raw) 
                /* This decltype is actually redundant (?) */
                -> decltype(*pos=v,void()) 
            {
                *pos=v;
            }

            template <typename Container, typename InputIterator, typename Iterator>
            auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end, tag::insert) 
                -> decltype(d.insert(pos,begin,end),void()) 
            {
                d.insert(pos,begin,end);
            }

            template <typename Container, typename InputIterator, typename Iterator>
            auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end, tag::raw) 
                -> decltype(begin != end, begin++, pos++, *pos = *begin, void())
            {
                auto p = pos;
                for (auto it = begin; (it != end) && (pos != std::end(d)); it++) {
                    *p = *it; p++;
                }
            }
            /* END : inserter boilerplate */
        } // namespace detail 

        /* entrypoints */
        template <typename Container, typename Value>
        auto insert(Container &d, Value v) 
        -> decltype(detail::insert(d,v,typename tag::resolve_insert_tag<Container,Value>::type{})) {
            using insert_tag = typename tag::resolve_insert_tag<Container,Value>::type;
            detail::insert(d,v,insert_tag{});
        }
        template <typename Container, typename Value, typename Iterator>
        auto insert(Container &d, Iterator pos, Value v) 
        -> decltype(detail::insert(d,pos,v,typename tag::resolve_insert_tag<Container,Value>::type{})) 
        {
            using insert_tag = typename tag::resolve_insert_tag<Container,Value>::type;
            detail::insert(d,pos,v,insert_tag{});
        }
        template <typename Container, typename InputIterator, typename Iterator>
        auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end)
        -> decltype(detail::insert(d,pos,begin,end,typename tag::resolve_insert_tag<Container,decltype(*begin)>::type{})) {
            using insert_tag = typename tag::resolve_insert_tag<Container,decltype(*begin)>::type;
            detail::insert(d,pos,begin,end,insert_tag{});
        }

        template <typename Scalar, typename Logger>
        struct Log {
            template <typename ...Args>
            static auto log(Logger *logger, const Args& ...args) {
                if(!logger) return;
                (*logger)(detail::log<Scalar>(args...));
            }
        };

        template <typename Scalar>
        struct Log<Scalar,void> {
            template <typename ...Args>
            static auto log(void*, const Args& ...args) {
                return;
            }
        };
    } // namespace helper
} // namespace numeric

#define VAR_NAME(X) (#X)
#define VAR_NAME_PAIR(X) std::make_pair(std::string(#X),X)
#define VNP(X) VAR_NAME_PAIR(X)
#define NARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, N, ...) N
#define NARGS(args...) NARGS_(args..., 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)

#define name_1(x)                                                   VNP(x)
#define name_2(x, x2)                                               VNP(x) , VNP(x2)
#define name_3(x, x2, x3)                                           VNP(x) , VNP(x2), VNP(x3)
#define name_4(x, x2, x3, x4)                                       VNP(x) , VNP(x2), VNP(x3), VNP(x4)
#define name_5(x, x2, x3, x4, x5)                                   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5)
#define name_6(x, x2, x3, x4, x5, x6)                               VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6)
#define name_7(x, x2, x3, x4, x5, x6, x7)                           VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7)
#define name_8(x, x2, x3, x4, x5, x6, x7, x8)                       VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8)
#define name_9(x, x2, x3, x4, x5, x6, x7, x8, x9)                   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9)
#define name_10(x, x2, x3, x4, x5, x6, x7, x8, x9, x10)             VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10)
#define name_11(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)        VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10), VNP(x11)
#define name_12(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10), VNP(x11), VNP(x12)

#define names(args...) CAT(name_, NARGS(args))(args) 
#define LOGVAR(logger,...) {                                           \
                            helper::Log<Scalar,Logger>::log(        \
                                logger,                             \
                                names(__VA_ARGS__)                  \
                            );                                      \
                        }

#endif // UTILITY_HPP