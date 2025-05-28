#include "soundPlay.h"
#include "utility.h"


sf::Music main_music{getPath(getExecutableDir(), {"assets", "Main.ogg"}).string()};
sf::Music win_music{getPath(getExecutableDir(), {"assets", "Win.wav"}).string()};
sf::Music lose_music{getPath(getExecutableDir(), {"assets", "Lose.ogg"}).string()};