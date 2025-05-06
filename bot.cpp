#include <stdio.h>
#include <tgbot/tgbot.h>
#include "farm.h"

void PrimtPLS(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7614764220:AAGAIgGzIBr5kFpaVnf4YA8QyRlkBbcHj0s");
    bot.getApi().sendMessage(message->chat->id, "Your message is not not: ");
    BasicFlag = true;
}
int main() {
    TgBot::Bot bot("7614764220:AAGAIgGzIBr5kFpaVnf4YA8QyRlkBbcHj0s"); // NONCommand(Как-то так)
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Здравствуйте! Добро пожаловать в Громбург! Его основатели - великие кододелы, их имена войдут в историю! И Они жесть какие крутые! здесь будет их игра, кстати");
        Start();
        BasicFarm(message);
        BasicFlag = true;
        GardenFlag = false;
        StorehouseFlag = false;
        ShopFlag = false;
        // bot.getApi().sendMessage(message->chat->id, std::to_string(BasicFlag));
        // for(int i = 0; i<5; ++i) {
        //     bot.getApi().sendMessage(message->chat->id, "Здравствуйте! Добро пожаловать в Громбург! Его основатели - великие кододелы, их имена войдут в историю! И Они жесть какие крутые! здесь будет их игра, кстати");
        // }
    });

    bot.getEvents().onCommand("огород", [&bot](TgBot::Message::Ptr message) {
        GardenFlag = true;
        if(BasicFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Garden(message);
            PrimtPLS(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("обновить", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Garden(message);
            PrimtPLS(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("посадить_семена", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            PlantSeed(message);
            PrimtPLS(message);
        } else {
            return;
        }
        GardenFlag = false;
        BasicFlag =true;
    });

    bot.getEvents().onCommand("собрать всё", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Garden(message);
            PrimtPLS(message);
        } else {
            return;
        }
        GardenFlag = false;
        BasicFlag =true;
    });

    bot.getEvents().onCommand("обратно", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Garden(message);
            PrimtPLS(message);
        } else {
            return;
        }
        BasicFlag = false;
    });


    bot.getEvents().onCommand("амбар", [&bot](TgBot::Message::Ptr message) {
        StorehouseFlag = true;
        if(BasicFlag) {
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Storehouse(message);
            PrimtPLS(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("магазин", [&bot](TgBot::Message::Ptr message) {
        ShopFlag = true;
        if(BasicFlag) {
            return;
            // bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            //     printf("User wrote %s\n", message->text.c_str());
            //     if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/truth") || !BasicFlag) {
            //         return;
            //     }
            //     bot.getApi().sendMessage(message->chat->id, "Your message is not: " + message->text);
            // });
            Shop(message);
            PrimtPLS(message);
        } else {
            return;
        }
        BasicFlag = false;
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
