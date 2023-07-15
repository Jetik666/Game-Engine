#pragma once

#include "../IndexedTriangleList.h"
#include "../Math.h"

#include <DirectXMath.h>

class Sphere
{
public:
	template<class V>
	static IndexedTriangleList<V> MakeTesselated(int latDiv, int longDiv)
	{
		assert(latDiv >= 3);
		assert(longDiv >= 3);

		constexpr float radius = 1.0f;
		const DirectX::XMVECTOR base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
		const float lattitudeAngle = PI / latDiv;
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		for (int iLat = 1; iLat < latDiv; iLat++)
		{
			const DirectX::XMVECTOR latBase = DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationX(lattitudeAngle * iLat));
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				vertices.emplace_back();
				DirectX::XMVECTOR v = DirectX::XMVector3Transform(latBase, DirectX::XMMatrixRotationZ(longitudeAngle * iLong));
				DirectX::XMStoreFloat3(&vertices.back().pos, v);
			}
		}

		// add the cap vertices
		const auto iNorthPole = (unsigned short)vertices.size();
		vertices.emplace_back(); 
		DirectX::XMStoreFloat3(&vertices.back().pos, base);
		const auto iSouthPole = (unsigned short)vertices.size();
		vertices.emplace_back();
		DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVectorNegate(base));

		std::vector<unsigned short> indices;
		for (unsigned short iLat = 0; iLat < latDiv - 2; iLat++)
		{
			for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
			{
				indices.push_back(CalcIndex(iLat, iLong, longDiv));
				indices.push_back(CalcIndex(iLat + 1, iLong, longDiv));
				indices.push_back(CalcIndex(iLat, iLong + 1, longDiv));
				indices.push_back(CalcIndex(iLat, iLong + 1, longDiv));
				indices.push_back(CalcIndex(iLat + 1, iLong, longDiv));
				indices.push_back(CalcIndex(iLat + 1, iLong + 1, longDiv));
			}
			// wrap band
			indices.push_back(CalcIndex(iLat, longDiv - 1, longDiv));
			indices.push_back(CalcIndex(iLat + 1, longDiv - 1, longDiv));
			indices.push_back(CalcIndex(iLat, 0, longDiv));
			indices.push_back(CalcIndex(iLat, 0, longDiv));
			indices.push_back(CalcIndex(iLat + 1, longDiv - 1, longDiv));
			indices.push_back(CalcIndex(iLat + 1, 0, longDiv));
		}

		// cap fans
		for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
		{
			// north
			indices.push_back(iNorthPole);
			indices.push_back(CalcIndex(0, iLong, longDiv));
			indices.push_back(CalcIndex(0, iLong + 1, longDiv));
			// south
			indices.push_back(CalcIndex(latDiv - 2, iLong + 1, longDiv));
			indices.push_back(CalcIndex(latDiv - 2, iLong, longDiv));
			indices.push_back(iSouthPole);
		}

		// wrap triangles
		// north
		indices.push_back(iNorthPole);
		indices.push_back(CalcIndex(0, longDiv - 1, longDiv));
		indices.push_back(CalcIndex(0, 0, longDiv));
		// south
		indices.push_back(CalcIndex(latDiv - 2, 0, longDiv));
		indices.push_back(CalcIndex(latDiv - 2, longDiv - 1, longDiv));
		indices.push_back(iSouthPole);

		return { std::move(vertices),std::move(indices) };
	}
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		return MakeTesselated<V>(12, 24);
	}

private:
	unsigned short CalcIndex(unsigned short iLat, unsigned short iLong, unsigned short longDiv)
	{
		return iLat * longDiv + iLong;
	}
};