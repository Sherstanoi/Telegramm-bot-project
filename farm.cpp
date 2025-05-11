#include "farm.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

void Start(){
    AllSeeds[0].Name = "Семена пшена";    AllSeeds[0].TimeGrowth = 10; AllSeeds[0].BuyCost = 4;  AllSeeds[0].SellCost = 3;  AllSeeds[0].Number = 0;
    AllSeeds[1].Name = "Семена морковки"; AllSeeds[1].TimeGrowth = 20; AllSeeds[1].BuyCost = 2;  AllSeeds[1].SellCost = 1;  AllSeeds[1].Number = 1;;
    AllSeeds[2].Name = "Семена свеклы";   AllSeeds[2].TimeGrowth = 30; AllSeeds[2].BuyCost = 6;  AllSeeds[2].SellCost = 5;  AllSeeds[2].Number = 2;
    AllSeeds[3].Name = "Семена тыквы";    AllSeeds[3].TimeGrowth = 60; AllSeeds[3].BuyCost = 12; AllSeeds[3].SellCost = 10; AllSeeds[3].Number = 3;

    AllVegatables[0].Name = "Пшено";    AllVegatables[0].SellCost = 6;  AllVegatables[0].Number = 0;
    AllVegatables[1].Name = "Морковка"; AllVegatables[1].SellCost = 4;  AllVegatables[1].Number = 1;
    AllVegatables[2].Name = "Свекла";   AllVegatables[2].SellCost = 10; AllVegatables[2].Number = 2;
    AllVegatables[3].Name = "Тыква";    AllVegatables[3].SellCost = 20; AllVegatables[3].Number = 3;
}

void BasicFarm(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    bot.getApi().sendMessage(message->chat->id, "Куда бы вы хотели пойти\n 1) огород\n 2) магазин\n 3) амбар\n 4) выход наружу\n");
    BasicFlag = true;
    GardenFlag = false;
    StorehouseFlag = false;
    ShopFlag = false;
}


void StoreHouse(TgBot::Message::Ptr message){
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    MessageOut = "Вы в амбаре, тут хранится ваше имуществу\ny вас ";
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    if (AllYouSeed != 0) {
        MessageOut.append("Ваши семена:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].amount != 0){
                MessageOut.append(std::to_string(AllSeeds[i].amount));
                MessageOut.append(": ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append("\n");
            }
        }
    }
    if (AllYourVegatables != 0) {
        MessageOut.append("\nВаши овощи:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllVegatables[i].amount != 0){
                MessageOut.append(std::to_string(AllVegatables[i].amount));
                MessageOut.append(": " );
                MessageOut.append(AllVegatables[i].Name);
                MessageOut.append("\n\n");
            }
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void ShopOut(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    MessageOut.append("У вас: \n");
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    MessageOut.append("Ассортимент товаров: \n");
    for (int i = 0; i < AvailableSeed; i++) {
        MessageOut.append(std::to_string(i+1));
        MessageOut.append(") ");
        MessageOut.append(AllSeeds[i].Name);
        MessageOut.append(" Цена: ");
        MessageOut.append(std::to_string(AllSeeds[i].BuyCost));
        MessageOut.append("\n");
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void BuyFirstStep(TgBot::Message::Ptr message, int Index, int Amount) { //ПРОВЕРКА НА ОТРИЦАТЕЛЬНЫЕ ДЕНЬГИ
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
        money -= AllSeeds[Index - 1].BuyCost * Amount;
    AllSeeds[Index - 1].amount += Amount;
    AllYouSeed += Amount;
    return;
}

void BuySecondStep(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    MessageOut.append("У вас: \n");
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    return;
}

int* SellSeedsOut(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    int schet = 0;
    int SchetAll = 1;
    if (AllYouSeed != 0) {
        MessageOut.append("Ваши семена(введите их индекс):\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].amount != 0){
                UsedSeedsInSellingSec[schet] = i;
                MessageOut.append(std::to_string(SchetAll));
                MessageOut.append(") ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append(": ");
                MessageOut.append(std::to_string(AllSeeds[i].amount));
                MessageOut.append("\n");
                ++schet;
                ++SchetAll;
            }
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    return UsedSeedsInSellingSec;
}

void SellSeeds(TgBot::Message::Ptr message, int Index, int Amount) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllSeeds[UsedSeedsInSellingSec[Index - 1]].amount >= Amount) {
        money += AllSeeds[UsedSeedsInSellingSec[Index - 1]].BuyCost * Amount;
        AllSeeds[UsedSeedsInSellingSec[Index - 1]].amount -= Amount;
        AllYouSeed -= Amount;
    } else {
        bot.getApi().sendMessage(message->chat->id, "ошибка ввода ");
    }
}

void SellVegetables(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    if (AllYourVegatables != 0) {
        MessageOut.append("\nВаши овощи:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllVegatables[i].amount != 0){
                MessageOut.append(std::to_string(AllVegatables[i].amount));
                MessageOut.append(": " );
                MessageOut.append(AllVegatables[i].Name);
                MessageOut.append("\n\n");
            }
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();

    bot.getApi().sendMessage(message->chat->id,"Введите номер овоща, который вы хотите продать, по порядку и количество: ");
    int Index = 0, Amount = 0;
    std::cin >> Index >> Amount;
    if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllVegatables[Index - 1].amount >= Amount) {
        money += AllVegatables[Index - 1].SellCost * Amount;
        AllVegatables[Index - 1].amount -= Amount;
        AllYourVegatables -= Amount;
    } else {
        bot.getApi().sendMessage(message->chat->id, "ошибка ввода");
    }
}

void Garden(TgBot::Message::Ptr message){
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    MessageOut.append("Вы вышли в огород\nВот ваши грядки\n");
    time_t timeNow = time (NULL);
    for(int i = 0; i < SeedBedAmount; i++){
        if (AllSeedBeds[i].buse) {
            if (AllSeeds[AllSeedBeds[i].NumberSeed].TimeGrowth - timeNow + AllSeedBeds[i].TimeLanding > 0){
                MessageOut.append("🪺  ");
                MessageOut.append( AllSeeds[AllSeedBeds[i].NumberSeed].Name);
                MessageOut.append(" осталось до полного созревания ");
                MessageOut.append(std::to_string(AllSeeds[AllSeedBeds[i].NumberSeed].TimeGrowth - timeNow + AllSeedBeds[i].TimeLanding));
                MessageOut.append("\n");
            } else {
                MessageOut.append("🪺  ");
                MessageOut.append(AllSeeds[AllSeedBeds[i].NumberSeed].Name);
                MessageOut.append(" созрели\n");
            }
        }else {
            MessageOut.append("🪹 \n");
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    bot.getApi().sendMessage(message->chat->id,  "Что вы хотите сделать ?\n 1)проверить_растения\n 2)посадить_семена\n 3)собрать_всё\n 4)обратно\n");
}

void PlantSeedOut(TgBot::Message::Ptr message) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    if (AllYouSeed != 0) {
        MessageOut.append("семена:\n");
        int Number = 1;
        int schet = 0;
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].amount != 0){
                UsedSeedsInSellingSec[schet] = i;
                MessageOut = std::to_string(Number);
                MessageOut.append(") ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append(" ");
                MessageOut.append(std::to_string(AllSeeds[i].amount));
                bot.getApi().sendMessage(message->chat->id, MessageOut);
                MessageOut.clear();
                Number++;
            }
        }
    } else {
        bot.getApi().sendMessage(message->chat->id, "У вас нет семян , потому что их надо купить");
    }
    bot.getApi().sendMessage(message->chat->id, "какие семена(номер) вы хотите посадить ?\n");
}

void PlantSeed(TgBot::Message::Ptr message, int Index, int Amount) {
    TgBot::Bot bot("7590778478:AAF_Y2viQaAtczVc6xYu3NphxnFmrJh8vO8");
    --Index;
    for(int i = 0; Amount > 0 && i < SeedBedAmount; i++){
        if (!AllSeedBeds[i].buse && AllSeeds[UsedSeedsInSellingSec[Index]].amount > 0){
            AllSeedBeds[i].buse = true;
            AllSeedBeds[i].NumberSeed = UsedSeedsInSellingSec[Index];
            AllSeedBeds[i].TimeLanding = time (NULL);
            Amount--;
            AllSeeds[UsedSeedsInSellingSec[Index]].amount--;
            AllYouSeed--;
        }
    }
    if (Amount != 0) {
        bot.getApi().sendMessage(message->chat->id, "У вас кончились семена(мы не смогли посадить столько сколько вы хотели)\n");
    }

}
