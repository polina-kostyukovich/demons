#include "collisions_controller.h"

void CollisionsController::CheckCollisions(
    const std::unique_ptr<Model>& model,
    const Point& old_hero_pos,
    const std::vector<Point>& old_npcs_pos,
    int window_width, int window_height) {
  CheckFireballsWithWalls(model, window_width, window_height);
  CheckHeroAndStaticObjects(model, old_hero_pos);
  CheckFireballsAndStaticObjects(model);
  CheckFireballsAndNpcs(model);
  CheckHeroAndNpcs(model, old_hero_pos, old_npcs_pos);
}

void CollisionsController::PrepareForDrawing(
    const std::unique_ptr<Model>& model) {
  auto objects = model->GetAllGameObjects();
  ResetAllRenderingLevels(objects);
  while (!AreAllRenderingLevelsNumerated(objects)) {
    NumerateAllRenderingLevels(objects);
  }
}

void CollisionsController::CheckFireballsWithWalls(
    const std::unique_ptr<Model>& model,
    int window_width, int window_height) {
  auto& fireballs = model->GetFireballs();
  for (int i = 0; i < fireballs.size(); ++i) {
    bool is_collided_with_left_wall =
        (fireballs[i].GetPosition().GetX() - constants::kFireballSize / 2.
            <= -constants::kEpsilon);
    bool is_collided_with_right_wall =
        (fireballs[i].GetPosition().GetX() + constants::kFireballSize / 2.
            - window_width >= constants::kEpsilon);
    bool is_collided_with_top_wall =
        (fireballs[i].GetPosition().GetY() - constants::kFireballSize / 2.
            <= -constants::kEpsilon);
    bool is_collided_with_bottom_wall =
        (fireballs[i].GetPosition().GetY() + constants::kFireballSize / 2.
            - window_height >= constants::kEpsilon);

    if (is_collided_with_left_wall || is_collided_with_right_wall ||
        is_collided_with_top_wall || is_collided_with_bottom_wall) {
      fireballs.erase(fireballs.begin() + i);
      --i;
    }
  }
}

void CollisionsController::CheckHeroAndStaticObjects(
    const std::unique_ptr<Model>& model,
    const Point& old_hero_position) {
  auto& objects = model->GetMap().GetObjects();
  for (const auto& object : objects) {
    CheckHeroAndStaticObject(model, old_hero_position, object);
  }
}

void CollisionsController::CheckHeroAndStaticObject(
    const std::unique_ptr<Model>& model,
    const Point& old_hero_position,
    const std::shared_ptr<StaticObject>& object) {
  auto& hero = model->GetHero();
  Point new_hero_position = hero.GetPosition();

  hero.SetPositionY(old_hero_position.GetY());
  bool has_horizontal_collision =
      hero.GetHitBox().IsCollided(object->GetHitBox());

  hero.SetPosition(new_hero_position);
  hero.SetPositionX(old_hero_position.GetX());
  bool has_vertical_collision =
      hero.GetHitBox().IsCollided(object->GetHitBox());

  hero.SetPosition(new_hero_position);
  if (has_horizontal_collision) {
    hero.SetPositionX(old_hero_position.GetX());
  }
  if (has_vertical_collision) {
    hero.SetPositionY(old_hero_position.GetY());
  }
  if (!has_horizontal_collision && !has_vertical_collision) {
    bool has_collision = hero.GetHitBox().IsCollided(object->GetHitBox());
    if (has_collision) {
      hero.SetPosition(old_hero_position);
    }
  }
}

void CollisionsController::CheckFireballsAndStaticObjects(
    const std::unique_ptr<Model>& model) {
  auto& objects = model->GetMap().GetObjects();
  auto& fireballs = model->GetFireballs();
  for (const auto& object : objects) {
    for (int i = 0; i < fireballs.size(); ++i) {
      if (!fireballs.at(i).IsBorn() &&
          fireballs.at(i).GetHitBox().IsCollided(object->GetHitBox())) {
        fireballs.erase(fireballs.begin() + i);
        --i;
      }
    }
  }
}

void CollisionsController::CheckFireballsAndNpcs(
    const std::unique_ptr<Model>& model) {
  auto& npcs = model->GetNpcController().GetNpcList();
  auto& fireballs = model->GetFireballs();
  for (int i = 0; i < npcs.size(); ++i) {
    bool is_dead = false;
    for (int j = 0; j < fireballs.size(); ++j) {
      if (!fireballs.at(j).IsBorn() &&
          fireballs.at(j).GetHitBox().IsCollided(npcs.at(i).GetHitBox())) {
        is_dead = true;
        fireballs.erase(fireballs.begin() + j);
        --j;
        break;
      }
    }
    if (is_dead) {
      npcs.erase(npcs.begin() + i);
      --i;
    }
  }
}

void CollisionsController::CheckHeroAndNpcs(
    const std::unique_ptr<Model>& model,
    const Point& old_hero_pos,
    const std::vector<Point>& old_npcs_pos) {
  auto& hero = model->GetHero();
  auto& npcs = model->GetNpcController().GetNpcList();
  for (int i = 0; i < npcs.size(); ++i) {
    if (!hero.GetHitBox().IsCollided(npcs[i].GetHitBox())) {
      npcs[i].SetAttackingStatus(false);
      npcs[i].SetAttackTickCounter(0);
      continue;
    }

    if (!npcs[i].IsAttacking()) {
      npcs[i].SetAttackingStatus(true);
      npcs[i].SetAttackTickCounter(0);
    }

    npcs[i].IncrementAttackTickCounter();
    if (npcs[i].GetAttackTickCounter() / constants::kNpcAttackSpeed ==
        constants::kNpcAttackTick) {
      npcs[i].AttackHero(&model->GetHero());
    }

    if (npcs[i].GetAttackTickCounter() / constants::kNpcAttackTick >
        constants::kNpcAttackSpeed) {
      npcs[i].SetAttackTickCounter(0);
    }

    npcs[i].SetPosition(old_npcs_pos[i]);

    Point current_hero_pos = hero.GetPosition();

    hero.SetPosition(old_hero_pos);
    hero.SetPositionX(current_hero_pos.GetX());

    bool has_horizontal_collision =
        (hero.GetHitBox().IsCollided(npcs[i].GetHitBox()));

    hero.SetPosition(old_hero_pos);
    hero.SetPositionY(current_hero_pos.GetY());

    bool has_vertical_collision =
        (hero.GetHitBox().IsCollided(npcs[i].GetHitBox()));
    hero.SetPosition(old_hero_pos);

    if (!has_horizontal_collision) {
      hero.SetPositionX(current_hero_pos.GetX());
    }

    if (!has_vertical_collision) {
      hero.SetPositionY(current_hero_pos.GetY());
    }
  }
}

void CollisionsController::ResetAllRenderingLevels(
    const std::vector<GameObject*>& all_objects) {
  for (auto& object : all_objects) {
    object->SetRenderingLevel(0);
  }
}

bool CollisionsController::AreAllRenderingLevelsNumerated(
    const std::vector<GameObject*>& all_objects) const {
  for (int i = 0; i < all_objects.size(); ++i) {
    for (int j = 0; j < all_objects.size(); ++j) {
      if (i == j) continue;

      if (dynamic_cast<Fireball*>(all_objects[i]) != nullptr &&
          dynamic_cast<Hero*>(all_objects[j]) != nullptr) {
        if (all_objects.at(i)->GetHitBox().IsCollided(
            all_objects.at(j)->GetPictureAboveHitBox()) &&
            all_objects.at(i)->GetRenderingLevel() <=
                all_objects.at(j)->GetRenderingLevel()) {
          return false;
        }
        continue;
      }

      if (dynamic_cast<Fireball*>(all_objects[j]) != nullptr &&
          dynamic_cast<Hero*>(all_objects[i]) != nullptr) {
        if (all_objects.at(j)->GetHitBox().IsCollided(
            all_objects.at(i)->GetPictureAboveHitBox()) &&
            all_objects.at(j)->GetRenderingLevel() <=
                all_objects.at(i)->GetRenderingLevel()) {
          return false;
        }
        continue;
      }

      if (all_objects.at(i)->GetHitBox().IsCollided(
          all_objects.at(j)->GetPictureAboveHitBox()) &&
          all_objects.at(i)->GetRenderingLevel() >=
              all_objects.at(j)->GetRenderingLevel()) {
        return false;
      }
    }
  }
  return true;
}

void CollisionsController::NumerateAllRenderingLevels(
    const std::vector<GameObject*>& all_objects) {
  for (int i = 0; i < all_objects.size(); ++i) {
    for (int j = 0; j < all_objects.size(); ++j) {
      if (i == j) continue;

      if (dynamic_cast<Fireball*>(all_objects[i]) != nullptr &&
          dynamic_cast<Hero*>(all_objects[j]) != nullptr) {
        if (all_objects.at(i)->GetHitBox().IsCollided(
            all_objects.at(j)->GetPictureAboveHitBox()) &&
            all_objects.at(i)->GetRenderingLevel() <=
                all_objects.at(j)->GetRenderingLevel()) {
          all_objects.at(i)->SetRenderingLevel(
              all_objects.at(j)->GetRenderingLevel() + 1);
        }
        continue;
      }

      if (all_objects.at(i)->GetHitBox().IsCollided(
          all_objects.at(j)->GetPictureAboveHitBox()) &&
          all_objects.at(i)->GetRenderingLevel() >=
              all_objects.at(j)->GetRenderingLevel()) {
        all_objects.at(j)->SetRenderingLevel(
            all_objects.at(i)->GetRenderingLevel() + 1);
      }
    }
  }
}
