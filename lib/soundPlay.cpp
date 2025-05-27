#include "soundPlay.h"
#include "utility.h"
#include "config.h"


sf::Music main_music{getPath(cwd, {"assets", "Main.ogg"}).string()};
sf::Music win_music{getPath(cwd, {"assets", "Win.wav"}).string()};
sf::Music lose_music{getPath(cwd, {"assets", "Lose.ogg"}).string()};