#include "world.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

World::World()
{
    int n = 35;
    int m = 65;
    m_vecActors.resize(n);
    m_earthEnergy.resize(n);
    for (int i = 0; i < n; i++) {
        m_vecActors[i].reserve(m);
        m_earthEnergy[i].reserve(m);
        for (int j = 0; j < m; j++) {
            m_earthEnergy[i][j] = rand() % 1000;
            if (rand() % 10000 <= FULLNESS * 10000)
                m_vecActors[i].push_back(actorInWorld(std::make_shared<Actor>(rand() % 1000), std::make_pair(i, j)));
            else
                m_vecActors[i].push_back(actorInWorld(std::make_shared<Actor>(Actor::NO_UNIT()), std::make_pair(i, j)));
        }
    }
}

void World::getNextMove()
{
    for (auto row : m_vecActors)
        for (auto actor : row)
            if (*actor.actor != Actor::NO_UNIT() && *actor.actor != Actor::CORPSE())
                handleOperation(actor.actor->nextMove(), actor);
            else {
                if (*actor.actor == Actor::CORPSE()) actor.actor->changeEnergy(-CORPSE_ENERGY * 2 / 3);
                if (actor.actor->getEnergy() <= 0) clean(actor);
            }
}

void World::handleOperation(const Operation& operation, actorInWorld& actor)
{
    actor.actor->changeEnergy(-actor.actor->getAge() / 80);
    switch (operation.type) {
        case GO:
            go(actor, operation.params[0]);
            break;
        case SEE:
            see(actor, operation.params[0]);
            break;
        case WAIT:
            wait(actor);
            break;
        case DIE:
            kill(actor);
            break;
        case MAKE_CHILD:
            makeChild(actor);
            break;
        case PHOTOSYNTESIS:
            photosynthesis(actor);
            break;
        case TILL:
            till(actor);
            break;
        case ATTACK:
            attack(actor, operation.params[0]);
            break;
        default:
            wait(actor);
    }
}
void World::go(actorInWorld& actor, const std::string& direction)
{
    auto newPos = getNewPos(actor.pos, direction);
    if (canGo(newPos)) {
        std::swap(m_vecActors[newPos.first][newPos.second], m_vecActors[actor.pos.first][actor.pos.second]);
        actor.pos = newPos;
    }
}

void World::attack(actorInWorld& actor, const std::string& direction)
{
    attacks++;
    auto newPos = getNewPos(actor.pos, direction);
    if (canAttack(newPos)) {
        size_t x = newPos.first, y = newPos.second;
        if (*m_vecActors[x][y].actor == Actor::CORPSE()) {
            actor.actor->changeEnergy(m_vecActors[x][y].actor->getEnergy() * 2);
            clean(m_vecActors[x][y]);
        } else {
            actor.actor->changeEnergy(BITE * 2);
            m_vecActors[x][y].actor->changeEnergy(-BITE);
            if (m_vecActors[x][y].actor->getEnergy() <= 0) clean(m_vecActors[x][y]);
        }
    }
}

void World::clean(actorInWorld& actor)
{
    m_earthEnergy[actor.pos.first][actor.pos.second] += actor.actor->getEnergy();
    *actor.actor = Actor::NO_UNIT();
}

void World::see(actorInWorld& actor, const std::string& direction)
{
    auto newPos = getNewPos(actor.pos, direction);
    if (*(actor.actor) == Actor::NO_UNIT())
        actor.actor->setAnswer(answer::Empty);
    else
        actor.actor->setAnswer(answer::ActorIsHere);
}

void World::wait(actorInWorld& actor) { actor.actor->changeEnergy(-1); }

void World::kill(actorInWorld& actor)
{
    long long energy = actor.actor->getEnergy();
    *actor.actor = Actor::CORPSE();
    actor.actor->changeEnergy(energy + CORPSE_ENERGY);
}

void World::till(actorInWorld& actor)
{
    tills++;
    actor.actor->changeEnergy(m_earthEnergy[actor.pos.first][actor.pos.second] / 30);
    m_earthEnergy[actor.pos.first][actor.pos.second] -= (m_earthEnergy[actor.pos.first][actor.pos.second] / 30);
}

void World::makeChild(actorInWorld& actor)
{
    for (size_t i = 0; i < 9; i++) {
        auto newPos = findPlace(actor.pos);
        if (newPos == NULL_POS) return;
        long long energyPerChild = actor.actor->getEnergy() / 9;
        actor.actor->changeEnergy(-energyPerChild);
        m_vecActors[newPos.first][newPos.second] =
            actorInWorld(std::make_shared<Actor>(actor.actor->Child(*actor.actor, energyPerChild)), newPos);
        if (rand() % 10000 < MUTATION_PROBABILITY * 10000) m_vecActors[newPos.first][newPos.second].actor->mutation();
    }
}
bool World::canGo(const std::pair<size_t, size_t>& newPos)
{
    if (newPos.first >= m_vecActors.size() || newPos.second >= m_vecActors[0].size()) return false;
    return (*m_vecActors[newPos.first][newPos.second].actor == Actor::NO_UNIT());
}

bool World::canAttack(const std::pair<size_t, size_t>& newPos)
{
    if (newPos.first >= m_vecActors.size() || newPos.second >= m_vecActors[0].size()) return false;
    return !(*m_vecActors[newPos.first][newPos.second].actor == Actor::NO_UNIT());
}

void World::photosynthesis(actorInWorld& actor) { actor.actor->changeEnergy(actor.pos.first / 10); }

std::pair<size_t, size_t> World::getNewPos(const std::pair<size_t, size_t>& pos, const std::string& direction)
{
    std::pair<size_t, size_t> newPos = pos;
    if (direction == directionToString(directions::LEFT)) newPos.second--;
    if (direction == directionToString(directions::RIGHT)) newPos.second++;
    if (direction == directionToString(directions::UP)) newPos.first--;
    if (direction == directionToString(directions::DOWN)) newPos.first++;
    if (direction == directionToString(directions::UP_LEFT)) {
        newPos.first--;
        newPos.second--;
    }
    if (direction == directionToString(directions::UP_RIGHT)) {
        newPos.first--;
        newPos.second++;
    }
    if (direction == directionToString(directions::DOWN_LEFT)) {
        newPos.first++;
        newPos.second--;
    }
    if (direction == directionToString(directions::DOWN_RIGHT)) {
        newPos.first++;
        newPos.second++;
    }
    newPos.first = (newPos.first + m_vecActors.size()) % m_vecActors.size();
    newPos.second = (newPos.first + m_vecActors[0].size()) % m_vecActors[0].size();
}

std::pair<size_t, size_t> World::getNewPos(const std::pair<size_t, size_t>& pos, const std::pair<int, int>& direction)
{
    std::pair<size_t, size_t> newPos;
    newPos.first = (pos.first + direction.first + m_vecActors.size()) % m_vecActors.size();
    newPos.second = (pos.second + direction.second + m_vecActors[0].size()) % m_vecActors[0].size();
    return newPos;
}

std::pair<size_t, size_t> World::findPlace(const std::pair<size_t, size_t>& pos)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (canGo(getNewPos(pos, std::make_pair(i, j)))) return getNewPos(pos, std::make_pair(i, j));
    return NULL_POS;
}

size_t World::getNumberOfAlives()
{
    size_t result = 0;
    for (auto row : m_vecActors)
        for (auto actor : row) {
            if (*actor.actor != Actor::NO_UNIT()) result++;
        }
    return result;
}

void World::show() const
{
    long long sumEnergy = 0;
    long long averageAge = 0;
    long long count = 0;
    for (auto row : m_vecActors) {
        for (auto actor : row) {
            if (*actor.actor == Actor::NO_UNIT())
                std::cout << " .";
            else if (*actor.actor == Actor::CORPSE()) {
                std::cout << " x";
            } else {
                std::cout << " O";
                sumEnergy += actor.actor->getEnergy();
                averageAge += actor.actor->getAge();
                count++;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Summary energy for world: " << sumEnergy << std::endl;
    std::cout << "Average age: " << (averageAge + .0) / count << std::endl;
    std::cout << "Tills: " << tills << "\tAttacks: " << attacks << std::endl;
}
