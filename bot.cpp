#include "farm.h"

int main() {
    TgBot::Bot bot("7590778478:AAGfg-6Q_PofDaS4D1tFB8F105M9p72gkrQ");
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
    });
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
            PlantSeedOutput(message);
        } else {
            return;
        }
        FirstStepInputFlag = true;
        ActionScenario = 3;
    });

    bot.getEvents().onCommand("собрать_всё", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            CollectAllVegatables(message);
            Garden(message);
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("выкопать_грядку", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag) {
            GetGardenUpgrade(message);
            Garden(message);
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("амбар", [&bot](TgBot::Message::Ptr message) {
        StorehouseFlag = true;
        if(BasicFlag) {
            StoreHouse(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("улучшить_амбар", [&bot](TgBot::Message::Ptr message) {
        if(StorehouseFlag) {
            BuyStorehouseUpgrade(message);
            StoreHouse(message);
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("выбросить_предметы", [&bot](TgBot::Message::Ptr message) {
        if(StorehouseFlag) {
            ThrowAwayItems(message);
            StoreHouse(message);
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("магазин", [&bot](TgBot::Message::Ptr message) {
        ShopFlag = true;
        if(BasicFlag) {
           Shop(message);
        } else {
            return;
        }
        BasicFlag = false;
    });

    bot.getEvents().onCommand("купить", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            ShopOutput(message);
            bot.getApi().sendMessage(message->chat->id, "Введите индекс товара. который хотите купить");
            ActionScenario = 1;
            FirstStepInputFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("продать_семена", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            SellSeedsOut(message);
            ActionScenario = 2;
            FirstStepInputFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("продать_овощи", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            SellVegetablesOut(message);
            ActionScenario = 4;
            FirstStepInputFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("улучшить_магазин", [&bot](TgBot::Message::Ptr message) {
        if(ShopFlag) {
            UpgradeLevelCheck = BuyShopUpgrade(message);
            AvailableSeed+= (UpgradeLevelCheck-1);
            Shop(message);
            BasicFlag = true;
        } else {
            return;
        }
    });

    bot.getEvents().onCommand("обратно", [&bot](TgBot::Message::Ptr message) {
        if(GardenFlag || ShopFlag || StorehouseFlag) {
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
            if(FirstStepInputFlag) {
                ShopFlag = false;
                Index = 1;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            } else if(SecondStepInputFlag) {
                Amount = 1;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                Shop(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInputFlag) {
            Index = 1;
            ShopFlag = false;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 1;
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
            SecondStepInputFlag = false;
            ShopFlag = true;
            Shop(message);
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInputFlag) {
            GardenFlag = false;
            Index = 1;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 1;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInputFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    case 4: {
        if(FirstStepInputFlag) {
            Index = 1;
            ShopFlag = false;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)один овощ\n2)пять овощей\n3)двадцать овощей \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 1;
            SellVegetables(message, Index, Amount);
            BuySecondStep(message);
            SecondStepInputFlag = false;
            ShopFlag = true;
            Shop(message);
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
            if(FirstStepInputFlag) {
                ShopFlag = false;
                Index = 2;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            } else if(SecondStepInputFlag) {
                Amount = 5;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                Shop(message);
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 2;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 5;
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
            SecondStepInputFlag = false;
            ShopFlag = true;
            Shop(message);
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInputFlag) {
            GardenFlag = false;
            Index = 2;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 2;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInputFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    case 4: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 2;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)один овощь\n2)пять овощей\n3)двадцать овощей \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 5;
                SellVegetables(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                Shop(message);
                return;
        }else {
            return;
    }
    }
    }
    });

    bot.getEvents().onCommand("3", [&bot](TgBot::Message::Ptr message) {
        switch(ActionScenario) {
            case 1: {
            if(FirstStepInputFlag) {
                ShopFlag = false;
                Index = 3;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            } else if(SecondStepInputFlag) {
                Amount = 20;
                BuyFirstStep(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                Shop(message);
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 3;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 20;
            SellSeeds(message, Index, Amount);
            BuySecondStep(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                Shop(message);
                return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInputFlag) {
            GardenFlag = false;
            Index = 3;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = MaxSeedBedAmount;
            PlantSeed(message, Index, Amount);
            Garden(message);
            SecondStepInputFlag = false;
            GardenFlag = true;
            return;
        }else {
            return;
    }
    }
    case 4: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 3;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)один овощь\n2)пять овощей\n3)двадцать овощей \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        } else if(SecondStepInputFlag) {
            Amount = 20;
                SellVegetables(message, Index, Amount);
                BuySecondStep(message);
                SecondStepInputFlag = false;
                ShopFlag = true;
                Shop(message);
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
            if(FirstStepInputFlag) {
                ShopFlag = false;
                Index = 4;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
        }
    }
    case 2: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 4;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        }else {
            return;
    }
    }
    case 3: {
        if(FirstStepInputFlag) {
            GardenFlag = false;
            Index = 4;
            bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        }else {
            return;
    }
    }
    case 4: {
        if(FirstStepInputFlag) {
            ShopFlag = false;
            Index = 4;
            bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
            SecondStepInputFlag = true;
            FirstStepInputFlag = false;
            return;
        }else {
            return;
    }
    }
    }
    });

    bot.getEvents().onCommand("5", [&bot](TgBot::Message::Ptr message) {
        switch(ActionScenario) {
            case 1: {
                ShopFlag = false;
                Index = 5;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }
            case 2: {
                if(FirstStepInputFlag && 5 <= AvailableSeed) {
                    ShopFlag = false;
                    Index = 5;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }else {
                    return;
            }
            }
            case 3: {
                if(FirstStepInputFlag && 5 <= AvailableSeed) {
                    GardenFlag = false;
                    Index = 5;
                    bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }else {
                    return;
            }
            }
            case 4: {
                if(FirstStepInputFlag && 5 <= AvailableSeed) {
                    ShopFlag = false;
                    Index = 5;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }else {
                    return;
            }
            }
    }

    });

    bot.getEvents().onCommand("6", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 1) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 6;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }
                case 2: {
                    if(FirstStepInputFlag && 6 <= AvailableSeed) {
                        ShopFlag = false;
                        Index = 6;
                        bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                        SecondStepInputFlag = true;
                        FirstStepInputFlag = false;
                        return;
                    }else {
                        return;
                }
                }
        case 3: {
            if(FirstStepInputFlag && 6 <= AvailableSeed) {
                GardenFlag = false;
                Index = 6;
                bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
        }
        }
        case 4: {
            if(FirstStepInputFlag && 6 <= AvailableSeed) {
                ShopFlag = false;
                Index = 6;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
            }
        }
        }
        }
    });

    bot.getEvents().onCommand("7", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 1) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 7;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
        }
        case 2: {
            if(FirstStepInputFlag && 7 <= AvailableSeed) {
                ShopFlag = false;
                Index = 7;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
        }
        }
        case 3: {
            if(FirstStepInputFlag && 7 <= AvailableSeed) {
                GardenFlag = false;
                Index = 7;
                bot.getApi().sendMessage(message->chat->id, "сколько семян вы хотите посадить:\n1)Одно семечко\n2)Два семечка\n3)Все семена");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
        }
        }
        case 4: {
            if(FirstStepInputFlag && 7 <= AvailableSeed) {
                ShopFlag = false;
                Index = 7;
                bot.getApi().sendMessage(message->chat->id, "Вы хотите продать:\n1)одно семечко\n2)пять семян\n3)двадцать семян \n");
                SecondStepInputFlag = true;
                FirstStepInputFlag = false;
                return;
            }else {
                return;
            }
        }
        }
        }
    });

    bot.getEvents().onCommand("8", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 1) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 8;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }
            }
        }
    });

    bot.getEvents().onCommand("9", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 1) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 9;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }
            }
        }
    });

    bot.getEvents().onCommand("10", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 2) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 10;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }
            }
        }
    });

    bot.getEvents().onCommand("11", [&bot](TgBot::Message::Ptr message) {
        if(UpgradeLevelCheck > 2) {
            switch(ActionScenario) {
                case 1: {
                    ShopFlag = false;
                    Index = 11;
                    bot.getApi().sendMessage(message->chat->id, "Вы хотите купить:\n1)одну единицу товара\n2)пять единиц товара\n3)двадцать единиц товара \n");
                    SecondStepInputFlag = true;
                    FirstStepInputFlag = false;
                    return;
                }
            }
        }
    });

    bot.getEvents().onCommand("выход", [&bot](TgBot::Message::Ptr message) {
        if(BasicFlag) {
            Vipe();
            bot.getApi().sendMessage(message->chat->id, "Спасибо вам за игру!");
            BasicFlag = false;
        } else {
            return;
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
