#include <stdio.h>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("7614764220:AAFjCX5LYfb33qJ8-f7HMXbxAzfNGWVEuK8");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Здравствуйте! Добро пожаловать в Громбург! Его основатели - великие кододелы, их имена войдут в историю! И Они жесть какие крутые! здесь будет их игра, кстати");
    });
    bot.getEvents().onCommand("truth", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Ты(Женя) - самое прекрасное на свете создание! Я,создатель этого бота, искренне люблю тебя! Спасибо. что ты есть <3");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
