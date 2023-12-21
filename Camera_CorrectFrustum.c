void Camera_CorrectFrustum(CameraMovement *movement, int param_2) {
  byte cam_type?;
  uint uVar1;
  bool is_neg;
  double dVar3;
  double dVar8;
  double dVar4;
  double in_f3;
  double dVar5;
  double dVar7;
  float fov_vertical;
  Vec cam_correction;
  Vec bottom_left;
  Vec bottom_right;
  Vec top_right;
  Vec top_left;
  float zero;
  float zero2;
  float minus_1;
  Vec interest_delta?;
  
  uVar1 = 0;
  zero = 0.0;
  zero2 = 0.0;
                    /* get half of angle in radians for tan [was dVar7]*/
  half_fov = (movement->target_fov * deg2rad * 0.5);
  minus_1 = -1.0;
  VectorSubtract(&movement->target_interest,&movement->target_position,&interest_delta?);
  VectorNormalize(&interest_delta?);
  
  // get the vertical angle
  fov_vertical = atan2(interest_delta?.y,-interest_delta?.z);
  dVar5 = fov_vertical;

  dVar4 = -interest_delta?.z;

  // get the horizontal angle
  fov_horizontal = atan2(-interest_delta?.x,-interest_delta?.z);
  dVar3 = fov_horizontal;

  // set up vectors
  bottom_left = {0, 0, -1};
  bottom_right = {0, 0, -1};
  top_right = {0, 0, -1};
  top_left = {0, 0, -1};

                    /* horizontal angle, -interest_delta?.z,  */
  Vector_Rotate(half_fov, dVar4, in_f3, &top_left, 1);
  Vector_Rotate(half_fov, dVar4, in_f3, &top_left, 2);
  top_left.x = top_left.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&top_left);
  Vector_Rotate(fov_vertical, dVar4, in_f3, &top_left, 1);
  Vector_Rotate(fov_horizontal, dVar4, in_f3, &top_left, 2);
  dVar4 = top_left.z;
  is_neg = -0.001 <= top_left.z;
  if (!is_neg) {
    fov_vertical = (-(movement->target_position).z / top_left.z);
    top_left.x = top_left.x * fov_vertical;
    top_left.y = top_left.y * fov_vertical;
    top_left.z = top_left.z * fov_vertical;
    VectorAdd(&top_left,&movement->target_position);
  }


  Vector_Rotate(dVar7,dVar4,in_f3,&top_right,1);
  dVar8 = -dVar7;
  Vector_Rotate(dVar8,dVar4,in_f3,&top_right,2);
  top_right.x = top_right.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&top_right);
  Vector_Rotate(dVar5,dVar4,in_f3,&top_right,1);
  Vector_Rotate(dVar3,dVar4,in_f3,&top_right,2);
  // dVar4 = top_right.z;
  if (-0.001 <= top_right.z) {
    cam_type? = BOTTOM_FIELD;
  }
  else {
    fov_vertical = (-(movement->target_position).z / top_right.z);
    top_right.x = top_right.x * fov_vertical;
    top_right.y = top_right.y * fov_vertical;
    top_right.z = top_right.z * fov_vertical;
    VectorAdd(&top_right,&movement->target_position);
    cam_type? = is_neg;
  }


  Vector_Rotate(dVar8,dVar4,in_f3,&bottom_right,1);
  Vector_Rotate(dVar7,dVar4,in_f3,&bottom_right,2);
  bottom_right.x = bottom_right.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&bottom_right);
  
  Vector_Rotate(dVar5,dVar4,in_f3,&bottom_right,1);
  Vector_Rotate(dVar3,dVar4,in_f3,&bottom_right,2);
  dVar4 = bottom_right.z;
  if (-0.001 <= bottom_right.z) {
    cam_type? = cam_type? | LEFT_FIELD;
  }
  else {
    fov_vertical = (-(movement->target_position).z / bottom_right.z);
    bottom_right.x = bottom_right.x * fov_vertical;
    bottom_right.y = bottom_right.y * fov_vertical;
    bottom_right.z = bottom_right.z * fov_vertical;
    VectorAdd(&bottom_right,&movement->target_position);
  }


  Vector_Rotate(dVar8,dVar4,in_f3,&bottom_left,1);
  Vector_Rotate(dVar8,dVar4,in_f3,&bottom_left,2);
  bottom_left.x = bottom_left.x * DefaultCameraCObjDesc.u.perspective.aspect;
  VectorNormalize(&bottom_left);
  Vector_Rotate(dVar5,dVar4,in_f3,&bottom_left,1);
  Vector_Rotate(dVar3,dVar4,in_f3,&bottom_left,2);
  if (-0.001 <= bottom_left.z) {
    cam_type? = cam_type? | RIGHT_FIELD;
  }
  else {
    fov_vertical = -(movement->target_position).z / bottom_left.z;
    bottom_left.x = bottom_left.x * fov_vertical;
    bottom_left.y = bottom_left.y * fov_vertical;
    bottom_left.z = bottom_left.z * fov_vertical;
    VectorAdd(&bottom_left,&movement->target_position);
  }


  top_dist = 0.0;
  right_dist = 0.0;
  bottom_dist = 0.0;
  left_dist = 0.0;
  if (param_2 == 0) {
    if (!is_neg) {
      float cam_limit_left = Stage_GetCameraLimitLeft();
      if (top_left.x < cam_limit_left) {
        cam_limit_left = Stage_GetCameraLimitLeft();
        if (0.0 < (cam_limit_left - top_left.x)) {
          uVar1 = LEFT_FIELD;
          left_dist = (cam_limit_left - top_left.x);
        }
      }
      cam_limit_top = Stage_GetCameraLimitTop();
      if (cam_limit_top < top_left.y) {
        cam_limit_top = Stage_GetCameraLimitTop();
        if ((cam_limit_top - top_left.y) < 0.0) {
          uVar1 = uVar1 | TOP_FIELD;
          top_dist = (cam_limit_top - top_left.y);
        }
      }
    }
    if ((cam_type? & BOTTOM_FIELD) == 0) {
      cam_limit_right = Stage_GetCameraLimitRight();
      if (cam_limit_right < top_right.x) {
        cam_limit_right = Stage_GetCameraLimitRight();
        if ((cam_limit_right - top_right.x) < 0.0) {
          uVar1 = uVar1 | RIGHT_FIELD;
          right_dist = (cam_limit_right - top_right.x);
        }
      }
      cam_limit_top = Stage_GetCameraLimitTop();
      if (cam_limit_top < top_right.y) {
        cam_limit_top = Stage_GetCameraLimitTop();
        if ((cam_limit_top - top_right.y) < 0.0) {
          uVar1 = uVar1 | TOP_FIELD;
          top_dist = (cam_limit_top - top_right.y);
        }
      }
    }
    if ((cam_type? & LEFT_FIELD) == 0) {
      cam_limit_left = Stage_GetCameraLimitLeft();
      if (bottom_right.x < cam_limit_left) {
        cam_limit_left = Stage_GetCameraLimitLeft();
        if ((cam_limit_left - bottom_right.x) > 0.0) {
          uVar1 = uVar1 | LEFT_FIELD;
          left_dist = (cam_limit_left - bottom_right.x);
        }
      }
      cam_limit_bottom = Stage_GetCameraLimitBottom();
      if (bottom_right.y < dVar8) {
        cam_limit_bottom = Stage_GetCameraLimitBottom();
        if ((cam_limit_bottom - bottom_right.y) > 0.0) {
          uVar1 = uVar1 | BOTTOM_FIELD;
          bottom_dist = (cam_limit_bottom - bottom_right.y);
        }
      }
    }
    if ((cam_type? & RIGHT_FIELD) == 0) {
      cam_limit_right = Stage_GetCameraLimitRight();
      if (cam_limit_right < bottom_left.x) {
        cam_limit_right = Stage_GetCameraLimitRight();
        if ((cam_limit_right - bottom_left.x) < 0.0) {
          uVar1 = uVar1 | RIGHT_FIELD;
          right_dist = (cam_limit_right - bottom_left.x);
        }
      }
      cam_limit_bottom = Stage_GetCameraLimitBottom();
      if (bottom_left.y < cam_limit_bottom) {
        cam_limit_bottom = Stage_GetCameraLimitBottom();
        if ((cam_limit_bottom - bottom_left.y) > 0.0) {
          uVar1 = uVar1 | BOTTOM_FIELD;
          bottom_dist = (cam_limit_bottom - bottom_left.y);
        }
      }
    }
  }
  else {
    if (!is_neg) {
      float leftBlastzone = Stage_GetLeftBlastzone();
      if (top_left.x < leftBlastzone) {
        leftBlastzone = Stage_GetLeftBlastzone();
        if ((leftBlastzone - top_left.x) > 0.0) {
          uVar1 = LEFT_FIELD;
          left_dist = (leftBlastzone - top_left.x);
        }
      }
      float topBlastzone = Stage_GetTopBlastzone();
      if (topBlastzone < top_left.y) {
        topBlastzone = Stage_GetTopBlastzone();
        if ((topBlastzone - top_left.y) < 0.0) {
          uVar1 = uVar1 | TOP_FIELD;
          top_dist = (dVar8 - top_left.y);
        }
      }
    }
    if ((cam_type? & BOTTOM_FIELD) == 0) {
      rightBlastzone = Stage_GetRightBlastzone();
      if (rightBlastzone < top_right.x) {
        rightBlastzone = Stage_GetRightBlastzone();
        if ((rightBlastzone - top_right.x) < 0.0) {
          uVar1 = uVar1 | RIGHT_FIELD;
          right_dist = (rightBlastzone - top_right.x);
        }
      }
      topBlastzone = Stage_GetTopBlastzone();
      if (topBlastzone < top_right.y) {
        topBlastzone = Stage_GetTopBlastzone();
        if ((topBlastzone - top_right.y) < 0.0) {
          uVar1 = uVar1 | TOP_FIELD;
          top_dist = (topBlastzone - top_right.y);
        }
      }
    }
    if ((cam_type? & LEFT_FIELD) == 0) {
      leftBlastzone = Stage_GetLeftBlastzone();
      if (bottom_right.x < dVar8) {
        leftBlastzone = Stage_GetLeftBlastzone();
        if ((leftBlastzone - bottom_right.x) > 0.0) {
          uVar1 = uVar1 | LEFT_FIELD;
          left_dist = (leftBlastzone - bottom_right.x);
        }
      }
      bottomBlastzone = Stage_GetBottomBlastzone();
      if (bottom_right.y < bottomBlastzone) {
        bottomBlastzone = Stage_GetBottomBlastzone();
        if ((bottomBlastzone - bottom_right.y) > 0.0) {
          uVar1 = uVar1 | BOTTOM_FIELD;
          bottom_dist = (bottomBlastzone - bottom_right.y);
        }
      }
    }
    if ((cam_type? & RIGHT_FIELD) == 0) {
      rightBlastzone = Stage_GetRightBlastzone();
      if (rightBlastzone < bottom_left.x) {
        rightBlastzone = Stage_GetRightBlastzone();
        if ((rightBlastzone - bottom_left.x) < 0.0) {
          uVar1 = uVar1 | RIGHT_FIELD;
          right_dist = (rightBlastzone - bottom_left.x);
        }
      }
      bottomBlastzone = Stage_GetBottomBlastzone();
      if (bottom_left.y < bottomBlastzone) {
        bottomBlastzone = Stage_GetBottomBlastzone();
        if ((bottomBlastzone - bottom_left.y) > 0.0) {
          uVar1 = uVar1 | BOTTOM_FIELD;
          bottom_dist = (bottomBlastzone - bottom_left.y);
        }
      }
    }
  }
  if (uVar1 != 0) {
    cam_correction.x = 0.0;
    cam_correction.y = 0.0;
    if (((uVar1 & LEFT_FIELD) == 0) || ((uVar1 & RIGHT_FIELD) == 0)) {
      if ((uVar1 & LEFT_FIELD) == 0) {
        if ((uVar1 & RIGHT_FIELD) != 0) {
          cam_correction.x = right_dist;
        }
      }
      else {
        cam_correction.x = left_dist;
      }
    }
    else {
      cam_correction.x = (left_dist + right_dist) * 0.5;
    }
    if (((uVar1 & TOP_FIELD) == 0) || ((uVar1 & BOTTOM_FIELD) == 0)) {
      if ((uVar1 & TOP_FIELD) == 0) {
        if ((uVar1 & BOTTOM_FIELD) != 0) {
          cam_correction.y = bottom_dist;
        }
      }
      else {
        cam_correction.y = top_dist;
      }
    }
    else {
      cam_correction.y = (bottom_dist + top_dist) * 0.5;
    }
    cam_correction.x = cam_correction.x * 1.0;
    cam_correction.y = cam_correction.y * 1.0;
    cam_correction.z = 0.0;
    VectorAdd(&movement->target_position,&cam_correction);
    VectorAdd(&movement->target_interest,&cam_correction);
  }
  return;
}
