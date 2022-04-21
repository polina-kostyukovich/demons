#include "animation.h"

Animation::Animation() {
  Q_INIT_RESOURCE(resources);
  lava=QPixmap(":Picture/StaticObject/lava.png");
  horizontal_wall=QPixmap(":Picture/StaticObject/horizontal_wall.png");
  vertical_wall=QPixmap(":Picture/StaticObject/vertical_wall.png");
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa1.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa2.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa3.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa4.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa5.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa6.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa5.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa4.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa3.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa2.png"));
  hero_pixmaps.emplace_back(QPixmap(":Picture/Hero/demonessa1.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings1.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings2.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings3.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings4.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings5.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings6.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings5.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings4.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings3.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings2.png"));
  wings_pixmaps.emplace_back(QPixmap(":Picture/Wings/wings1.png"));
}
