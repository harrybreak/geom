#pragma once

#include "Std.hpp"
#include "SATCollisionSolver.hpp"
#include "Scene.hpp"

class PhysicsEngine
{
public:
	enum class CollisionSolverType : uint8
	{
		SAT,
		GJK
	};

private:

	CollisionSolver* m_pCollisionSolver;

	Scene* m_pScene;

public:

	PhysicsEngine(Scene* scene);

	void Init(CollisionSolverType collisionSolver);

	void Shutdown();

	void Update();

	bool CheckForCollision(const Polygon* polygon);
};