#ifndef ITILESTATE_H
#define ITILESTATE_H

#include <memory>

class Tile;
class ITileBehavior;

/**
 * @class ITileState
 * @brief Interface for tile states.
 */
class ITileState {
public:
    virtual ~ITileState() = default;
    virtual std::unique_ptr<ITileState> clone() const = 0;
    virtual void updateTile(Tile& t) = 0;
    virtual char getColor() const = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void forceBlue(Tile& t) = 0;
};

/**
 * @class TileStateYellow
 * @brief Concrete implementation of ITileState for the yellow state.
 */
class TileStateYellow : public ITileState {
public:
    TileStateYellow(std::unique_ptr<ITileBehavior> aBehavior);
    TileStateYellow(const TileStateYellow& other);
    TileStateYellow& operator=(const TileStateYellow& other);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior; ///< Behavior associated with the tile state.
    int mCounter; ///< Counter for tracking state-specific actions.
    static const int requiredActions = 2; ///< Number of required actions to change state.
};

/**
 * @class TileStateWhite
 * @brief Concrete implementation of ITileState for the white state.
 */
class TileStateWhite : public ITileState {
public:
    TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior);
    TileStateWhite(const TileStateWhite& other);
    TileStateWhite& operator=(const TileStateWhite& other);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior; ///< Behavior associated with the tile state.
};

/**
 * @class TileStateRed
 * @brief Concrete implementation of ITileState for the red state.
 */
class TileStateRed : public ITileState {
public:
    TileStateRed(std::unique_ptr<ITileBehavior> aBehavior);
    TileStateRed(const TileStateRed& other);
    TileStateRed& operator=(const TileStateRed& other);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior; ///< Behavior associated with the tile state.
};

/**
 * @class TileStateGray
 * @brief Concrete implementation of ITileState for the gray state.
 */
class TileStateGray : public ITileState {
public:
    TileStateGray(std::unique_ptr<ITileBehavior> aBehavior);
    TileStateGray(const TileStateGray& other);
    TileStateGray& operator=(const TileStateGray& other);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior; ///< Behavior associated with the tile state.
    int mCounter; ///< Counter for tracking state-specific actions.
    static const int requiredActions = 2; ///< Number of required actions to change state.
};

/**
 * @class TileStateBlue
 * @brief Concrete implementation of ITileState for the blue state.
 */
class TileStateBlue : public ITileState {
public:
    TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior);
    TileStateBlue(const TileStateBlue& other);
    TileStateBlue& operator=(const TileStateBlue& other);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior; ///< Behavior associated with the tile state.
    int mCounter; ///< Counter for tracking state-specific actions.
    static const int requiredActions = 3; ///< Number of required actions to change state.
};

#endif // ITILESTATE_H