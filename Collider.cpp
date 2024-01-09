#pragma once

#include "pch.h";
#include "Collider.h";

Collider::Collider()
{
}

DirectX::SimpleMath::Vector2 Collider::GetEdgeNormal(const DirectX::SimpleMath::Vector2& v1, const DirectX::SimpleMath::Vector2& v2)
{
	const DirectX::SimpleMath::Vector2 edge = { v2.x - v1.x, v2.y - v2.y };
	float length = std::sqrt(edge.x * edge.x + edge.y * edge.y);			// Calculating the magnitude.
	return { edge.y / length, -edge.x / length };
}

bool Collider::OverlapOnAxis(const Collider& coll2, const DirectX::SimpleMath::Vector2& axis)
{
	// Project polygons onto axis (normal).
	float projection1 = axis.Dot(vertices[0]);
	float projection2 = axis.Dot(coll2.vertices[0]);

	// Project the other vertices.
	for (const auto& vertex : vertices)
	{
		float dot = axis.Dot(vertex);
		projection1 = std::min(projection1, dot);
	}

	// Project the other vertices from shape 2.
	for (const auto& vertex : coll2.vertices)
	{
		float dot = axis.Dot(vertex);
		projection2 = std::min(projection2, dot);
	}

	// After finding the smallest projection from both rigidbodies, check if we get a collision (overlap on the normal). 
	return projection1 > projection2 || projection2 > projection1;
}

bool Collider::isColliding(Collider& coll2)
{
	// Check overlap 
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		// Wrap around so we never reach overflow.
		size_t nextIndex = (i + 1) % vertices.size();
		DirectX::SimpleMath::Vector2 edgeNormal = GetEdgeNormal(vertices[i], vertices[nextIndex]);

		if (!OverlapOnAxis(coll2, edgeNormal))
		{
			// No collision.
			return false;
		}
	}

	for (size_t i = 0; i < coll2.vertices.size(); ++i)
	{
		// Wrap around so we never reach overflow.
		size_t nextIndex = (i + 1) % coll2.vertices.size();
		DirectX::SimpleMath::Vector2 edgeNormal = coll2.GetEdgeNormal(coll2.vertices[i], coll2.vertices[nextIndex]);

		if (!coll2.OverlapOnAxis(*this, edgeNormal))
		{
			// No collision.
			return false;
		}
	}

	return true;
}

bool Collider::CanCollide()
{
	return canCollide;
}