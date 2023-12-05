#include "spawn.h"

#include "algorithms.h"

#if __linux__

uint16_t HIWORD(uint32_t x) {
	return (uint16_t)(x >> 16);
}

uint16_t LOWORD(uint32_t x) {
	return (uint16_t)x;
}

#define _declspec(x)

#endif


//////// Bot list ////////

_linkedlist <botInfo> botlist;

botInfo *findBot(CALL_HANDLE handle)
{
	_listnode <botInfo> *parse = botlist.head;

	while (parse)
	{
		botInfo *item = parse->item;

		if (item->validate(handle))
			return item;

		parse = parse->next;
	}

	return 0;
}


//////// DLL "import" ////////

void botInfo::tell(BotEvent event)
{
	if (callback && handle)
	{
		event.handle = handle;
		callback(event);
	}
}

void botInfo::gotEvent(BotEvent &event)
{
	if (CONNECTION_DENIED) return;

	switch (event.code)
	{
//////// Periodic ////////
	case EVENT_Tick:
		{
			for (int i = 0; i < 4; ++i)
				--countdown[i];
		}
		break;
//////// Arena ////////
	case EVENT_ArenaEnter:
		{
			arena = (char*)event.p[0];
			me = (Player*)event.p[1];	// if(me) {/*we are in the arena*/}
			bool biller_online = *(bool*)&event.p[2];
		}
		break;
	case EVENT_ArenaSettings:
		{
			settings = (arenaSettings*)event.p[0];

			std::ofstream fout("arena.conf");
			fout << "[Bomb]\n";
			fout << "BBombDamagePercent = " << settings->BBombDamagePercent << "\n";
			fout << "BombAliveTime = " << settings->BombAliveTime << "\n";
			fout << "BombDamageLevel = " << settings->BombDamageLevel << "\n";
			fout << "BombExplodeDelay = " << settings->BombExplodeDelay << "\n";
			fout << "BombExplodePixels = " << settings->BombExplodePixels << "\n";
			fout << "BombSafety = " << (int)settings->BombSafety << "\n";
			fout << "EBombDamagePercent = " << settings->EBombDamagePercent << "\n";
			fout << "EBombShutdownTime = " << settings->EBombShutdownTime << "\n";
			fout << "JitterTime = " << settings->JitterTime << "\n";
			fout << "ProximityDistance = " << settings->ProximityDistance << "\n";
			fout << "\n";
			fout << "[Brick]\n";
			fout << "BrickTime = " << settings->BrickTime << "\n";
			fout << "\n";
			fout << "[Bullet]\n";
			fout << "BulletAliveTime = " << settings->BulletAliveTime << "\n";
			fout << "BulletDamageLevel = " << settings->BulletDamageLevel << "\n";
			fout << "BulletDamageUpgrade = " << settings->BulletDamageUpgrade << "\n";
			fout << "ExactDamage = " << settings->ExactDamage << "\n";
			fout << "\n";
			fout << "[Burst]\n";
			fout << "BurstDamageLevel = " << settings->BurstDamageLevel << "\n";
			fout << "\n";
			fout << "[Door]\n";
			fout << "DoorDelay = " << settings->DoorDelay << "\n";
			fout << "DoorMode = " << settings->DoorMode << "\n";
			fout << "\n";
			fout << "[Flag]\n";
			fout << "CarryFlags = " << (int)settings->CarryFlags << "\n";
			fout << "EnterGameFlaggingDelay = " << settings->EnterGameFlaggingDelay << "\n";
			fout << "FlagBlankDelay = " << settings->FlagBlankDelay << "\n";
			fout << "FlagDropDelay = " << settings->FlagDropDelay << "\n";
			fout << "FlagDropResetReward = " << settings->FlagDropResetReward << "\n";
			fout << "FlaggerBombFireDelay = " << settings->FlaggerBombFireDelay << "\n";
			fout << "FlaggerBombUpgrade = " << (int)settings->FlaggerBombUpgrade << "\n";
			fout << "FlaggerDamagePercent = " << settings->FlaggerDamagePercent << "\n";
			fout << "FlaggerFireCostPercent = " << settings->FlaggerFireCostPercent << "\n";
			fout << "FlaggerGunUpgrade = " << (int)settings->FlaggerGunUpgrade << "\n";
			fout << "FlaggerKillMultiplier = " << settings->FlaggerKillMultiplier << "\n";
			fout << "FlaggerOnRadar = " << settings->FlaggerOnRadar << "\n";
			fout << "FlaggerSpeedAdjustment = " << settings->FlaggerSpeedAdjustment << "\n";
			fout << "FlaggerThrustAdjustment = " << settings->FlaggerThrustAdjustment << "\n";
			fout << "NoDataFlagDropDelay = " << settings->NoDataFlagDropDelay << "\n";
			fout << "\n";
			fout << "[Kill]\n";
			fout << "BountyIncreaseForKill = " << settings->BountyIncreaseForKill << "\n";
			fout << "EnterDelay = " << settings->EnterDelay << "\n";
			fout << "MaxBonus = " << settings->MaxBonus << "\n";
			fout << "MaxPenalty = " << settings->MaxPenalty << "\n";
			fout << "RewardBase = " << settings->RewardBase << "\n";
			fout << "\n";
			fout << "[Latency]\n";
			fout << "ClientSlowPacketSampleSize = " << settings->CliSlowPacketSampleSize << "\n";
			fout << "ClientSlowPacketTime = " << settings->ClientSlowPacketTime << "\n";
			fout << "S2CNoDataKickoutDelay = " << settings->S2CNoDataKickoutDelay << "\n";
			fout << "SendRoutePercent = " << settings->SendRoutePercent << "\n";
			fout << "\n";
			fout << "[Message]\n";
			fout << "AllowAudioMessages = " << (int)settings->AllowAudioMessages << "\n";
			fout << "MessageReliable = " << (int)settings->MessageReliable << "\n";
			fout << "\n";
			fout << "[Mine]\n";
			fout << "MineAliveTime = " << settings->MineAliveTime << "\n";
			fout << "TeamMaxMines = " << (int)settings->TeamMaxMines << "\n";
			fout << "\n";
			fout << "[Misc]\n";
			fout << "ActivateAppShutdownTime = " << settings->ActivateAppShutdownTime << "\n";
			fout << "AllowSavedShips = " << (int)settings->AllowSavedShip << "\n";
			fout << "BounceFactor = " << settings->BounceFactor << "\n";
			fout << "DecoyAliveTime = " << settings->DecoyAliveTime << "\n";
			fout << "ExtraPositionData = " << (int)settings->ExtraPositionData << "\n";
			fout << "FrequencyShift = " << settings->FrequencyShift << "\n";
			fout << "NearDeathLevel = " << settings->NearDeathLevel << "\n";
			fout << "SafetyLimit = " << settings->SafetyLimit << "\n";
			fout << "SendPositionDelay = " << settings->SendPositionDelay << "\n";
			fout << "SlowFrameCheck = " << (int)settings->SlowFrameCheck << "\n";
			fout << "TickerDelay = " << settings->HelpTickerDelay << "\n";
			fout << "VictoryMusic = " << (int)settings->VictoryMusic << "\n";
			fout << "WarpPointDelay = " << settings->WarpPointDelay << "\n";
			fout << "WarpRadiusLimit = " << settings->WarpRadiusLimit << "\n";
			fout << "\n";
			fout << "[Prize]\n";
			fout << "DeathPrizeTime = " << settings->DeathPrizeTime << "\n";
			fout << "EngineShutdownTime = " << settings->EngineShutdownTime << "\n";
			fout << "MinimumVirtual = " << settings->PrizeMinimumVirtual << "\n";
			fout << "MultiPrizeCount = " << settings->MultiPrizeCount << "\n";
			fout << "PrizeDelay = " << settings->PrizeDelay << "\n";
			fout << "PrizeFactor = " << settings->PrizeFactor << "\n";
			fout << "PrizeHideCount = " << (int)settings->PrizeHideCount << "\n";
			fout << "PrizeMaxExist = " << settings->PrizeMaxExist << "\n";
			fout << "PrizeMinExist = " << settings->PrizeMinExist << "\n";
			fout << "PrizeNegativeFactor = " << settings->PrizeNegativeFactor << "\n";
			fout << "TakePrizeReliable = " << (int)settings->TakePrizeReliable << "\n";
			fout << "UpgradeVirtual = " << settings->PrizeUpgradeVirtual << "\n";
			fout << "\n";
			fout << "[PrizeWeight]\n";
			fout << "AllWeapons = " << (int)settings->pw.AllWeapons << "\n";
			fout << "AntiWarp = " << (int)settings->pw.AntiWarp << "\n";
			fout << "Bomb = " << (int)settings->pw.Bomb << "\n";
			fout << "BouncingBullets = " << (int)settings->pw.BouncingBullets << "\n";
			fout << "Brick = " << (int)settings->pw.Brick << "\n";
			fout << "Burst = " << (int)settings->pw.Burst << "\n";
			fout << "Cloak = " << (int)settings->pw.Cloak << "\n";
			fout << "Decoy = " << (int)settings->pw.Decoy << "\n";
			fout << "Energy = " << (int)settings->pw.Energy << "\n";
			fout << "Glue = " << (int)settings->pw.Glue << "\n";
			fout << "Gun = " << (int)settings->pw.Gun << "\n";
			fout << "MultiFire = " << (int)settings->pw.MultiFire << "\n";
			fout << "MultiPrize = " << (int)settings->pw.MultiPrize << "\n";
			fout << "Portal = " << (int)settings->pw.Portal << "\n";
			fout << "Proximity = " << (int)settings->pw.Proximity << "\n";
			fout << "QuickCharge = " << (int)settings->pw.Recharge << "\n";
			fout << "Recharge = " << (int)settings->pw.QuickCharge << "\n";
			fout << "Repel = " << (int)settings->pw.Repel << "\n";
			fout << "Rocket = " << (int)settings->pw.Rocket << "\n";
			fout << "Rotation = " << (int)settings->pw.Rotation << "\n";
			fout << "Shields = " << (int)settings->pw.Shields << "\n";
			fout << "Shrapnel = " << (int)settings->pw.Shrapnel << "\n";
			fout << "Stealth = " << (int)settings->pw.Stealth << "\n";
			fout << "Thor = " << (int)settings->pw.Thor << "\n";
			fout << "Thruster = " << (int)settings->pw.Thruster << "\n";
			fout << "TopSpeed = " << (int)settings->pw.TopSpeed << "\n";
			fout << "Warp = " << (int)settings->pw.Warp << "\n";
			fout << "XRadar = " << (int)settings->pw.XRadar << "\n";
			fout << "\n";
			fout << "[Radar]\n";
			fout << "MapZoomFactor = " << settings->MapZoomFactor << "\n";
			fout << "RadarMode = " << (int)settings->RadarMode << "\n";
			fout << "RadarNeutralSize = " << settings->RadarNeutralSize << "\n";
			fout << "\n";
			fout << "[Repel]\n";
			fout << "RepelDistance = " << settings->RepelDistance << "\n";
			fout << "RepelSpeed = " << settings->RepelSpeed << "\n";
			fout << "RepelTime = " << settings->RepelTime << "\n";
			fout << "\n";
			fout << "[Rocket]\n";
			fout << "RocketSpeed = " << settings->RocketSpeed << "\n";
			fout << "RocketThrust = " << settings->RocketThrust << "\n";
			fout << "\n";
			fout << "[Shrapnel]\n";
			fout << "InactiveShrapDamage = " << settings->InactiveShrapnelDamage << "\n";
			fout << "Random = " << (int)settings->RandomShrapnel << "\n";
			fout << "ShrapnelDamagePercent = " << settings->ShrapnelDamagePercent << "\n";
			fout << "ShrapnelSpeed = " << settings->ShrapnelSpeed << "\n";
			fout << "\n";
			fout << "[Soccer]\n";
			fout << "AllowBombs = " << (int)settings->SoccerAllowBombs << "\n";
			fout << "AllowGuns = " << (int)settings->SoccerAllowGuns << "\n";
			fout << "BallBlankDelay = " << settings->SoccerBallBlankDelay << "\n";
			fout << "BallBounce = " << (int)settings->SoccerBallBounce << "\n";
			fout << "BallLocation = " << (int)settings->SoccerBallLocation << "\n";
			fout << "Mode = " << (int)settings->SoccerMode << "\n";
			fout << "PassDelay = " << settings->SoccerPassDelay << "\n";
			fout << "UseFlagger = " << (int)settings->SoccerUseFlagger << "\n";
			fout << "\n";
			fout << "[Spectator]\n";
			fout << "HideFlags = " << settings->HideFlags << "\n";
			fout << "NoXRadar = " << settings->NoXRadar << "\n";
			fout << "\n";
			fout << "[Team]\n";
			fout << "MaxFrequency = " << settings->MaxFrequency << "\n";
			fout << "MaxPerPrivateTeam = " << (int)settings->MaxPerPrivateTeam << "\n";
			fout << "MaxPerTeam = " << (int)settings->MaxPerTeam << "\n";
			fout << "\n";
			fout << "[Toggle]\n";
			fout << "AntiWarpPixels = " << settings->AntiwarpPixels << "\n";
			fout << "\n";
			fout << "[Wormhole]\n";
			fout << "GravityBombs = " << (int)settings->WormholeGravityBombs << "\n";
			fout << "SwitchTime = " << settings->WormholeSwitchTime << "\n";

			const char *shipSectionNames[] = {"Warbird", "Javelin", "Spider", "Leviathan", "Terrier", "Weasel", "Lancaster", "Shark"};

			for (int i = 0; i < 8; ++i) {
				fout << "\n";
				fout << "[" << shipSectionNames[i] << "]\n";
				fout << "AfterburnerEnergy = " << settings->ships[i].AfterburnerEnergy << "\n";
				fout << "AntiWarpEnergy = " << settings->ships[i].AntiWarpEnergy << "\n";
				fout << "AntiWarpStatus = " << settings->ships[i].AntiwarpStatus << "\n";
				fout << "AttachBounty = " << settings->ships[i].AttachBounty << "\n";
				fout << "BombBounceCount = " << (int)settings->ships[i].BombBounceCount << "\n";
				fout << "BombFireDelay = " << settings->ships[i].BombFireDelay << "\n";
				fout << "BombFireEnergy = " << settings->ships[i].BombFireEnergy << "\n";
				fout << "BombFireEnergyUpgrade = " << settings->ships[i].BombFireEnergyUpgrade << "\n";
				fout << "BombSpeed = " << settings->ships[i].BombSpeed << "\n";
				fout << "BombThrust = " << settings->ships[i].BombThrust << "\n";
				fout << "BrickMax = " << (int)settings->ships[i].BrickMax << "\n";
				fout << "BulletFireDelay = " << settings->ships[i].BulletFireDelay << "\n";
				fout << "BulletFireEnergy = " << settings->ships[i].BulletFireEnergy << "\n";
				fout << "BulletSpeed = " << settings->ships[i].BulletSpeed << "\n";
				fout << "BurstMax = " << (int)settings->ships[i].BurstMax << "\n";
				fout << "BurstShrapnel = " << (int)settings->ships[i].BurstShrapnel << "\n";
				fout << "BurstSpeed = " << settings->ships[i].BurstSpeed << "\n";
				fout << "CloakEnergy = " << settings->ships[i].CloakEnergy << "\n";
				fout << "CloakStatus = " << settings->ships[i].CloakStatus << "\n";
				fout << "DamageFactor = " << settings->ships[i].DamageFactor << "\n";
				fout << "DecoyMax = " << (int)settings->ships[i].DecoyMax << "\n";
				fout << "DisableFastShooting = " << settings->ships[i].DisableFastBombs << "\n";
				fout << "DoubleBarrel = " << settings->ships[i].DoubleBarrel << "\n";
				fout << "EmpBomb = " << settings->ships[i].EmpBomb << "\n";
				fout << "Gravity = " << settings->ships[i].Gravity << "\n";
				fout << "GravityTopSpeed = " << settings->ships[i].GravityTopSpeed << "\n";
				fout << "InitialBombs = " << settings->ships[i].InitialBombs << "\n";
				fout << "InitialBounty = " << settings->ships[i].InitialBounty << "\n";
				fout << "InitialBrick = " << (int)settings->ships[i].InitialBrick << "\n";
				fout << "InitialBurst = " << (int)settings->ships[i].InitialBurst << "\n";
				fout << "InitialDecoy = " << (int)settings->ships[i].InitialDecoy << "\n";
				fout << "InitialEnergy = " << settings->ships[i].InitialEnergy << "\n";
				fout << "InitialGuns = " << settings->ships[i].InitialGuns << "\n";
				fout << "InitialPortal = " << (int)settings->ships[i].InitialPortal << "\n";
				fout << "InitialRecharge = " << settings->ships[i].InitialRecharge << "\n";
				fout << "InitialRepel = " << (int)settings->ships[i].InitialRepel << "\n";
				fout << "InitialRocket = " << (int)settings->ships[i].InitialRocket << "\n";
				fout << "InitialRotation = " << settings->ships[i].InitialRotation << "\n";
				fout << "InitialSpeed = " << settings->ships[i].InitialSpeed << "\n";
				fout << "InitialThor = " << (int)settings->ships[i].InitialThor << "\n";
				fout << "InitialThrust = " << settings->ships[i].InitialThrust << "\n";
				fout << "LandmineFireDelay = " << settings->ships[i].LandmineFireDelay << "\n";
				fout << "LandmineFireEnergy = " << settings->ships[i].MineFireEnergy << "\n";
				fout << "LandmineFireEnergyUpgrade = " << settings->ships[i].MineFireEnergyUpgrade << "\n";
				fout << "MaxBombs = " << settings->ships[i].MaxBombs << "\n";
				fout << "MaxGuns = " << settings->ships[i].MaxGuns << "\n";
				fout << "MaximumEnergy = " << settings->ships[i].MaximumEnergy << "\n";
				fout << "MaximumRecharge = " << settings->ships[i].MaximumRecharge << "\n";
				fout << "MaximumRotation = " << settings->ships[i].MaximumRotation << "\n";
				fout << "MaximumSpeed = " << settings->ships[i].MaximumSpeed << "\n";
				fout << "MaximumThrust = " << settings->ships[i].MaximumThrust << "\n";
				fout << "MaxMines = " << (int)settings->ships[i].MaxMines << "\n";
				fout << "MultiFireAngle = " << settings->ships[i].MultiFireAngle << "\n";
				fout << "MultiFireDelay = " << settings->ships[i].MultiFireDelay << "\n";
				fout << "MultiFireEnergy = " << settings->ships[i].MultiFireEnergy << "\n";
				fout << "PortalMax = " << (int)settings->ships[i].PortalMax << "\n";
				fout << "PrizeShareLimit = " << settings->ships[i].PrizeShareLimit << "\n";
				fout << "Radius = " << settings->ships[i].Radius << "\n";
				fout << "RepelMax = " << (int)settings->ships[i].RepelMax << "\n";
				fout << "RocketMax = " << (int)settings->ships[i].RocketMax << "\n";
				fout << "RocketTime = " << settings->ships[i].RocketTime << "\n";
				fout << "SeeBombLevel = " << settings->ships[i].SeeBombLevel << "\n";
				fout << "SeeMines = " << settings->ships[i].SeeMines << "\n";
				fout << "ShieldsTime = " << settings->ships[i].ShieldsTime << "\n";
				fout << "ShrapnelMax = " << settings->ships[i].ShrapnelMax << "\n";
				fout << "ShrapnelRate = " << settings->ships[i].ShrapnelRate << "\n";
				fout << "SoccerBallFriction = " << settings->ships[i].SoccerBallFriction << "\n";
				fout << "SoccerBallProximity = " << settings->ships[i].SoccerBallProximity << "\n";
				fout << "SoccerBallSpeed = " << settings->ships[i].SoccerBallSpeed << "\n";
				fout << "SoccerThrowTime = " << settings->ships[i].SoccerThrowTime << "\n";
				fout << "StealthEnergy = " << settings->ships[i].StealthEnergy << "\n";
				fout << "StealthStatus = " << settings->ships[i].StealthStatus << "\n";
				fout << "SuperTime = " << settings->ships[i].SuperTime << "\n";
				fout << "ThorMax = " << (int)settings->ships[i].ThorMax << "\n";
				fout << "TurretLimit = " << (int)settings->ships[i].TurretLimit << "\n";
				fout << "TurretSpeedPenalty = " << settings->ships[i].TurretSpeedPenalty << "\n";
				fout << "TurretThrustPenalty = " << settings->ships[i].TurretThrustPenalty << "\n";
				fout << "UpgradeEnergy = " << settings->ships[i].UpgradeEnergy << "\n";
				fout << "UpgradeRecharge = " << settings->ships[i].UpgradeRecharge << "\n";
				fout << "UpgradeRotation = " << settings->ships[i].UpgradeRotation << "\n";
				fout << "UpgradeSpeed = " << settings->ships[i].UpgradeSpeed << "\n";
				fout << "UpgradeThrust = " << settings->ships[i].UpgradeThrust << "\n";
				fout << "XRadarEnergy = " << settings->ships[i].XRadarEnergy << "\n";
				fout << "XRadarStatus = " << settings->ships[i].XRadarStatus << "\n";
			}
			//sendPublic(0, "Persisted arena settings.");
		}
		break;
	case EVENT_ArenaLeave:
		{
			me = 0;
			killTags();
		}
		break;
	case EVENT_ArenaListEntry:
		{
			char *name = (char*)event.p[0];
			bool current = *(bool*)&event.p[1];
			int population = *(int*)&event.p[2];
		}
		break;
	case EVENT_ArenaListEnd:
		{
			char *name = (char*)event.p[0];
			bool current = *(bool*)&event.p[1];
			int population = *(int*)&event.p[2];
		}
		break;
//////// Flag ////////
	case EVENT_FlagGrab:
		{
			Player *p = (Player*)event.p[0];
			Flag *f = (Flag*)event.p[1];
		}
		break;
	case EVENT_FlagDrop:
		{
			Player *p = (Player*)event.p[0];
		}
		break;
	case EVENT_FlagMove:
		{
			Flag *f = (Flag*)event.p[0];
		}
		break;
	case EVENT_FlagVictory:
		{
			int team = *(int*)&event.p[0];
			int reward = *(int*)&event.p[1];
		}
		break;
	case EVENT_FlagGameReset:
		{
		}
		break;
	case EVENT_FlagReward:
		{
			int team = *(int*)&event.p[0];
			int reward = *(int*)&event.p[1];
		}
		break;
//////// Timed ////////
	case EVENT_TimedGameOver:
		{
			Player *p[5];
			for (int i = 0; i < 5; i++)
				p[i] = (Player*)event.p[i];
		}
		break;
//////// Soccer ////////
	case EVENT_SoccerGoal:
		{
			int team = *(int*)&event.p[0];
			int reward = *(int*)&event.p[1];
		}
		break;
	case EVENT_BallMove:
		{
			PBall *ball = (PBall*)event.p[0];
		}
		break;
//////// File ////////
	case EVENT_File:
		{
			char *name = (char*)event.p[0];
		}
		break;
//////// Player ////////
	case EVENT_PlayerEntering:
		{
			Player *p = (Player*)event.p[0];
		}
		break;
	case EVENT_PlayerMove:
		{
			Player *p = (Player*)event.p[0];
		}
		break;
	case EVENT_PlayerWeapon:
		{
			Player *p = (Player*)event.p[0];
			weaponInfo wi;
			wi.n = *(Uint16*)&event.p[1];
		}
		break;
	case EVENT_WatchDamage:
		{
			Player *p = (Player*)event.p[0];	// player
			Player *k = (Player*)event.p[1];	// attacker
			weaponInfo wi;
			wi.n = *(Uint16*)&event.p[2];
			Uint16 energy = *(Uint16*)&event.p[3];
			Uint16 damage = *(Uint16*)&event.p[4];
		}
		break;
	case EVENT_PlayerDeath:
		{
			Player *p = (Player*)event.p[0],
				   *k = (Player*)event.p[1];
			Uint16 bounty = *(Uint16*)&event.p[2];
			Uint16 flags = *(Uint16*)&event.p[3];
		}
		break;
	case EVENT_BannerChanged:
		{
			Player *p = (Player*)event.p[0];
		}
		break;
	case EVENT_PlayerScore:
		{
			Player *p = (Player*)event.p[0];
		}
		break;
	case EVENT_PlayerPrize:
		{
			Player *p = (Player*)event.p[0];
			int prize = *(int *)&event.p[1];
		}
		break;
	case EVENT_PlayerShip:
		{
			Player *p = (Player*)event.p[0];
			Uint16 oldship = *(Uint16*)&event.p[1];
			Uint16 oldteam = *(Uint16*)&event.p[2];
		}
		break;
	case EVENT_PlayerSpec:
		{
			Player *p = (Player*)event.p[0];
			Uint16 oldteam = *(Uint16*)&event.p[1];
			Uint16 oldship = *(Uint16*)&event.p[2];
		}
		break;
	case EVENT_PlayerTeam:
		{
			Player *p = (Player*)event.p[0];
			Uint16 oldteam = *(Uint16*)&event.p[1];
			Uint16 oldship = *(Uint16*)&event.p[2];
		}
		break;
	case EVENT_PlayerLeaving:
		{
			Player *p = (Player*)event.p[0];

			killTags(p);
		}
		break;
//////// Selfish ////////
	case EVENT_SelfShipReset:
		{
		}
		break;
	case EVENT_SelfPrize:
		{
			Uint16 prize = *(Uint16*)&event.p[0];
			Uint16 count = *(Uint16*)&event.p[1];
		}
		break;
	case EVENT_SelfUFO:
		{
		}
		break;
	case EVENT_PositionHook:
		{
		}
		break;
//////// Bricks ////////
	case EVENT_BrickDropped:
		{
			int x1 = *(int*)&event.p[0];
			int y1 = *(int*)&event.p[1];
			int x2 = *(int*)&event.p[2];
			int y2 = *(int*)&event.p[3];
			int team = *(int*)&event.p[4];
		}
		break;
//////// LVZ ////////
	case EVENT_ObjectToggled:
		{
			objectInfo obj;
			obj.n = *(Uint16*)&event.p[0];
		}
		break;
//////// Turret ////////
	case EVENT_CreateTurret:
		{
			Player *turreter = (Player*)event.p[0];
			Player *turretee = (Player*)event.p[1];
		}
		break;
	case EVENT_DeleteTurret:
		{
			Player *turreter = (Player*)event.p[0];
			Player *turretee = (Player*)event.p[1];
		}
		break;
//////// Chat ////////
	case EVENT_Chat:
		{
			int type  = *(int*)&event.p[0];
			int sound = *(int*)&event.p[1];
			Player *p = (Player*)event.p[2];
			char *msg = (char*)event.p[3];

			switch (type)
			{
			case MSG_Arena:
				{
				}
				break;
			case MSG_PublicMacro:		if (!p) break;
				{
				}
				break;
			case MSG_Public:			if (!p) break;
				{
				}
				break;
			case MSG_Team:				if (!p) break;
				{
				}
				break;
			case MSG_TeamPrivate:		if (!p) break;
				{
				}
				break;
			case MSG_Private:			if (!p) break;
				{
				}
				break;
			case MSG_PlayerWarning:		if (!p) break;
				{
				}
				break;
			case MSG_RemotePrivate:
				{
				}
				break;
			case MSG_ServerError:
				{
				}
				break;
			case MSG_Channel:
				{
				}
				break;
			};
		}
		break;
	case EVENT_LocalCommand:
		{
			Player *p = (Player*)event.p[0];
			Command *c = (Command*)event.p[1];

			gotCommand(p, c);
		}
		break;
	case EVENT_LocalHelp:
		{
			Player *p = (Player*)event.p[0];
			Command *c = (Command*)event.p[1];

			gotHelp(p, c);
		}
		break;
	case EVENT_RemoteCommand:
		{
			char *p = (char*)event.p[0];
			Command *c = (Command*)event.p[1];
			Operator_Level o = *(Operator_Level*)&event.p[2];

			gotRemote(p, c, o);
		}
		break;
	case EVENT_RemoteHelp:
		{
			char *p = (char*)event.p[0];
			Command *c = (Command*)event.p[1];
			Operator_Level o = *(Operator_Level*)&event.p[2];

			gotRemoteHelp(p, c, o);
		}
		break;
//////// Containment ////////
	case EVENT_Init:
		{
			uint32_t major = HIWORD(*(uint32_t*)&event.p[0]);
			uint32_t minor = LOWORD(*(uint32_t*)&event.p[0]);
			callback	= (CALL_COMMAND)event.p[1];
			playerlist	= (CALL_PLIST)event.p[2];
			flaglist	= (CALL_FLIST)event.p[3];
			map			= (CALL_MAP)event.p[4];
			bricklist	= (CALL_BLIST)event.p[5];

			if (major > CORE_MAJOR_VERSION)
			{
				tell(makeEcho("Plugin cannot connect.  This plugin is out of date."));

				CONNECTION_DENIED = true;

				return;
			}
			else if ((major < CORE_MAJOR_VERSION) || (minor < CORE_MINOR_VERSION))
			{
				tell(makeEcho("Plugin cannot connect.  This plugin requires the latest version of MERVBot."));

				CONNECTION_DENIED = true;

				return;
			}
			else
				tell(makeEcho("Plugin connected."));

		}
		break;
	case EVENT_Term:
		{
			tell(makeEcho("Plugin disconnected."));
		}
		break;
	};
}


//////// DLL export ////////

_declspec(dllexport) void __stdcall talk(BotEvent &event)
{
	botInfo *bot;

	bot = findBot(event.handle);

	if (!bot)
	{
		bot = new botInfo(event.handle);
		botlist.append(bot);
	}

	if (bot) bot->gotEvent(event);
}


//////// Tag emulation ////////

int botInfo::get_tag(Player *p, int index)
{
	_listnode <PlayerTag> *parse = taglist.head;
	PlayerTag *tag;

	while (parse)
	{
		tag = parse->item;

		if (tag->p == p)
		if (tag->index == index)
			return tag->data;

		parse = parse->next;
	}

	return 0;
}

void botInfo::set_tag(Player *p, int index, int data)
{
	_listnode <PlayerTag> *parse = taglist.head;
	PlayerTag *tag;

	while (parse)
	{
		tag = parse->item;

		if (tag->p == p)
		if (tag->index == index)
		{
			tag->data = data;
			return;
		}

		parse = parse->next;
	}

	tag = new PlayerTag;
	tag->p = p;
	tag->index = index;
	tag->data = data;
	taglist.append(tag);
}

void botInfo::killTags(Player *p)
{
	_listnode <PlayerTag> *parse = taglist.head;
	PlayerTag *tag;

	while (parse)
	{
		tag = parse->item;
		parse = parse->next;

		if (tag->p != p) continue;

		taglist.kill(tag);
	}
}

void botInfo::killTags()
{
	taglist.clear();
}


//////// LVZ Object Toggling ////////

void botInfo::clear_objects()
{
	num_objects = 0;
}

void botInfo::object_target(Player *p)
{
	object_dest = p;
}

void botInfo::toggle_objects()
{
	Player *p = object_dest;

	if (!p)	tell(makeToggleObjects(UNASSIGNED, (Uint16 *)object_array, num_objects));
	else	tell(makeToggleObjects(p->ident, (Uint16 *)object_array, num_objects));

	num_objects = 0;
}

void botInfo::queue_enable(int id)
{
	if (num_objects == MAX_OBJECTS)
		toggle_objects();

	object_array[num_objects].id = id;
	object_array[num_objects].disabled = false;
	++num_objects;
}

void botInfo::queue_disable(int id)
{
	if (num_objects == MAX_OBJECTS)
		toggle_objects();

	object_array[num_objects].id = id;
	object_array[num_objects].disabled = true;
	++num_objects;
}


//////// Chatter ////////

void botInfo::sendPrivate(Player *player, BYTE snd, const char *msg)
{
	tell(makeSay(MSG_Private, snd, player->ident, msg));
}

void botInfo::sendPrivate(Player *player, const char *msg)
{
	tell(makeSay(MSG_Private, 0, player->ident, msg));
}

void botInfo::sendTeam(const char *msg)
{
	tell(makeSay(MSG_Team, 0, 0, msg));
}

void botInfo::sendTeam(BYTE snd, const char *msg)
{
	tell(makeSay(MSG_Team, snd, 0, msg));
}

void botInfo::sendTeamPrivate(Uint16 team, const char *msg)
{
	tell(makeSay(MSG_TeamPrivate, 0, team, msg));
}

void botInfo::sendTeamPrivate(Uint16 team, BYTE snd, const char *msg)
{
	tell(makeSay(MSG_TeamPrivate, snd, team, msg));
}

void botInfo::sendPublic(const char *msg)
{
	tell(makeSay(MSG_Public, 0, 0, msg));
}

void botInfo::sendPublic(BYTE snd, const char *msg)
{
	tell(makeSay(MSG_Public, snd, 0, msg));
}

void botInfo::sendPublicMacro(const char *msg)
{
	tell(makeSay(MSG_PublicMacro, 0, 0, msg));
}

void botInfo::sendPublicMacro(BYTE snd, const char *msg)
{
	tell(makeSay(MSG_PublicMacro, snd, 0, msg));
}

void botInfo::sendChannel(const char *msg)
{
	tell(makeSay(MSG_Channel, 0, 0, msg));
}

void botInfo::sendRemotePrivate(const char *msg)
{
	tell(makeSay(MSG_RemotePrivate, 0, 0, msg));
}

void botInfo::sendRemotePrivate(const char *name, const char *msg)
{
	String s;
	s += ":";
	s += name;
	s += ":";
	s += msg;

	sendRemotePrivate(s);
}
