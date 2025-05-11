#include <stdio.h>
#include <tgbot/tgbot.h>
#include "farm.h"

void PrimtPLS(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    bot.getApi().sendMessage(message->chat->id, "Your message is not not: ");
    BasicFlag = true;
}
int main() {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,"Вы всегда хотели переехать в уединенное место, поэтому вы долго копили деньги и купили домик в деревушке.И вот,наконец, вы приезжаете к своему новому дому");
        Start();
        BasicFarm(message);
        BasicFlag = true;
        GardenFlag = false;
        StorehouseFlag = false;
        ShopFlag = false;

    });

    bot.getEvents().onCommand("огород", [&bot](TgBot::Message::Ptr message) {
        GardenFlag = true;
        if(BasicFlag) {
            Garden(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("проверить_растения", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            Garden(message);
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("посадить_семена", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            PlantSeedOut(message);
        } else {
            return;
        }
        FirstStepInFlag = true;
        ActionScenario = 3;
    });

    bot.getEvents().onCommand("собрать_всё", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            Garden(message);
            PrimtPLS(message);
        } else {
            return;
        }
        GardenFlag = false;
        BasicFlag =true;
    });

    bot.getEvents().onCommand("амбар", [&bot](TgBot::Message::Ptr message) {
        StorehouseFlag = true;
        if(BasicFlag) {
            StoreHouse(message);
        } else {
            return;
        }
        BasicFarm(message);
    });

    bot.getEvents().onCommand("магазин", [&bot](TgBot::Message::Ptr message) {
        ShopFlag = true;
        if(BasicFlag) {
            bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("купить", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            ShopOut(message);
            bot.getApi().sendMessage(message->chat->id, "Введите индекс товара. который хотите купить");
            ActionScenario = 1;
            FirstStepInFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("продать_семена", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            SellSeedsOut(message);
            ActionScenario = 2;
            FirstStepInFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("продать_овощи", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            SellVegetables(message);
            ActionScenario = 3;
            FirstStepInFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("обратно", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag || ShopFlag) {
            BasicFarm(message);
            BasicFlag = true;
            GardenFlag = false;
            StorehouseFlag = false;
            ShopFlag = false;
            return;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("1", [&bot](TgBot::Message::Ptr message) {
        switch(ActionScenario) {
            case 1: {
            if(FirstStepInFlag) {
                ShopFlag = false;
                Index = 1;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInFlag = true;
                FirstStepInFlag = false;
                return;
            } else if(SecondStepInFlag) {
                Amount = 1;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
                SecondStepInFlag = false;
                ShopFlag = true;
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInFlag) {
            Index = 1;
            ShopFlag = false;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = 1;
            bot.getApi().sendMessage(message->chat->id, std::to_string(UsedSeedsInSellingSec[0]));
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
            SecondStepInFlag = false;
            ShopFlag = true;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInFlag) {
            GardenFlag = false;
            Index = 1;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = 1;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    }
    });

    bot.getEvents().onCommand("2", [&bot](TgBot::Message::Ptr message) {
        switch(ActionScenario) {
            case 1: {
            if(FirstStepInFlag) {
                ShopFlag = false;
                Index = 2;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInFlag = true;
                FirstStepInFlag = false;
                return;
            } else if(SecondStepInFlag) {
                Amount = 5;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInFlag = false;
                ShopFlag = true;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInFlag) {
            ShopFlag = false;
            Index = 2;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = 5;
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
            SecondStepInFlag = false;
            ShopFlag = true;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInFlag) {
            GardenFlag = false;
            Index = 2;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = 2;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    }
    });

    bot.getEvents().onCommand("3", [&bot](TgBot::Message::Ptr message) { //ТУТ ПРОБЛЕМА С ЗАСАЖИВАНИЕМ ВСЕХ СЕМЯН
        switch(ActionScenario) {
            case 1: {
            if(FirstStepInFlag) {
                ShopFlag = false;
                Index = 3;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInFlag = true;
                FirstStepInFlag = false;
                return;
            } else if(SecondStepInFlag) {
                Amount = 20;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInFlag = false;
                ShopFlag = true;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInFlag) {
            ShopFlag = false;
            Index = 3;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = 20;
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
                SecondStepInFlag = false;
                ShopFlag = true;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)обратно \n");
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInFlag) {
            GardenFlag = false;
            Index = 3;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        } else if(SecondStepInFlag) {
            Amount = AllYouSeed;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    }
    });

    bot.getEvents().onCommand("4", [&bot](TgBot::Message::Ptr message) {
        switch(ActionScenario) {
            case 1: {
            if(FirstStepInFlag) {
                ShopFlag = false;
                Index = 4;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInFlag = true;
                FirstStepInFlag = false;
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInFlag) {
            ShopFlag = false;
            Index = 4;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInFlag) {
            GardenFlag = false;
            Index = 4;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInFlag = true;
            FirstStepInFlag = false;
            return;
        }else {
            return;
    }
    }
    }
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
