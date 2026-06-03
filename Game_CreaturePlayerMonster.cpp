#include <iostream>
#include <string>
#include <array>
#include <random>

//-----------------------------------------------------------------------------
class Creature
{
protected:
   std::string m_name;
   char m_symbol{};
   int m_health{};
   int m_damage{};
   int m_gold{};

public:
   Creature(const std::string& name, const char& symbol, const int& health, const int& damage, const int& gold)
      : m_name{name}, m_symbol{symbol}, m_health{health}, m_damage{damage}, m_gold{gold}
   { }

   const std::string& getName() const { return m_name; }
   char getSymbol() const { return m_symbol; }
   int getHealth() const { return m_health; }
   int getDamage() const { return m_damage; }
   int getGold() const { return m_gold; }

   void reduceHealth(int value) { if(m_health > 0) m_health -= value; }
   bool isDead() const { return m_health <= 0; }
   void addGold(int value){ m_gold += value; }
   void changeHealth(int value){m_health += value;}
   void changeDamage(int value){m_damage += value;}
};
//-----------------------------------------------------------------------------
class Player : public Creature
{
private:
   int m_level{ 1 };
public:
   Player(const std::string& name, const char& symbol = '@', const int& health = 10,
      const int& damage = 1, const int& gold = 0, const int& level = 1)
      : Creature(name, '@', 10, 1, 0)
      , m_level{level}
   { }

   int getLevel() const { return m_level; }
   void levelUp() { m_damage += 1; m_level += 1; }
   bool hasWon() const { return m_level >= 20; }
};
//-----------------------------------------------------------------------------
class Monster : public Creature
{
public:
   enum Type
   {
      dragon,
      orc, 
      slime,

      max_types,
   };
private:
    inline static Creature monsterData[]{ 
      Creature{"dragon", 'D', 20, 4, 100},
      Creature{"orc", 'o', 4, 2, 25},
      Creature{"slime", 's', 1, 1, 10}
   };

    static_assert(std::size(monsterData) == max_types);

public:
   Monster(const Monster::Type& type)
      : Creature{monsterData[type]}
   { }

   static Monster::Type getRandomMonster()
   {
      {
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<int> dist(0, Monster::Type::max_types-1);

         return static_cast<Monster::Type>(dist(gen));
      }
   }
};
//-----------------------------------------------------------------------------
enum class Potion
{
   Health,
   Strength,
   Poison,

   Max_Potion,
};
//-----------------------------------------------------------------------------
std::string setName()
{
   std::string name{};
   std::cout << "Enter your name: ";
   std::cin >> name;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   return name;
}
//-----------------------------------------------------------------------------
char setChooseRunFight()
{
   char choose{};
   while(true)
   {
      std::cout << "(R)un or (F)ight: ";
      std::cin >> choose;
      if (!std::cin)
      {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (choose == 'f' || choose == 'F' ||
         choose == 'r' || choose == 'R')
         return choose;
   }
}
//-----------------------------------------------------------------------------
char setChooseDrink()
{
   char choose{};
   while(true)
   {
      std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
      std::cin >> choose;
      if (!std::cin)
      {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (choose == 'y' || choose == 'Y' ||
         choose == 'n' || choose == 'N')
         return choose;
   }
}
//-----------------------------------------------------------------------------
bool Random(int min, int max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> dist(min, max);

   return static_cast<bool>(dist(gen));
}
//-----------------------------------------------------------------------------
void foundPotion(Player& player)
{
   char Choose{setChooseDrink()};
   if (Choose == 'n' || Choose == 'N')
      return;
   switch (static_cast<Potion>(Random(0, static_cast<int>(Potion::Max_Potion) - 1)))
   {
   case(Potion::Health): 
      std::cout << "You drank a potion of Health\n";
      player.changeHealth(Random(1, 5));break;
   case(Potion::Strength): 
      std::cout << "You drank a potion of Strength\n";
      player.changeDamage(1);break;
   case(Potion::Poison): 
      std::cout << "You drank a potion of Poison\n";
      player.changeHealth(-1);break;
   default:
      break;
   }
}
//-----------------------------------------------------------------------------
void attackMonster(Player& player, Monster& monster)
{
   std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() <<" damage.\n";
   player.reduceHealth(monster.getDamage());
}
//-----------------------------------------------------------------------------
void attackPlayer(Player& player, Monster& monster)
{
   std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
   monster.reduceHealth(player.getDamage());
   if (monster.isDead())
   {
      player.levelUp();
      player.addGold(monster.getGold());
      std::cout << "You killed the " << monster.getName() << ".\n";
      std::cout << "You are now level " << player.getLevel() << ".\n";
      std::cout << "You found " << monster.getGold() << " gold.\n";
      foundPotion(player);
   }
}
//-----------------------------------------------------------------------------
void fightMonster(Player& player)
{
   Monster monster{Monster::getRandomMonster()};   
   std::cout << "You have encountered a " << monster.getName() << "(" << monster.getSymbol() << ").\n";
   while (!player.isDead())
   {
      char Choose{setChooseRunFight()};
      if (Choose == 'r' || Choose == 'R')
      {
         if (Random(0,1))
         {
            std::cout << "You successfully fled.\n";
            return;
         }
         else
         {
            std::cout << "You failed to flee.\n";
            attackMonster(player, monster);
         }
      }
      else 
      {
         attackPlayer(player, monster);
         if (monster.isDead())
            return;
         else
            attackMonster(player, monster);
      }
   }
}
//-----------------------------------------------------------------------------
int main()
{
   Player player{setName()};
   std::cout << "Welcome, " << player.getName() << "\n";

   while (!player.isDead() && !player.hasWon())
      fightMonster(player);
      
   if (player.isDead())
      std::cout << "You died at level " << player.getLevel() << " and with 35 gold.\n"
      << "Too bad you can’t take it with you!\n";
   else if(player.hasWon())
      std::cout << "You win! You have 35 gold.\n"
      << "Too bad you can't take it with you!\n";

   return 0;
}
//-----------------------------------------------------------------------------
