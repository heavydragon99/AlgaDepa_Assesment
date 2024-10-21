#ifndef ITILESTATE_H
#define ITILESTATE_H

#include <memory>

class Tile;
class ITileBehavior;

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

// TileStateYellow
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
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 2;
};

// TileStateWhite
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
    std::unique_ptr<ITileBehavior> mBehavior;
};

// TileStateRed
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
    std::unique_ptr<ITileBehavior> mBehavior;
};

// TileStateGray
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
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 2;
};

// TileStateBlue
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
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 3;
};

#endif // ITILESTATE_H