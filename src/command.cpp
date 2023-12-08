#include "spawn.h"

#include "algorithms.h"

void botInfo::gotHelp(Player *p, Command *c)
{
	// List commands

	if (!*c->final)
	{
		switch (p->access)
		{
		case OP_Duke:
		case OP_Baron:
		case OP_King:
		case OP_Emperor:
		case OP_RockStar:
		case OP_Q:
		case OP_God:
		case OP_Owner:
			{	// Owner-level commands
//				sendPrivate(p, "Ext: ");
			}
		case OP_SysOp:	/* FALL THRU */
			{	// SysOp-level commands
//				sendPrivate(p, "Ext: ");
			}
		case OP_SuperModerator:	/* FALL THRU */
			{	// SuperModerator-level commands
//				sendPrivate(p, "Ext: ");
			}
		case OP_Moderator:	/* FALL THRU */
			{	// Moderator-level commands
//				sendPrivate(p, "Ext: ");
			}
		case OP_Limited:	/* FALL THRU */
			{	// Limited-level commands
			}
		case OP_Player:	/* FALL THRU */
			{	// Player-level commands
				sendPrivate(p, "Ext: !about");
			}
		}

		return;
	}

	// Specific command help

	switch (p->access)
	{
	case OP_Duke:
	case OP_Baron:
	case OP_King:
	case OP_Emperor:
	case OP_RockStar:
	case OP_Q:
	case OP_God:
	case OP_Owner:
		{	// Owner-level commands
			if (c->checkParam("owner") || c->checkParam("all"))
			{
//				sendPrivate(p, "Ext: ");
			}
		}
	case OP_SysOp:
		{	// SysOp-level commands
			if (c->checkParam("sop") || c->checkParam("all"))
			{
//				sendPrivate(p, "Ext: ");
			}
		}
	case OP_SuperModerator:
		{	// SuperModerator-level commands
			if (c->checkParam("smod") || c->checkParam("all"))
			{
//				sendPrivate(p, "Ext: ");
			}
		}
	case OP_Moderator:
		{	// Moderator-level commands
			if (c->checkParam("mod") || c->checkParam("all"))
			{
//				sendPrivate(p, "Ext: ");
			}
		}
	case OP_Limited:
		{	// Limited-level commands
		}
	case OP_Player:
		{	// Player-level commands
			if (c->checkParam("about"))
			{
				sendPrivate(p, "!about (query me about my function)");
			}
		}
	}
}

void botInfo::gotCommand(Player *p, Command *c)
{
	if (!p) return;
	if (!c) return;

	switch (p->access)
	{
	case OP_Duke:
	case OP_Baron:
	case OP_King:
	case OP_Emperor:
	case OP_RockStar:
	case OP_Q:
	case OP_God:
	case OP_Owner:
		{	// Owner-level commands
		}
	case OP_SysOp:
		{	// SysOp-level commands
		}
	case OP_SuperModerator:
		{	// SuperModerator-level commands
			if (c->check("version"))
			{
				String s = "[name:";
				s += plugin_name;
				s += "] [maker:";
				s += plugin_author;
				s += "] [build:";
				s += plugin_version;
				s += "]";
				sendPrivate(p, s);
			}
		}
	case OP_Moderator:
		{	// Moderator-level commands
		}
	case OP_Limited:
		{	// Limited-level commands
		}
	case OP_Player:
		{	// Player-level commands
			if (c->check("about"))
			{
				sendPrivate(p, "I am a plain vanilla flavored bot.  Yup, just as plain and useless as can be.");
			}
		}
	}
}

void botInfo::gotRemoteHelp(char *p, Command *c, Operator_Level l)
{
	// List commands

	if (!*c->final)
	{
		switch (l)
		{
		case OP_Duke:
		case OP_Baron:
		case OP_King:
		case OP_Emperor:
		case OP_RockStar:
		case OP_Q:
		case OP_God:
		case OP_Owner:
			{	// Owner-level commands
			}
		case OP_SysOp:
			{	// SysOp-level commands
			}
		case OP_SuperModerator:
			{	// SuperModerator-level commands
			}
		case OP_Moderator:
			{	// Moderator-level commands
			}
		case OP_Limited:
			{	// Limited-level commands
			}
		case OP_Player:
			{	// Player-level commands
			}
		}

		return;
	}

	// Specific command help

	switch (l)
	{
	case OP_Duke:
	case OP_Baron:
	case OP_King:
	case OP_Emperor:
	case OP_RockStar:
	case OP_Q:
	case OP_God:
	case OP_Owner:
		{	// Owner-level commands
		}
	case OP_SysOp:
		{	// SysOp-level commands
		}
	case OP_SuperModerator:
		{	// SuperModerator-level commands
		}
	case OP_Moderator:
		{	// Moderator-level commands
		}
	case OP_Limited:
		{	// Limited-level commands
		}
	case OP_Player:
		{	// Player-level commands
		}
	}
}

void botInfo::gotRemote(char *p, Command *c, Operator_Level l)
{
	if (!c) return;

	switch (l)
	{
	case OP_Duke:
	case OP_Baron:
	case OP_King:
	case OP_Emperor:
	case OP_RockStar:
	case OP_Q:
	case OP_God:
	case OP_Owner:
		{	// Owner-level commands
		}
	case OP_SysOp:
		{	// SysOp-level commands
		}
	case OP_SuperModerator:
		{	// SuperModerator-level commands
		}
	case OP_Moderator:
		{	// Moderator-level commands
		}
	case OP_Limited:
		{	// Limited-level commands
		}
	case OP_Player:
		{	// Player-level commands
		}
	}
}
