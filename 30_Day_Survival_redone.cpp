#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

int ammo, dayCounter, playHealth, basicZombieHealth, biggerZombieHealth, medic, i, firstChoice, food, hunger, meat, cityEvent, forestEvent, huntEvent, cookEvent, healEvent, smallHordeSize, bigHordeSize;
string playerName;
bool searchArea;

//first choice
void explore();
void setCamp();

//Explore choices
void exploreCity();
void exploreForest();

//Player effects
void hunt();
void cook();
void heal();

//City explore Events
void searchHouse();
void searchStore();
void zombieHorde();
void vehicle();
void scavanger();

//Forest explore Events
void survivorCamp();
void farmHouse();
void deerHunt();
void zombieBear(); //Also in hunting
void banditCamp();
void crashedHeli();

//hunting
void wolfPack();
void fishing();

//Searching
bool search();

//Fighting
void figthBasicZombie();
void fightLargeZombie();
void fightScavanger();

//Player health and hunger check
void checkPlayerHp();
void checkHunger();

//End states
void runOutOfAmmo();
void endGame();

//damage
int bulletDamage();

int main(){
  cout << "Welcome to 30 day survival your goal is to survive 30 days and be rescued.\nPlease enter a survivors name and begin \n";
  getline(cin, playerName);
  cout << "Hello " << playerName << endl << endl;

  dayCounter = 1; // Keeps track of days
  playHealth = 10; // Players health if below 5 risk of of infection the lower it goes from 5 the higher the risk
  ammo = 24; // Ammo for the gun you start with, ammo can be found in relavent buildings such as homes and gun stores (hunting rifle)
  medic = 3; // Medic can heal injuries to reduce the infection
  basicZombieHealth = 3; // basic Zombies health
  biggerZombieHealth = 5; // Stronger Zombies health
  food = 5; // Food the player has stored
  hunger = 5; // Hunger level, 1 = 1 whole day of Hunger
  meat = 0;

  for(i = 0; i < 30; i++){
    srand(time(0));
    cout << "---------------- Day " << dayCounter << " ----------------" << endl;
    cout << "Name = " << playerName << endl << "Health = " << playHealth << endl << "Ammo = " << ammo << endl << "Medicine = " << medic << endl << "Hunger = " << hunger << endl << "Food = " << food << endl << "Raw meat = " << meat << endl << endl;
    cout << "Enter 1 if you wish to explore. \nEnter 2 if you wish to set up camp " << endl;
    cin >> firstChoice;

    //option branchs
    if(firstChoice == 1){
      explore();
    } else {
      setCamp();
    }

    //End of day calculations
    hunger = hunger - 1;
    dayCounter = dayCounter + 1;
    checkHunger();
    if(food > 0){
      hunger = hunger + 1;
      food = food - 1;
    }
    cout << " " << endl;
  }
  if(dayCounter >= 30){
    cout << "You have been rescued" << endl;
  }
}

// IF the player choses to explore they can choose between the nearby forest to hunt or look for buildings in the forrest or the city to scavange from buildings and cars
void explore(){
  int choice;
  cout << " \nWhere do you wish to explore \n1 City \n2 Forest " << endl;
  cin >> choice;
  if (choice == 1){
    exploreCity();
  } else {
    exploreForest();
  }
}

// Setting camp will allow the player to cook, rest/heal and
void setCamp(){
  int choice;
  cout << "Camp set, do you wish to \n1 Hunt \n2 Cook \n3 Heal " << endl;
  cin >> choice;
  if(choice == 1){
    hunt();
  }
  if(choice == 2){
    cook();
  }
  if (choice == 3){
    heal();
  }

}

void exploreCity(){
  cityEvent = rand() % 11 + 1;
  cout << " " << endl;
  switch(cityEvent){
    //1 and 2 will be two different houses
    case 1:
    case 2:
      searchHouse();
      break;
    //3 and 4 will be supermarket and gas station
    case 3:
    case 4:
      searchStore();
      break;
    //5 and 6 will be a large or small horde of Zombies
    case 5:
    case 6:
      zombieHorde();
      break;
    //7 and 8 train and car crash
    case 7:
    case 8:
      vehicle();
      break;
    //9 and 10 a rouge scvanger
    case 9:
    case 10:
      scavanger();
      break;
  }
}

void exploreForest(){
  forestEvent = rand() % 10 + 1;
  if(forestEvent == 1){
    //Survivor camp
    survivorCamp();
  }
  if(forestEvent == 2){
    //Farmhouse
    farmHouse();
  }
  if((forestEvent == 3) || (forestEvent == 4)){
    //hunt
    hunt();
  }
  if(forestEvent == 5){
    //Zombie bear
    zombieBear();
  }
  if((forestEvent == 6) || (forestEvent == 7)){
    //Bandit camp
    banditCamp();
  }
  if((forestEvent == 8) || (forestEvent == 9)){
    //Crashed heli
    crashedHeli();
  }
}

void hunt(){
  huntEvent = rand() % 7 + 1;
  //1 and 2  rabbit
  //3 and 4 deer and zombie bear
  //5 and 6 fishing and wolf pack
  if((huntEvent == 1) || (huntEvent == 2)){
    cout << "Rabbit spotted " << endl;
    int sucChance = rand() % (4 - 1) + 1;
    switch(sucChance){
      case 1:
      case 2:
      if(ammo < 0){
        cout << "You sneak up and stab the rabbit " << endl;
        meat = meat + 2;
      }else{
        cout << "You shoot the and hit the rabbit " << endl;
        meat = meat + 2;
        ammo = ammo - 1;
      }
      case 3:
      if(ammo < 0){
        cout << "You fail to hunt rabbit " << endl;
      }else{
        cout << "You fail to hunt rabbit " << endl;
        ammo = ammo - 1;
    }
  }
  } else if(huntEvent == 3){
    cout << "Deer spotted " << endl;
    int sucChance = rand() % 4 + 1;
    switch(sucChance){
      case 1:
      case 2:
      if(ammo < 0){
        cout << "You fail to hunt the deer" << endl;
      }else{
        cout << "You shoot and hit the deer " << endl;
        meat = meat + 5;
        ammo = ammo - 1;
      }
      case 3:
      if(ammo < 0){
        cout << "You fail to hunt the deer" << endl;
      }else{
        cout << "You fail to hunt the deer" << endl;
        ammo = ammo - 1;
    }
  }
  } else if(huntEvent == 4){
    zombieBear();
  } else if(huntEvent == 5){
    fishing();
  } else{
    wolfPack();
  }

}

void cook(){
  cookEvent = rand() % 4 + 1;
  //1 and 2 cooked right
  //3 burnt meat (unedible)
  while(meat > 0){
    switch (cookEvent){
      case 1:
      case 2:
        cout << "Food Cooked" << endl;
        meat = meat - 1;
        food = food + 1;
        break;
      case 3:
        cout << "Food ruined" << endl;
        meat = meat - 1;
        break;
    }
    return;
  }
}

void heal(){
  healEvent = rand() % 7 + 1;
  //1, 2 and 3 perfect heal
  //4 and 5 uneffective health
  //6 butchers heal deals damage and is uneffective
  while(medic > 0){
    switch (healEvent){
      case 1:
      case 2:
      case 3:
        cout << "Healed" << endl;
        medic = medic - 1;
        playHealth = playHealth + 3;
        break;
      case 4:
      case 5:
        cout << "Heal failed" << endl;
        medic = medic - 1;
        break;
      case 6:
        cout << "Heal failed and butcherd" << endl;
        medic = medic - 1;
        playHealth = playHealth - 1;
        checkPlayerHp();
        break;
    }
    return;
  }
}

void searchHouse(){ //CITY
  int iteamId;
  iteamId = 0;
  //1 is one story small houses - small houses contain food and medicine and possible small zombies highst chance of nothing
  if(cityEvent == 1){
    cout << "Small house found" << endl;
    for(i = 0; i < 2; i++){
      searchArea = search();
      if(searchArea == false){
        cout << "Room is empty " << endl;
      }else{
        int iteamId = rand() % 4 + 1;
        if(iteamId == 1){
          medic = medic + 1;
          cout << "Medicine found" << endl;
        }else if(iteamId == 2){
          food = food + 1;
          cout << "Food found" << endl;
        } else {
          cout << "Zombie found" << endl;
          figthBasicZombie(); // NOT DONE YET
        }
      }
    }
  }
  //2 is a two story big house - bigger houses have food, medicine, ammo and armor and possible small and large zombies 2nd highest chance of nothing
  if(cityEvent == 2){
    cout << "large house found" << endl;
    for(i = 0; i < 3; i++){
      searchArea = search();
      if(searchArea == false){
        cout << "Room is empty" << endl;
      }else{
        iteamId = rand() % (7 - 1) + 1;
        if(iteamId == 1){
          medic = medic + 1;
          cout << "Medicine found" << endl;
        }else if(iteamId == 2){
          food = food + 1;
          cout << "Food found" << endl;
        }else if(iteamId == 3){
          ammo = ammo + 1;
          cout << "Ammo found" << endl;
        } else {
          cout << "Zombie found" << endl;
          fightLargeZombie(); // NOT DONE Yet
        }
      }
    }
  }
}

void searchStore(){ //CITY
  //3 is a gas station - food, medicine, ammo greater 3rd highest chance of nothing
  int iteamId;
  if(cityEvent == 3){
    cout << "Gas station found" << endl;
    for(i = 0; i < 1; i++){
      searchArea = search();
      if(searchArea == false){
        cout << "Gas station is empty" << endl;
      }else{
        iteamId = rand() % 4 + 1;
      if (iteamId == 1){
          food = food + 1;
          cout << "Food found" << endl;
        }else if(iteamId == 2){
          ammo = ammo + 1;
          cout << "Ammo found" << endl;
        } else {
          cout << "Zombie found" << endl;
          fightLargeZombie(); // NOT DONE Yet
        }
      }
    }
  }

  //4 is a supermarket food and medice has lowest chance of nothing
  if(cityEvent == 4){
    cout << "Supermarket found" << endl;
    for(i = 0; i < 5; i++){
      searchArea = search();
      if(searchArea == false){
        cout << "Isle is empty" << endl;
      }else{
        iteamId = rand() % 5 + 1;
        if(iteamId == 1){
          medic = medic + 1;
          cout << "Medicine found" << endl;
        }else if(iteamId == 2){
          food = food + 1;
          cout << "Food found" << endl;
        } else {
          cout << "Zombie found" << endl;
          fightLargeZombie(); // NOT DONE Yet
        }
      }
    }
  }
}

void zombieHorde(){ //CITY
  //5 is a small horde (3-4 small zombies) - can fight to loot or can attempt to sneak by or run back to camp higher chance to sneak by
  if(cityEvent == 5){
    smallHordeSize = rand() % 5 + 1;
    cout << "A horde of small zombies spotted with " << smallHordeSize << " zombies " << endl;
      figthBasicZombie();
    }
  //6 is larger horde 7-9 small zombies  - can fight or can attempt to sneak by or run back to camp lower chance to sneak by
  if(cityEvent == 6){
    bigHordeSize = rand() % 5 + 1;
    cout << "A horde of large zombies spotted with " << bigHordeSize << " zombies " << endl;
      fightLargeZombie();
    }
 }

void vehicle(){ //CITY
  //7 is a searchable car - food and guns
  if(cityEvent == 7){
    cout << "Car found " << endl;
    int carSearch = rand() % 5 + 1;
    switch (carSearch) {
      case 1:
        cout << "Ammo found " << endl;
        ammo = ammo + 1;
        break;
      case 2:
        cout << "Food found " << endl;
        food = food + 1;
        break;
      case 3:
      case 4:
        cout << "Car is empty " << endl;
        break;
    }
  }
  //8 is a train - food, medicne and zombies
  if(cityEvent == 8){
    cout << "Train found " << endl;
    for(i = 0; i < 3; i++){
      int trainSearch = rand() % 8 + 1;
      switch(trainSearch){
        case 1:
          cout << "Ammo found " << endl;
          ammo = ammo + 1;
          break;
        case 2:
          cout << "Food found " << endl;
          food = food + 1;
          break;
        case 3:
        case 4:
          cout << "Zombie found " << endl;
          figthBasicZombie();
          break;
        case 6:
        case 7:
          cout << "Train is empty " << endl;
          break;
      }
    }
  }
}

void scavanger(){ //CITY
  //9 freindly trader scavanger - can trade food for medicine and vice versa
  if(cityEvent == 9){
    cout << "A freindly scavanger calls out to you, and offers some supplies!" << endl;
    food = food + 1;
    medic = medic + 1;
    ammo = ammo + 3;
  }

  //10 Hostle scavanger - has to fight (gunfight)
  if(cityEvent == 10){
    cout <<"You catch the gaze of scavanger who is aiming their gun at you " << endl;
    fightScavanger();
  }
}

bool search(){ // Loot area
  int findChance = rand() % 5 + 1;

  if((findChance == 1) || (findChance == 2) || (findChance == 3)){
    return false; // 75% likely to find nothing
  }else{
    return true; //25% likely to find somthing
  }
}

void figthBasicZombie(){ // Fight with basic zombie
  int hordeHp, fightEvent, damageChance;
  hordeHp = smallHordeSize * 3;
  while(hordeHp > 0){
    damageChance = bulletDamage();
    fightEvent = rand() % 10 + 1;
    switch(fightEvent){
    case 1:
    case 2:
    case 3:
    case 4:
      if(ammo > 0){
        cout << "Zombie shot " << endl << endl;
        hordeHp = hordeHp - damageChance;
        ammo = ammo - 1;
      } else{
        cout << "Zombie stabbed " << endl;
        hordeHp = hordeHp - damageChance;
        playHealth = playHealth - 1;
        cout << "New health = " << playHealth << endl << endl;
        checkPlayerHp();
      }
      break;
    case 5:
    case 6:
    if(ammo > 0){
      cout << "Missed shot " << endl;
      ammo = ammo - 1;
    } else{
      cout << "Missed hit on Zombie who hits you " << endl;
      playHealth = playHealth - 1;
      cout << "New health = " << playHealth << endl << endl;
      checkPlayerHp();
    }
      break;
    case 8:
    case 9:
      cout << "Zombie attacks you " << endl << endl;
      playHealth = playHealth - 1;
      checkPlayerHp();
      break;
    }
  }
  cout << "Zombie dead " << endl;
}

void fightLargeZombie(){ // Fight with larger zombie
  int hordeHp, fightEvent, damageChance;
  hordeHp = bigHordeSize * 5;
  while(hordeHp > 0){
    damageChance = bulletDamage();
    fightEvent = rand() % 10 + 1;
    switch(fightEvent){
    case 1:
    case 2:
    case 3:
    case 4:
      if(ammo > 0){
        cout << "Zombie shot " << endl;
        hordeHp = hordeHp - damageChance;
        ammo = ammo - 1;
      } else{
        cout << "While stabbing the Zombie you trade hits " << endl;
        hordeHp = hordeHp - damageChance;
        playHealth = playHealth - 2;
        cout << "New health = " << playHealth << endl << endl;
        checkPlayerHp();
      }
      break;
    case 5:
    case 6:
    if(ammo > 0){
      cout << "You miss " << endl;
      ammo = ammo - 1;
    } else{
      cout << "Missed hit on Zombie who hits you " << endl;
      playHealth = playHealth - 2;
      cout << "New health = " << playHealth << endl << endl;
      checkPlayerHp();
    }
      break;
    case 8:
    case 9:
      cout << "Zombie attacks you " << endl;
      playHealth = playHealth - 2;
      cout << "New health = " << playHealth << endl << endl;
      checkPlayerHp();
      break;
  }
  }
  cout << "Zombie dead " << endl;
}

void fightScavanger(){
  int scavangerHealth, damage, playerHit, scavangerHit;
  scavangerHealth = 10;
  cout << playerName << " " << playHealth << "Hp" << " VS " << "Scavanger " << scavangerHealth << "Hp" << endl;
  int whoShootsFirst = rand() % 3 + 1; // 50/50 who shoots first
  if(whoShootsFirst == 1){ // Scavanger shoots first
    cout << "Scavanger shoots first " << endl;
      while(playHealth > 0){
        damage = bulletDamage();
        playerHit = rand() % 3 + 1;
        scavangerHit = rand() % 5 + 1;
        if(ammo == 0){
          runOutOfAmmo();
        } else {
          //Scavangers turn
          switch (scavangerHit){
            case 1:
              cout << "Scavanger hits " << endl;
              playHealth = playHealth - 1;
              checkPlayerHp();
              cout << "New health = " << playHealth << endl << endl;
              break;
            case 2:
            case 3:
            case 4:
              cout << "Scavanger misses " << endl << endl;
              break;
          }
          //Players turn
          switch (playerHit){
            case 1:
              scavangerHealth = scavangerHealth - damage;
              ammo = ammo - 1;
              cout << "You hit the scavanger " << endl;
              cout << "Scavangers Hp = " << scavangerHealth << endl;
              cout << "Ammo = " << ammo << endl << endl;
              break;
            case 2:
              ammo = ammo - 1;
              cout << "You missed " << endl;
              cout << "Ammo = " << ammo << endl << endl;
              break;
          }
          if(scavangerHealth == 0){
            cout << "Scavanger dies " << endl << endl;
            return;
          }
        }
      }

  }else{ // Player shoots first
    cout << "Player shoots first " << endl;
    while(playHealth > 0){
        int playerHit = rand() % 3 + 1;
        int scavangerHit = rand() % 5 + 1;
        if(ammo == 0){
          runOutOfAmmo();
          return;
        } else {
          //Players turn
          switch (playerHit){
            case 1:
              scavangerHealth = scavangerHealth - 1;
              ammo = ammo - 1;
              cout << "You hit the scavanger " << endl;
              cout << "Scavangers Hp = " << scavangerHealth << endl;
              cout << "Ammo = " << ammo << endl << endl;
              break;
            case 2:
              ammo = ammo - 1;
              cout << "You missed " << endl;
              cout << "Ammo = " << ammo << endl << endl;
              break;
          }
          //Scavangers turn
          switch (scavangerHit){
            case 1:
              cout << "Scavanger hits " << endl;
              playHealth = playHealth - 1;
              checkPlayerHp();
              cout << "New health = " << playHealth << endl << endl;
              break;
            case 2:
            case 3:
            case 4:
              cout << "Scavanger misses " << endl << endl;
              break;
          }
          if(scavangerHealth == 0){
            cout << "Scavanger is dead " << endl;
            return;
          }
        }
    }
  }
}

void survivorCamp(){
  //Give supplies
  cout << "Freindly survivors found who offer some supplies " << endl;
  int suppliesGiven = rand() % 4 + 1;
  switch(suppliesGiven){
    case 1:
    case 2:
      cout << "They offer some basic supplies " << endl;
      ammo = ammo + 3;
      food = food + 2;
      break;
    case 3:
      cout << "They offer some important supplies " << endl;
      ammo = ammo + 8;
      food = food + 4;
      medic = medic + 1;
      break;
  }
}
void farmHouse(){
  //Search for loot beware zombies
  int iteamId;
  cout << "Farm house found" << endl;
  for(i = 0; i < 3; i++){
    searchArea = search();
    if(searchArea == false){
      cout << "Room is empty " << endl;
    }else{
      iteamId = rand() % 7 + 1;
      if(iteamId == 1){
        medic = medic + 1;
        cout << "Medicine found" << endl;
      }else if(iteamId == 2){
        food = food + 1;
        cout << "Food found" << endl;
      }else if(iteamId == 3){
        ammo = ammo + 1;
        cout << "Ammo found" << endl;
      } else {
        cout << "Zombie found" << endl;
        fightLargeZombie(); // NOT DONE Yet
      }
    }
  }

}
void deerHunt(){
  //option to hunt deer
  int playerOption;
  cout << "Deer found \n do you wish to hunt? " << endl << "1 Hunt " << endl << "2 continue" << endl;
  cin >> playerOption;
  switch(playerOption){
    case 1:
      hunt();
    case 2:
    return;
  }
}

void zombieBear(){
  //70% to escape 20% to die and 10% to kill
  int playerOption;
  cout << "You enconter a Zombie bear and you try to run before he spots you " << endl;
  playerOption = rand() % 11 + 1;
  switch(playerOption){
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      cout << "You manage to escape the bear before he spots you" << endl;
      break;
    case 8:
    case 9:
      cout << "You get spotted and the bear dashes for you" << endl;
      cout << "after shooting it a few times the bear manages to maul you " << endl;
      endGame();
      break;
    case 10:
      cout << "You get spotted and the bear dashes for you" << endl;
      cout << "you pull out your knife and manage to get a miracle stab through its eye killing it instantly" << endl;
      break;
}
}

void banditCamp(){
  // sneak by or fight scavangers then search their camp
  int playerOption, banditHp, numberOfBandits, totalHp, damage;
  banditHp = 5;
  numberOfBandits = rand() % 4 + 1;

  cout << "you enconter a bandit camp with " << numberOfBandits << " they each have " << banditHp << "Hp " << endl;
  cout << "1 Fight " << endl;
  cout << "2 Run " << endl;
  cin >> playerOption;

  if(playerOption == 2){
    cout << "You runaway to avoid conflict " << endl;
    return;
  } else{
    cout << "You choose to fight " << endl;
    totalHp = banditHp * numberOfBandits;
    while(totalHp > 0){
      damage  = 0;
      damage = bulletDamage();
      int playerHit = rand() % 3 + 1;
      int banditHit = rand() % 5 + 1;
      if(ammo == 0){
        runOutOfAmmo();
      } else {
        //Players turn
        switch (playerHit){
          case 1:
            totalHp = totalHp - damage;
            ammo = ammo - 1;
            cout << "You hit one of the bandits " << endl;
            cout << "Bandits total Hp = " << totalHp << endl;
            cout << "Ammo = " << ammo << endl << endl;
            break;
          case 2:
            ammo = ammo - 1;
            cout << "You missed " << endl;
            cout << "Ammo = " << ammo << endl << endl;
            break;
        }
        //Scavangers turn
        switch (banditHit){
          case 1:
            cout << "Bandit hits " << endl;
            playHealth = playHealth - 1;
            checkPlayerHp();
            cout << "New health = " << playHealth << endl << endl;
            break;
          case 2:
          case 3:
          case 4:
            cout << "Bandit misses " << endl << endl;
            break;
        }
        if(totalHp == 0){
          cout << "Bandits are  dead " << endl;
          return;
        }
      }
    }
  }
}

void crashedHeli(){
  //zombies gurding a heli crash with loot
}

void fishing(){
  for(i = 0; i < 5; i++){
    int fishChance = rand() % 10 + 1;
    switch(fishChance){
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        cout << "Nothing caught " << endl;
      break;
      case 6:
      case 7:
        cout << "Cod caught " << endl;
        meat = meat + 1;
      break;
      case 8:
        cout << "Salmon caught " << endl;
        meat = meat + 3;
      break;
      case 9:
        cout << "Trout caught " << endl;
        meat = meat + 5;
      break;
    }
  }

}

void wolfPack(){
  //40% to escape 20% to die and 40% to kill
  int playerOption;
  cout << "You enconter a Pack of wolves and you try to run before he spots you " << endl;
  playerOption = rand() % 11 + 1;
  switch(playerOption){
    case 1:
    case 2:
    case 3:
    case 4:
      cout << "You manage to escape the pack before they spot you" << endl;
      break;
    case 5:
    case 6:
      cout << "You get spotted and the pack and attempt to fight them" << endl;
      cout << "after killing a couple the pack overwhelms you " << endl;
      endGame();
      break;
    case 7:
    case 8:
    case 9:
    case 10:
      if(ammo > 5){
        cout << "You get spotted and the pack and shoot them" << endl;
        cout << "you mangage to kill a couple pack before they reach you" << endl;
        endGame();
      } else{
        cout << "after killing a couple of the pack but you run out of ammo  and the wolves overwhelms you " << endl;
      }
      break;
}
}

int bulletDamage(){
  //player can hit 1 through to 3
  int damageChance, damage;
  damage = 0;
  damageChance = rand () % 10 + 1;
  switch(damageChance){
    case 1:
    case 2:
    case 3:
    case 4:
      damage = 1;
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      damage = 2;
      break;
    case 9:
    case 10:
      damage = 3;
      break;
}
return damage;
}

void runOutOfAmmo(){
  cout << "You run out of Ammo this looks like the end " <<endl;
  cout << "GAME OVER " << endl;
}

void endGame(){
  int noPromt;
  cout << "Game over " << endl;
  cin >> noPromt;
}

void checkPlayerHp(){
  if(playHealth <= 0){
    endGame();
  } else {
    return;
  }
}

void checkHunger(){
  if(hunger <= 0){
    playHealth = playHealth - 1;
  }
}
