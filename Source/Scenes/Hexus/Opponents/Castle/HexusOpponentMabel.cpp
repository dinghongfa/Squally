#include "HexusOpponentMabel.h"

const std::string HexusOpponentMabel::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MABEL";
HexusOpponentMabel* HexusOpponentMabel::instance = nullptr;

HexusOpponentMabel* HexusOpponentMabel::getInstance()
{
	if (HexusOpponentMabel::instance == nullptr)
	{
		HexusOpponentMabel::instance = new HexusOpponentMabel();
	}

	return HexusOpponentMabel::instance;
}

HexusOpponentMabel::HexusOpponentMabel() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Mabel_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -40.0f),
	HexusOpponentMabel::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.56f,
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

HexusOpponentMabel::~HexusOpponentMabel()
{
}