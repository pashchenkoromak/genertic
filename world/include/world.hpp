#include <memory>
#include <vector>
#include "actor.hpp"

/// @struct actorInWorld
/// @brief includes actor and his position
struct actorInWorld
{
    /// @brief default constructor
    actorInWorld() = default;

    /// @brief constructor with data
    actorInWorld(std::shared_ptr<Actor> _actor, const std::pair<size_t, size_t>& _pos) : actor(_actor), pos(_pos) {}

    /// @brief used for ugly actor.actor usage.
    Actor operator*() const { return *actor; }
    std::shared_ptr<Actor> operator->() const { return actor; }

    /// @brief actor
    std::shared_ptr<Actor> actor;

    /// @brief position
    std::pair<size_t, size_t> pos;
};

/// @class World
/// @brief it includes actors and can wrap their moves.
class World
{
public:
    /// @brief Constructor. It creates a world, and fill it due to FULLNESS with
    /// actors.
    /// @note It also fill earthEnergy.
    World();

    /// @brief Default destructor
    ~World() = default;

    /// @brief Get next state of the world.
    void getNextMove();

    /// @brief Get number of Alives actor in the world
    size_t getNumberOfAlives();

    /// @brief show the world to the std::cout
    void show() const;

private:
    /// @brief some statistic info about actor moves
    /// @{
    size_t attacks = 0;
    size_t tills = 0;
    /// @}

    /// @brief Energy, that you can take when bite anyone.
    const size_t BITE = 40;

    /// @brief Probability for children to mutate
    const double MUTATION_PROBABILITY = 0.5;

    /// @brief Fullness of world in the start.
    const double FULLNESS = 0.3333;

    /// @brief Default energy of any corpse.
    const long long CORPSE_ENERGY = 100;

    /// @brief Some position, that means "HERE IS NO POSITION!".
    const std::pair<size_t, size_t> NULL_POS = std::make_pair(SIZE_MAX, SIZE_MAX);

    /// @brief Earth energy matrix. Used for tilling.
    std::vector<std::vector<long long>> m_earthEnergy;

    /// @brief Actors matrix
    std::vector<std::vector<actorInWorld>> m_vecActors;

    /// @brief Handles operation by actor
    void handleOperation(const Operation& operation, actorInWorld& actor);

    /// @brief Get new position, which is pos + direction.
    /// @param[in] pos - current position.
    /// @param[in] direction - shift direction as string (LEFT, RIGHT, etc).
    /// @return New position.
    std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos, const std::string& direction);
    /// @brief Get new position, which is pos + direction
    /// @param[in] pos - current position
    /// @param[in] direction - shift direction as pair<int, int>
    /// @return New position
    std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos, const std::pair<int, int>& direction);
    /// @brief Add energy to the actor, due to his position
    /// @param[in] actor - doer
    void photosynthesis(actorInWorld& actor);

    /// @brief finds an empty place near the actor
    std::pair<size_t, size_t> findPlace(const std::pair<size_t, size_t>& pos);

    /// @brief move actor to the direction
    /// @param[in] actor - doer
    /// @param[in] direction - where to move
    void go(actorInWorld& actor, const std::string& direction);

    /// @brief attack in direction
    /// @param[in] actor - doer
    /// @param[in] direction - where to attack
    /// @note if there is nothing - nothing will happened
    void attack(actorInWorld& actor, const std::string& direction);

    /// @brief clean a corpse to the earth.
    /// @param[in] actor - actor to clean
    void clean(actorInWorld& actor);

    /// @brief see to the direction
    /// @param[in] actor - doer
    /// @param[in] direction - where to move
    /// @result actor will have an answer by the world
    void see(actorInWorld& actor, const std::string& direction);

    /// @brief actor doesnt want to do anything
    /// @param[in] actor - some lazy actor
    void wait(actorInWorld& actor);

    /// @brief create a corpse from a actor
    /// @param[in] actor - actor, who will die
    void kill(actorInWorld& actor);

    /// @brief till ground under the actor to get energy.
    /// @param[in] actor - tiller
    void till(actorInWorld& actor);

    /// @brief creates children where it's possible around the actor
    /// @param[in] actor - parent
    void makeChild(actorInWorld& actor);

    /// @brief check, if there is no actors, and it's possible to go there
    /// @param[in] newPos - position for check
    bool canGo(const std::pair<size_t, size_t>& newPos);

    /// @brief check, if there is a actor or a corpse to attack
    /// @param[in] newPos - position for check
    bool canAttack(const std::pair<size_t, size_t>& newPos);
};
