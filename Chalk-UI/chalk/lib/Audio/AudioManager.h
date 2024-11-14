#ifndef CHK_AUDIO_MANAGER_H
#define CHK_AUDIO_MANAGER_H

#include <fmod.hpp>
#include <fmod_errors.h>

namespace chk {
	namespace audioManager {       


        #define MAX_AUDIO_CHANNELS 512

        FMOD::System* system;

        // Returns 1 if successful, returns -1 if initialization fails
        inline int init() {
            FMOD_RESULT result;

            result = FMOD::System_Create(&system);
            if (result != FMOD_OK) {
                return -1;  // initialization failed
            }
            
            result = system->init(MAX_AUDIO_CHANNELS, FMOD_INIT_NORMAL, 0);

            if (result != FMOD_OK) {
                return -1;  // initialization failed
            }

            return 1; // initialization successful
        }

        // This should always be called when the program quits.
        inline void cleanup() {
            if (system) {
                system->close();
                system->release();
                system = nullptr;
            }
        }
	}
}

#endif // !CHK_AUDIO_MANAGER_H
