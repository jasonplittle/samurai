#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "Player.hpp"

struct InputState
{
    bool left;
    bool right;
    bool down;
};


class Command
{
public:
    virtual ~Command() = default;

    virtual void Execute(Player& entity) = 0;
};

class CommandQueue
{
public:
    void Push(std::unique_ptr<Command> command)
    {
        m_Queue.push(std::move(command));
    }

    bool Empty() const
    {
        return m_Queue.empty();
    }

    std::unique_ptr<Command> Pop()
    {
        auto cmd = std::move(m_Queue.front());
        m_Queue.pop();

        return cmd;
    }

private:
    std::queue<std::unique_ptr<Command>> m_Queue;
};


class JumpCommand : public Command
{
public:
    void Execute(Player& player) override
    {
        player.Jump();
    }
};

class AttackCommand : public Command
{
public:
    void Execute(Player& player) override
    {
        player.Attack();
    }
};


class PlayerController
{
public:
    PlayerController(Player& player) : m_player(player) {};

    void Update(float dt);

    void MoveLeft() { m_inputState.left = true; }
    void MoveRight() { m_inputState.right = true; }
    void MoveDown() { m_inputState.down = true; }
    void Jump() { m_commandQueue.Push(std::make_unique<JumpCommand>()); }
    void Attack() { m_commandQueue.Push(std::make_unique<AttackCommand>()); }


private:
    Player& m_player;

    CommandQueue m_commandQueue;
    InputState m_inputState;
};