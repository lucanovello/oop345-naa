#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"

namespace seneca
{
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth>
    {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon;

    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon);

        int getAttackAmnt() const override;
        int getDefenseAmnt() const override;
        Character* clone() const override;
        void attack(Character* enemy) override;
        void takeDamage(int dmg) override;
    };

    template <typename Weapon_t>
    Archer<Weapon_t>::Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
        : CharacterTpl<SuperHealth>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_weapon(weapon) {}

    template <typename Weapon_t>
    int Archer<Weapon_t>::getAttackAmnt() const
    {
        return static_cast<int>(1.3 * m_baseAttack);
    }

    template <typename Weapon_t>
    int Archer<Weapon_t>::getDefenseAmnt() const
    {
        return static_cast<int>(1.2 * m_baseDefense);
    }

    template <typename Weapon_t>
    Character* Archer<Weapon_t>::clone() const
    {
        return new Archer<Weapon_t>(*this);
    }

    template <typename Weapon_t>
    void Archer<Weapon_t>::attack(Character* enemy)
    {
        std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
        int damage = getAttackAmnt();
        std::cout << "    Archer deals " << damage << " ranged damage!\n";
        enemy->takeDamage(damage);
    }

    template <typename Weapon_t>
    void Archer<Weapon_t>::takeDamage(int dmg)
    {
        std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
        std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";
        dmg -= getDefenseAmnt();
        if (dmg < 0) dmg = 0;
        CharacterTpl<SuperHealth>::takeDamage(dmg);
    }

} // namespace seneca

#endif
