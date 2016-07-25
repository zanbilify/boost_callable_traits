#ifndef CALLABLE_TRAITS_PARAMETER_INDEX_HELPER_HPP
#define CALLABLE_TRAITS_PARAMETER_INDEX_HELPER_HPP

CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

    template<std::size_t I, typename T, bool IgnoreThisPointer = false, bool AllowPlusOne = false, std::size_t Count = 0>
    struct parameter_index_helper {

        using args_tuple = typename std::conditional<IgnoreThisPointer,
            typename detail::traits<T>::non_invoke_arg_types,
            typename detail::traits<T>::arg_types>::type;

        static constexpr bool has_parameter_list =
            !std::is_same<args_tuple, invalid_type>::value;

        using temp_tuple = typename std::conditional<has_parameter_list,
            args_tuple, std::tuple<invalid_type>>::type;

        static constexpr std::size_t parameter_list_size =
            std::tuple_size<temp_tuple>::value;

        static constexpr bool is_out_of_range = has_parameter_list &&
            I >= parameter_list_size + static_cast<std::size_t>(AllowPlusOne);

        static constexpr bool is_count_out_of_range = has_parameter_list &&
            I + Count > parameter_list_size + static_cast<std::size_t>(AllowPlusOne);

        static constexpr std::size_t index =
            has_parameter_list && !is_out_of_range ? I : 0;

        static constexpr std::size_t count =
            has_parameter_list && !is_count_out_of_range ? Count : 0;

        using permissive_tuple = typename std::conditional<
            has_parameter_list && !is_out_of_range,
            args_tuple, std::tuple<invalid_type>>::type;

        using permissive_function = typename std::conditional<
            has_parameter_list && !is_out_of_range,
            T, invalid_type(invalid_type)>::type;
    };



CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif // #ifndef CALLABLE_TRAITS_PARAMETER_INDEX_HELPER_HPP
