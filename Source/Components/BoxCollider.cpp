#pragma once

#include "pch.h";
#include "Source/Managers/GameObjectManager.h";
#include "BoxCollider.h";

BoxCollider::BoxCollider()
{
	resourceManager = GameObjectManager::GetInstance();
}

BoxCollider::BoxCollider(GameObject& inp_parentObj, std::vector<DirectX::SimpleMath::Vector2>& inp_vertices, bool inp_isMovable)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	localVertices = inp_vertices;
	worldVertices = inp_vertices;
	isMovable = inp_isMovable;

	std::string parentName = parentObj->GetName() + " - ColliderLine ";

	for (int i = 0; i < inp_vertices.size(); ++i)
	{
		std::string colliderName = parentName + std::to_string(i);

		vertexLines.emplace_back(Line(colliderName, Colors::DeepPink, inp_parentObj, inp_vertices[i], inp_vertices[(i + 1) % inp_vertices.size()], 1.0f));
	}
}

void BoxCollider::Update(float deltaTime)
{
	SetWorldPositions();
}

DirectX::SimpleMath::Vector2 BoxCollider::GetEdgeNormal(const DirectX::SimpleMath::Vector2& v1, const DirectX::SimpleMath::Vector2& v2) const
{
	const DirectX::SimpleMath::Vector2 edge = { v2.x - v1.x, v2.y - v2.y };
	float length = std::sqrt(edge.x * edge.x + edge.y * edge.y);			// Calculating the magnitude.
	return { edge.y / length, -edge.x / length };
}

bool BoxCollider::IsColliding_SAT(BoxCollider &other)
{
	BoxCollider* poly1 = this;
	BoxCollider* poly2 = &other;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &other;
			poly2 = this;
		}

		for (int a = 0; a < poly1->worldVertices.size(); a++)
		{
			int b = (a + 1) % poly1->worldVertices.size();
			DirectX::SimpleMath::Vector2 axisProj = { -(poly1->worldVertices[b].y - poly1->worldVertices[a].y), poly1->worldVertices[b].x - poly1->worldVertices[a].x }; // Normal projection.

			// Get min and max projections from the normal projection for the first shape.
			float min_r1 = INFINITY, max_r1 = -INFINITY;
			for (int p = 0; p < poly1->worldVertices.size(); p++)
			{
				float q = (poly1->worldVertices[p].x * axisProj.x + poly1->worldVertices[p].y * axisProj.y);
				min_r1 = std::min(min_r1, q);
				max_r1 = std::max(max_r1, q);
			}

			// Do the same for shape 2.
			float min_r2 = INFINITY, max_r2 = -INFINITY;
			for (int p = 0; p < poly2->worldVertices.size(); p++)
			{
				float q = (poly2->worldVertices[p].x * axisProj.x + poly2->worldVertices[p].y * axisProj.y);
				min_r2 = std::min(min_r2, q);
				max_r2 = std::max(max_r2, q);
			}

			// Check if "shadows" overlap on the normal projection.
			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
			{
				return false;
			}
		}
	}
	return true;
}

bool BoxCollider::IsColliding_DIAG(BoxCollider& other)
{
	BoxCollider* poly1 = this;
	BoxCollider* poly2 = &other;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &other;
			poly2 = this;
		}

		// Check diagonals of polygon.
		for (int p = 0; p < poly1->worldVertices.size(); p++)
		{
			DirectX::SimpleMath::Vector2 line_r1s = poly1->GetParent()->GetPosition();
			DirectX::SimpleMath::Vector2 line_r1e = poly1->worldVertices[p];

			// against the other polygon's edges.
			for (int q = 0; q < poly2->worldVertices.size(); q++)
			{
				DirectX::SimpleMath::Vector2 line_r2s = poly2->worldVertices[q];
				DirectX::SimpleMath::Vector2 line_r2e = poly2->worldVertices[(q + 1) % poly2->worldVertices.size()];	// neighboring point.

				// Standdard "off the shelf" line segment intersection.
				float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
				float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
				float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool BoxCollider::IsColliding_DIAG_STATIC(BoxCollider& other)
{
	BoxCollider* poly1 = this;
	BoxCollider* poly2 = &other;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &other;
			poly2 = this;
		}

		// Check diagonals of polygon.
		for (int p = 0; p < poly1->worldVertices.size(); p++)
		{
			DirectX::SimpleMath::Vector2 line_r1s = poly1->GetParent()->GetPosition();
			DirectX::SimpleMath::Vector2 line_r1e = poly1->worldVertices[p];

			DirectX::SimpleMath::Vector2 displacement = { 0, 0 };

			// against the other polygon's edges.
			for (int q = 0; q < poly2->worldVertices.size(); q++)
			{
				DirectX::SimpleMath::Vector2 line_r2s = poly2->worldVertices[q];
				DirectX::SimpleMath::Vector2 line_r2e = poly2->worldVertices[(q + 1) % poly2->worldVertices.size()];	// neighboring point.

				// Standard "off the shelf" line segment intersection.
				float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
				float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
				float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					displacement.x += (1.0f - t1) * (line_r1e.x - line_r1s.x);
					displacement.y += (1.0f - t1) * (line_r1e.y - line_r1s.y);
				}
			}
			
			if (isMovable && (displacement.x > .4 || displacement.y > .4))
			{
				DirectX::SimpleMath::Vector2 parentPos = this->GetParent()->GetPosition();

				parentPos.x += displacement.x * (shape == 0 ? -1 : +1);
				parentPos.y += displacement.y * (shape == 0 ? -1 : +1);

				this->parentObj->SetPosition(parentPos);
			}
		}
	}
	return false;
}

bool BoxCollider::CanCollide()
{
	return canCollide;
}

std::shared_ptr<GameObject> BoxCollider::GetParent() const
{
	return parentObj;
}

std::vector<DirectX::SimpleMath::Vector2> BoxCollider::GetWorldPositions()
{
	return worldVertices;
}

void BoxCollider::SetWorldPositions()
{
	DirectX::SimpleMath::Vector2 parentPosition = parentObj->GetPosition();

	for (int i = 0; i < worldVertices.size(); i++)
	{
		worldVertices[i] = {localVertices[i].x + parentPosition.x, localVertices[i].y + parentPosition.y};
	}
}