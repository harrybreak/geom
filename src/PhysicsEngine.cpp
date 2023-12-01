#include "PhysicsEngine.hpp"
#include "CollisionSolver.hpp"
#include "Polygon.hpp"
#include "Scene.hpp"

#include <iostream>
#include <stdexcept>


PhysicsEngine::PhysicsEngine(Scene* scene) : m_pCollisionSolver(nullptr), m_pScene(scene)
{

}

void PhysicsEngine::Init(CollisionSolverType collisionSolver)
{
	switch (collisionSolver)
	{
		case CollisionSolverType::SAT:
			m_pCollisionSolver = new SATCollisionSolver();
			break;
		case CollisionSolverType::GJK:
			//TODO: implement;
			std::runtime_error("Not implemented.");
			break;
	}
}

void PhysicsEngine::Shutdown()
{
	delete m_pCollisionSolver;
}

bool PhysicsEngine::CheckForCollision(const Polygon* polygon)
{
    for (size_t i = 0; i < m_pScene->size(); i++)
    {
        Polygon* polygonP = dynamic_cast<Polygon*>(m_pScene->at(i));

        if (polygonP == nullptr || polygonP == polygon)
            continue;

        if (m_pCollisionSolver->IsColliding(polygon, polygonP))
            return true;
    }

    return false;
}

void PhysicsEngine::Update()
{
    for (size_t i = 0; i < m_pScene->size(); i++)
    {
        Polygon* polygonP = dynamic_cast<Polygon*>(m_pScene->at(i));

        if (polygonP == nullptr)
            continue;

        if (CheckForCollision(polygonP))
            polygonP->SetColor({255, 0, 0, 255});
        else
            polygonP->SetColor(polygonP->Color);
    }
}
