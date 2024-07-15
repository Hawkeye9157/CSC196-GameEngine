#include "Model.h"
#include "Transform.h"

void Model::Draw(Renderer& renderer,Transform& transform) {

	if (m_points.empty()) return;

	for (int i = 0; i < m_points.size() - 1; i++) {
		Vector2 p1 = m_points[i].Rotate(transform.rotation) * transform.scale + transform.position;
		Vector2 p2 = m_points[i + 1].Rotate(transform.rotation) * transform.scale + transform.position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
