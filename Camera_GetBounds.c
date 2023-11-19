void Camera_GetBounds(CameraBounds *bounds,CameraMovement *movement)
{
  float fVar1;
  float fVar2;
  bool enabled;
  uint subject_cam_bounds;
  uint subjects_enabled;
  double dVar3;
  double cam_limit;
  double dVar4;
  double dVar5;
  double dVar125;
  double in_f29;
  double dVar34;
  double in_f31;
  float local_a0;
  float fStack_9c;
  float local_98;
  float fStack_94;
  float local_90;
  float fStack_8c;
  float cam_bottom_override;
  float bottom_override_delta;
  float cam_bottom_override;
  float bottom_override_delta;
  Vec cam_offset;
  Vec local_6c;
  Vec local_60;
  CmSubject *subject;
  
  subjects_enabled = 0;
  for (subject = UsedCmSubjectPoolHead; subject != (CmSubject *)0x0; subject = subject->prev) {
    enabled = CmSubject_IsEnabled(subject);
                    /* increments until a player is not in bounds \
                       camera only changes bounds if a subject is out of bounds \
                       this is why float array has 5 slots because the first one is some kind of
                       base case */
    if (enabled) {
      subjects_enabled = subjects_enabled + 1;
    }
  }
  if (subjects_enabled != 0) {
    if (subjects_enabled < 5) {
                    /* get fixedness value for number of player slots */
      subject_fixedness = SubjectCountFixedness[subjects_enabled];
    }
    else {
      subject_fixedness = 1.0;
    }
    float stage_fixedness = GetStageFixedness?();

    float fixedness = (stage_fixedness * subject_fixedness);


    float override_offset = 1.0f;
    subjects_enabled = 0;

    // initialize values
    float y_min = float.MAX; // dVar34
    float y_max = float.MIN; // dVar125
    float x_max = float.MIN; // f29
    float x_min = float.MAX; // f31

    for (subject = UsedCmSubjectPoolHead; subject != (CmSubject *)0x0; subject = subject->prev) {
      enabled = CmSubject_IsEnabled(subject);
      if (enabled) {
        subjects_enabled = subjects_enabled + 1;

        local_60.x = (subject->focus).x;
        local_60.y = (subject->focus).y;
        local_60.z = (subject->focus).z;

        local_6c.x = (subject->focus).x;
        local_6c.y = (subject->focus).y;
        local_6c.z = (subject->focus).z;

        subject_cam_bounds = CmSubject_IsInCameraBounds(&local_60,0);
        if (subject_cam_bounds != 0) {
          GetCameraBottomOverride(&cam_bottom_override,&bottom_override_delta);
          cam_bottom_override = (cam_bottom_override + override_offset);
          if ((subject_cam_bounds & 0b00000100) != 0) {
            cam_limit = Stage_GetCameraLimitLeft();
            local_60.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00001000) != 0) {
            cam_limit = Stage_GetCameraLimitRight();
            local_60.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000001) != 0) {
            cam_limit = Stage_GetCameraLimitTop();
            local_60.y = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000010) != 0) {
            float cam_limit_bottom = Stage_GetCameraLimitBottom();
            cam_limit = cam_bottom_override;
            if (cam_limit < cam_limit_bottom) {
              cam_limit = Stage_GetCameraLimitBottom();
            }
            local_60.y = cam_limit;
          }
        }
        // focus x position + left bounds * fixedness
        local_6c.x = ((subject->default_bounds).left * fixedness + local_60.x);
        // check bounds again in case this extends past the limit
        subject_cam_bounds = CmSubject_IsInCameraBounds(&local_6c,0);
        if (subject_cam_bounds != 0) {
          GetCameraBottomOverride(&cam_bottom_override,&bottom_override_delta);
          cam_bottom_override = (cam_bottom_override + override_offset);
          if ((subject_cam_bounds & 0b00000100) != 0) {
            cam_limit = Stage_GetCameraLimitLeft();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00001000) != 0) {
            cam_limit = Stage_GetCameraLimitRight();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000001) != 0) {
            cam_limit = Stage_GetCameraLimitTop();
            local_6c.y = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000010) != 0) {
            cam_limit_bottom = Stage_GetCameraLimitBottom();
            cam_limit = cam_bottom_override;
            if (cam_limit < cam_limit_bottom) {
              cam_limit = Stage_GetCameraLimitBottom();
            }
            local_6c.y = cam_limit;
          }
        }
        cam_limit = local_6c.x;
        if (cam_limit < float.MAX) {
          x_min = cam_limit;
        }
        if (cam_limit > float.MIN) {
          x_max = cam_limit;
        }
        local_6c.x = ((subject->default_bounds).right * dVar5 + local_60.x);
        subject_cam_bounds = CmSubject_IsInCameraBounds(&local_6c,0);
        if (subject_cam_bounds != 0) {
          GetCameraBottomOverride(&local_90,&fStack_8c);
          local_90 = (local_90 + dVar3);
          if ((subject_cam_bounds & 0b00000100) != 0) {
            cam_limit = Stage_GetCameraLimitLeft();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00001000) != 0) {
            cam_limit = Stage_GetCameraLimitRight();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000001) != 0) {
            cam_limit = Stage_GetCameraLimitTop();
            local_6c.y = cam_limit;
          }
          if (((subject_cam_bounds & 0b00000010) != 0) &&
             (cam_limit = Stage_GetCameraLimitBottom(), local_90 < cam_limit)) {
            Stage_GetCameraLimitBottom();
          }
        }
        cam_limit = local_6c.x;
        if (cam_limit < x_min) {
          x_min = cam_limit;
        }
        if (x_max < cam_limit) {
          x_max = cam_limit;
        }
        local_6c.y = ((subject->default_bounds).bottom * dVar5 + local_60.y);
        subject_cam_bounds = CmSubject_IsInCameraBounds(&local_6c,0);
        if (subject_cam_bounds != 0) {
          GetCameraBottomOverride(&local_98,&fStack_94);
          local_98 = (local_98 + dVar3);
          if ((subject_cam_bounds & 0b00000100) != 0) {
            cam_limit = Stage_GetCameraLimitLeft();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00001000) != 0) {
            cam_limit = Stage_GetCameraLimitRight();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000001) != 0) {
            cam_limit = Stage_GetCameraLimitTop();
            local_6c.y = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000010) != 0) {
            dVar4 = Stage_GetCameraLimitBottom();
            cam_limit = local_98;
            if (cam_limit < dVar4) {
              cam_limit = Stage_GetCameraLimitBottom();
            }
            local_6c.y = cam_limit;
          }
        }
        cam_limit = local_6c.y;
        if (cam_limit < y_min) {
          y_min = cam_limit;
        }
        if (y_max < cam_limit) {
          y_max = cam_limit;
        }
        local_6c.y = ((subject->default_bounds).top * dVar5 + local_60.y);
        subject_cam_bounds = CmSubject_IsInCameraBounds(&local_6c,0);
        if (subject_cam_bounds != 0) {
          GetCameraBottomOverride(&local_a0,&fStack_9c);
          local_a0 = (local_a0 + dVar3);
          if ((subject_cam_bounds & 0b00000100) != 0) {
            cam_limit = Stage_GetCameraLimitLeft();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00001000) != 0) {
            cam_limit = Stage_GetCameraLimitRight();
            local_6c.x = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000001) != 0) {
            cam_limit = Stage_GetCameraLimitTop();
            local_6c.y = cam_limit;
          }
          if ((subject_cam_bounds & 0b00000010) != 0) {
            dVar4 = Stage_GetCameraLimitBottom();
            cam_limit = local_a0;
            if (cam_limit < dVar4) {
              cam_limit = Stage_GetCameraLimitBottom();
            }
            local_6c.y = cam_limit;
          }
        }
        cam_limit = local_6c.y;
        if (cam_limit < y_min) {
          y_min = cam_limit;
        }
        if (y_max < cam_limit) {
          y_max = cam_limit;
        }
      }
    }
  }
                    /* default bounds */
  if (subjects_enabled == 0) {
    Stage_GetCameraOffset2D(&cam_offset);
    x_min = (cam_offset.x - 40.0);
    y_min = (cam_offset.y - 40.0);
    x_max = (cam_offset.x + 40.0);
    y_max = (cam_offset.y + 40.0);
  }

  float z_pos = (movement->position).z;
  float z_clamp;
  if (z_pos < 0.0) {
    z_pos = -z_pos;
  }
  if (z_pos >= 80.0) {
    if (z_pos <= 5000.0) {
      z_clamp? = (z_pos - 80.0) / 4920.0;
    }
    else {
      z_clamp? = 1.0;
    }
  }
  else {
    z_clamp? = 0.0;
  }
  bounds->x_min = x_min;
  bounds->y_min = (y_min - (z_clamp? * 390.0 + 10.0));
  bounds->x_max = x_max;
  bounds->y_max = y_max;
  bounds->subjects = subjects_enabled;
  bounds->z_pos = z_pos;
  return;
}
