//
// Created by Connor Beard on 4/30/20.
//

#ifndef BISTRO_TIMESTEP_H
#define BISTRO_TIMESTEP_H

namespace Bistro {

    class Timestep {
    public:
        Timestep(float time = 0.0f) : m_time(time) {}

        operator float() const { return m_time; }

        float getSeconds() const { return m_time; }
        float getMilliseconds() const { return m_time * 1000.f; }
    private:
        float m_time;
    };
}

#endif //BISTRO_TIMESTEP_H
