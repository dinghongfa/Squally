#include "HexusOpponentJingles.h"

const std::string HexusOpponentJingles::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JINGLES";
HexusOpponentJingles* HexusOpponentJingles::instance = nullptr;

HexusOpponentJingles* HexusOpponentJingles::getInstance()
{
	if (HexusOpponentJingles::instance == nullptr)
	{
		HexusOpponentJingles::instance = new HexusOpponentJingles();
	}

	return HexusOpponentJingles::instance;
}

HexusOpponentJingles::HexusOpponentJingles() : HexusOpponentData(
	EntityResources::Platformer_Environment_Snow_Npcs_Jingles_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentJingles::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.655f),
	HexusOpponentData::generateDeck(25, 0.655f,
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

HexusOpponentJingles::~HexusOpponentJingles()
{
}
