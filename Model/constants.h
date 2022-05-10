#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

namespace constants {
const long double kEpsilon = 1e-9;
const long double kClose = 3;
const long double kMaxDistance = 1e9;
const long double kDirectionStep = 0.2;

const int kTickTime = 20;
const long double kHeroStep = 8;
const long double kNpcStep = 5;
const long double kFireballSpeed = 20;

const int kHeroSpeedCoefficient = 3;
const int kNumberAnimation = 11;
const int kHeroSize = 120;
const int kNpcSize = 120;
const int kFireballSize = 60;
const int kLavaSize = 60;
const int kWallSize = 30;
const int kMiddleAnimation = 6;

const int kFireballSpeedCoefficient = 5;
const int kNumberBorn = 4;
const int kNumberFireBall = 7;

const int kNumberFight = 3;
const int kNumberNpc = 4;
const int kNumberEquallySidedNpc = 7;
const int kNpcSpeedCoefficient = 5;

const long double kTorsoPercentage = 1.65;
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
