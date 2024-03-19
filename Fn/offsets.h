#pragma once
#pragma once
#include <Windows.h>
uintptr_t OFFSET_UWORLD = 0xEE9ED98;
//

namespace offsets
{
    uintptr_t Gameinstance = 0x1b8;
    uintptr_t LocalPlayers = 0x38;
    uintptr_t PlayerController = 0x30;
    uintptr_t LocalPawn = 0x338;
    uintptr_t PlayerState = 0x2b0;
    uintptr_t RootComponet = 0x198;
    uintptr_t GameState = 0x158;
    uintptr_t PersistentLevel = 0x30;

    uintptr_t ActorCount = 0xA0;
    uintptr_t Cameramanager = 0x348;
    uintptr_t AActor = 0x98;
    uintptr_t CurrentActor = 0x8;
    uintptr_t Mesh = 0x318;
    uintptr_t Revivefromdbnotime = 0x46d8;
    uintptr_t TeamId = 0x10D0;
    uintptr_t ActorTeamId = 0x10C8;

    uintptr_t LocalActorPos = 0x128;
    uintptr_t ComponetToWorld = 0x240;
    uintptr_t BoneArray = 0x600;
    uintptr_t Velocity = 0xb8;
    uintptr_t PawnPrivate = 0x308;
    uintptr_t PlayerArray = 0x2a8;
    uintptr_t relativelocation = 0x128;
    uintptr_t UCharacterMovementComponent = 0x318;
    uintptr_t entity_actor = 0x310;
    uintptr_t bIsReloadingWeapon = 0x358;
    uintptr_t GlobalAnimRateScale = 0xA80;
    uintptr_t CurrentWeapon = 0x948;
}

namespace samsung
{
    uintptr_t Uworld;
    uintptr_t LocalPawn;
    uintptr_t PlayerState;
    uintptr_t Localplayer;
    uintptr_t Rootcomp;
    uintptr_t PlayerController;
    uintptr_t Persistentlevel;
    uintptr_t PlayerCamManager;
    uintptr_t GameInstance;
    uintptr_t LocalPlayers;
    Vector3 localactorpos;
    DWORD ActorCount;
    uintptr_t AActors;
    uint64_t TargetPawn;
    int localplayerID;
}