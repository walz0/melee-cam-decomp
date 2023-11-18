void zz_002a768_(CameraMovement *movement,int param_2) {
  byte cam_type?
  uint uVar1
  bool bVar2
  double dVar3
  double dVar8
  double dVar4
  double in_f3
  double dVar5
  double dVar7
  float fVar6
  Vec local_90
  Vec local_84
  Vec local_78
  Vec local_6c
  Vec local_60
  float zero
  float zero2
  float minus_1
  Vec interest_delta?
  
  uVar1 = 0
  zero = 0.0
  zero2 = 0.0

  // get half of angle in radians for tan 
  float rad2deg = deg2rad

  dVar7 = (movement->target_fov * rad2deg * 0.5)
  minus_1 = -1.0
  VectorSubtract(&movement->target_interest, &movement->target_position, &interest_delta?)
  VectorNormalize(&interest_delta?)
                    /* get vertical angle */
  fVar6 = atan2(interest_delta?.y,-interest_delta?.z)
  dVar5 = fVar6;
                    /* get horizontal angle */
  dVar4 = -interest_delta?.z
  fVar6 = atan2(-interest_delta?.x,-interest_delta?.z)
  dVar3 = fVar6

  local_60.x = zero
  local_60.y = zero2
  local_60.z = minus_1
                    /* horizontal angle, -interest_delta?.z,  */
  Vector_Rotate(dVar7,dVar4,in_f3,&local_60,1)
  Vector_Rotate(dVar7,dVar4,in_f3,&local_60,2)
}
