//
// Created by Qiuzhe on 2022/6/11.
//
#pragma once
#ifndef THREEDAYVULKAN_WINDOW_SYSTEM_H
#define THREEDAYVULKAN_WINDOW_SYSTEM_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <array>
#include <functional>
#include <vector>

namespace VulkanManager{
    struct WindowCreateInfo{
        int         width{1280};
        int         height{720};
        const char* title{"Vulkan Test"};
        bool        is_fullscreen{false};
    };

    class WindowSystem{
    public:
        WindowSystem() = default;
        ~WindowSystem();
        void                initialize(WindowCreateInfo create_info);
        void                pollEvents() const;
        bool                shouldClose() const;
        void                setTile(const char* title);
        GLFWwindow*         getWindow() const;
        std::array<int, 2>  getWindowSize() const;

    protected:

    private:
        GLFWwindow* m_window{nullptr};
        int         m_width{0};
        int         m_height{0};

        bool m_is_focus_mode{false};
    };

    // TODO: Create callback_fn

}

#endif //THREEDAYVULKAN_WINDOW_SYSTEM_H
