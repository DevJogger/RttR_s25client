// Copyright (c) 2017 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "AIInfo.h"
#include "BuildingType.h"
#include "FlagType.h"
#include "GameSettingTypes.h"
#include "JobTypes.h"
#include "MapType.h"
#include "Nation.h"
#include "PactTypes.h"
#include "PlayerState.h"
#include "gameTypes/BuildingQuality.h"
#include "gameTypes/Direction.h"
#include "gameTypes/FoWNode.h"
#include "gameTypes/MapTypes.h"
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <ostream>

#define RTTR_CASE_OUT(Enum, Enumerator) \
    case Enum::Enumerator: os << #Enumerator; break

// LCOV_EXCL_START

#define RTTR_ENUM_CASE_SINGLE(s, EnumName, Enumerator) \
    case EnumName::Enumerator: return os << #EnumName "::" BOOST_PP_STRINGIZE(Enumerator);

/// Generates an output operator for enum
///
/// Usage: ENUM_OUTPUT(MyFancyEnum, Value1, Value2, Value3, ...)
#define RTTR_ENUM_OUTPUT(EnumName, ...)                                                                   \
    inline std::ostream& operator<<(std::ostream& os, const EnumName& e)                                  \
    {                                                                                                     \
        switch(e)                                                                                         \
        {                                                                                                 \
            BOOST_PP_SEQ_FOR_EACH(RTTR_ENUM_CASE_SINGLE, EnumName, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
        }                                                                                                 \
        return os;                                                                                        \
    }

RTTR_ENUM_OUTPUT(BorderStonePos, OnPoint, HalfEast, HalfSouthEast, HalfSouthWest)
RTTR_ENUM_OUTPUT(BuildingQuality, Nothing, Flag, Hut, House, Castle, Mine, Harbor)
RTTR_ENUM_OUTPUT(Direction, WEST, NORTHWEST, NORTHEAST, EAST, SOUTHEAST, SOUTHWEST)
RTTR_ENUM_OUTPUT(Exploration, Disabled, Classic, FogOfWar, FogOfWarExplored)
RTTR_ENUM_OUTPUT(FlagType, Normal, Large, Water)
RTTR_ENUM_OUTPUT(GameObjective, None, Conquer3_4, TotalDomination, EconomyMode, Tournament1, Tournament2, Tournament3,
                 Tournament4, Tournament5)
RTTR_ENUM_OUTPUT(GameSpeed, VerySlow, Slow, Normal, Fast, VeryFast)
RTTR_ENUM_OUTPUT(MapType, OldMap, Savegame)
RTTR_ENUM_OUTPUT(PlayerState, Free, Occupied, Locked, AI)
RTTR_ENUM_OUTPUT(PointRoad, None, Normal, Donkey, Boat)
RTTR_ENUM_OUTPUT(PactType, TreatyOfAlliance, NonAgressionPact);
RTTR_ENUM_OUTPUT(RoadDir, East, SouthEast, SouthWest)
RTTR_ENUM_OUTPUT(StartWares, VLow, Low, Normal, ALot)
RTTR_ENUM_OUTPUT(Visibility, Invisible, FogOfWar, Visible)

namespace AI {
RTTR_ENUM_OUTPUT(Type, Dummy, Default)
RTTR_ENUM_OUTPUT(Level, Easy, Medium, Hard)
} // namespace AI

#undef RTTR_ENUM_CASE_SINGLE
#undef RTTR_ENUM_OUTPUT

// Simple only
#define RTTR_ENUM_OUTPUT(EnumName)                                                 \
    static std::ostream& operator<<(std::ostream& out, const EnumName e)           \
    {                                                                              \
        return out << #EnumName "::" << static_cast<unsigned>(rttr::enum_cast(e)); \
    }

RTTR_ENUM_OUTPUT(BuildingType)
RTTR_ENUM_OUTPUT(Job)
RTTR_ENUM_OUTPUT(Nation)

#undef RTTR_ENUM_OUTPUT

// LCOV_EXCL_STOP

#undef RTTR_CASE_OUT
