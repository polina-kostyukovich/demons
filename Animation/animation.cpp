#include "animation.h"

Animation::Animation() {
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa1.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa2.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa3.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa4.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa5.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa6.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa5.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa4.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa3.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa2.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa1.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings1.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings2.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings3.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings4.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings5.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings4.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings3.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings2.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings1.png"));
}
