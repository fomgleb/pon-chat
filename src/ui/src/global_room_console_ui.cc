#include "pon-chat/ui/global_room_console_ui.h"

namespace pon_chat::ui {

namespace grp = pon_chat::protocols::global_room_protocol;

ftxui::Component GlobalRoomConsoleUI::CreateMessangerRenderer()
{
    auto message_input_field_option = ftxui::InputOption();
    message_input_field_option.on_enter = [&] {
        enteredMessageEvent.Invoke(message_input_field_text_);
    };
    message_input_field_ =
        ftxui::Input(&message_input_field_text_, "Enter your message...", message_input_field_option);

    auto messanger_renderer = ftxui::Renderer(message_input_field_, [&] {
        return ftxui::vbox({
                   ftxui::vbox({message_elements}) | ftxui::vscroll_indicator | ftxui::focusPositionRelative(0, 1) |
                       ftxui::yframe | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 40),
                   ftxui::separator(),
                   message_input_field_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 5),
               }) |
               ftxui::borderHeavy | ftxui::flex;
    });
    return messanger_renderer;
}

ftxui::Component GlobalRoomConsoleUI::CreateLoginRenderer()
{
    auto login_input_field_option = ftxui::InputOption();
    login_input_field_option.on_enter = [&] {
        enteredUserNameEvent.Invoke(user_name_input_field_text_);
    };
    login_input_field_ = ftxui::Input(&user_name_input_field_text_, login_input_field_option);

    auto login_renderer = ftxui::Renderer(login_input_field_, [&] {
        return ftxui::vbox({
                   ftxui::text("Введи своё имя:"),
                   ftxui::separator(),
                   login_input_field_->Render(),
               }) |
               ftxui::border | ftxui::center;
    });
    return login_renderer;
}

void GlobalRoomConsoleUI::SubscribeToEnteredUserNameEvent(std::function<void(const std::string& username)> func)
{
    enteredUserNameEvent.Subscribe(func);
}

void GlobalRoomConsoleUI::SubscribeToEnteredMessageEvent(std::function<void(const std::string& message)> func)
{
    enteredMessageEvent.Subscribe(func);
}

void GlobalRoomConsoleUI::StartLoginScreen()
{
    ftxui::Component login_renderer = CreateLoginRenderer();
    login_screen_.Loop(login_renderer);
}

void GlobalRoomConsoleUI::StartChatScreen()
{
    ftxui::Component messenger_renderer = CreateMessangerRenderer();
    chat_screen_.Loop(messenger_renderer);
}

void GlobalRoomConsoleUI::StopLoginScreen()
{
    login_screen_.Exit();
}

void GlobalRoomConsoleUI::StopChatScreen()
{
    chat_screen_.Exit();
}

void GlobalRoomConsoleUI::AddAndDrawNewMessage(grp::Message& message)
{
    message_elements.push_back(ftxui::window(ftxui::text(message.sender_name), ftxui::paragraph(message.text)));
    chat_screen_.PostEvent(ftxui::Event::Custom);
}

void GlobalRoomConsoleUI::ClearMessageInputField()
{
    message_input_field_text_ = "";
}

}  // namespace pon_chat::ui
