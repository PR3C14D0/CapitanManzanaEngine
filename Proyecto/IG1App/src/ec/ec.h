#pragma once
#include <cstdint> // wtf
#define _CMPS_LIST_ TRANSFORM, MESH_RENDERER, NUM_COMPONENTS
#define _GRPS_LIST_ TRANSPARENT, NUM_GROUP

namespace ec
{
	class Entity;
	class Component;
	using entity_t = Entity*;

	// Para ahorrar, no hay tantos componentes
	using cmpID_t = uint8_t;
	namespace comp
	{
		enum cmpID : cmpID_t
		{
			DEFAULT = 0,
			_CMPS_LIST_
		};
		constexpr cmpID_t maxComponentId = NUM_COMPONENTS;
	}

	// Dado un componente, devolver su ID que corresponde al enum cmpID
	// Para ello el componente tiene que estar "registrado"
	// El tipo es uint8_t, el mismo para el cmpID
	template<typename T>
	constexpr cmpID_t getComponentID = T::id;


	using groupID_t = uint8_t;
	namespace ent
	{
		enum groupID : groupID_t
		{
			None = 0,
			_GRPS_LIST_
		};
		constexpr groupID_t maxGroupLayer = NUM_GROUP;
	}
}
#define __CMPID_DECL__(cId) constexpr static ec::cmpID_t id = cId;
