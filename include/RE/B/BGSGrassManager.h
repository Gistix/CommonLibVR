#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	struct GrassTypeKey
	{
		[[nodiscard]] bool operator==(const GrassTypeKey&) const = default;

		// members
		RE::FormID    id;     // 00
		std::uint16_t cellX;  // 04
		std::uint16_t cellY;  // 06
	};
	static_assert(sizeof(GrassTypeKey) == 0x8);

	template <>
	struct BSCRC32<GrassTypeKey>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const GrassTypeKey& a_info) const noexcept
		{
			return detail::GenerateCRC32(
				std::span(
					reinterpret_cast<const std::uint8_t*>(std::addressof(a_info)),
					sizeof(GrassTypeKey)));
		}
	};

	struct GrassType
	{
		BSMultiStreamInstanceTriShape* typeShape;        // 00
		ModelDBHandle                  typeModelHandle;  // 08
	};
	static_assert(sizeof(GrassType) == 0x10);

	class BGSGrassManager : public BSTSingletonSDM<BGSGrassManager>
	{
	public:
		struct InstanceData
		{
			std::uint16_t x;            // 00
			std::uint16_t y;            // 02
			std::uint16_t z;            // 04
			std::uint16_t colorScale;   // 06

			std::uint16_t rot00;        // 08
			std::uint16_t rot01;        // 0A
			std::uint16_t rot02;        // 0C
			std::uint16_t rot10;        // 0E
			std::uint16_t rot11;        // 10
			std::uint16_t rot12;        // 12
			std::uint16_t rot20;        // 14
			std::uint16_t rot21;        // 16
			std::uint16_t rot22;        // 18

			std::uint16_t heightScale;  // 1A
			std::uint16_t unk1C;        // 1C always 0?
			std::uint16_t unk1E;        // 1E always 0?
		};
		static_assert(sizeof(InstanceData) == 0x20);

		static BGSGrassManager* GetSingleton()
		{
			static REL::Relocation<BGSGrassManager**> singleton{ RELOCATION_ID(514292, 400452) };
			return *singleton;
		}

		// members
		bool                                     generateGrassDataFiles;  // 01
		std::uint8_t                             unk02;                   // 02
		std::uint16_t                            unk04;                   // 04
		std::uint32_t                            unk08;                   // 08
		std::uint32_t                            unk0C;                   // 0C
		BSTFixedHashMap<GrassTypeKey, GrassType*> grassTypes;             // 10
		mutable BSReadWriteLock                  lock;                    // 38
		volatile mutable std::uint32_t           grassShapeLock;          // 40
		std::uint32_t                            pad44;                   // 44
		BSTArray<BSMultiStreamInstanceTriShape*> grassShapes;             // 48
		float                                    totalGrassRange;         // 60
		std::uint32_t                            pad64;                   // 64
		NiPointer<NiNode>                        grassNode;               // 68
		std::uint32_t                            grassEvalSize;           // 70
		std::uint32_t                            grassEvalSizeSquared;    // 74
		std::uint32_t                            grassPatchSize;          // 78
		std::uint32_t                            unk7C;                   // 7C
		InstanceData*                            instanceData;            // 80
		bool                                     enableGrass;             // 88
	};
	static_assert(sizeof(BGSGrassManager) == 0x90);
}
