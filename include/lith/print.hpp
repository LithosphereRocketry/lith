#ifndef LITH_PRINT_HPP
#define LITH_PRINT_HPP

#include <iostream>

namespace lith {
    namespace print {
        // We need to block std::string, char[], and char* from using this
        // overload - they are both a default-printable type and an iterable
        // type, so this would create a conflicting overload
        template <class T, class = typename std::enable_if<
               !(std::is_array<T>::value
                    && std::is_convertible<std::remove_extent_t<T>, const char>::value)
                && !std::is_same<T, std::string>::value
                && !std::is_convertible<T, const char*>::value
        , void>::type>
        std::ostream& operator<<(std::ostream& stream, const T& container) {
            stream << "[";
            bool first = true;
            for(auto item : container) {
                if(!first) { stream << ", "; }
                stream << item;
                first = false;
            }
            stream << "]";
            return stream;
        }

        template<class T1, class T2>
        std::ostream& operator<<(std::ostream& stream, std::pair<T1, T2> item) {
            stream << "<" << item.first << " : " << item.second << ">";
            return stream;
        }
    }
}

#endif