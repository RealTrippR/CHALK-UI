#ifndef CHK_SOUND_H
#define CHK_SOUND_H

#include <fmod.hpp>
#include <fmod_errors.h>

namespace chk {
	class sound {
	public:
        // Constructor
        sound(const std::string& filePath)
            : system(system), soundData(nullptr), channel(nullptr) {

            M_filepath = filePath;
            system = audioManager::system;
            // Load the sound
            printf("filepath: %s\n", filePath.c_str());
            FMOD_RESULT result = system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &soundData);
            if (result != FMOD_OK) {
                // Handle error
                printf("chk::sound Constructor - FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
            }
        }

        sound() = default;

        // Destructor
        ~sound() {
            if (soundData) {
                soundData->release();
            }
        }

        void loadFromDisk(const std::string filePath) {
            M_filepath = filePath;
            system = audioManager::system;
            // Load the sound
            FMOD_RESULT result = system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &soundData);
            if (result != FMOD_OK) {
                // Handle error
                printf("loadFromDisk - FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
            }
        }

        inline void play() {
            if (channel) {
                bool buffer = isPaused();
                channel->setPaused(false);
                if (buffer) {
                    setPosition(M_PositionOnPause);
                }
            }
            else {
                if (system && soundData) {
                    system->playSound(soundData, nullptr, false, &channel);
                }
            }
        }

        inline void setPitch() {
            if (channel) {
                channel->stop();
            }
        }

        inline void setPaused(const bool paused) {
            if (channel) {
                channel->setPaused(paused);
                if (paused) {
                    M_PositionOnPause = getPosition();
                }
            }
        }

        inline bool isPaused() {
            bool isPaused = false;
            if (channel) {
                channel->getPaused(&isPaused);
            }
            return isPaused;
        }

        // this not to be confused with the pause function - it stops the entire fmod channel.
        /*inline void stop() {
            if (channel) {
                channel->stop();
            }
        }*/

        // returns true if the sound is actively loaded into a FMOD channel
        inline bool isActive() {
            bool buffer=false;
            if (channel) {
                channel->isPlaying(&buffer);
            }
            return buffer;
        }

        inline void setPitch(const float pitch) {
            if (channel) {
                channel->setPitch(pitch);
            }
        }

        inline float getPitch() {
            float pitch = 0;
            if (channel) {
                channel->getPitch(&pitch);
            }
            return pitch;
        }

        // changes the volume multiplier
        inline void setVolume(const float volume) {
            if (channel) {
                channel->setVolume(volume);
            }
        }
        
        // returns the volume multiplier
        inline bool getVolume() {
            register float volume = 0;
            if (channel) {
                channel->getVolume(&volume);
            }
            return volume;
        }

        inline void setPosition(const float milliseconds) {
            if (channel) {
                channel->setPosition(milliseconds, FMOD_TIMEUNIT_MS);
            }
        }

        // returns the current position of song in milliseconds
        inline const unsigned int getPosition() {
            unsigned int position_milli;
            if (channel) {
                channel->getPosition(&position_milli, FMOD_TIMEUNIT_MS);
            }
            return position_milli;
        }

        // returns the length of the audio in milliseconds
        inline unsigned int getLength() {
            register unsigned int length = 0;
            if (soundData) {
                soundData->getLength(&length, FMOD_TIMEUNIT_MS);
            }
            return length;
        }

        std::string getFilepath() {
            return M_filepath;
        }

        FMOD::Channel* getChannel() {
            return channel;
        }

	private:
        std::string M_filepath;
		FMOD::System* system;        // Pointer to the FMOD system
		FMOD::Sound* soundData;      // Pointer to the FMOD sound data
		FMOD::Channel* channel;      // Pointer to the FMOD channel

        float M_PositionOnPause = 0;
	};
}
#endif // !CHK_SOUND_H