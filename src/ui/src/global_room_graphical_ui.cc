#include "pon-chat/ui/global_room_graphical_ui.h"

#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include "SDL_opengl.h"
#endif

namespace pon_chat::ui {

namespace grp = pon_chat::protocols::global_room_protocol;
using std::unique_ptr;

static void SetupSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0) {
        printf("Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
}

static std::string ChooseGLSLVersion()
{
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    std::string glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    std::string glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    std::string glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    return glsl_version;
}

static void SetupImgui()
{
    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    imgui_io.IniFilename = nullptr;
    imgui_io.LogFilename = nullptr;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
}

GlobalRoomGraphicalUI::GlobalRoomGraphicalUI()
{
    SetupSDL();
    std::string glsl_version = ChooseGLSLVersion();

    sdl_window_ = CreateSDLWindow();
    opengl_context_ = CreateOpenGLContext();

    SDL_GL_SetSwapInterval(1);  // Enable vsync

    imgui_context_ = CreateImguiContext();
    SetupImgui();

    ImGui_ImplSDL2_InitForOpenGL(sdl_window_.get(), opengl_context_.get());
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/Roboto-Regular.ttf", 24, nullptr,
                                 io.Fonts->GetGlyphRangesCyrillic());
}

GlobalRoomGraphicalUI::~GlobalRoomGraphicalUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    SDL_Quit();
}

void GlobalRoomGraphicalUI::SubscribeToEnteredUserNameEvent(
    std::function<void(const std::string& username)> func)
{
    enteredUserNameEvent.Subscribe(func);
}

void GlobalRoomGraphicalUI::SubscribeToEnteredMessageEvent(
    std::function<void(const std::string& message)> func)
{
    enteredMessageEvent.Subscribe(func);
}

void GlobalRoomGraphicalUI::StartLoginScreen()
{
    showing_windows_.set(Windows::LOGIN);
    MainLoop();
}

void GlobalRoomGraphicalUI::StartChatScreen()
{
    showing_windows_.set(Windows::MESSENGER);
}

void GlobalRoomGraphicalUI::StopLoginScreen()
{
    showing_windows_.reset(Windows::LOGIN);
}

void GlobalRoomGraphicalUI::StopChatScreen()
{
    showing_windows_.reset(Windows::MESSENGER);
}

void GlobalRoomGraphicalUI::AddAndDrawNewMessage(grp::Message& message)
{
    messages_to_draw_.push_back(message);
}

void GlobalRoomGraphicalUI::ClearMessageInputField()
{
    message_buff_[0] = '\0';
}

unique_ptr<SDL_Window, GlobalRoomGraphicalUI::UiDeleter>
GlobalRoomGraphicalUI::CreateSDLWindow()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = static_cast<SDL_WindowFlags>(
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* sdl_window =
        SDL_CreateWindow("pon-chat", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (sdl_window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return unique_ptr<SDL_Window, GlobalRoomGraphicalUI::UiDeleter>(sdl_window);
}

unique_ptr<void, GlobalRoomGraphicalUI::UiDeleter>
GlobalRoomGraphicalUI::CreateOpenGLContext()
{
    SDL_GLContext opengl_context = SDL_GL_CreateContext(sdl_window_.get());
    SDL_GL_MakeCurrent(sdl_window_.get(), opengl_context);
    return unique_ptr<void, GlobalRoomGraphicalUI::UiDeleter>(opengl_context);
}

unique_ptr<ImGuiContext, GlobalRoomGraphicalUI::UiDeleter>
GlobalRoomGraphicalUI::CreateImguiContext()
{
    IMGUI_CHECKVERSION();
    ImGuiContext* imgui_context = ImGui::CreateContext();
    return unique_ptr<ImGuiContext, GlobalRoomGraphicalUI::UiDeleter>(
        imgui_context);
}

void GlobalRoomGraphicalUI::MainLoop()
{
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);

    bool exited = false;
    while (!exited) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                exited = true;
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(sdl_window_.get()))
                exited = true;
        }
        if (SDL_GetWindowFlags(sdl_window_.get()) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        int window_width, window_height;
        SDL_GetWindowSize(sdl_window_.get(), &window_width, &window_height);

        static constexpr ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoBackground;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(window_width),
                                        static_cast<float>(window_height)));

        ImGui::Begin("Pon Chat", nullptr, window_flags);

        if (showing_windows_[Windows::LOGIN]) {
            ImGui::InputText(" ", username_buff_, USERNAME_BUFF_SIZE_);
            if (ImGui::Button("Login")) {
                enteredUserNameEvent.Invoke(std::string(username_buff_));
            }
        } else if (showing_windows_[Windows::MESSENGER]) {
            ImVec2 available_size = ImGui::GetContentRegionAvail();
            float input_height = ImGui::GetTextLineHeightWithSpacing() +
                                 ImGui::GetStyle().ItemSpacing.y;

            ImGui::BeginChild("Scrolling",
                              ImVec2(0, available_size.y - input_height - 10),
                              true);

            for (const auto& msg : messages_to_draw_) {
                ImGui::Text("%s: %s", msg.sender_name.c_str(),
                            msg.text.c_str());
            }

            ImGui::SetScrollHereY(1.0f);
            ImGui::EndChild();

            ImGui::InputText(" ", message_buff_, MESSAGE_BUFF_SIZE_);
            ImGui::SameLine();
            if (ImGui::Button("Send") && message_buff_[0] != '\0') {
                enteredMessageEvent.Invoke(std::string(message_buff_));
            }
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, static_cast<int>(ImGui::GetIO().DisplaySize.x),
                   static_cast<int>(ImGui::GetIO().DisplaySize.y));
        glClearColor(clear_color.x * clear_color.w,
                     clear_color.y * clear_color.w,
                     clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(sdl_window_.get());
    }
}

}  // namespace pon_chat::ui
