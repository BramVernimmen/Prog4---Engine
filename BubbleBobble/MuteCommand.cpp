#include "MuteCommand.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

void dae::MuteCommand::Execute()
{
	ServiceLocator::GetSoundSystem().MuteOrUnMute();
}
