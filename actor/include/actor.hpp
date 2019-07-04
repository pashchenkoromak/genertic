#include <string>
#include <vector>
#include "genom.hpp"

#ifndef ACTOR_HPP
#define ACTOR_HPP

/// @class Actor
/// @brief includes genom and some additional info, that could be used be World.
class Actor
{
public:
    /// @brief starting energy for every actor by default
    static const long long START_ENERGY = 400;

    /// @brief construct actor with some energy.
    /// @param[in] energy - start energy.
    /// @note Every actor has unique id.
    Actor(const long long energy = START_ENERGY);

    /// @brief Copy actor.
    /// @param[in] rhs - base actor.
    /// @note Be care: you'll have 2 actors with equals id
    Actor(const Actor& rhs) = default;

    /// @brief move constructor
    Actor(Actor&& rhs);

    /// @brief mutation of genom
    /// @result some changes in genom
    virtual void mutation();

    /// @brief get next move of actor
    /// @return Operation to the World
    virtual Operation nextMove();

    /// @brief changes energy for value
    /// @param[in] value - adding to the energy value
    /// @note value can be <0
    void changeEnergy(const long long value);

    /// @brief set answer by the world to the actor
    /// @param[in] rhs - answer be the world.
    void setAnswer(const answer& rhs);

    /// @brief operator =
    /// @param[in] rhs - base actor
    /// @result - the same actor with the same id.
    Actor& operator=(const Actor& rhs) = default;

    /// @brief operators == and !=
    /// @note it checking equality only using id.
    /// @{
    friend bool operator==(const Actor& lhs, const Actor& rhs);
    friend bool operator!=(const Actor& lhs, const Actor& rhs);
    /// @}

    /// @brief Make actor with id = -1
    static Actor NO_UNIT();
    /// @brief Make actor with id = -2
    static Actor CORPSE();

    /// @brief Energy getter
    /// @return current energy of actor
    long long getEnergy() const;

    /// @brief Age getter
    /// @return current actor age
    long long getAge() const;

    /// @brief makes new actor. It`s the same as base actor, but with other energy, id and 0 age.
    /// @param[in] rhs - base actor
    /// @param[in] - start energy
    static Actor Child(const Actor& rhs, const long long energy);

private:
    /// @brief next free id
    static int nextId;

    /// @brief current actor id
    int id;

    /// @brief age of actor
    size_t m_age;

    /// @brief energy of actor
    long long m_energy;

    /// @brief genom
    Genom m_genom;

    /// @brief last answer by world
    answer m_worldAnswer;
};

#endif // UNIT_HPP
