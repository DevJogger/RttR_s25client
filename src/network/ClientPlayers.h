// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
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

#ifndef ClientPlayers_h__
#define ClientPlayers_h__

#include "ClientPlayer.h"
#include <vector>

struct ClientPlayer;

struct ClientPlayers
{
    void add(unsigned playerId) { players.push_back(ClientPlayer(playerId)); }
    const ClientPlayer& get(unsigned idx) const { return players[idx]; }
    ClientPlayer& get(unsigned idx) { return players[idx]; }
    unsigned getNumPlayers() const { return static_cast<unsigned>(players.size()); }
    std::vector<ClientPlayer> players;

    /// Set the isLagging flag and returns true iff any player is lagging
    bool checkForLaggingPlayers();
};

#endif // ClientPlayers_h__
