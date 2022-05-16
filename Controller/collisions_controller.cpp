#include "collisions_controller.h"

void CollisionsController::CheckHeroAndStaticObjects(
    Hero* hero,
    const Point& old_hero_position,
    const std::vector<std::shared_ptr<StaticObject>>& objects) {
  for (const auto& object : objects) {
    CheckHeroAndStaticObject(hero, old_hero_position, object);
  }
}

void CollisionsController::CheckHeroAndStaticObject(
    Hero* hero,
    const Point& old_hero_position,
    const std::shared_ptr<StaticObject>& object) {
  Point new_hero_position = hero->GetPosition();

  hero->SetPositionY(old_hero_position.GetY());
  bool has_horizontal_collision =
      hero->GetHitBox().IsCollided(object->GetHitBox());

  hero->SetPosition(new_hero_position);
  hero->SetPositionX(old_hero_position.GetX());
  bool has_vertical_collision =
      hero->GetHitBox().IsCollided(object->GetHitBox());

  hero->SetPosition(new_hero_position);
  if (has_horizontal_collision) {
    hero->SetPositionX(old_hero_position.GetX());
  }
  if (has_vertical_collision) {
    hero->SetPositionY(old_hero_position.GetY());
  }
  if (!has_horizontal_collision && !has_vertical_collision) {
    bool has_collision = hero->GetHitBox().IsCollided(object->GetHitBox());
    if (has_collision) {
      hero->SetPosition(old_hero_position);
    }
  }

  bool has_top_intersection =
      hero->GetHitBox().IsCollided(object->GetTopHitBox());
  object->SetIsOverHero(has_top_intersection);
}

void CollisionsController::CheckFireballsAndStaticObjects(
    std::vector<Fireball>* fireballs,
    const std::vector<std::shared_ptr<StaticObject>>& objects) {
  for (const auto& static_object : objects) {
    CheckFireballsAndStaticObject(fireballs, static_object);
  }
}

void CollisionsController::CheckFireballsAndStaticObject(
    std::vector<Fireball>* fireballs,
    const std::shared_ptr<StaticObject>& object) {
  for (int i = 0; i < fireballs->size(); ++i) {
    if (!fireballs->at(i).IsBorn() &&
        (fireballs->at(i).GetHitBox().IsCollided(object->GetHitBox()) ||
        fireballs->at(i).GetHitBox().IsCollided(object->GetTopHitBox()))) {
      fireballs->erase(fireballs->begin() + i);
      --i;
    }
  }
}

void CollisionsController::CheckFireballsAndNpcs(
    std::vector<Fireball>* fireballs,
    const std::vector<Npc>& npcs) {
  for (const auto& object : npcs) {
    CheckFireballsAndNpc(fireballs, object);
  }
}

void CollisionsController::CheckFireballsAndNpc(
    std::vector<Fireball>* fireballs,
    const Npc& npc) {
  for (int i = 0; i < fireballs->size(); ++i) {
    if (!fireballs->at(i).IsBorn() &&
        fireballs->at(i).GetHitBox().IsCollided(npc.GetHitBox())) {
      fireballs->erase(fireballs->begin() + i);
      --i;
    }
  }
}
void CollisionsController::CheckHeroAndNpcs(
    Hero* hero,
    std::vector<Npc>* npcs,
    const Point& old_hero_pos,
    const std::vector<Point>& old_npcs_pos) {
  for (int i = 0; i < npcs->size(); ++i) {
    auto& npc = npcs->at(i);
    CheckHeroAndNpc(hero, &npc, old_hero_pos, old_npcs_pos[i]);
  }
}

void CollisionsController::CheckHeroAndNpc(Hero* hero,
                                           Npc* npc,
                                           const Point& old_hero_pos,
                                           const Point& old_npc_pos) {
  if (hero->GetHitBox().IsCollided(npc->GetHitBox())) {
    Vector2D repulsion_direction(hero->GetPosition(), old_npc_pos);
    repulsion_direction.Normalize();

    Point new_npc_pos = npc->GetPosition()
        + (constants::kNpcRepulsionCoefficient * repulsion_direction);
    npc->SetPosition(new_npc_pos);
  }
}
