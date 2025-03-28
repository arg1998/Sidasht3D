#pragma once

#include "S3D/Definitions.hpp"

namespace s3d {
namespace Editor {

    b8 IsEditorEnabled();
    void EnableEditor();
    void DisableEditor();

    void StartClientWithEditor();

    void SetEditorThemeToDefault(f32 fotnSize = 18.0f);


}  // namespace Editor
}  // namespace s3d