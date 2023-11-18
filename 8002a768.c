void zz_002a768_(CameraMovement *movement,int param_2)
{
  byte cam_type?;
  uint uVar1;
  bool bVar2;
  double dVar3;
  double dVar8;
  double dVar4;
  double in_f3;
  double dVar5;
  double dVar7;
  float fVar6;
  Vec local_90;
  Vec local_84;
  Vec local_78;
  Vec local_6c;
  Vec local_60;
  float zero;
  float zero2;
  float minus_1;
  Vec interest_delta?;
  
  uVar1 = 0;
  zero = 0.0;
  zero2 = 0.0;
                    /* get half of angle in radians for tan */
  dVar7 = (movement->target_fov * deg2rad * 0.5);
  minus_1 = -1.0;
  VectorSubtract(&movement->target_interest,&movement->target_position,&interest_delta?);
  VectorNormalize(&interest_delta?);
                    /* get vertical angle */
  fVar6 = atan2(interest_delta?.y,-interest_delta?.z);
  dVar5 = fVar6;
                    /* get horizontal angle */
  dVar4 = -interest_delta?.z;
  fVar6 = atan2(-interest_delta?.x,-interest_delta?.z);
  dVar3 = fVar6;
  local_84.x = zero;
  local_84.y = zero2;
  local_84.z = minus_1;
  local_78.x = zero;
  local_78.y = zero2;
  local_78.z = minus_1;
  local_6c.x = zero;
  local_6c.y = zero2;
  local_6c.z = minus_1;
  local_60.x = zero;
  local_60.y = zero2;
  local_60.z = minus_1;
                    /* horizontal angle, -interest_delta?.z,  */
  FOVZoomHandler?\(dVar7,dVar4,in_f3,&local_60,1);
  FOVZoomHandler?\(dVar7,dVar4,in_f3,&local_60,2);
  local_60.x = local_60.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&local_60);
  FOVZoomHandler?\(dVar5,dVar4,in_f3,&local_60,1);
  FOVZoomHandler?\(dVar3,dVar4,in_f3,&local_60,2);
  dVar4 = local_60.z;
  bVar2 = -0.001000000047497451 <= dVar4;
  if (!bVar2) {
    fVar6 = (-(movement->target_position).z / dVar4);
    local_60.x = local_60.x * fVar6;
    local_60.y = local_60.y * fVar6;
    local_60.z = local_60.z * fVar6;
    VectorAdd(&local_60,&movement->target_position);
  }
  FOVZoomHandler?\(dVar7,dVar4,in_f3,&local_6c,1);
  dVar8 = -dVar7;
  FOVZoomHandler?\(dVar8,dVar4,in_f3,&local_6c,2);
  local_6c.x = local_6c.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&local_6c);
  FOVZoomHandler?\(dVar5,dVar4,in_f3,&local_6c,1);
  FOVZoomHandler?\(dVar3,dVar4,in_f3,&local_6c,2);
  dVar4 = local_6c.z;
  if (-0.001000000047497451 <= dVar4) {
    cam_type? = 2;
  }
  else {
    fVar6 = (-(movement->target_position).z / dVar4);
    local_6c.x = local_6c.x * fVar6;
    local_6c.y = local_6c.y * fVar6;
    local_6c.z = local_6c.z * fVar6;
    VectorAdd(&local_6c,&movement->target_position);
    cam_type? = bVar2;
  }
  FOVZoomHandler?\(dVar8,dVar4,in_f3,&local_78,1);
  FOVZoomHandler?\(dVar7,dVar4,in_f3,&local_78,2);
  local_78.x = local_78.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&local_78);
  FOVZoomHandler?\(dVar5,dVar4,in_f3,&local_78,1);
  FOVZoomHandler?\(dVar3,dVar4,in_f3,&local_78,2);
  dVar4 = local_78.z;
  if (-0.001000000047497451 <= dVar4) {
    cam_type? = cam_type? | 4;
  }
  else {
    fVar6 = (-(movement->target_position).z / dVar4);
    local_78.x = local_78.x * fVar6;
    local_78.y = local_78.y * fVar6;
    local_78.z = local_78.z * fVar6;
    VectorAdd(&local_78,&movement->target_position);
  }
  FOVZoomHandler?\(dVar8,dVar4,in_f3,&local_84,1);
  FOVZoomHandler?\(dVar8,dVar4,in_f3,&local_84,2);
  local_84.x = local_84.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&local_84);
  FOVZoomHandler?\(dVar5,dVar4,in_f3,&local_84,1);
  FOVZoomHandler?\(dVar3,dVar4,in_f3,&local_84,2);
  if (-0.001 <= local_84.z) {
    cam_type? = cam_type? | 8;
  }
  else {
    fVar6 = -(movement->target_position).z / local_84.z;
    local_84.x = local_84.x * fVar6;
    local_84.y = local_84.y * fVar6;
    local_84.z = local_84.z * fVar6;
    VectorAdd(&local_84,&movement->target_position);
  }
  dVar5 = 0.0;
  dVar3 = dVar5;
  dVar4 = dVar5;
  dVar7 = dVar5;
  if (param_2 == 0) {
    if (!bVar2) {
      dVar8 = Stage_GetCameraLimitLeft();
      if (local_60.x < dVar8) {
        dVar8 = Stage_GetCameraLimitLeft();
        if (dVar7 < (dVar8 - local_60.x)) {
          uVar1 = 4;
          dVar7 = (dVar8 - local_60.x);
        }
      }
      dVar8 = Stage_GetCameraLimitTop();
      if (dVar8 < local_60.y) {
        dVar8 = Stage_GetCameraLimitTop();
        if ((dVar8 - local_60.y) < 0.0) {
          uVar1 = uVar1 | 1;
          dVar5 = (dVar8 - local_60.y);
        }
      }
    }
    if ((cam_type? & 2) == 0) {
      dVar8 = Stage_GetCameraLimitRight();
      if (dVar8 < local_6c.x) {
        dVar8 = Stage_GetCameraLimitRight();
        if ((dVar8 - local_6c.x) < dVar3) {
          uVar1 = uVar1 | 8;
          dVar3 = (dVar8 - local_6c.x);
        }
      }
      dVar8 = Stage_GetCameraLimitTop();
      if (dVar8 < local_6c.y) {
        dVar8 = Stage_GetCameraLimitTop();
        if ((dVar8 - local_6c.y) < dVar5) {
          uVar1 = uVar1 | 1;
          dVar5 = (dVar8 - local_6c.y);
        }
      }
    }
    if ((cam_type? & 4) == 0) {
      dVar8 = Stage_GetCameraLimitLeft();
      if (local_78.x < dVar8) {
        dVar8 = Stage_GetCameraLimitLeft();
        if (dVar7 < (dVar8 - local_78.x)) {
          uVar1 = uVar1 | 4;
          dVar7 = (dVar8 - local_78.x);
        }
      }
      dVar8 = Stage_GetCameraLimitBottom();
      if (local_78.y < dVar8) {
        dVar8 = Stage_GetCameraLimitBottom();
        if (dVar4 < (dVar8 - local_78.y)) {
          uVar1 = uVar1 | 2;
          dVar4 = (dVar8 - local_78.y);
        }
      }
    }
    if ((cam_type? & 8) == 0) {
      dVar8 = Stage_GetCameraLimitRight();
      if (dVar8 < local_84.x) {
        dVar8 = Stage_GetCameraLimitRight();
        if ((dVar8 - local_84.x) < dVar3) {
          uVar1 = uVar1 | 8;
          dVar3 = (dVar8 - local_84.x);
        }
      }
      dVar8 = Stage_GetCameraLimitBottom();
      if (local_84.y < dVar8) {
        dVar8 = Stage_GetCameraLimitBottom();
        if (dVar4 < (dVar8 - local_84.y)) {
          uVar1 = uVar1 | 2;
          dVar4 = (dVar8 - local_84.y);
        }
      }
    }
  }
  else {
    if (!bVar2) {
      dVar8 = Stage_GetLeftBlastzone();
      if (local_60.x < dVar8) {
        dVar8 = Stage_GetLeftBlastzone();
        if (dVar7 < (dVar8 - local_60.x)) {
          uVar1 = 4;
          dVar7 = (dVar8 - local_60.x);
        }
      }
      dVar8 = Stage_GetTopBlastzone();
      if (dVar8 < local_60.y) {
        dVar8 = Stage_GetTopBlastzone();
        if ((dVar8 - local_60.y) < 0.0) {
          uVar1 = uVar1 | 1;
          dVar5 = (dVar8 - local_60.y);
        }
      }
    }
    if ((cam_type? & 2) == 0) {
      dVar8 = Stage_GetRightBlastzone();
      if (dVar8 < local_6c.x) {
        dVar8 = Stage_GetRightBlastzone();
        if ((dVar8 - local_6c.x) < dVar3) {
          uVar1 = uVar1 | 8;
          dVar3 = (dVar8 - local_6c.x);
        }
      }
      dVar8 = Stage_GetTopBlastzone();
      if (dVar8 < local_6c.y) {
        dVar8 = Stage_GetTopBlastzone();
        if ((dVar8 - local_6c.y) < dVar5) {
          uVar1 = uVar1 | 1;
          dVar5 = (dVar8 - local_6c.y);
        }
      }
    }
    if ((cam_type? & 4) == 0) {
      dVar8 = Stage_GetLeftBlastzone();
      if (local_78.x < dVar8) {
        dVar8 = Stage_GetLeftBlastzone();
        if (dVar7 < (dVar8 - local_78.x)) {
          uVar1 = uVar1 | 4;
          dVar7 = (dVar8 - local_78.x);
        }
      }
      dVar8 = Stage_GetBottomBlastzone();
      if (local_78.y < dVar8) {
        dVar8 = Stage_GetBottomBlastzone();
        if (dVar4 < (dVar8 - local_78.y)) {
          uVar1 = uVar1 | 2;
          dVar4 = (dVar8 - local_78.y);
        }
      }
    }
    if ((cam_type? & 8) == 0) {
      dVar8 = Stage_GetRightBlastzone();
      if (dVar8 < local_84.x) {
        dVar8 = Stage_GetRightBlastzone();
        if ((dVar8 - local_84.x) < dVar3) {
          uVar1 = uVar1 | 8;
          dVar3 = (dVar8 - local_84.x);
        }
      }
      dVar8 = Stage_GetBottomBlastzone();
      if (local_84.y < dVar8) {
        dVar8 = Stage_GetBottomBlastzone();
        if (dVar4 < (dVar8 - local_84.y)) {
          uVar1 = uVar1 | 2;
          dVar4 = (dVar8 - local_84.y);
        }
      }
    }
  }
  if (uVar1 != 0) {
    local_90.x = 0.0;
    local_90.y = 0.0;
    if (((uVar1 & 4) == 0) || ((uVar1 & 8) == 0)) {
      if ((uVar1 & 4) == 0) {
        if ((uVar1 & 8) != 0) {
          local_90.x = dVar3;
        }
      }
      else {
        local_90.x = dVar7;
      }
    }
    else {
      local_90.x = (dVar7 + dVar3) * 0.5;
    }
    if (((uVar1 & 1) == 0) || ((uVar1 & 2) == 0)) {
      if ((uVar1 & 1) == 0) {
        if ((uVar1 & 2) != 0) {
          local_90.y = dVar4;
        }
      }
      else {
        local_90.y = dVar5;
      }
    }
    else {
      local_90.y = (dVar4 + dVar5) * 0.5;
    }
    local_90.x = local_90.x * 1.0;
    local_90.y = local_90.y * 1.0;
    local_90.z = 0.0;
    VectorAdd(&movement->target_position,&local_90);
    VectorAdd(&movement->target_interest,&local_90);
  }
  return;
}
