uint CmSubject_IsInCameraBounds(Vec *subject_pos,uint bound_field) {
    uint bounds;
    
    bounds = 0;
    GetCameraBottomOverride(&cam_bottom_override,&fStack_40);
    cam_bottom_override = cam_bottom_override + 1.0;

    limit_left = Stage_GetCameraLimitLeft();
    limit_right = Stage_GetCameraLimitRight();
    limit_top = Stage_GetCameraLimitTop();
    limit_bottom = Stage_GetCameraLimitBottom();

    dVar1 = cam_bottom_override;
    if (dVar1 < limit_bottom) {
        dVar1 = Stage_GetCameraLimitBottom();
    }
    if (subject_pos->x < limit_left) {
        bounds = 0b00000100;
    }
    if (subject_pos->x > limit_right) {
        bounds = bounds | 0b00001000;
    }
    if (subject_pos->y > limit_top) {
        bounds = bounds | 0b00000001;
    }
    if (subject_pos->y < limit_bottom) {
        bounds = bounds | 0b00000010;
    }
    return bounds;
}