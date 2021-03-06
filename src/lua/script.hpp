// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_SCRIPT_HPP
#define HARMONY_LUA_SCRIPT_HPP

#include <string>
#include <vector>
#include <map>
#include <lua.hpp>
#include "optic_store.hpp"

namespace Harmony::Lua {
    class Script {
    public:
        /**
         * Get script name
         */
        const char *get_name() const noexcept;

        /**
         * Get script type
         */
        const char *get_type() const noexcept;

        /**
         * Get data path
         */
        const char *get_data_path() const noexcept;

        /**
         * Check if the path is inside of the script data directory
         * @param path  Path to check
         * @return      True if the path is valid, false if not
         */
        bool path_is_valid(std::string path) noexcept;

        /**
         * Get callbacks
         */
        std::vector<std::string> &get_callbacks(const char *callback) noexcept;

        /**
         * Get optic store
         */
        OpticStore &get_optic_store() noexcept;

        /**
         * Get script state
         */
        lua_State *get_state() noexcept;

        /**
         * Get global from script
         */
        const char *get_global(std::string name) const noexcept;

        /**
         * Register a callback
         */
        void add_callback(const char *callback, const char *function) noexcept;

        /**
         * Constructor for script
         * @param state     Pointer to Lua script state
         */
        Script(lua_State *state) noexcept;

        /**
         * Equals operator for std::find function
         */
        inline bool operator==(const std::string name) {
            return this->name == name;
        }

        /**
         * Get script name from state
         * @param state     Pointer to Lua script state
         * @param global    Name of the global
         * @return          Global value
         */
        static std::string get_global_from_state(lua_State *state, const char *global) noexcept;

        /**
         * Get script name from state
         * @param state     Pointer to Lua script state
         */
        static std::string get_script_name_from_state(lua_State *state) noexcept;

    private:
        /** Name of the script */
        std::string name;

        /** is the script global? */
        std::string type;

        /** Data directory */
        std::string data_path;

        /** Script callbacks */
        std::map<std::string, std::vector<std::string>> callbacks;

        /** Optic stores */
        OpticStore optic_store;

        /** The script itself */
        lua_State *script;

        /**
         * Get script data directory from state
         * @return      Data folder path
         */
        std::string get_script_data_path() noexcept;
    };
}

#endif
