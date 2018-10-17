#include "HexusOpponentAsh.h"

const std::string HexusOpponentAsh::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASH";
HexusOpponentAsh* HexusOpponentAsh::instance = nullptr;

HexusOpponentAsh* HexusOpponentAsh::getInstance()
{
	if (HexusOpponentAsh::instance == nullptr)
	{
		HexusOpponentAsh::instance = new HexusOpponentAsh();
	}

	return HexusOpponentAsh::instance;
}

HexusOpponentAsh::HexusOpponentAsh() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Ash_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAsh::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.72f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentAsh::~HexusOpponentAsh()
{
}