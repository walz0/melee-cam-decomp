void CmSubject_UpdateBoundsAll(void)
{
    float fVar1;
    bool enabled;
    CmSubject *subject;
    double dVar2;
    double dVar3;
    double dVar4;
    double dVar5;
    double dVar6;

    for (subject = UsedCmSubjectPoolHead; subject != (CmSubject *)0x0; subject = subject->prev) {
        enabled = CmSubject_IsEnabled(subject);
        if (enabled) {
            float bounds_left = (subject->bounds).left;
            float default_bounds_left = (subject->default_bounds).left;
            float bounds_delta = (bounds_left - default_bounds_left);
            if (bounds_delta != 0.0) {
                if (bounds_delta <= 0.5) {
                    if (bounds_delta >= -0.5) {
                        (subject->default_bounds).left = bounds_left;
                    }
                    else {
                        (subject->default_bounds).left = (default_bounds_left - 0.5f);
                    }
                }
                else {
                    (subject->default_bounds).left = (default_bounds_left + 0.5);
                }
            }

            float bounds_right = (subject->bounds).right;
            float default_bounds_right = (subject->default_bounds).right;
            float bounds_delta = (bounds_right - default_bounds_right);
            if (bounds_delta != 0.0) {
                if (bounds_delta <= 0.5) {
                    if (bounds_delta >= -0.5) {
                        (subject->default_bounds).right = bounds_right;
                    }
                    else {
                        (subject->default_bounds).right = (default_bounds_right - 0.5);
                    }
                }
                else {
                    (subject->default_bounds).right = (default_bounds_right + 0.5);
                }
            }

            float bounds_top = (subject->bounds).top;
            float default_bounds_top = (subject->default_bounds).top;
            float bounds_delta = (bounds_top - default_bounds_top);
            if (bounds_delta != 0.0) {
                if (bounds_delta <= 0.5) {
                    if (bounds_delta >= -0.5) {
                        (subject->default_bounds).top = bounds_top;
                    }
                    else {
                        (subject->default_bounds).top = (default_bounds_top - 0.5);
                    }
                }
                else {
                    (subject->default_bounds).top = (default_bounds_top + 0.5);
                }
            }

            float bounds_bottom = (subject->bounds).bottom;
            float default_bounds_bottom = (subject->default_bounds).bottom;
            float bounds_delta = (bounds_bottom - default_bounds_bottom);
            if (bounds_delta != 0.0) {
                if (bounds_delta <= 0.5) {
                    if (bounds_delta >= -0.5) {
                        (subject->default_bounds).bottom = bounds_bottom;
                    }
                    else {
                        (subject->default_bounds).bottom = (default_bounds_bottom - 0.5);
                    }
                }
                else {
                    (subject->default_bounds).bottom = (default_bounds_bottom + 0.5);
                }
            }

            float size = subject->size;
            float size_delta = (subject->default_size - size);
            if (size_delta != 0.0) {
                if (size_delta <= 0.5) {
                    if (size_delta >= -0.5) {
                        subject->size = subject->default_size;
                    }
                    else {
                        subject->size = (size - 0.5);
                    }
                }
                else {
                    subject->size = (size + 0.5);
                }
            }
        }
    }
    return;
}