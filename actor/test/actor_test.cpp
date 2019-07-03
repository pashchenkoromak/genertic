#include "actor.hpp"
#include "common/common.hpp"
#include "gtest/gtest.h"

TEST(ActorTest, default_energy_constructor)
{
    Actor a1;
    EXPECT_EQ(a1.getEnergy(), Actor::START_ENERGY);
}
TEST(ActorTest, custom_energy_constructor)
{
    const int energy = 1;
    Actor a2(energy);
    EXPECT_EQ(a2.getEnergy(), energy);
}
TEST(ActorTest, copy_constructor)
{
    int energy = 10;
    Actor a1(energy);
    EXPECT_NO_THROW(Actor(a1));
    Actor a2(a1);
    EXPECT_EQ(a2.getEnergy(), a1.getEnergy());
    EXPECT_EQ(a2.getEnergy(), energy);
    EXPECT_EQ(a2, a1);
}
TEST(ActorTest, move_constructor)
{
    Actor a1;
    EXPECT_NO_THROW(Actor(std::move(a1)));
    int energy = 10;
    Actor a2(energy);
    Actor a3(std::move(a2));
    EXPECT_EQ(a3.getEnergy(), energy);
    EXPECT_NE(a3.getEnergy(), a2.getEnergy());

    Actor a4 = std::move(a3);
    EXPECT_EQ(a4.getEnergy(), energy);
}
TEST(ActorTest, child)
{
    int energy = 10;
    Actor a1(energy);
    Actor a5 = Actor::Child(a1, energy);
    EXPECT_NE(a5, a1);
    EXPECT_EQ(0, a5.getAge());
}

TEST(ActorTest, MetaActors)
{
    EXPECT_NO_THROW(Actor::NO_UNIT());
    EXPECT_NO_THROW(Actor::CORPSE());
}

TEST(ActorTest, Moves)
{
    int energy(100);
    Actor a(energy);
    EXPECT_NO_THROW(a.setAnswer(answer::Empty));
    EXPECT_NO_THROW(a.changeEnergy(-1));
    EXPECT_EQ(a.getEnergy(), energy - 1);
    EXPECT_NO_THROW(a.mutation());
    EXPECT_NO_THROW(a.nextMove());
}