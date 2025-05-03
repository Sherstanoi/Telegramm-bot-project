#include <stdio.h>
#include <tgbot/tgbot.h>
#include "farm.h"

bool Flag1 = false;
bool Flag2 = false;

void PrimtPLS(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7614764220:AAFjCX5LYfb33qJ8-f7HMXbxAzfNGWVEuK8");
    bot.getApi().sendMessage(message->chat->id, "Your message is not not: ");
    Flag1 = true;
}
int main() {
    TgBot::Bot bot("7614764220:AAFjCX5LYfb33qJ8-f7HMXbxAzfNGWVEuK8"); // NONCommand(Как-то так)
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        Flag2 = true;
        bot.getApi().sendMessage(message->chat->id, "Здравствуйте! Добро пожаловать в Громбург! Его основатели - великие кододелы, их имена войдут в историю! И Они жесть какие крутые! здесь будет их игра, кстати");
        bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            printf("User wrote %s\n", message->text.c_str());
            bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
        });
    });
    bot.getEvents().onCommand("GH", [&bot](TgBot::Message::Ptr message) {
        PrimtPLS(message);
        if(Flag1) {
            bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
                printf("User wrote %s\n", message->text.c_str());
                if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || Flag2) {
                    std::cout<<Flag2;
                    return;
                }
                bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            });
        } else {
            return;
        }
        // Flag1 = true;
        // PrimtPLS(message);
        // std::cout<<"aaa";
        // if(Flag1) {
        //     bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        //         printf("User wrote %s\n", message->text.c_str());
        //         if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth")) {
        //             return;
        //         }
        //         bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
        //     });
        // }
        //     bot.getEvents().onCommand("HG", [&bot](TgBot::Message::Ptr message) {
        //         bot.getApi().sendMessage(message->chat->id, "YEEEES: " + message->text);
        //         if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth")) {
        //             return;
        //         }
        //         Flag2 = true;
        //     });
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
