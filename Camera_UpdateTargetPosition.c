
void Camera_UpdateTargetPosition(CameraBounds *bounds,CameraMovement *movement)
{
    float fVar1;
    float fVar2;
    double dVar3;
    double dVar4;
    double dVar5;
    double dVar6;
    double dVar7;
    double dVar8;
    Vec cam_offset2;
    Vec cam_offset;
    
    Stage_GetCameraOffset2D(&cam_offset);
    float bounds_width = bounds->x_max - bounds->x_min;
    float bounds_height = bounds->y_max - bounds->y_min;

    float bounds_length = bounds_height;
    if (bounds_height < bounds_width) {
        bounds_length = bounds_width;
    }

    scale_unk = 0.0682f;
    if ((bounds_length <= 120.0f) && (scale_unk = 0.0f, bounds_length >= 60.0f)) {
        scale_unk = (0.0682f) * ((bounds_length - 60.0f) / (120.0f - 60.0f));
    }

    float height_multiplier = (((bounds->y_min - cam_offset.y) + (bounds->y_max - cam_offset.y)) * (0.5 - scale_unk) + cam_offset.y);
    float stage_vertical_rot = GetStageVerticalRotation();
                        /* 0.01745329 is degrees to radians */
    float vertical_rot_scaled = -(((height_multiplier + -30.0f) * stage_vertical_rot) * deg2rad);
    if (vertical_rot_scaled > (5.0f * deg2rad)) {
        vertical_rot_scaled = (5.0f * deg2rad);
    }
    if (vertical_rot_scaled < (-7.0f * deg2rad)) {
        vertical_rot_scaled = (-7.0f * deg2rad);
    }
    float stage_tilt = GetStageTilt();
    float total_tilt = (vertical_rot_scaled + stage_tilt);
    float fov_up = ((movement->fov * deg2rad) * 0.5 + total_tilt);

    if (fov_up >= 1.570796370506287) {
        __assert("camera.c",0x4fa,"fov_u<MTXDegToRad(90.0F)");
    }
    float fov_down = ((movement->fov * deg2rad) * 0.5 - total_tilt);
    if (fov_down >= 1.570796370506287) {
        __assert("camera.c",0x4fb,"fov_d<MTXDegToRad(90.0F)");
    }

    float tan_fov_up = tan(fov_up);
    float tan_fov_down = tan(fov_down);

    // get distance from camera to the top of the frustum (1/2 frustum height)
    float cam_pos_vert = ((bounds->y_max - bounds->y_min) / (tan_fov_up + tan_fov_down));

    Stage_GetCameraLimitBottom();
    Stage_GetCameraLimitTop();

    float tan_tilt = tan(total_tilt);
    float tilted_cam_pos_y = (cam_pos_vert * tan_tilt);
    (movement->target_interest).y = (tilted_cam_pos_y + -(cam_pos_vert * tan_fov_up - bounds->y_max));



    Stage_GetCameraOffset2D(&cam_offset2);
    float bounds_width = ((bounds->x_min + bounds->x_max));
    float stage_horziontal_rot = GetStageHorizontalRotation();

    float horizontal_rot_scaled = -(((bounds_width - cam_offset2.x) * stage_horziontal_rot) * deg2rad * 0.5f);

    if (horizontal_rot_scaled > (17.5f * deg2rad)) {
        horizontal_rot_scaled = (17.5f * deg2rad);
    }
    if (horizontal_rot_scaled < (-17.5f * deg2rad)) {
        horizontal_rot_scaled = (-17.5f * deg2rad);
    }

    float fov_right = ((movement->fov * deg2rad) * 0.5 - horizontal_rot_scaled);
    if (fov_right >= 1.570796370506287) {
        __assert("camera.c",0x508,"fov_r<MTXDegToRad(90.0F)");
    }

    float fov_left = ((movement->fov * deg2rad) * 0.5 + horizontal_rot_scaled);
    if (fov_left >= 1.570796370506287) {
        __assert("camera.c",0x509,"fov_l<MTXDegToRad(90.0F)");
    }

    float tan_fov_right = tan(fov_right);
    // correct fov for horizontal aspect
    tan_fov_right = (DefaultCameraCObjDesc.u.perspective.aspect * tan_fov_right);

    float tan_fov_left= tan(fov_left);
    tan_fov_left = (DefaultCameraCObjDesc.u.perspective.aspect * tan_fov_left);

    float cam_pos_horizontal = ((bounds->x_max - bounds->x_min) / (tan_fov_right + tan_fov_left));

    Stage_GetCameraLimitLeft();
    Stage_GetCameraLimitRight();

    tan_tilt = tan(horizontal_rot_scaled);
    float tilted_cam_pos_x = (DefaultCameraCObjDesc.u.perspective.aspect * (cam_pos_horizontal * tan_tilt));

    (movement->target_interest).x = (-(cam_pos_horizontal * tan_fov_right - bounds->x_max) - tilted_cam_pos_x);
    (movement->target_interest).z = 0.0;

    float depth = cam_pos_horizontal;
    if (cam_pos_horizontal < cam_pos_vert) {
        depth = cam_pos_vert;
    }
    float cam_dist_min = StageInfo_GetCamDistMin();
    if (depth < cam_dist_min) {
        depth = StageInfo_GetCamDistMin();
    }
    float cam_dist_max = StageInfo_GetCamDistMax();
    if (depth < cam_dist_max) {
        depth = StageInfo_GetCamDistMax();
    }
    (movement->target_position).x = ((movement->target_interest).x + tilted_cam_pos_x);
    (movement->target_position).y = ((movement->target_interest).y - tilted_cam_pos_y);
    (movement->target_position).z = ((movement->target_interest).z + depth);
    return;
}