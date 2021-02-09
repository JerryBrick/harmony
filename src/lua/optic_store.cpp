// SPDX-License-Identifier: GPL-3.0-only

#include "../harmony.hpp"
#include "../optic/handler.hpp"
#include "optic_store.hpp"

namespace Harmony::Lua {
    Optic::Animation *OpticStore::get_animation(std::string name) noexcept {
        if(this->animations.find(name) != this->animations.end()) {
            return &(this->animations[name]);
        }
        return nullptr;
    }

    void OpticStore::add_animation(std::string name, Optic::Animation anim) noexcept {
        if(this->animations.find(name) == this->animations.end()) {
            this->animations[name] = anim;
        }
    }

    void OpticStore::remove_animation(std::string name) noexcept {
        if(this->animations.find(name) != this->animations.end()) {
            this->animations.erase(name);
        }
    }

    Optic::Sprite *OpticStore::get_sprite(std::string name) noexcept {
        if(this->sprites.find(name) != this->sprites.end()) {
            return &(this->sprites[name]);
        }
        return nullptr;
    }

    void OpticStore::add_sprite(std::string name, Optic::Sprite sprite) noexcept {
        if(this->sprites.find(name) == this->sprites.end()) {
            this->sprites[name] = sprite;
        }
    }

    void OpticStore::remove_sprite(std::string name) noexcept {
        if(this->sprites.find(name) != this->sprites.end()) {
            this->sprites.erase(name);
        }
    }

    void OpticStore::load_sprites(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &sprite : this->sprites) {
            sprite.second.load(device);
        }
    }

    void OpticStore::release_sprites() noexcept {
        for(auto &sprite : this->sprites) {
            sprite.second.unload();
        }
    }

    void OpticStore::register_group(std::string name) noexcept {
        this->groups.push_back(name);
    }

    void OpticStore::remove_group(std::string name) noexcept {
        for(std::size_t i = 0; i < this->groups.size(); i++) {
            if(this->groups[i] == name) {
                this->groups.erase(this->groups.begin() + i);
            }
        }
    }

    void OpticStore::remove_groups() noexcept {
        auto &optic_handler = get_harmony().get_optic_handler();
        for(std::size_t i = 0; i < this->groups.size(); i++) {
            optic_handler.remove_render_group(this->groups[i]);
        }
    }

    OpticStore::~OpticStore() {
        this->remove_groups();
    }
}