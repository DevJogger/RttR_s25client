// Copyright (C) 2005 - 2024 Settlers Freaks (sf-team at siedler25.org)
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "figures/noFigure.h"

class noBuildingSite;
class SerializedGameData;

class nofBuilder final : public noFigure
{
private:
    // Wie weit der Bauarbeiter maximal in alle vier richtungen laufen darf (in Pixeln, rel..)
    static const short LEFT_MAX = -28;
    static const short RIGHT_MAX = 28;
    static const short UP_MAX = 0;
    static const short DOWN_MAX = 16;

    enum class BuilderState : uint8_t
    {
        FigureWork,
        WaitingFreewalk, // Bauarbeiter geht auf und ab und wartet auf Rohstoffe
        BuildFreewalk,   // Bauarbeiter geht auf und ab und baut
        Build            // Bauarbeiter "baut" gerade (hämmert auf Gebäude ein)
    } state;
    friend constexpr auto maxEnumValue(BuilderState) { return BuilderState::Build; }

    /// Baustelle des Bauarbeiters
    noBuildingSite* building_site;

    // const GameEvent* current_ev;

    /// X,Y relativ zur Baustelle in Pixeln
    /// next ist der angesteuerte Punkt
    Point<int16_t> offsetSite, nextOffsetSite;

    /// Wie viele Bauschritte noch verfügbar sind, bis der nächste Rohstoff geholt werden muss
    unsigned char building_steps_available;

    void GoalReached() override;
    void Walked() override;
    void AbrogateWorkplace() override;
    void HandleDerivedEvent(unsigned id) override;

    /// In neue Richtung laufen (Freewalk)
    void StartFreewalk();
    /// "Frisst" eine passende Ware (falls vorhanden, gibt true in dem Fall zurück!) von der Baustelle, d.h nimmt sie in
    /// die Hand und erhöht die building_steps_avaible
    bool ChooseWare();

public:
    nofBuilder(MapPoint pos, unsigned char player, noBuildingSite* building_site);
    nofBuilder(SerializedGameData& sgd, unsigned obj_id);
    nofBuilder(const nofBuilder&) = delete;

    void Destroy() override
    {
        RTTR_Assert(!building_site);
        noFigure::Destroy();
    }

    void Serialize(SerializedGameData& sgd) const override;

    GO_Type GetGOT() const final { return GO_Type::NofBuilder; }

    void Draw(DrawPoint drawPt) override;

    // Wird von der Baustelle aus aufgerufen, um den Bauarbeiter zu sagen, dass er gehen kann
    void LostWork();
};
