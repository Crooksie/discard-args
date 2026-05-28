#ifndef DISCARD_ARGS_DISCARD_PARAMS_H
#define DISCARD_ARGS_DISCARD_PARAMS_H

#include <tuple>
namespace discard_args {
    
template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> {
    using return_type = R;
    using args_tuple = std::tuple<Args...>;
};


template <auto Fn>
class adapt_function
{
private:
    template <typename... ToArgs>
    class ToType
    {
    public:
        explicit ToType()
        {}

        template <std::size_t ...Indices>
        constexpr inline auto map() {
            static_assert(((Indices < sizeof...(ToArgs)) && ...), "Index is greater than the number of arguments.");
            return [](ToArgs ...args) {
                auto arg_tuple = std::tuple{args...};
                auto mapped_args = std::tuple{std::get<Indices>(arg_tuple)...};
                std::apply(Fn, mapped_args);
            };
        }

        constexpr inline auto discard_inputs() {
            return [](ToArgs ...) {
                Fn();
            };
        }
    };

public:
    template <typename... InArgs>
    [[nodiscard]] constexpr inline auto to() const
    {
        return ToType<InArgs...>{};
    }

    [[nodiscard]] constexpr inline auto no_args() const
    {
        return [](){
            const auto default_args = typename function_traits<decltype(Fn)>::args_tuple{};
            std::apply(Fn, default_args);
        };
    }

};

template <auto Fn>
auto adapt()
{
    return adapt_function<Fn>();
}
    
}  // namespace discard_args
#endif //DISCARD_ARGS_DISCARD_PARAMS_H
