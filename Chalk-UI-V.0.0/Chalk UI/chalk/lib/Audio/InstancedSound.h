#ifndef CHK_INSTANCED_SOUND
#define CHK_INSTANCED_SOUND

#include <fmod.hpp>
#include <fmod_errors.h>

namespace chk {
	class InstancedSound {
	public:

		// Destructor
		~InstancedSound() {
			if (M_filepath.length() != 0) {
				InstancedSoundManager::decrementSoundReferenceCount(M_filepath);
			}
		}

		void pause() {
			if (M_channel) {
				M_channel->setPaused(true);
			}
		}

		void unpause() {
			if (M_channel) {
				M_channel->setPaused(false);
			}
		}

		void setSoundFilepath(std::string filepath) {
			if (M_filepath != filepath) {
				if (M_filepath.length() != 0) {
					InstancedSoundManager::decrementSoundReferenceCount(M_filepath);
				}
			}
			M_soundRef = InstancedSoundManager::getSoundFromFilename(filepath);
		}

		std::string getSoundFilepath() {
			return M_filepath;
		}

	private:
		FMOD::Sound* M_soundRef = NULL;
		FMOD::Channel* M_channel = NULL;
		std::string M_filepath;
	};
}

#endif // !CHK_INSTANCED_SOUND