#pragma once

#include "../IndexedTriangleList.h"
#include "../Math.h"

#include <DirectXMath.h>

class Cone
{
public:
	template<class V>
	static IndexedTriangleList<V> MakeTesselated(int longDiv)
	{
		assert(longDiv >= 3);

		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		// Base vertices
		std::vector<V> vertices;
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto vector = DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationZ(longitudeAngle * i));
			DirectX::XMStoreFloat3(&vertices.back().pos, vector);
		}

		// Center
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, 1.0f };
		const unsigned short center = (unsigned short)(vertices.size() - 1);

		// Tip :darkness:
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, -1.0f };
		const unsigned short tip = (unsigned short)(vertices.size() - 1);

		// Base indices
		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < longDiv; i++)
		{
			indices.push_back(center);
			indices.push_back((i + 1) % longDiv);
			indices.push_back(i);
		}

		// Cone indices
		for (unsigned short i = 0; i < longDiv; i++)
		{
			indices.push_back(tip);
			indices.push_back((i + 1) % longDiv);
			indices.push_back(i);
		}

		return { std::move(vertices), std::move(indices) };
	}
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		return MakeTesselated<V>(24);
	}
};