#pragma once

#include <algorithm>


class HitstopManager
{
public:

    void Trigger(float duration)
    {
        m_remaining = std::max(m_remaining, duration);
    }

    void Update(float dt)
    {
        m_remaining = std::max(0.0f, m_remaining - dt);
    }

    bool Active() const
    {
        return m_remaining > 0.0f;
    }

private:

    float m_remaining = 0.0f;
};
