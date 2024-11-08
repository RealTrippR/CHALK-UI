#ifndef CHK_UTIL_H
#define CHK_UTIL_H

#include <windows.h>
#include <knownfolders.h>
#include <shlobj.h>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <chalk/lib/Universal_Includes.h>

namespace chk {
	namespace util {
		// all functions under the util namespace must be marked as inline

		inline std::string to_lower(std::string str) {
			for (int i = 0; i < str.length(); ++i) {
				str[i] = std::tolower(str[i]);
			}
			return str;
		}

		inline std::string to_upper(std::string str) {
			for (int i = 0; i < str.length(); ++i) {
				str[i] = std::toupper(str[i]);
			}
			return str;
		}

		inline std::string getAbsoluteFilepath(std::string relativeFilepath) {
			std::filesystem::path p = relativeFilepath;
			return std::filesystem::absolute(p).string();
		}

		inline std::string getEnvVar(const std::string& varName) {
			char* buffer = nullptr;
			size_t bufferSize = 0;

			// Use _dupenv_s to safely get the environment variable
			if (_dupenv_s(&buffer, &bufferSize, varName.c_str()) == 0 && buffer != nullptr) {
				std::string result(buffer);
				free(buffer);  // Free the allocated buffer after use
				return result;
			}

			return "";  // Return an empty string if the variable is not found
		}
		inline std::string getAppDataPath() {
			// Get the user's home directory
			std::string homePath = (std::filesystem::path(getEnvVar("USERPROFILE"))).string(); // For Windows

			// Construct the AppData path
			return homePath + "\\AppData\\Roaming\\"; // Standard path to Roaming
			/*
			PWSTR path = NULL;

			// Get the path to the AppData\Roaming folder
			if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path))) {
				// Get the size needed for the narrow string
				int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, path, -1, NULL, 0, NULL, NULL);

				// Create a string with the required size
				std::string ansiString(sizeNeeded, 0);

				// Perform the conversion
				WideCharToMultiByte(CP_ACP, 0, path, -1, &ansiString[0], sizeNeeded, NULL, NULL);


				CoTaskMemFree(path);  // Free the allocated memory

				return ansiString+"\\";
			}
			return "";*/
		}

		// returns true is the directory exists, returns false if not.
		inline bool checkDirectoryExistance(std::string absoluteFilePath) {
			return std::filesystem::exists(absoluteFilePath) && std::filesystem::is_directory(absoluteFilePath);
		}


		inline bool createDirectory(const std::string& absolutePath) {
			try {
				if (!std::filesystem::exists(absolutePath)) {
					if (std::filesystem::create_directory(absolutePath)) {
						return true;
					}
					else {
						std::cerr << "CHK::UTIL | Failed to create directory: " << absolutePath << std::endl;
					}
				}
				else {
					std::cerr << "CHK::UTIL | Directory already exists: " << absolutePath << std::endl;
				}
			}
			catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "CHK::UTIL | Error creating directory: " << e.what() << std::endl;
			}
			return false;
		}

		inline bool isValidKey(sf::Keyboard::Key key) {
			// Check for valid alphanumeric keys (A-Z, 0-9)
			if ((key >= sf::Keyboard::A && key <= sf::Keyboard::Z) || (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)) {
				return true;
			}

			// Check for valid punctuation and symbols
			switch (key) {
			case sf::Keyboard::Space:
			case sf::Keyboard::Period:
			case sf::Keyboard::Comma:
			case sf::Keyboard::Slash:
			case sf::Keyboard::BackSlash:
			case sf::Keyboard::Semicolon:
			case sf::Keyboard::Quote:
			case sf::Keyboard::LBracket:
			case sf::Keyboard::RBracket:
			case sf::Keyboard::Equal:
			case sf::Keyboard::Hyphen:
			case sf::Keyboard::Tilde:
				return true;
			}

			// If none of the above, the key is invalid for ASCII typing
			return false;
		}

		inline bool isShiftPressed() {
			return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
		}

		// Function to convert SFML key into ASCII character
		inline char sfKeyToAscii(sf::Keyboard::Key key, bool shiftPressed) {
			// Handle alphabetic keys
			if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
				if (shiftPressed) {
					return static_cast<char>('A' + (key - sf::Keyboard::A)); // Return uppercase letter
				}
				else {
					return static_cast<char>('a' + (key - sf::Keyboard::A)); // Return lowercase letter
				}
			}
			// Handle numeric keys (non-numpad)
			if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
				if (shiftPressed) {
					// Shifted numeric keys give special characters
					switch (key) {
					case sf::Keyboard::Num1: return '!';
					case sf::Keyboard::Num2: return '@';
					case sf::Keyboard::Num3: return '#';
					case sf::Keyboard::Num4: return '$';
					case sf::Keyboard::Num5: return '%';
					case sf::Keyboard::Num6: return '^';
					case sf::Keyboard::Num7: return '&';
					case sf::Keyboard::Num8: return '*';
					case sf::Keyboard::Num9: return '(';
					case sf::Keyboard::Num0: return ')';
					}
				}
				else {
					// Return corresponding digit
					return static_cast<char>('0' + (key - sf::Keyboard::Num0));
				}
			}
			// Handle common punctuation and symbols
			switch (key) {
			case sf::Keyboard::Space: return ' ';
			case sf::Keyboard::Period: return shiftPressed ? '>' : '.';
			case sf::Keyboard::Comma: return shiftPressed ? '<' : ',';
			case sf::Keyboard::Slash: return shiftPressed ? '?' : '/';
			case sf::Keyboard::BackSlash: return shiftPressed ? '|' : '\\';
			case sf::Keyboard::Semicolon: return shiftPressed ? ':' : ';';
			case sf::Keyboard::Quote: return shiftPressed ? '"' : '\'';
			case sf::Keyboard::LBracket: return shiftPressed ? '{' : '[';
			case sf::Keyboard::RBracket: return shiftPressed ? '}' : ']';
			case sf::Keyboard::Equal: return shiftPressed ? '+' : '=';
			case sf::Keyboard::Hyphen: return shiftPressed ? '_' : '-';
			case sf::Keyboard::Tilde: return shiftPressed ? '~' : '`';
			}

			// Return 0 for non-character keys
			return '\0';
		}

		// wide substr to work with multi-byte characters
		inline std::string wsubstr(const std::string &str, const long begin, const long length = LONG_MAX) {
			// Check for valid begin index
			if (begin < 0 || begin >= str.length()) {
				return "";
			}
			std::string s;
			for (int i = begin;  i < std::clamp(begin+length, 0l, long(str.length())); ++i) {
				s.push_back(str[i]);
			}
			return s;
		}
	}
}

#endif // !CHK_UTIL_H