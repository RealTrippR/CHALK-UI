#ifndef CHK_INSTANCED_SOUND_MANGER_H
#define CHK_INSTANCED_SOUND_MANGER_H

#include <fmod.hpp>
#include <fmod_errors.h>

namespace chk {
	namespace InstancedSoundManager {

		std::vector<FMOD::Sound*> sounds;
		std::map<std::string, int> soundMap; // first is filename; second is vector index
		std::map<int, int> referenceMap; // first is vector index; second is reference count

		/*void playSoundFromHandle() {

		}

		void pauseSoundFromHandle() {

		}

		void stopSoundFromHandle() {

		}*/


		// Returns a pointer to the FMOD::Sound associated with the filepath.
		// If it's not already in the sound map, a new sound is created and added to the map.
		FMOD::Sound* getSoundFromFilename(const std::string &absoluteFilepath) {
			if (soundMap.find(absoluteFilepath) == soundMap.end()) {
				// this sound does not yet exist, create it
				FMOD::Sound* soundData = NULL;
				FMOD_RESULT result = audioManager::system->createSound(absoluteFilepath.c_str(), FMOD_DEFAULT, 0, &soundData);
				sounds.push_back(soundData);
				if (result != FMOD_OK) {
					// Handle error
					std::cerr << "FMOD error: (%d) %s\n", result, FMOD_ErrorString(result);
					return nullptr;
				}
				soundMap[absoluteFilepath] = sounds.size() - 1;
				referenceMap[sounds.size() - 1]++;

			}

			return sounds[soundMap[absoluteFilepath]];
		}

		void decrementSoundReferenceCount(const std::string &soundFilepath) {
			auto it = soundMap.find(soundFilepath);
			if (it == soundMap.end()) {
				//std::cerr << "Attempted to decrement reference count of the sound: " << soundFilepath << ", but it was not found in the soundMap!";
				return;
			}
			const int vecIndex = it->second;
			referenceMap[vecIndex]--;

			if (referenceMap[vecIndex] <= 0) {
				// Remove sound from vector
				sounds[vecIndex]->release();
				sounds.erase(sounds.begin() + vecIndex);
				referenceMap.erase(vecIndex);

				// Update indices in maps
				for (auto& pair : soundMap) {
					if (pair.second > vecIndex) {
						pair.second--;
					}
				}
				soundMap.erase(it);
			}
		}
	}
}

#endif // !CHK_INSTANCED_SOUND_MANGER_H