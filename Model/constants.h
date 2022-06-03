#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

namespace constants {
const long double kEpsilon = 1e-9;
const long double kCollisionEpsilon = 0.5;
const long double kClose = 3;
const long double kMaxDistance = 1e9;
const long double kDirectionStep = 0.2;

const int kTickTime = 20;
const long double kHeroStep = 9;
const long double kNpcStep = 7;
const long double kFireballSpeed = 20;

const int kHeroSize = 120;
const int kNpcSize = 120;
const int kFireballSize = 60;
const int kLavaSize = 60;
const int kWallSize = 30;
const int kHealthSize = 30;
const int kKnifeSize = 30;

const int kFireballSpeedCoefficient = 5;
const int kNpcSpeedCoefficient = 5;
const int kHeroSpeedCoefficient = 3;

const int kMaxCountOfNpc = 15;
const int kNumberOfOperations = 300;
const int kNumberOfBornFireballs = 4;
const int kNumberOfAnimation = 11;
const int kNumberOfFireBall = 7;
const int kNumberOfRaisingHandNpc = 3;
const int kNumberOfFightingNpc = 2 * kNumberOfRaisingHandNpc;
const int kNumberOfNpc = 4;
const int kNumberOfEquallySidedNpc = kNumberOfFightingNpc + kNumberOfNpc;

const int kMiddleAnimation = 6;
const long double kTorsoPercentage = 0.105;

const long double kHeroHitBoxHeightCoefficient = 0.4;
const long double kBoilerHitBoxHeightCoefficient = 0.55;
const long double kNpcHitBoxHeightCoefficient = 0.5;
const long double kNpcHitBoxWidthCoefficient = 0.4;
const long double kFireballHitBoxHeightCoefficient = 0.4;
const long double kFireballHitBoxWidthCoefficient = 0.6;
const long double kHeroHealthBarWidthCoefficient = 0.4;
const long double kProgressBarWidthCoefficient = 0.5;
const long double kProgressBarIndentionCoefficient = 0.01;

const long double kHeroHealthPoints = 300;

const long double kHeroHealthBarHeight = 20;
const long double kProgressBarHeight = 20;

const int kGoalKills = 20;
const long double kLavaDamage = 0.3;
const long double kNpcDamage = 5;

const int kStandingTicksToGetLavaDamage = 50;

const int kTicksBetweenNpcAppearance = 100;

const long double kUpperWallCollisionConstant = 30;
const int kIndentionAlongXAxis = 50;
const int kIndentionAlongYAxis = 5;
const double kHealthKnifeIndention = 5.0;

}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
