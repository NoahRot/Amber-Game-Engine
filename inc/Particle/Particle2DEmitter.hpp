#pragma once

#include "Particle/Particle2D.hpp"

namespace AMB {

class Emitter2D {
public:
	Emitter2D(int32_t time_between_emission, void (*spawn)(mat::Vec2f&, mat::Vec2f&, mat::Vec4f&, mat::Vec2f&, float&) = nullptr,
		void (*update)(Particle2DContext&, float) = nullptr,
		uint32_t preallocate = 32);

	void activate();

	void deactivate();

	bool is_active() const;

	void update(float dt);

	void spawn_particles(uint32_t nbr_particles);

	uint32_t get_particle_count() const;

	const std::vector<Particle2DVertex>& get_particles() const;

private:
	void spawn(float dt);

	void kill_particle(uint32_t id);

	void capacity_check();

	Particle2DStorage m_storage;
	int32_t m_time_since_last_emit;
	int32_t m_time_between_emission;
	uint32_t m_particle_count;
	bool m_active;

	std::vector<Particle2DVertex> m_vertex;
	
	void (*m_spawn)(mat::Vec2f&, mat::Vec2f&, mat::Vec4f&, mat::Vec2f&, float&);
	void (*m_update)(Particle2DContext&, float);
};

}