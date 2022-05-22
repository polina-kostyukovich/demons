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
      hero->GetHitBox().IsCollided(object->GetPictureAboveHitBox());
  if (has_top_intersection) {
    hero->SetRenderingLevel(object->GetRenderingLevel() + 1);
  }
  if (object->GetHitBox().IsCollided(hero->GetPictureAboveHitBox())) {
    object->SetRenderingLevel(hero->GetRenderingLevel() + 1);
  }
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
    if (fireballs->at(i).GetHitBox().IsCollided(object->GetPictureAboveHitBox())) {
      fireballs->at(i).SetRenderingLevel(object->GetRenderingLevel() + 1);
    }

    if (!fireballs->at(i).IsBorn() &&
        fireballs->at(i).GetHitBox().IsCollided(object->GetHitBox())) {
      fireballs->erase(fireballs->begin() + i);
      --i;
    }
  }
}

void CollisionsController::CheckFireballsAndNpcs(
    std::vector<Fireball>* fireballs,
    std::vector<Npc>* npcs) {
  for (int i = 0; i < npcs->size(); ++i) {
    bool is_dead = false;
    for (int j = 0; j < fireballs->size(); ++j) {
      if (!fireballs->at(j).IsBorn() &&
          fireballs->at(j).GetHitBox().IsCollided(npcs->at(i).GetHitBox())) {
        is_dead = true;
        fireballs->erase(fireballs->begin() + j);
        --j;
        break;
      }
    }
    if (is_dead) {
      npcs->erase(npcs->begin() + i);
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
    CheckHeroAndNpc(hero, &npcs->at(i), old_hero_pos, old_npcs_pos.at(i));
  }
}

void CollisionsController::CheckHeroAndNpc(Hero* hero,
                                           Npc* npc,
                                           const Point& old_hero_pos,
                                           const Point& old_npc_pos) {
  if (hero->GetHitBox().IsCollided(npc->GetHitBox())) {
    npc->SetPosition(old_npc_pos);

    Point current_hero_pos = hero->GetPosition();

    hero->SetPosition(old_hero_pos);
    hero->SetPositionX(current_hero_pos.GetX());

    bool has_horizontal_collision =
        (hero->GetHitBox().IsCollided(npc->GetHitBox()));

    hero->SetPosition(old_hero_pos);
    hero->SetPositionY(current_hero_pos.GetY());

    bool has_vertical_collision =
        (hero->GetHitBox().IsCollided(npc->GetHitBox()));
    hero->SetPosition(old_hero_pos);

    if (!has_horizontal_collision) {
      hero->SetPositionX(current_hero_pos.GetX());
    }

    if (!has_vertical_collision) {
      hero->SetPositionY(current_hero_pos.GetY());
    }
  }

  if (hero->GetHitBox().IsCollided(npc->GetPictureAboveHitBox())) {
    hero->SetRenderingLevel(npc->GetRenderingLevel() + 1);
  }

  if (npc->GetHitBox().IsCollided(hero->GetPictureAboveHitBox())) {
    npc->SetRenderingLevel(hero->GetRenderingLevel() + 1);
  }
}

void CollisionsController::CheckNpcAndStaticObjects(
    std::vector<Npc>* npcs,
    const std::vector<std::shared_ptr<StaticObject>>& objects) {
  for (auto npc : *npcs) {
    for (auto object : objects) {
      CheckNpcAndStaticObject(&npc, object);
    }
  }
}

void CollisionsController::CheckNpcAndStaticObject(
     Npc* npc,
    std::shared_ptr<StaticObject> object) {
  if (npc->GetHitBox().IsCollided(object->GetPictureAboveHitBox())) {
    npc->SetRenderingLevel(object->GetRenderingLevel() + 1);
  }
  if (object->GetHitBox().IsCollided(npc->GetPictureAboveHitBox())) {
    object->SetRenderingLevel(npc->GetRenderingLevel() + 1);
  }
}
