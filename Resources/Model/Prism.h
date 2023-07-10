#pragma once

#include "../IndexedTriangleList.h"
#include "../Math.h"

#include <DirectXMath.h>

class Prism
{
public:
	template<class V>
	static IndexedTriangleList<V> MakeTesselated(int longDiv)
	{
		assert(longDive >= 3);
		
		const DirectX::XMVECTOR base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const DirectX::XMVECTOR offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		// Near center
		std::vector<V> vertices;
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, -1.0f };
		const unsigned short centerNear = (unsigned short)(vertices.size() - 1);

		// Far center
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, 1.0f };
		const unsigned short centerFar = (unsigned short)(vertices.size() - 1);

		// Base vertices
		for (int i = 0; i < longDiv; i++)
		{
			// Near base
			vertices.emplace_back();
			DirectX::XMVECTOR v = DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationZ(longitudeAngle * i));
			DirectX::XMStoreFloat3(&vertices.back().pos, v);

			// Far base
			vertices.emplace_back();
			DirectX::XMVECTOR vOf = DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationZ(longitudeAngle * i));
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
		}

		// Side indices
		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < longDiv; i++)
		{
			const unsigned short sideI = i * 2;
			const unsigned short mod = longDiv * 2;
			indices.push_back(i + 2);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back(i + 1 + 2);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back((i + 3) % mod + 2);
			indices.push_back(i + 1 + 2);
		}

		// Base indices
		for (unsigned short i = 0; i < longDiv; i++)
		{
			const unsigned short baseI = i * 2;
			const unsigned short mod = longDiv * 2;
			indices.push_back(i + 2);
			indices.push_back(centerNear);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back(centerFar);
			indices.push_back(i + 1 + 2);
			indices.push_back((i + 3) % mod + 2);
		}

		return { std::move(vertices), std::move(indices) };
	}

	template<class V>
	static IndexedTriangleList<V> Make()
	{
		return MakeTesselated<V>(24);
	}
};