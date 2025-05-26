#include "farm.h"

TgBot::Bot bot("7590778478:AAGfg-6Q_PofDaS4D1tFB8F105M9p72gkrQ");

void Start(){
    AllSeeds[0].Name = "Семена пшена";    AllSeeds[0].TimeGrowth = 10; AllSeeds[0].BuyingPrice = 4;  AllSeeds[0].SeedsSellingPrice = 3;  AllSeeds[0].Number = 0;
    AllSeeds[1].Name = "Семена морковки"; AllSeeds[1].TimeGrowth = 20; AllSeeds[1].BuyingPrice = 2;  AllSeeds[1].SeedsSellingPrice = 1;  AllSeeds[1].Number = 1;
    AllSeeds[2].Name = "Семена свеклы";   AllSeeds[2].TimeGrowth = 30; AllSeeds[2].BuyingPrice = 6;  AllSeeds[2].SeedsSellingPrice = 5;  AllSeeds[2].Number = 2;
    AllSeeds[3].Name = "Семена тыквы";    AllSeeds[3].TimeGrowth = 60; AllSeeds[3].BuyingPrice = 12; AllSeeds[3].SeedsSellingPrice = 15; AllSeeds[3].Number = 3;
    AllSeeds[4].Name = "Семена черники";    AllSeeds[4].TimeGrowth = 60; AllSeeds[4].BuyingPrice = 12; AllSeeds[4].SeedsSellingPrice = 15; AllSeeds[4].Number = 4;
    AllSeeds[5].Name = "Семена малины";    AllSeeds[5].TimeGrowth = 60; AllSeeds[5].BuyingPrice = 15; AllSeeds[5].SeedsSellingPrice = 20; AllSeeds[5].Number = 5;
    AllSeeds[6].Name = "Семена винограда";    AllSeeds[6].TimeGrowth = 80; AllSeeds[6].BuyingPrice = 20; AllSeeds[6].SeedsSellingPrice = 30; AllSeeds[6].Number = 6;

    AllVegatables[0].Name = "Пшено";    AllVegatables[0].VegarableSellingPrice = 6;  AllVegatables[0].Number = 0;
    AllVegatables[1].Name = "Морковка"; AllVegatables[1].VegarableSellingPrice = 4;  AllVegatables[1].Number = 1;
    AllVegatables[2].Name = "Свекла";   AllVegatables[2].VegarableSellingPrice = 10; AllVegatables[2].Number = 2;
    AllVegatables[3].Name = "Тыква";    AllVegatables[3].VegarableSellingPrice = 20; AllVegatables[3].Number = 3;
    AllVegatables[4].Name = "черники";    AllVegatables[4].VegarableSellingPrice = 20; AllVegatables[4].Number = 4;
    AllVegatables[5].Name = "малины";    AllVegatables[5].VegarableSellingPrice = 20; AllVegatables[5].Number = 5;
    AllVegatables[6].Name = "винограда";    AllVegatables[6].VegarableSellingPrice = 20; AllVegatables[6].Number = 6;

    AllProducts[0].Name = "чернозем";  AllProducts[0].ProductPrice = 20; AllProducts[0].Number = 7;
    AllProducts[1].Name = "гвозди";   AllProducts[1].ProductPrice = 5; AllProducts[1].Number = 8;
    AllProducts[2].Name = "доски";  AllProducts[2].ProductPrice = 15; AllProducts[2].Number = 9;
    AllProducts[3].Name = "лопата";  AllProducts[3].ProductPrice = 25; AllProducts[3].Number = 10;

    Vipe();
}

void BasicFarm(TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Куда бы вы хотели пойти\n 1) огород\n 2) магазин\n 3) амбар\n 4) выход\n");
    BasicFlag = true;
    GardenFlag = false;
    StorehouseFlag = false;
    ShopFlag = false;
}


void StoreHouse(TgBot::Message::Ptr message){
    MessageOut = "Вы в амбаре, тут хранится ваше имущество\ny вас ";
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    if (AllYourSeeds != 0) {
        MessageOut.append("Ваши семена:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].Amount != 0){
                MessageOut.append(std::to_string(AllSeeds[i].Amount));
                MessageOut.append(": ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append("\n");
            }
        }
    }
    if (AllYourVegatables != 0) {
        MessageOut.append("\nВаши овощи:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllVegatables[i].Amount != 0){
                MessageOut.append(std::to_string(AllVegatables[i].Amount));
                MessageOut.append(": " );
                MessageOut.append(AllVegatables[i].Name);
                MessageOut.append("\n\n");
            }
        }
    }
    if (AllYourProducts != 0) {
        MessageOut.append("Ваш товар:\n");
        for (int i = 0; i < AvailableProducts; i++) {
            if (AllProducts[i].Amount != 0){
                MessageOut.append(std::to_string(AllProducts[i].Amount ));
                MessageOut.append(": " );
                MessageOut.append(AllProducts[i].Name);
                MessageOut.append("\n");
            }
        }
    }
    if(CurrentStorehouseLevel != 5) {
        MessageOut.append("\n1)улучшить_амбар (");
        MessageOut.append("единиц досок: ");
        MessageOut.append(std::to_string(StorehouseLevelling[CurrentStorehouseLevel-1]));
        MessageOut.append(", гвоздей: ");
        MessageOut.append(std::to_string(StorehouseLevelling[CurrentStorehouseLevel]));
        MessageOut.append(")\n2)Выбросить_предметы\n3)обратно\n");
    } else {
        MessageOut.append("\n1)улучшить_амбар (максимальный уровень)\n2)выбросить_предметы\n3)обратно\n");
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void BuyStorehouseUpgrade(TgBot::Message::Ptr message) {
    if(AllProducts[2].Amount >= StorehouseLevelling[CurrentStorehouseLevel-1] & AllProducts[1].Amount >= StorehouseLevelling[CurrentStorehouseLevel]) {
        AllProducts[2].Amount -= StorehouseLevelling[CurrentStorehouseLevel-1];
        AllProducts[1].Amount -= StorehouseLevelling[CurrentStorehouseLevel];
        AllYourProducts -= (StorehouseLevelling[CurrentStorehouseLevel]+StorehouseLevelling[CurrentStorehouseLevel-1]);
        UpgradeStorehouse(CurrentStorehouseLevel+2, message);
    } else {
        MessageOut.append("Вам не хватает материалов\n ");
        bot.getApi().sendMessage(message->chat->id, MessageOut);
        MessageOut.clear();
    }
}

void UpgradeStorehouse(int Level, TgBot::Message::Ptr message){
    switch (Level){
        case 3: {
                MaxItemStorage += 10;
                MaxSeedsStorage += 10;
                bot.getApi().sendMessage(message->chat->id, "Место хранения увеличилось на 20 единиц");
                CurrentStorehouseLevel+=2;
            break;
        }
        case 5: {
                MaxItemStorage += 20;
                MaxSeedsStorage += 20;
                bot.getApi().sendMessage(message->chat->id, "Место хранения увеличилось на 40 единиц");
                CurrentStorehouseLevel+=2;
            break;
            }
        default: {
            bot.getApi().sendMessage(message->chat->id, "Вы уже улучшили амбар до максимального уровня!");
        }
    }
}

void ThrowAwayItems(TgBot::Message::Ptr message) {
    for(int i = 0; i < MaxAvailableProducts; ++i) {
        AllProducts[i].Amount = 0;
    }
    AllYourProducts = 0;
}

void Shop(TgBot::Message::Ptr message) {
    MessageOut.append("У вас: \n");
    MessageOut.append(std::to_string(money));
    if(CurrentShopLevel != 3) {
        MessageOut.append(" денег \nВы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)улучшить_магазин (");
        MessageOut.append(std::to_string(ShopLevelling[CurrentShopLevel-1]));
        MessageOut.append(" денег)\n5)обратно \n");
    } else {
        MessageOut.append(" денег \nВы хотите:\n1)купить\n2)продать_семена\n3)продать_овощи\n4)улучшить_магазин (максимальный уровень)\n5)обратно");
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void ShopOutput(TgBot::Message::Ptr message) {
    int schet = 0;
    MessageOut.append("У вас: \n");
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    MessageOut.append("Ассортимент товаров: \n");
    for (int i = 0; i < AvailableSeed; i++) {
        MessageOut.append(std::to_string(i+1));
        MessageOut.append(") ");
        MessageOut.append(AllSeeds[i].Name);
        MessageOut.append(" Цена: ");
        MessageOut.append(std::to_string(AllSeeds[i].BuyingPrice));
        MessageOut.append("\n");
        ++schet;
    }
    MessageOut.append("Другие товары:\n");
    for (int i = schet; i < AvailableProducts+schet; i++) {
        MessageOut.append(std::to_string(i+1));
        MessageOut.append(") ");
        MessageOut.append(AllProducts[i-schet].Name);
        MessageOut.append(" Цена: ");
        MessageOut.append(std::to_string(AllProducts[i-schet].ProductPrice));
        MessageOut.append("\n");
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void BuyFirstStep(TgBot::Message::Ptr message, int Index, int Amount) {
    if(Index <= AvailableSeed) {
        if (AllYourSeeds + Amount> MaxSeedsStorage){
            bot.getApi().sendMessage(message->chat->id, "Недостаточно места в амбаре\n");
            return;
        }
        if(money - AllSeeds[Index - 1].BuyingPrice * Amount > 0) {
            money -= AllSeeds[Index - 1].BuyingPrice * Amount;
            AllSeeds[Index - 1].Amount += Amount;
            AllYourSeeds += Amount;
        }
        else{
            bot.getApi().sendMessage(message->chat->id, "Недостаточно денег\n");
        }
    }
    if (Index > AvailableSeed){
        if (Amount+ AllYourProducts > MaxItemStorage){
            bot.getApi().sendMessage(message->chat->id, "Недостаточно места в амбаре\n");
            return;
        }
        Index-=AvailableSeed;
        if (Index > 0 && Index <= AvailableProducts && Amount > 0 && AllProducts[Index - 1].ProductPrice * Amount <= money) {
                money -= AllProducts[Index - 1].ProductPrice * Amount;
                AllProducts[Index - 1].Amount += Amount;
                AllYourProducts += Amount;
        } else {
            bot.getApi().sendMessage(message->chat->id, "Недостаточно денег\n");
        }
    }
    return;
}

void BuySecondStep(TgBot::Message::Ptr message) {
    MessageOut.append("У вас: \n");
    MessageOut.append(std::to_string(money));
    MessageOut.append(" денег \n");
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    return;
}

void SellSeedsOut(TgBot::Message::Ptr message) {
    int schet = 0;
    int SchetAll = 1;
    if (AllYourSeeds != 0) {
        MessageOut.append("Ваши семена(введите их индекс):\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].Amount != 0){
                UsedSeedsInSelling[schet] = i;
                MessageOut.append(std::to_string(SchetAll));
                MessageOut.append(") ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append(": ");
                MessageOut.append(std::to_string(AllSeeds[i].Amount));
                MessageOut.append("\n");
                ++schet;
                ++SchetAll;
            }
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    return;
}

void SellSeeds(TgBot::Message::Ptr message, int Index, int Amount) {
    if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllSeeds[UsedSeedsInSelling[Index - 1]].Amount >= Amount) {
        money += AllSeeds[UsedSeedsInSelling[Index - 1]].BuyingPrice * Amount;
        AllSeeds[UsedSeedsInSelling[Index - 1]].Amount -= Amount;
        AllYourSeeds -= Amount;
    } else {
        bot.getApi().sendMessage(message->chat->id, "ошибка ввода ");
    }
}

void SellVegetablesOut(TgBot::Message::Ptr message) {
    int schet = 0;
    int SchetAll = 1;
    if (AllYourVegatables != 0) {
        MessageOut.append("\nВаши овощи:\n");
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllVegatables[i].Amount != 0){
                UsedVegetablesInSelling[schet] = i;
                MessageOut.append(std::to_string(SchetAll));
                MessageOut.append(") ");
                MessageOut.append(AllVegatables[i].Name);
                MessageOut.append(": ");
                MessageOut.append(std::to_string(AllVegatables[i].Amount));
                MessageOut.append("\n");
                ++schet;
                ++SchetAll;
            }
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    return;
}

void SellVegetables(TgBot::Message::Ptr message, int Index, int Amount) {
    if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllVegatables[UsedVegetablesInSelling[Index - 1]].Amount >= Amount) {
        money += AllVegatables[UsedVegetablesInSelling[Index - 1]].VegarableSellingPrice * Amount;
        AllVegatables[UsedVegetablesInSelling[Index - 1]].Amount -= Amount;
        AllYourVegatables -= Amount;
    } else{
        bot.getApi().sendMessage(message->chat->id, "У вс недостаточно овощей! ");
    }
}

int BuyShopUpgrade(TgBot::Message::Ptr message) {
    if(money >= ShopLevelling[CurrentShopLevel-1]) {
        money -= ShopLevelling[CurrentShopLevel-1];
        UpgradeShop(CurrentShopLevel+1, message);
        return CurrentShopLevel;
    } else {
        MessageOut.append("Вам нехватает денег");
        bot.getApi().sendMessage(message->chat->id, MessageOut);
        MessageOut.clear();
        return CurrentShopLevel;
    }
}

int UpgradeShop(int Level, TgBot::Message::Ptr message){
    switch (Level){
        case 2: {
            AvailableSeed+=1;
            AvailableProducts+=3;
            CurrentShopLevel+=1;
            break;
        }
        case 3:{
            AvailableSeed+=2;
            CurrentShopLevel+=1;
            break;
        }
        default: {
            MessageOut.append("Ваш магазин уже достиг максимального уровня!\n");
            bot.getApi().sendMessage(message->chat->id, MessageOut);
            MessageOut.clear();
        }
    }
    return CurrentShopLevel;
}

void Garden(TgBot::Message::Ptr message){
    MessageOut.append("Вы вышли в огород\nВот ваши грядки:\n");
    time_t timeNow = time (NULL);
    for(int i = 0; i < SeedBedAmount; i++){
        if (AllSeedBeds[i].buse) {
            if (AllSeeds[AllSeedBeds[i].SeedNumber].TimeGrowth - timeNow + AllSeedBeds[i].PlantingTime > 0){
                MessageOut.append("🪺  ");
                MessageOut.append( AllSeeds[AllSeedBeds[i].SeedNumber].Name);
                MessageOut.append(" осталось до полного созревания ");
                MessageOut.append(std::to_string(AllSeeds[AllSeedBeds[i].SeedNumber].TimeGrowth - timeNow + AllSeedBeds[i].PlantingTime));
                MessageOut.append("\n");
            } else {
                MessageOut.append("🪺  ");
                MessageOut.append(AllSeeds[AllSeedBeds[i].SeedNumber].Name);
                MessageOut.append(" созрели\n");
            }
        }else {
            MessageOut.append("🪹 \n");
        }
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
    if(CurrentGardenLevel != 3) {
        MessageOut.append("Что вы хотите сделать ?\n 1)проверить_растения\n 2)посадить_семена\n 3)собрать_всё\n 4)выкопать_грядку (");
        MessageOut.append("единиц чернозёма: ");
        MessageOut.append(std::to_string(GardenLevelling[CurrentGardenLevel-1]));
        MessageOut.append(", лопат: 1)\n 5)обратно\n");
    } else {
        MessageOut.append("Что вы хотите сделать ?\n 1)проверить_растения\n 2)посадить_семена\n 3)собрать_всё\n 4)выкопать_грядку (максимальное количество)\n 5)обратно\n");
    }
    bot.getApi().sendMessage(message->chat->id, MessageOut);
    MessageOut.clear();
}

void PlantSeedOutput(TgBot::Message::Ptr message) {
    if (AllYourSeeds != 0) {
        MessageOut.append("семена:\n");
        int Number = 1;
        int schet = 0;
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].Amount != 0){
                UsedSeedsInSelling[schet] = i;
                MessageOut = std::to_string(Number);
                MessageOut.append(") ");
                MessageOut.append(AllSeeds[i].Name);
                MessageOut.append(" ");
                MessageOut.append(std::to_string(AllSeeds[i].Amount));
                bot.getApi().sendMessage(message->chat->id, MessageOut);
                MessageOut.clear();
                Number++;
                schet++;
            }
        }
    } else {
        bot.getApi().sendMessage(message->chat->id, "У вас нет семян , потому что их надо купить");
    }
    bot.getApi().sendMessage(message->chat->id, "какие семена(номер) вы хотите посадить ?\n");
}

void PlantSeed(TgBot::Message::Ptr message, int Index, int Amount) {
    --Index;
    SeedInArrFlag = false;
    if(Index > 1 && UsedSeedsInSelling[Index] == 0) {
        std::cout<<UsedSeedsInSelling[Index] << Index <<std::endl;
        SeedInArrFlag = true;
    }
    if(SeedInArrFlag) {
        bot.getApi().sendMessage(message->chat->id, "У вас кончились такие семена или недостаточно свободных грядок\n");
        return;
    }
    for(int i = 0; Amount > 0 && i < SeedBedAmount; i++){
        if (!AllSeedBeds[i].buse && AllSeeds[UsedSeedsInSelling[Index]].Amount > 0){
            AllSeedBeds[i].buse = true;
            AllSeedBeds[i].SeedNumber = UsedSeedsInSelling[Index];
            AllSeedBeds[i].PlantingTime = time (NULL);
            Amount--;
            AllSeeds[UsedSeedsInSelling[Index]].Amount--;
            AllYourSeeds--;
        }
    }
    if (Amount != 0) {
        bot.getApi().sendMessage(message->chat->id, "У вас кончились такие семена или недостаточно свободных грядок\n");
    }
}

void CollectAllVegatables(TgBot::Message::Ptr message) {
    for(int i = 0; i < SeedBedAmount; i++) {
        if (AllSeedBeds[i].buse && AllSeeds[AllSeedBeds[i].SeedNumber].TimeGrowth - time (NULL) + AllSeedBeds[i].PlantingTime <= 0) {
            AllSeedBeds[i].buse = false;
            AllVegatables[AllSeeds[AllSeedBeds[i].SeedNumber].Number].Amount++;
            AllYourVegatables++;
        }
    }
}

void GetGardenUpgrade(TgBot::Message::Ptr message) {
    if(AllProducts[3].Amount > 0 && AllProducts[0].Amount >= GardenLevelling[CurrentGardenLevel-1]) {
        AllProducts[0].Amount-= GardenLevelling[CurrentGardenLevel-1];
        UpgradeGarden(CurrentGardenLevel+1, message);
    } else {
        bot.getApi().sendMessage(message->chat->id, "Вам нехватает товара\n ");
    }
}

void UpgradeGarden(int Level, TgBot::Message::Ptr message){
    switch (Level){
        case 2: {
            SeedBedAmount+=1;
            CurrentGardenLevel+=1;
            break;
        }
        case 3: {
            SeedBedAmount+=1;
            CurrentGardenLevel+=1;
            break;
        }
        default: {
            bot.getApi().sendMessage(message->chat->id, "Грядки уже улучшены до максимального уровня!");
            break;
        }
    }
}

void Vipe() {
    money = 3000;
    CurrentShopLevel = 1;
    CurrentStorehouseLevel = 1;
    CurrentGardenLevel =1;
    MaxItemStorage = 30;
    MaxSeedsStorage = 20;
    SeedBedAmount = 5;
    AllYourSeeds = 0;
    AllYourVegatables = 0;
    AvailableSeed = 4;
    BasicFlag = false;
    GardenFlag = false;
    StorehouseFlag = false;
    ShopFlag = false;
    FirstStepInputFlag = false;
    SecondStepInputFlag = false;
    SeedInArrFlag = false;
    for(int i = 0; i<SeedBedAmount; i++) {
        AllSeedBeds[i].buse = false;
    }
    for(int i = 0; i<MaxAvailableSeed; i++) {
        AllSeeds[i].Amount = 0;
        AllVegatables[i].Amount = 0;
    }
    for(int i = 0; i<MaxAvailableProducts; i++) {
        AllProducts[i].Amount = 0;
    } //Нужно для рестарта игры
}
