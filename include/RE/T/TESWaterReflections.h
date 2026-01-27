#pragma once

#include "RE/N/NiPlane.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/B/BSCubeMapCamera.h"

namespace RE
{
	class BSWaterShaderMaterial;

	class TESWaterReflections : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWaterReflections;
		inline static constexpr auto VTABLE = VTABLE_TESWaterReflections;

		struct CubeMapSide
		{
			std::uint32_t idx;    // 00
			float         unk04;  // 04
		};
		static_assert(sizeof(CubeMapSide) == 0x8);

		// https://github.com/libxse/commonlibf4/blob/main/include/RE/T/TESWaterReflections.h
		enum class Flags : std::uint32_t
		{
			kDirty = 1 << 0,
			kStaticCubemap = 1 << 1,
			kDynamicCubemap = 1 << 2,
			kInterior = 1 << 3,
			kSilhouette = 1 << 4,
			kLODScene = 1 << 5,
			kFullScene = 1 << 6,
			kLand = 1 << 7,
			kSky = 1 << 8,
			kExplosions = 1 << 9,
			kSelective = 1 << 10,
			kDontUpdate = 1 << 11,
			kWorldOrigin = 1 << 12
		};

		virtual ~TESWaterReflections() override { Dtor(); };  // 00

		void Update();

		// members
		REX::EnumSet<Flags, std::uint32_t>	flags;            // 10
		NiPlane								reflectPlane;     // 14
		std::uint32_t						unk24;            // 24
		NiPointer<BSCubeMapCamera>			cubeMapCamera;    // 28
		std::uint64_t                       unk30;            // 30
		std::uint64_t                       unk38;            // 38
		BSWaterShaderMaterial*				waterMaterial;    // 40
		float								lastUpdate;       // 48
		std::uint32_t						currentSide;      // 4C
		CubeMapSide							cubeMapSides[6];  // 50
		std::uint8_t						unk80;            // 80
		std::uint8_t						pad81;            // 81
		std::uint16_t						pad82;            // 82
		std::uint32_t						pad84;            // 84
	private:
		void Dtor();
	};
	static_assert(sizeof(TESWaterReflections) == 0x88);
}
