#include "GiveScoreCommand.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::GiveScoreCommand::GiveScoreCommand(GameObject* pGameObject, int score)
	: m_pGameObject{pGameObject}
	, m_ScoreValue{score}
{
	m_pScore = pGameObject->GetComponent<ScoreComponent>().get();
}

void dae::GiveScoreCommand::Execute()
{
	m_pScore->AddScore(m_ScoreValue);
}
