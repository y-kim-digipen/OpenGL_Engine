//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Camera {
public:
    Camera(void);
    Camera(const glm::vec3& E, const glm::vec3& look, const glm::vec3& vp,
           float fov, float aspect, float near, float far);
    [[nodiscard]] glm::vec3 Eye(void) const;
    [[nodiscard]] glm::vec3 Right(void) const;
    [[nodiscard]] glm::vec3 Up(void) const;
    [[nodiscard]] glm::vec3 Back(void) const;
    [[nodiscard]] glm::vec3 ViewportGeometry(void) const;
    [[nodiscard]] float NearDistance(void) const;
    [[nodiscard]] float FarDistance(void) const;

    Camera& Zoom(float factor);
    Camera& Forward(float distance_increment);
    void SetPosition(glm::vec3 pos);
    Camera& Yaw(float angle);
    Camera& Pitch(float angle);
    Camera& Roll(float angle);

    glm::mat4 GetLookAtMatrix() const;
    glm::mat4 GetPerspectiveMatrix() const;
    glm::mat4 GetOrthogonalMatrix() const;

    glm::vec3 GetEyePosition() const;

//    virtual void SetupBuffer(Demo*);
    virtual void Update();
//    virtual void Unload() {}
private:
protected:
    glm::vec3 eye;
    glm::vec3 back, right, up;
    float width, height, near, far, distance;
    float fov;
    GLuint m_vaoid = static_cast<GLuint>(-1);
    GLuint m_ebo_hdl = static_cast<GLuint>(-1);
//    std::unique_ptr<Shader> mCameraFrustrumShader = std::make_unique<Shader>();
};



#endif //ENGINE_CAMERA_H
