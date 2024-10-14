#ifndef PONCHAT_UI_GLOBALROOMGRAPHICALUI_H_
#define PONCHAT_UI_GLOBALROOMGRAPHICALUI_H_

#include <list>
#include "SDL.h"
#include "global_room_ui.h"
#include "imgui.h"
#include "pon-chat/events/events.h"
#include "pon-chat/flags/flags.h"

namespace pon_chat::ui {

class GlobalRoomGraphicalUI : public GlobalRoomUI {
  public:
    GlobalRoomGraphicalUI();
    ~GlobalRoomGraphicalUI();
    void SubscribeToEnteredUserNameEvent(std::function<void(const std::string& username)> func) override;
    void SubscribeToEnteredMessageEvent(std::function<void(const std::string& message)> func) override;

    void StartLoginScreen() override;
    void StartChatScreen() override;
    void StopLoginScreen() override;
    void StopChatScreen() override;

    void AddAndDrawNewMessage(protocols::global_room_protocol::Message& message) override;
    void ClearMessageInputField() override;

  private:
    struct UiDeleter {
        inline void operator()(SDL_Window* win) { SDL_DestroyWindow(win); }
        inline void operator()(SDL_GLContext c) { SDL_GL_DeleteContext(c); }
        inline void operator()(ImGuiContext* c) { ImGui::DestroyContext(c); }
    };
    enum class Windows : uint8_t {
        NONE,
        LOGIN,
        MESSENGER,
        SIZE,
    };

    flags::Flags<Windows> showing_windows_ = Windows::NONE;

    events::Event<const std::string&> entered_username_event_;
    events::Event<const std::string&> entered_message_event_;

    static constexpr size_t MESSAGE_BUFF_SIZE_ = 512;
    char message_buff_[MESSAGE_BUFF_SIZE_] = {};

    static constexpr size_t USERNAME_BUFF_SIZE_ = 64;
    char username_buff_[MESSAGE_BUFF_SIZE_] = {};

    std::unique_ptr<SDL_Window, UiDeleter> sdl_window_;
    std::unique_ptr<void, UiDeleter> opengl_context_;
    std::unique_ptr<ImGuiContext, UiDeleter> imgui_context_;

    std::list<protocols::global_room_protocol::Message> messages_to_draw_;

    static std::unique_ptr<SDL_Window, UiDeleter> CreateSDLWindow();
    std::unique_ptr<void, UiDeleter> CreateOpenGLContext();
    std::unique_ptr<ImGuiContext, UiDeleter> CreateImguiContext();

    void MainLoop();
};

}  // namespace pon_chat::ui

#endif  // PONCHAT_UI_GLOBALROOMGRAPHICALUI_H_
