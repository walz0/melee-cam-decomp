
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

    // hard limits for positive / negative
    float float_max = 3.402823466385289e+38;
    float float_min = -3.402823466385289e+38;

    float override_offset = 1.0f;
    subjects_enabled = 0;

    in_f29 = float_min;
    in_f31 = float_max;

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
            dVar4 = Stage_GetCameraLimitBottom();
            cam_limit = cam_bottom_override;
            if (cam_limit < dVar4) {
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
            dVar4 = Stage_GetCameraLimitBottom();
            cam_limit = cam_bottom_override;
            if (cam_limit < dVar4) {
              cam_limit = Stage_GetCameraLimitBottom();
            }
            local_6c.y = cam_limit;
          }
        }
        cam_limit = local_6c.x;
        if (cam_limit < float.MAX) {
          in_f31 = cam_limit;
        }
        if (cam_limit > float.MIN) {
          in_f29 = cam_limit;
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
        if (cam_limit < in_f31) {
          in_f31 = cam_limit;
        }
        if (in_f29 < cam_limit) {
          in_f29 = cam_limit;
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
        if (cam_limit < dVar34) {
          dVar34 = cam_limit;
        }
        if (dVar125 < cam_limit) {
          dVar125 = cam_limit;
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
        if (cam_limit < dVar34) {
          dVar34 = cam_limit;
        }
        if (dVar125 < cam_limit) {
          dVar125 = cam_limit;
        }
      }
    }
  }
                    /* default bounds */
  if (subjects_enabled == 0) {
    Stage_GetCameraOffset2D(&cam_offset);
    in_f31 = (cam_offset.x - 40.0);
    dVar34 = (cam_offset.y - 40.0);
    in_f29 = (cam_offset.x + 40.0);
    dVar125 = (cam_offset.y + 40.0);
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
  bounds->x_min = in_f31;
  bounds->y_min = (dVar34 - (z_clamp? * 390.0 + 10.0));
  bounds->x_max = in_f29;
  bounds->y_max = dVar125;
  bounds->subjects = subjects_enabled;
  bounds->z_pos = z_pos;
  return;
}