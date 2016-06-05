#pragma once

#include <string>
#include <regex>
#include <utility>
#include <unordered_map>

#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "inexor/util/InexorException.hpp"

namespace std {

/// Hashes for enum types.
/// TODO: Move this somewhere more appropriate
/// https://stackoverflow.com/questions/9646297/c11-hash-function-for-any-enum-type#21029900
template<class E>
struct hash {
    using sfinale = typename std::enable_if<std::is_enum<E>::value, E>::type;
    size_t operator()(const E&e) const {
        return std::hash<typename std::underlying_type<E>::type>()(e);
    }
};

}

namespace inexor {
namespace rpc {
namespace gluegen {

class ShTreeNode {
public:

    /// Known C++ SharedVar types
    enum cpp_type_t {
        t_cstring = 0,
        t_float,
        t_int
    };

    /// Maps C++ string type declarations to the numeric,
    /// unambiguity types above
    static const std::unordered_map<std::string, cpp_type_t> type_parsers;

    /// The numeric types above to their protocol buffers
    /// equivalents
    static const std::unordered_map<cpp_type_t, std::string> protoc_types;

    /// The canonical name (including ::) of the inexor c++
    /// variable
    std::string cpp_var;

    /// Path of the variable inside the tree
    std::string path;

    /// Path but not containing any slashes
    std::string mangled_path;

    /// The type literal of the c++ type
    std::string type_lit;

    /// C++ type of the variable
    cpp_type_t type;

    /// The protocol buffers type for this node
    std::string protoc_lit;

    /// The protocol buffers variable index; 0 if unset
    uint64_t protoc_idx = 0;

    /// @param type_decl The literal type declaration (e.g.
    ///     "int" or "char *") from which the correct index
    ///     for type will be deduced
    ShTreeNode(const std::string &type_decl
        , const std::string &cpp_var, const std::string &path)
        : cpp_var{cpp_var}, path{path} {
        _init_mangled_path();
        _init_type(type_decl);
    }

    /// @param type_decl The literal type declaration (e.g.
    ///     "int" or "char *") from which the correct index
    ///     for type will be deduced
    ShTreeNode(const std::string &type_decl
        , std::string &&cpp_var, std::string &&path)
        : cpp_var{ std::move(cpp_var) }, path{ std::move(path) } {
        _init_mangled_path();
        _init_type(type_decl);
    }

private:
    void _init_mangled_path() {
        using boost::algorithm::replace_all_copy;
        mangled_path = replace_all_copy(path, "/", "_");
    }

    void _init_type(const std::string &type_decl) {
        type = type_parsers.at(type_decl);
        type_lit = type_decl;
        protoc_lit = protoc_types.at(type);
    }
};

typedef std::vector<ShTreeNode> ShTree;

}
}
}
